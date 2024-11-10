// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/StaticArray.h"
#include "UObject/Object.h"
#include "Macros/TorcherPreProcMacros.h"

TORCH_INCLUDES_START
#include <torch/csrc/autograd/function.h>
TORCH_INCLUDES_END

#include "MMTokenizer.generated.h"


struct bigramLookups
{
private:
	TCHAR letters[27];

public:

	bigramLookups()
	{
		letters[0] = '.';
		for (int i = 0; i < 26; i++)
		{
			letters[i+1] = 'a' + i;
		}
	}

	TCHAR getCharAtIndex(int32 index) const
	{
		return ((0 <= index) && (index <=26)) ? letters[index] : NULL;
	}

	int32 getIndexOfChar(char inChar, int32 startIdx = 0, int32 endIdx = 25) const
	{
		if (startIdx >= endIdx)
			return -1;

		int32 index = -1;
		int32 pivot = startIdx + (endIdx - startIdx) / 2;
		if (inChar == letters[pivot])
			return pivot;
		
		if (inChar < letters[pivot])
		{
			return getIndexOfChar(inChar, startIdx, pivot);
		}
		else
		{
			return getIndexOfChar(inChar, pivot + 1, endIdx);
		}
	}
};


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TORCHER_API UMMTokenizer : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Tokens|Files")
	FString FilePath;

public:

	UMMTokenizer();

	UFUNCTION(BlueprintCallable, Category="MMTokenizer|FileOps")
	void GetWordsList();

protected:


public:

	[[nodiscard]]
	at::Tensor GetBigramCounts() const noexcept;

private:
	TArray<FString> WordsList;

	static bigramLookups bgl;
};
