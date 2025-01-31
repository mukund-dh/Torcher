// Fill out your copyright notice in the Description page of Project Settings.


#include "TorcherGraph/TorcherModelGraph.h"
#include "TorcherGraph/TorcherModelGraphAppMode.h"
#include "Models/TorcherModelBase.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Nodes/TorcherLayerNode.h"
#include "TorcherGraph/TorcherGraphSchema.h"
#include "TorcherGraph/TorcherRuntimeGraph.h"
#include "Nodes/Default/TorcherNNStartNode.h"

void TorcherModelGraph::RegisterTabSpawners(const TSharedRef<FTabManager>& tabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(tabManager);
}

void TorcherModelGraph::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost,
	UObject* InObject)
{
	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(InObject);

	_workingAsset = Cast<UTorcherModelBase>(InObject);
	_workingAsset->SetPreSaveListener(
		[this] ()
		{
			OnWorkingAssetPreSave();
		}
	);

	_workingGraph = FBlueprintEditorUtils::CreateNewGraph(
		_workingAsset,
		NAME_None,
		UEdGraph::StaticClass(),
		UTorcherGraphSchema::StaticClass()
	);

	InitAssetEditor(
		Mode,
		InitToolkitHost,
		TEXT("TorcherGraphApp"),
		FTabManager::FLayout::NullLayout,
		true,
		true,
		ObjectsToEdit
	);

	AddApplicationMode(TEXT("TorcherModelGraphAppMode"), MakeShareable(new TorcherModelGraphAppMode(SharedThis(this))));
	SetCurrentMode(TEXT("TorcherModelGraphAppMode"));

	UpdateGraphFromWorkingAsset();
}


UTorcherGraphNode* TorcherModelGraph::GetSelectedNode(const FGraphPanelSelectionSet& Selection)
{
	for (UObject* obj : Selection)
	{
		UTorcherGraphNode* node = Cast<UTorcherGraphNode>(obj);
		if (node)
		{
			return node;
		}
	}
	return nullptr;
}

void TorcherModelGraph::SetSelectedNodeDetailView(TSharedPtr<class IDetailsView> DetailsView)
{
	_selectedNodeDetailsView = DetailsView;
	_selectedNodeDetailsView->OnFinishedChangingProperties().AddRaw(this, &TorcherModelGraph::OnNodeDetailsViewPropertyUpdated);
}

void TorcherModelGraph::OnGraphSelectionChanged(const FGraphPanelSelectionSet& Selection)
{
	UTorcherGraphNode* SelectedNode = GetSelectedNode(Selection);
	_selectedNodeDetailsView->SetObject(SelectedNode);
}

void TorcherModelGraph::OnClose()
{
	UpdateWorkingAssetFromGraph();
	_workingAsset->SetPreSaveListener(nullptr);
	FAssetEditorToolkit::OnClose();
}

void TorcherModelGraph::OnNodeDetailsViewPropertyUpdated(const FPropertyChangedEvent& Event)
{
	if (_workingGraphUi != nullptr)
	{
		UTorcherGraphNode* TorcherNode = GetSelectedNode(_workingGraphUi->GetSelectedNodes());
		if (TorcherNode)
		{
			// Set the layer node options here.
			
		}
		_workingGraphUi->NotifyGraphChanged();
	}
}

void TorcherModelGraph::OnWorkingAssetPreSave()
{
	// Update our asset from the graph just before saving it
	UpdateWorkingAssetFromGraph();
}

void TorcherModelGraph::UpdateWorkingAssetFromGraph()
{
	if (_workingAsset == nullptr || _workingGraph == nullptr)
		return;

	UTorcherRuntimeGraph* RuntimeGraph = NewObject<UTorcherRuntimeGraph>(_workingAsset);
	_workingAsset->ModelGraph = RuntimeGraph;

	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UTorcherRuntimePin*> IdToPinMap;

	for (UEdGraphNode* UiNode : _workingGraph->Nodes)
	{		
		UTorcherRuntimeNode* RuntimeNode = NewObject<UTorcherRuntimeNode>(RuntimeGraph);
		RuntimeNode->Location = FVector2D(UiNode->NodePosX, UiNode->NodePosY);

		for (UEdGraphPin* Pin : UiNode->Pins)
		{
			UTorcherRuntimePin* RuntimePin = NewObject<UTorcherRuntimePin>(RuntimeNode);
			RuntimePin->PinName = Pin->PinName;
			RuntimePin->PinId = Pin->PinId;

			if (Pin->HasAnyConnections() && Pin->Direction == EGPD_Output)
			{
				std::pair<FGuid, FGuid> Connection = std::make_pair(Pin->PinId, Pin->LinkedTo[0]->PinId);
				Connections.Add(Connection);
			}

			IdToPinMap.Add(Pin->PinId, RuntimePin);
			if (Pin->Direction == EGPD_Input)
			{
				RuntimeNode->InputPin = RuntimePin;
			}
			else
			{
				RuntimeNode->OutputPins.Add(RuntimePin);
			}
		}

		if (UiNode->IsA(UTorcherLayerNode::StaticClass()))
		{
			UTorcherLayerNode* UiGraphNode = Cast<UTorcherLayerNode>(UiNode);
			FTorcherLayerBaseOptions BaseOpts =	UiGraphNode->GetLayerNodeOptions();
			RuntimeNode->SetLayerOptions(BaseOpts);
		} else if (UiNode->IsA(UTorcherNNStartNode::StaticClass()))
		{
			RuntimeNode->NodeType = ETorcherNodeType::Input;
		}
		
		RuntimeGraph->GraphNodes.Add(RuntimeNode);
	}

	for (std::pair<FGuid, FGuid> connection : Connections)
	{
		UTorcherRuntimePin* A = IdToPinMap[connection.first];
		UTorcherRuntimePin* B = IdToPinMap[connection.second];
		A->Connection = B;
	}
}

