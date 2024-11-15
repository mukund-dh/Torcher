// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeMore/LinearLayer.h"

ULinearLayer::ULinearLayer(const FObjectInitializer& ObjectInitializer) noexcept
	: Super(ObjectInitializer)
	, FanIn(27)
	, FanOut(27)
	, bHasBias(true)
	, Seed(2147483647)
	, Weights(nullptr)
	, Bias(nullptr)
	, Out(nullptr)
{
}

ULinearLayer::~ULinearLayer() noexcept
{
	// free up the pointers to at::Tensors
	if (Weights != nullptr)
		delete Weights;
	
	if (Bias != nullptr)
		delete Bias;

	if (Out != nullptr)
		delete Out;
}

void ULinearLayer::InitTensors() noexcept
{
	// Define the tensor creation options
	auto opt = at::TensorOptions().dtype(c10::ScalarType::Float).device(c10::DeviceType::CPU);

	// Are the weights currently valid? Only set weights if there are none.
	if (!Weights)
	{
		UE_LOG(LogTemp, Log, TEXT("Initializing weights to a normalized random tensor"));
		// Create a generator with a manual seed.
		auto gen = at::detail::createCPUGenerator(Seed);
		// Set the Weights. We will have to create a new at::Tensor initialized with a torch::randn
		Weights = new at::Tensor(torch::randn({FanIn, FanOut}, gen, opt) / FMath::Pow(FanIn, 0.5));
	}

	// Initialize biases to a zero tensor if this has biases.
	if (bHasBias)
	{
		UE_LOG(LogTemp, Log, TEXT("Initializing biases to a 0 tensor"));
		Bias = new at::Tensor(at::zeros({FanOut}, opt));
	}
}

at::Tensor ULinearLayer::Forward(const at::Tensor& InTensor) noexcept
{
	// Out will have to be set as a new at::Tensor initialized with a torch::matmul
	Out = new at::Tensor(torch::matmul(InTensor, *Weights));
	if (Bias->defined())
		*Out += *Bias;

	return *Out;
}

float ULinearLayer::GetValueAtIndex(TArray<int32> IndexArray) const
{
	// Debug.
	return Weights->data()[IndexArray[0]][IndexArray[1]].item<float>();
}

void ULinearLayer::GetParameters(TArray<float>& WeightVals, TArray<float>& Biases)
{
	// Extract values from Weights
	if (Weights && Weights->defined())
	{
		std::vector<float> WeightsVec = ConvertTensorToVector(*Weights);
		WeightVals.Append(&WeightsVec[0], WeightsVec.size());
	}

	// Extract values from Bias
	if (Bias && Bias->defined())
	{
		std::vector<float> BiasVec = ConvertTensorToVector(*Bias);
		Biases.Append(&BiasVec[0], BiasVec.size());
	}
}

void ULinearLayer::GetOutputs(TArray<float>& OutVals)
{
	if (Out && Out->defined())
	{
		std::vector<float> OutVec = ConvertTensorToVector(*Out);
		OutVals.Append(&OutVec[0], OutVec.size());
	}
}

std::vector<float> ULinearLayer::ConvertTensorToVector(const at::Tensor& InTensor)
{
	return std::vector<float>(InTensor.data_ptr<float>(), InTensor.data_ptr<float>() + InTensor.numel());
}

/*at::Tensor ULinearLayer::ConvertArrayToTensor(const TArray<float>& Array, const std::vector<int64_t>& Sizes) const
{
}*/


