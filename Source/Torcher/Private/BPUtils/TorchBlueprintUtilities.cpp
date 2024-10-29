// Fill out your copyright notice in the Description page of Project Settings.


#include "BPUtils/TorchBlueprintUtilities.h"
#include <iostream>

void UTorchBlueprintUtilities::TestTorchTensor() noexcept
{
	/*const TArray<int64>& Sizes = {6, 6};
	at::Tensor emptyTensor = torch::randn(c10::IntArrayRef(Sizes.GetData(), Sizes.Num()));
	int64 dimSize = emptyTensor.size(0);

	TArray<TUniquePtr<float>> Dim0;
	Dim0.Reserve(dimSize);

	for(int64 i = 0; i < dimSize; i++)
	{
		float temp = emptyTensor[0][i].item<float>();
		UE_LOG(LogTemp, Warning, TEXT("Value of Tensor at [0][%d] is [%f]"), i, temp);
	}*/

	UE_LOG(LogTemp, Warning, TEXT("Tensor Initialized!"));
}