void TorcherModelGraph::UpdateGraphFromWorkingAsset()
{
	if (_workingAsset->ModelGraph == nullptr)
	{
		_workingGraph->GetSchema()->CreateDefaultNodesForGraph(*_workingGraph);
		return;
	}
	
	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UEdGraphPin*> IdToPinMap;

	for (UTorcherRuntimeNode* RuntimeNode : _workingAsset->ModelGraph->GraphNodes)
	{
		// Get the layer options here.
		FTorcherLayerBaseOptions Options = RuntimeNode->GetLayerOptions();
		
		UTorcherGraphNode* NewNode = nullptr;
		switch (RuntimeNode->NodeType)
		{
			case ETorcherNodeType::Default:
				{
					UTorcherLayerNode* DefNode = NewObject<UTorcherLayerNode>(_workingGraph);
					NewNode = DefNode;
					break;
				}
			case ETorcherNodeType::Linear:
				{
					UTorcherLayerNode* LinearNode = NewObject<UTorcherLayerNode>(_workingGraph);
					LinearNode->SetLayerNodeOptions(Options);
					NewNode = LinearNode;
					break;
				}
			case ETorcherNodeType::BatchNorm1D:
				{
					UTorcherLayerNode* BN1D = NewObject<UTorcherLayerNode>(_workingGraph);
					BN1D->SetLayerNodeOptions(Options);
					NewNode = BN1D;
					break;
				}
			case ETorcherNodeType::TanH:
				{
					UTorcherLayerNode* TanH = NewObject<UTorcherLayerNode>(_workingGraph);
					TanH->SetLayerNodeOptions(Options);
					NewNode = TanH;
					break;
				}
			case ETorcherNodeType::Input:
				{
					NewNode = NewObject<UTorcherNNStartNode>(_workingGraph);
					break;
				}
			case ETorcherNodeType::Output:
				{
					NewNode = nullptr;
					break;
				}
		}
		
		NewNode->CreateNewGuid();

		NewNode->NodePosX = RuntimeNode->Location.X;
		NewNode->NodePosY = RuntimeNode->Location.Y;

		if (RuntimeNode->InputPin != nullptr)
		{
			UTorcherRuntimePin* Pin = RuntimeNode->InputPin;
			UEdGraphPin* UiPin = NewNode->CreateCustomPin(EGPD_Input, Pin->PinName);
			UiPin->PinId = Pin->PinId;

			if (Pin->Connection != nullptr)
			{
				Connections.Add(std::make_pair(Pin->PinId, Pin->Connection->PinId));
			}

			IdToPinMap.Add(Pin->PinId, UiPin);
		}

		for (UTorcherRuntimePin* Pin : RuntimeNode->OutputPins)
		{
			UEdGraphPin* UiPin = NewNode->CreateCustomPin(EGPD_Output, Pin->PinName);
			UiPin->PinId = Pin->PinId;

			if (Pin->Connection != nullptr)
			{
				Connections.Add(std::make_pair(Pin->PinId, Pin->Connection->PinId));
			}

			IdToPinMap.Add(Pin->PinId, UiPin);
		}

		_workingGraph->AddNode(NewNode, true, true);
	}

	for (std::pair<FGuid, FGuid> connection : Connections)
	{
		UEdGraphPin* A = IdToPinMap[connection.first];
		UEdGraphPin* B = IdToPinMap[connection.second];
		A->LinkedTo.Add(B);
		B->LinkedTo.Add(A);
	}
}
