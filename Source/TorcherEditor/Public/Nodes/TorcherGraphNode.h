// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "Layers/TorcherLayerBaseOptions.h"
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

public:
	/*
	 * Creates a customized pin on our node.
	 * @param Direction Is the pin an input or an output?
	 * @param Name Name of the pin
	 */
	virtual UEdGraphPin* CreateCustomPin(EEdGraphPinDirection Direction, FName Name);

	/*
	 * Virtual function which can be overridden in derived classes to
	 * set additional fields in their Node Properties
	 */
	virtual void OnOptionsSet(const FTorcherLayerBaseOptions& InOptions) {}

	/*
	 * Virtual function which can be overridden in derived classes to
	 * get additional LayerNodeOptions from the Node Properties
	 */
	virtual void OnGetOptions(FTorcherLayerBaseOptions& OutOptions) const {}
	
	/*
	 * Set the LayerNodeOptions from the given Options struct
	 * @param InOptions The Base Layer Options Struct
	 */
	template<typename TOptions = FTorcherLayerBaseOptions>
	void SetLayerNodeOptions(const TOptions InOptions)
	{
		static_assert(std::is_base_of<FTorcherLayerBaseOptions, TOptions>::value,
			"TOptions must derive from FTorcherLayerBaseOptions");

		LayerName = InOptions.LayerName;
		LayerDeviceType = InOptions.LayerDeviceType;

		OnOptionsSet(InOptions);
	}

	/*
	 * Get the LayerNode options as a struct
	 *
	 * @return struct of type FTorcherLayerBaseOptions
	 */
	template<typename TOptions = FTorcherLayerBaseOptions>
	TOptions GetLayerNodeOptions() const
	{
		static_assert(std::is_base_of<FTorcherLayerBaseOptions, TOptions>::value,
			"TOptions must derive from FTorcherLayerBaseOptions");

		TOptions Options;

		Options.LayerName = LayerName;
		Options.LayerDeviceType = LayerDeviceType;

		OnGetOptions(Options);

		return Options;
	}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Base Attributes")
	FString LayerName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Base Attributes")
	ETorcherTensorDeviceType LayerDeviceType;
};
