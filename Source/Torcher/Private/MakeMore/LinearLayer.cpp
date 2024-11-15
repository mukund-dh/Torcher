// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeMore/LinearLayer.h"

#include "ATen/TensorIndexing.h"
#include "ATen/core/interned_strings.h"

TORCH_INCLUDES_START
#include <torch/csrc/autograd/function.h>
TORCH_INCLUDES_END

ULinearLayer::ULinearLayer(const FObjectInitializer& ObjectInitializer) noexcept
	: Super(ObjectInitializer)
	, FanIn(27)
	, FanOut(27)
{
	Weights = NewObject<UObject>(GetTransientPackage(), UTorcherTensorFloat::StaticClass());
	Bias = NewObject<UObject>(GetTransientPackage(), UTorcherTensorFloat::StaticClass());
}

void ULinearLayer::InitTensors() noexcept
{
	auto opt = at::TensorOptions().dtype(c10::ScalarType::Float).device(c10::DeviceType::CPU);
	at::Tensor RandWeights = torch::randn({FanIn, FanOut}, opt);
	at::Tensor ZeroBiases = at::zeros({FanOut}, opt);

	c10::IntArrayRef Sizes(RandWeights.sizes().data(), RandWeights.sizes().size());

	auto* const TensorObject = NewObject<UObject>(GetTransientPackage(), UTorcherTensorFloat::StaticClass());
	auto* const Tensor = CastChecked<ITorcherTensor>(TensorObject);

	Tensor->SetDeviceType(ETorcherTensorDeviceType::Cpu);
	Tensor->SetData(RandWeights);

	Weights = TensorObject;

	auto* const BiasTensorObject = NewObject<UObject>(GetTransientPackage(), UTorcherTensorFloat::StaticClass());
	auto* const BiasTensor = CastChecked<ITorcherTensor>(BiasTensorObject);
	BiasTensor->SetDeviceType(ETorcherTensorDeviceType::Cpu);
	BiasTensor->SetData(ZeroBiases);

	Bias = BiasTensorObject;
}

