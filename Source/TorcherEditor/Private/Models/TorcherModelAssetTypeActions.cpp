// Fill out your copyright notice in the Description page of Project Settings.


#include "Models/TorcherModelAssetTypeActions.h"
#include "Models/TorcherModelBase.h"
#include "TorcherGraph/TorcherModelGraph.h"

FTorcherModelAssetTypeActions::FTorcherModelAssetTypeActions(EAssetTypeCategories::Type category)
{
	_assetCategory = category;
}

UClass* FTorcherModelAssetTypeActions::GetSupportedClass() const
{
	return UTorcherModelBase::StaticClass();
}

FText FTorcherModelAssetTypeActions::GetName() const
{
	return INVTEXT("Torcher Model");
}

FColor FTorcherModelAssetTypeActions::GetTypeColor() const
{
	return FColor::Cyan;
}

uint32 FTorcherModelAssetTypeActions::GetCategories()
{
	return _assetCategory;
}

void FTorcherModelAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (UObject* _object : InObjects)
	{
		UTorcherModelBase* TorchModel = Cast<UTorcherModelBase>(_object);
		if (TorchModel != nullptr)
		{
			TSharedRef<TorcherModelGraph> editor(new TorcherModelGraph);
			editor->InitEditor(Mode, EditWithinLevelEditor, TorchModel);
		}
	}
}
