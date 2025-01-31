// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TorcherGraphNode.h"
#include "TorcherTypes.h"
#include "Layers/TorcherLayerBaseOptions.h"
#include "TorcherLayerNode.generated.h"

/**
 * 
 */
UCLASS()
class TORCHEREDITOR_API UTorcherLayerNode : public UTorcherGraphNode
{
	GENERATED_BODY()

public:
	// Constructor
	UTorcherLayerNode();

	// UEdGraphNode
	virtual FLinearColor GetNodeTitleColor() const override { return FColor::Blue; }

	/*
	 * Set the LayerNodeOptions for this node. Accepts any struct which is
	 * derived from FTorcherLayerBaseOptions.
	 * @param InOptions The Base Layer Options Struct
	 * 
	 */
	template<typename TOptions = FTorcherLayerBaseOptions>
	void SetLayerNodeOptions(const TOptions InOptions)
	{
		static_assert(std::is_base_of_v<FTorcherLayerBaseOptions, TOptions>,
			"TOptions must derive from FTorcherLayerBaseOptions");

		NodeType = InOptions.LayerType;
		LayerName = InOptions.LayerName;
		LayerDeviceType = InOptions.LayerDeviceType;
		Gain = InOptions.Gain;
		Confidence = InOptions.Confidence;

		OnSetOptions(InOptions);
	}

	/*
	 * Get the LayerNodeOptions of this node. Returns a struct derived from
	 * FTorcherLayerBaseOptions.
	 * @return struct of type FTorcherLayerBaseOptions
	 * 
	 */
	template<typename TOptions = FTorcherLayerBaseOptions>
	TOptions GetLayerNodeOptions() const
	{
		static_assert(std::is_base_of_v<FTorcherLayerBaseOptions, TOptions>,
			"TOptions must derive from FTorcherLayerBaseOptions");

		TOptions Options;

		Options.LayerType = NodeType;
		Options.LayerName = LayerName;
		Options.LayerDeviceType = LayerDeviceType;
		Options.Gain = Gain;
		Options.Confidence = Confidence;

		OnGetOptions(Options);

		return Options;
	}

public:
	/*
	 * Creates a customized pin on our node.
	 * @param Direction Is the pin an input or an output?
	 * @param Name Name of the pin
	 */
	virtual UEdGraphPin* CreateCustomPin(EEdGraphPinDirection Direction, FName Name) override;

	/*
	 * Virtual function which can be overridden in derived classes to
	 * set additional fields in their Node Properties
	 */
	virtual void OnSetOptions(const FTorcherLayerBaseOptions& InOptions) {}

	/*
	 * Virtual function which can be overridden in derived classes to
	 * get additional LayerNodeOptions from the Node Properties
	 */
	virtual void OnGetOptions(FTorcherLayerBaseOptions& OutOptions) const {}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Layer Attributes")
	ETorcherNodeType NodeType = ETorcherNodeType::Default;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Base Layer Attributes")
	ETorcherTensorDeviceType LayerDeviceType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Base Layer Attributes")
	float Gain;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Base Layer Attributes")
	float Confidence;
};
