// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Models/TorcherModelBase.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

/**
 * 
 */
class TorcherModelGraph : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook
{
public:
	// Tells parent class what tabs to spawn
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& tabManager) override;
	
	// Initialize
	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UObject* InObject);

private:
	UTorcherModelBase* _workingAsset = nullptr;
	
	class UEdGraph* _workingGraph = nullptr;

	FDelegateHandle _graphChangeDelegateHandle;
	
public: // FAssetEditorToolkit interface
	virtual FName GetToolkitFName() const override { return FName(TEXT("TorcherGraphApp")); }
	virtual FText GetBaseToolkitName() const override { return FText::FromString("Torcher Graph App"); }
	virtual FString GetWorldCentricTabPrefix() const override { return TEXT("TorcherGraphApp"); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f); }
	virtual FString GetDocumentationLink() const override { return TEXT(""); }

	UTorcherModelBase* GetWorkingAsset() { return _workingAsset; }
	class UEdGraph* GetWorkingGraph() { return _workingGraph; }
	
	virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override { }
	virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override { }

	virtual void OnClose() override;
	void OnGraphChanged(const FEdGraphEditAction& EditAction);

protected:

	void UpdateWorkingAssetFromGraph();
	void UpdateGraphFromWorkingAsset();
};
