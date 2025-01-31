// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "TorcherGraphNode.generated.h"

// Forward declare the TorcherTensorDeviceType
enum class ETorcherTensorDeviceType : uint8;

/**
 * 
 */
UCLASS()
class TORCHEREDITOR_API UTorcherGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	// Constructor
	UTorcherGraphNode();
	
	// UEdGraphNode
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override { return FColor::Emerald; }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

	/*
	 * Creates a customized pin on our node.
	 * @param Direction Is the pin an input or an output?
	 * @param Name Name of the pin
	 */
	virtual UEdGraphPin* CreateCustomPin(EEdGraphPinDirection Direction, FName Name) { return nullptr; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Base Attributes")
	FString LayerName;
};
