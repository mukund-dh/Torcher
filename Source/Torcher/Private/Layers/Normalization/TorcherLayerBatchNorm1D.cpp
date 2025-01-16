// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/Normalization/TorcherLayerBatchNorm1D.h"
#include "BPUtils/TorcherTensorUtilities.h"
#include "Tensors/TorcherTensorFloat.h"
#include "UObject/Package.h"


UTorcherLayerBatchNorm1D::UTorcherLayerBatchNorm1D(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UTorcherLayerBatchNorm1D::InitializeLayerParams()
{
	Gamma = UTorcherTensorUtilities::CreateOnesTensor(
		UTorcherTensorFloat::StaticClass(),
		TArray<int64>{TorcherLayerBatchNorm1DOptions.Dimensions},
		TorcherLayerBatchNorm1DOptions.LayerDeviceType
	);
	Gamma->SetTensorLabel(TEXT("Gamma"));

	Beta = UTorcherTensorUtilities::CreateZeroTensor(
		UTorcherTensorFloat::StaticClass(),
		TArray<int64>{TorcherLayerBatchNorm1DOptions.Dimensions},
		TorcherLayerBatchNorm1DOptions.LayerDeviceType
	);
	Beta->SetTensorLabel(TEXT("Beta"));

	RunningMean = UTorcherTensorUtilities::CreateZeroTensor(
		UTorcherTensorFloat::StaticClass(),
		TArray<int64>{TorcherLayerBatchNorm1DOptions.Dimensions},
		TorcherLayerBatchNorm1DOptions.LayerDeviceType
	);
	RunningMean->SetTensorLabel(TEXT("RunningMean"));

	RunningVariance = UTorcherTensorUtilities::CreateOnesTensor(
		UTorcherTensorFloat::StaticClass(),
		TArray<int64>{TorcherLayerBatchNorm1DOptions.Dimensions},
		TorcherLayerBatchNorm1DOptions.LayerDeviceType
	);
	RunningVariance->SetTensorLabel(TEXT("RunningVariance"));
}

TArray<TScriptInterface<ITorcherTensorBase>> UTorcherLayerBatchNorm1D::GetParameters() const
{
	TArray<TScriptInterface<ITorcherTensorBase>> Params;
	Params.Add(Gamma);
	Params.Add(Beta);
	return Params;
}

bool UTorcherLayerBatchNorm1D::Forward(const TScriptInterface<ITorcherTensorBase>& Input,
	TScriptInterface<ITorcherTensorBase>& Output) const
{
	at::Tensor* InputTensor = Input->GetData();
	at::Tensor* XMean = RunningMean->GetData();
	at::Tensor* XVar = RunningVariance->GetData();
	if (TorcherLayerBatchNorm1DOptions.bIsTraining)
	{
		*XMean = InputTensor->mean(0, true);
		*XVar = InputTensor->var(0, true, true);
	}

	at::Tensor XHat = (*InputTensor - *XMean) / torch::sqrt(*XVar + TorcherLayerBatchNorm1DOptions.Eps);
	at::Tensor OutTensor = *Gamma->GetData() * XHat * *Beta->GetData();

	// Update the buffers
	if (TorcherLayerBatchNorm1DOptions.bIsTraining)
	{
		torch::NoGradGuard NoGrad;
		RunningMean->SetData((1 - TorcherLayerBatchNorm1DOptions.Momentum) * (*RunningMean->GetData() + TorcherLayerBatchNorm1DOptions.Momentum + *XMean));
		RunningVariance->SetData((1 - TorcherLayerBatchNorm1DOptions.Momentum) * (*RunningVariance->GetData() + TorcherLayerBatchNorm1DOptions.Momentum + *XVar));
	}

	auto* const TensorObject = NewObject<UObject>(GetTransientPackage(), UTorcherTensorFloat::StaticClass());
	auto* const Tensor = CastChecked<ITorcherTensorBase>(TensorObject);

	Tensor->SetTensorDevice(TorcherLayerBatchNorm1DOptions.LayerDeviceType);
	Tensor->SetData(OutTensor);

	Output = TensorObject;
	return true;
}

bool UTorcherLayerBatchNorm1D::SetGradientToZero(bool bSetToNone)
{
	if (Gamma->GetData()->grad().defined())
	{
		Gamma->SetGradientToZero();
	}

	if (Beta->GetData()->grad().defined())
	{
		Beta->SetGradientToZero();
	}
	return true;
}

void UTorcherLayerBatchNorm1D::CloneData(TScriptInterface<ITorcherTensorBase>& OutClone, UObject* Outer)
{
}

void UTorcherLayerBatchNorm1D::SetLayerDeviceType(ETorcherTensorDeviceType DeviceType)
{
	TorcherLayerBatchNorm1DOptions.LayerDeviceType = DeviceType;
	Gamma->SetTensorDevice(DeviceType);
	Beta->SetTensorDevice(DeviceType);
	
	RunningVariance->SetTensorDevice(DeviceType);
	RunningMean->SetTensorDevice(DeviceType);
}
