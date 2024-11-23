// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeMore/MLP.h"
#include "MakeMore/MMTokenizer.h"
#include "torch/csrc/jit/tensorexpr/types.h"

UMLP::UMLP(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, FloatTensor(nullptr)
	, Tokenizer(nullptr)
{
}

void UMLP::InitTensors() noexcept
{
	auto gen = at::detail::createCPUGenerator(2147483647);
	auto opt = at::TensorOptions().dtype(c10::kFloat).device(c10::DeviceType::CPU);
	at::Tensor randTensor = torch::randn({27, 27}, gen, opt);
	double ScalingFactor = FMath::Pow(27.0, 0.5);
	
	FloatTensor = NewObject<UTorcherTensorFloat>();

	randTensor = randTensor.div(ScalingFactor);
	FloatTensor->SetData(randTensor);
}

