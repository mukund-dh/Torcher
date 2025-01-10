// Fill out your copyright notice in the Description page of Project Settings.


#include "TorcherGraph/TorcherModelGraph.h"
#include "TorcherGraph/TorcherModelGraphAppMode.h"
#include "Models/TorcherModelBase.h"


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
}
