// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/Linear/TorcherLayerLinear.h"

#define LOCTEXT_NAMESPACE "TorcherLayerLinear"

bool UTorcherLayerLinear::OnInitializeData_Implementation()
{
	if (Options.InFeatures <= 0LL)
	{
		UE_LOG(LogTorcherLayer, Error, TEXT("There must be at least 1 input feature!"));
		return false;
	}
	if (Options.OutFeatures <= 0LL)
	{
		UE_LOG(LogTorcherLayer, Error, TEXT("There must be at least 1 output feature!"));
		return false;
	}

	Module = MakeShared<torch::nn::Linear>(
		std::make_shared<torch::nn::LinearImpl>(
			static_cast<torch::nn::LinearOptions>(Options)
			));
	return true;
}

bool UTorcherLayerLinear::OnForward_Implementation(const UTorcherTensorBase* InTensor, UTorcherTensorBase*& OutTensor)
{
	TArray<int64> InputSizes = InTensor->GetDimensions();

	if (InputSizes.IsEmpty())
	{
		UE_LOG(LogTorcherLayer, Error, TEXT("Invalid input tensor"));
		return false;
	}

	const int64 GivenChannels = InputSizes.Last();
	if (const int64 ExpectedChannels = Options.InFeatures; GivenChannels != ExpectedChannels)
	{
		UE_LOG(
			LogTorcherLayer,
			Error,
			TEXT("Expected %lld %ls but got %lld"),
			ExpectedChannels,
			ExpectedChannels == 1LL ? TEXT("channel") : TEXT("channels"),
			GivenChannels);
		return false;
	}

	OutTensor = DuplicateObject(InTensor, nullptr);
	OutTensor->SetData((*Module)(InTensor->GetData()->to(c10::kFloat)));
	return true;
}

#undef LOCTEXT_NAMESPACE