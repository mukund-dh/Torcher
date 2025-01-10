// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 * 
 */
class FTorcherModelAssetTypeActions : public FAssetTypeActions_Base
{
public:
	FTorcherModelAssetTypeActions(EAssetTypeCategories::Type category);
	virtual UClass* GetSupportedClass() const override;
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;
	
private:
	EAssetTypeCategories::Type _assetCategory;
};
