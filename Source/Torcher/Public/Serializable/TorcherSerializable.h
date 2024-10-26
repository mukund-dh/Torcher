// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TorcherSerializable.generated.h"


#define LOCTEXT_NAMESPACE "ITorcherSerializable"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName="Torcher Serializable")
class UTorcherSerializable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Serializable object which helps us load and write to files
 */
class TORCHER_API ITorcherSerializable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Saves the Serializable Object to a file
	UFUNCTION(BlueprintNativeEvent, BlueprintPure=false, BlueprintCallable, Category="Torcher|Serializable")
	bool SaveToFile(const FString& Path) const;

	// Loads the Serializable Object from a file
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Torcher|Serializable")
	bool LoadFromFile(const FString& Path) const;

protected:

	// Saves the serializable data to a file
	virtual bool SaveToFile_Implementation([[maybe_unused]] const FString& Path) const
	PURE_VIRTUAL(ITorcherSerializable::SaveToFile, return false;);

	// Loads the serializable data from a file
	virtual  bool LoadFromFile_Implementation([[maybe_unused]] const FString& Path) const
	PURE_VIRTUAL(ITorcherSerializable::LoadFromFile, return false;);
};

#undef LOCTEXT_NAMESPACE