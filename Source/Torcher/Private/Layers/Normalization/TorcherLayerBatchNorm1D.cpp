// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/Normalization/TorcherLayerBatchNorm1D.h"
#include "BPUtils/TorcherTensorUtilities.h"
#include "Tensors/TorcherTensorFloat.h"
#include "UObject/Package.h"


UTorcherLayerBatchNorm1D::UTorcherLayerBatchNorm1D(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, LayerDeviceType(ETorcherTensorDeviceType::Cpu)
	, Dimensions(4)
	, Eps(0.00001)
	, Momentum(0.1)
	, bIsTraining(true)
{}

void UTorcherLayerBatchNorm1D::InitializeLayerParams()
{
	Gamma = UTorcherTensorUtilities::CreateOnesTensor(UTorcherTensorFloat::StaticClass(), TArray<int64>{Dimensions}, LayerDeviceType);
	Gamma->SetTensorLabel(TEXT("Gamma"));

	Beta = UTorcherTensorUtilities::CreateZeroTensor(UTorcherTensorFloat::StaticClass(), TArray<int64>{Dimensions}, LayerDeviceType);
	Beta->SetTensorLabel(TEXT("Beta"));

	RunningMean = UTorcherTensorUtilities::CreateZeroTensor(UTorcherTensorFloat::StaticClass(), TArray<int64>{Dimensions}, LayerDeviceType);
	RunningMean->SetTensorLabel(TEXT("RunningMean"));

	RunningVariance = UTorcherTensorUtilities::CreateOnesTensor(UTorcherTensorFloat::StaticClass(), TArray<int64>{Dimensions}, LayerDeviceType);
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
	if (bIsTraining)
	{
		*XMean = InputTensor->mean(0, true);
		*XVar = InputTensor->var(0, true, true);
	}

	at::Tensor XHat = (*InputTensor - *XMean) / torch::sqrt(*XVar + Eps);
	at::Tensor OutTensor = *Gamma->GetData() * XHat * *Beta->GetData();

	// Update the buffers
	if (bIsTraining)
	{
		torch::NoGradGuard NoGrad;
		RunningMean->SetData((1 - Momentum) * (*RunningMean->GetData() + Momentum + *XMean));
		RunningVariance->SetData((1 - Momentum) * (*RunningVariance->GetData() + Momentum + *XVar));
	}

	auto* const TensorObject = NewObject<UObject>(GetTransientPackage(), UTorcherTensorFloat::StaticClass());
	auto* const Tensor = CastChecked<ITorcherTensorBase>(TensorObject);

	Tensor->SetTensorDevice(LayerDeviceType);
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
	LayerDeviceType = DeviceType;
	Gamma->SetTensorDevice(DeviceType);
	Beta->SetTensorDevice(DeviceType);
	
	RunningVariance->SetTensorDevice(DeviceType);
	RunningMean->SetTensorDevice(DeviceType);
}
