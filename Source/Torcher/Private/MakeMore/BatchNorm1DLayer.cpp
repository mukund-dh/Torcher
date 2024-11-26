// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeMore/BatchNorm1DLayer.h"
#include "Macros/TorcherLogs.h"

/*UBatchNorm1DLayer::UBatchNorm1DLayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, TensorDimensions({27, 27})
	, Epsilon(std::numeric_limits<float>::epsilon())
	, Momentum(0.1)
	, bTraining(true)
	, Gamma(nullptr)
	, Beta(nullptr)
	, RunningMean(nullptr)
	, RunningVariance(nullptr)
{
}

void UBatchNorm1DLayer::InitTensors() noexcept
{
	// Is Gamma currently valid? Only set gamma if it's not.
	if (!Gamma)
	{
		UE_LOG(LogTorcherTensor, Log, TEXT("Initializing gamma to a 1s"));
		// Set the Weights. We will have to create a new at::Tensor initialized with a torch::randn
		Gamma = new at::Tensor(torch::ones(dims).clone());
	}

	// Initialize Beta to a zero tensor if Beta hasn't already been initialized.
	if (!Beta)
	{
		UE_LOG(LogTorcherTensor, Log, TEXT("Initializing Beta to a 0s"));
		Beta = new at::Tensor(at::zeros(dims).clone());
	}

	// Initialize RunningMean to 0s
	if (!RunningMean)
	{
		UE_LOG(LogTorcherTensor, Log, TEXT("Initializing RunningMean to 0s"));
		RunningMean = new at::Tensor(torch::zeros(dims).clone());
	}

	// Initialize RunningVariance to 1s
	if (!RunningVariance)
	{
		UE_LOG(LogTorcherTensor, Log, TEXT("Initializing RunnningVariance to 1s"));
		RunningVariance = new at::Tensor(torch::ones(dims).clone());
	}
}

TArray<float> UBatchNorm1DLayer::GetGammaAsFloatArray() noexcept
{
	return GetTensorAsArray<float>(Gamma);
}

TArray<float> UBatchNorm1DLayer::GetBetaAsFloatArray() noexcept
{
	return GetTensorAsArray<float>(Beta);
}

TArray<float> UBatchNorm1DLayer::GetRunningMeanAsFloatArray() noexcept
{
	return GetTensorAsArray<float>(RunningMean);
}

TArray<float> UBatchNorm1DLayer::GetRunningVarianceAsFloatArray() noexcept
{
	return GetTensorAsArray<float>(RunningVariance);
}

TArray<int32> UBatchNorm1DLayer::GetGammaAsIntArray() noexcept
{
	return GetTensorAsArray<int32>(Gamma);
}

TArray<int32> UBatchNorm1DLayer::GetBetaAsIntArray() noexcept
{
	return GetTensorAsArray<int32>(Beta);
}

TArray<int32> UBatchNorm1DLayer::GetRunningMeanAsIntArray() noexcept
{
	return GetTensorAsArray<int32>(RunningMean);
}

TArray<int32> UBatchNorm1DLayer::GetRunningVarianceAsIntArray() noexcept
{
	return GetTensorAsArray<int32>(RunningVariance);
}

TArray<uint8> UBatchNorm1DLayer::GetGammaAsByteArray() noexcept
{
	return GetTensorAsArray<uint8>(Gamma);
}

TArray<uint8> UBatchNorm1DLayer::GetBetaAsByteArray() noexcept
{
	return GetTensorAsArray<uint8>(Beta);
}

TArray<uint8> UBatchNorm1DLayer::GetRunningMeanAsByteArray() noexcept
{
	return GetTensorAsArray<uint8>(RunningMean);
}

TArray<uint8> UBatchNorm1DLayer::GetRunningVarianceAsByteArray() noexcept
{
	return GetTensorAsArray<uint8>(RunningVariance);
}

at::Tensor UBatchNorm1DLayer::operator()(const at::Tensor& InTensor) noexcept
{
	// Calculate the forward pass
	at::Tensor itMean;
	at::Tensor itVar;
	if (bTraining)
	{
		itMean = InTensor.mean(0, true);
		itVar = InTensor.var(0, true);
	}
	else
	{
		itMean = *RunningMean;
		itVar = *RunningVariance;
	}

	at::Tensor xhat = (InTensor - itMean) / torch::sqrt(itVar + Epsilon);
	SetTensor(Out, (*Gamma * xhat + *Beta));
	if (bTraining)
	{
		torch::NoGradGuard noGrad;
		*RunningMean = (1.0f - Momentum) * *RunningMean + Momentum * itMean;
		*RunningVariance = (1.0f - Momentum) * *RunningVariance + Momentum * itVar;
	}
	
	return *Out;
}*/
