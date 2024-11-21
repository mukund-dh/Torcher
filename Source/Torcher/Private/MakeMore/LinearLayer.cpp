// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeMore/LinearLayer.h"
#include "Macros/TorcherLogs.h"

ULinearLayer::ULinearLayer(const FObjectInitializer& ObjectInitializer) noexcept
	: Super(ObjectInitializer)
	, FanIn(27)
	, FanOut(27)
	, bHasBias(true)
	, Seed(2147483647)
	, Weights(nullptr)
	, Bias(nullptr)
{
}

ULinearLayer::~ULinearLayer() noexcept
{
	// free up the pointers to at::Tensors
	if (Weights != nullptr)
		delete Weights;
	
	if (Bias != nullptr)
		delete Bias;
}

void ULinearLayer::InitTensors() noexcept
{
	// Define the tensor creation options
	auto opt = at::TensorOptions().dtype(c10::ScalarType::Float).device(c10::DeviceType::CPU);

	// Are the weights currently valid? Only set weights if there are none.
	if (!Weights)
	{
		UE_LOG(LogTorcherTensor, Log, TEXT("Initializing weights to a normalized random tensor"));
		// Create a generator with a manual seed.
		auto gen = at::detail::createCPUGenerator(Seed);
		// Set the Weights. We will have to create a new at::Tensor initialized with a torch::randn
		Weights = new at::Tensor((torch::randn({FanIn, FanOut}, gen, opt) / FMath::Pow(FanIn, 0.5)).clone());
	}

	// Initialize biases to a zero tensor if this has biases and Bias hasn't already been initialized.
	if (bHasBias and !Bias)
	{
		UE_LOG(LogTorcherTensor, Log, TEXT("Initializing biases to a 0 tensor"));
		Bias = new at::Tensor(at::zeros({FanOut}, opt).clone());
	}
}

at::Tensor ULinearLayer::operator()(const at::Tensor& InTensor) noexcept
{
	if (Out && Out->defined())
	{
		delete Out;
		Out = nullptr;
	}

	// IN CASE Weights aren't initialized/defined
	if (!Weights || !Weights->defined())
	{
		UE_LOG(LogTorcherTensor, Warning, TEXT("Weights haven't been properly defined. Initializing to torch::zeros."));
		auto opt = at::TensorOptions().dtype(c10::ScalarType::Float).device(c10::DeviceType::CPU);
		Weights = new at::Tensor(torch::zeros({FanIn, FanOut}, opt));
	}
	
	// Out will have to be set as a new at::Tensor initialized with a torch::matmul
	Out = new at::Tensor(torch::matmul(InTensor, *Weights).clone());
	if (Bias->defined())
		*Out += *Bias;

	return *Out;
}

float ULinearLayer::GetValueAtIndex(TArray<int32> IndexArray) const
{
	// Debug.
	return (Weights && Weights->defined()) ? Weights->data()[IndexArray[0]][IndexArray[1]].item<float>() : INFINITY;
}
