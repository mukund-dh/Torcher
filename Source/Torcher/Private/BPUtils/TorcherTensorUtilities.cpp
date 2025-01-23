// Fill out your copyright notice in the Description page of Project Settings.

#include "BPUtils/TorcherTensorUtilities.h"
#include "Tensors/TorcherTensorBase.h"
#include "UObject/Package.h"
#include "Macros/TorcherPreProcMacros.h"

TORCH_INCLUDES_START
#include <torch/torch.h>
TORCH_INCLUDES_END


UObject* UTorcherTensorUtilities::CreateEmptyTensor(const UClass* Class, const TArray<int64> Sizes,
	ETorcherTensorDeviceType TensorDeviceType)
{
	check(Class && Class->ImplementsInterface(UTorcherTensorBase::StaticClass()));

	auto* const TensorObject = NewObject<UObject>(GetTransientPackage(), Class);
	auto* const Tensor = CastChecked<ITorcherTensorBase>(TensorObject);

	Tensor->SetTensorDevice(TensorDeviceType);
	Tensor->SetData(
		torch::empty(at::IntArrayRef(Sizes.GetData(), Sizes.Num()),
			TorcherEnums::Cast(TensorDeviceType)));
	return TensorObject;
}

UObject* UTorcherTensorUtilities::CreateEyeTensor(const UClass* Class, const int64 Size,
	ETorcherTensorDeviceType TensorDeviceType)
{
	check(Class && Class->ImplementsInterface(UTorcherTensorBase::StaticClass()));

	auto* const TensorObject = NewObject<UObject>(GetTransientPackage(), Class);
	auto* const Tensor = CastChecked<ITorcherTensorBase>(TensorObject);

	Tensor->SetTensorDevice(TensorDeviceType);
	Tensor->SetData(torch::eye(Size, TorcherEnums::Cast(TensorDeviceType)));
	return TensorObject;
}

UObject* UTorcherTensorUtilities::CreateZeroTensor(const UClass* Class, const TArray<int64> Sizes,
	ETorcherTensorDeviceType TensorDeviceType)
{
	check(Class && Class->ImplementsInterface(UTorcherTensorBase::StaticClass()));

	auto* const TensorObject = NewObject<UObject>(GetTransientPackage(), Class);
	auto* const Tensor = CastChecked<ITorcherTensorBase>(TensorObject);

	Tensor->SetTensorDevice(TensorDeviceType);
	Tensor->SetData(
		torch::zeros(at::IntArrayRef(Sizes.GetData(), Sizes.Num()),
			TorcherEnums::Cast(TensorDeviceType)));
	return TensorObject;
}

UObject* UTorcherTensorUtilities::CreateOnesTensor(const UClass* Class, const TArray<int64> Sizes,
	ETorcherTensorDeviceType TensorDeviceType)
{
	check(Class && Class->ImplementsInterface(UTorcherTensorBase::StaticClass()));

	auto* const TensorObject = NewObject<UObject>(GetTransientPackage(), Class);
	auto* const Tensor = CastChecked<ITorcherTensorBase>(TensorObject);

	Tensor->SetTensorDevice(TensorDeviceType);
	Tensor->SetData(
		torch::ones(at::IntArrayRef(Sizes.GetData(), Sizes.Num()),
			TorcherEnums::Cast(TensorDeviceType)));
	return TensorObject;
}

UObject* UTorcherTensorUtilities::CreateRandTensor(const UClass* Class, const TArray<int64> Sizes,
	ETorcherTensorDeviceType TensorDeviceType)
{
	check(Class && Class->ImplementsInterface(UTorcherTensorBase::StaticClass()));

	auto* const TensorObject = NewObject<UObject>(GetTransientPackage(), Class);
	auto* const Tensor = CastChecked<ITorcherTensorBase>(TensorObject);

	Tensor->SetTensorDevice(TensorDeviceType);
	Tensor->SetData(
	torch::rand(at::IntArrayRef(Sizes.GetData(), Sizes.Num()),
		TorcherEnums::Cast(TensorDeviceType)));
	return TensorObject;
}

UObject* UTorcherTensorUtilities::CreateRandnTensor(const UClass* Class, const TArray<int64> Sizes,
	ETorcherTensorDeviceType TensorDeviceType)
{
	check(Class && Class->ImplementsInterface(UTorcherTensorBase::StaticClass()));

	auto* const TensorObject = NewObject<UObject>(GetTransientPackage(), Class);
	auto* const Tensor = CastChecked<ITorcherTensorBase>(TensorObject);
	
	Tensor->SetTensorDevice(TensorDeviceType);
	Tensor->SetData(
		torch::randn(at::IntArrayRef(Sizes.GetData(), Sizes.Num()),
			TorcherEnums::Cast(TensorDeviceType)));
	return TensorObject;
}

void UTorcherTensorUtilities::execConv_TensorToString(UObject* Context, FFrame& Stack, void* const Z_Param__Result)
{
	TScriptInterface<const ITorcherTensorBase> TensorTemp;
	const TScriptInterface<const ITorcherTensorBase>& Tensor = Stack.StepCompiledInRef<FInterfaceProperty, TScriptInterface<const ITorcherTensorBase>>(&TensorTemp);

	P_FINISH

	P_NATIVE_BEGIN
	*static_cast<FString*>(Z_Param__Result) = Conv_TensorToString(Tensor);
	P_NATIVE_END
}
