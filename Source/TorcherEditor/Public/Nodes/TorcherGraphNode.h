// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "Layers/TorcherLayerBaseOptions.h"
#include "TorcherGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class TORCHEREDITOR_API UTorcherGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	// UEdGraphNode
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override { return FColor::Emerald; }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

public:
	// Our Functions
	UEdGraphPin* CreateCustomPin(EEdGraphPinDirection Direction, FName name);
	
	void SetLayerNodeOptions(const FTorcherLayerBaseOptions& Options) { LayerNodeOptions = Options; }

	FTorcherLayerBaseOptions GetLayerNodeOptions() const { return LayerNodeOptions; }

protected:
	
	UPROPERTY(EditAnywhere)
	FTorcherLayerBaseOptions LayerNodeOptions = FTorcherLayerBaseOptions();
};
