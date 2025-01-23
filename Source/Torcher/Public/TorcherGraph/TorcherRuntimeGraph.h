// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NameTypes.h"
#include "Layers/TorcherLayerBaseOptions.h"
#include "TorcherRuntimeGraph.generated.h"

UENUM()
enum class ETorcherNodeType
{
	// The Start Node
	Input,

	Default, // The default node type which gets created when the graph is initialized

	// Linear Layer
	Linear,

	// Normalization Layers
	BatchNorm1D,

	// Activation Layers
	TanH,

	// The End Node
	Output
};

/**
 * Holds data for runtime pin generation
 */
UCLASS()
class TORCHER_API UTorcherRuntimePin : public UObject
{
    GENERATED_BODY()
public:
	/*
	 * The Pin Name
	 */
	UPROPERTY()
	FName PinName;

	/*
	 * The Pin Guid
	 */
	UPROPERTY()
	FGuid PinId;

	/*
	 * The pin we are connected to
	 */
	UPROPERTY()
	UTorcherRuntimePin* Connection = nullptr;
};

/**
 * Holds data for runtime node generation
 */
UCLASS()
class TORCHER_API UTorcherRuntimeNode : public UObject
{
    GENERATED_BODY()

public:
	/*
	 * The Node Type of this node.
	 */
	UPROPERTY()
	ETorcherNodeType NodeType = ETorcherNodeType::Default;

	/*
	 * The Input Pin
	 */
	UPROPERTY()
	UTorcherRuntimePin* InputPin;

	/*
	 * The Output Pins of this node
	 */
	UPROPERTY()
	TArray<UTorcherRuntimePin*> OutputPins;

	/*
	 * Where is this node located on the graph?
	 */
	UPROPERTY()
	FVector2D Location;

	/*
	 * The Layer Node Name
	 */
	UPROPERTY()
	FString LayerName;

	/*
	 * The Layer Device Type
	 */
	UPROPERTY()
	ETorcherTensorDeviceType LayerDeviceType;

	/*
	 * The Gain for this layer
	 */
	UPROPERTY()
	float Gain = 1.0f;

	/*
	 * The Confidence of this layer 
	 */
	UPROPERTY()
	float Confidence = 1.0f;

	/*
	 * Set the layer options for this layer. Can take in any struct which derives from
	 * FTorcherLayerBaseOptions
	 * @param Options The options struct to use to set the options from
	 * 
	 */
	template<typename TOptions = FTorcherLayerBaseOptions>
	void SetLayerOptions(const TOptions& Options)
	{
		static_assert(std::is_base_of<FTorcherLayerBaseOptions, TOptions>::value,
			"TOptions must derive from FTorcherLayerBaseOptions");

		LayerName = Options.LayerName;
		LayerDeviceType = Options.LayerDeviceType;
		Gain = Options.Gain;
		Confidence = Options.Confidence;

		OnSetOptions(Options);
	}

	/*
	 * Get the layer options for this layer. Can return any struct which derives from
	 * FTorcherLayerBaseOptions
	 * @return The options struct to use to set the options from
	 * 
	 */
	template<typename TOptions = FTorcherLayerBaseOptions>
	TOptions GetLayerOptions()
	{
		static_assert(std::is_base_of<FTorcherLayerBaseOptions, TOptions>::value,
			"TOptions must derive from FTorcherLayerBaseOptions");

		TOptions Options;

		Options.LayerName = LayerName;
		Options.LayerDeviceType = LayerDeviceType;
		Options.Gain = Gain;
		Options.Confidence = Confidence;

		OnGetOptions(Options);

		return Options;
	}

public:
	/*
	 * Virtual function call which can be overridden in the derived classes to set
	 * any extra properties that class may possess.
	 * @param InOptions The Incoming Options struct.
	 * 
	 */
	virtual void OnSetOptions(const FTorcherLayerBaseOptions& InOptions) {}

	/*
	 * Virtual function call which can be overridden in the derived classes to get
	 * any extra properties that class may possess.
	 * @param OutOptions The Options struct you want to populate here.
	 * 
	 */
	virtual void OnGetOptions(FTorcherLayerBaseOptions& OutOptions) const {}
};

/**
 * Holds data for runtime graph generation
 */
UCLASS()
class TORCHER_API UTorcherRuntimeGraph : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<UTorcherRuntimeNode*> GraphNodes;
};
