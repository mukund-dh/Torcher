// Fill out your copyright notice in the Description page of Project Settings.


#include "BPUtils/TorchBlueprintUtilities.h"

void UTorchBlueprintUtilities::TestTorchTensor() noexcept
{
	const TArray<int64>& Sizes = {32, 27, 10};
	at::Tensor emptyTensor = torch::randn(c10::IntArrayRef(Sizes.GetData(), Sizes.Num()));

	UE_LOG(LogTemp, Warning, TEXT("Tensor Initialized!"));
}
