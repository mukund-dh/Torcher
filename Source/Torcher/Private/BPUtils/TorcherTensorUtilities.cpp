// Fill out your copyright notice in the Description page of Project Settings.

#include "BPUtils/TorcherTensorUtilities.h"
#include "Tensors/TorcherTensorByte.h"
#include "Tensors/TorcherTensorFloat.h"
#include "Tensors/TorcherTensorInt.h"
#include "Macros/TorcherPreProcMacros.h"

TORCH_INCLUDES_START
#include <torch/torch.h>
TORCH_INCLUDES_END


UTorcherTensorFloat* UTorcherTensorUtilities::CreateEmptyFloatTensor(const TArray<int64> Sizes, const ETorcherTensorDeviceType DeviceType)
{
	UTorcherTensorFloat* const Tensor = NewObject<UTorcherTensorFloat>();
	Tensor->SetTensorDevice(DeviceType);
	c10::DeviceType TensorDevice = TorcherEnums::Cast(DeviceType);
	torch::TensorOptions options = torch::TensorOptions().device(TensorDevice);
	
	Tensor->SetData(torch::empty(at::IntArrayRef(Sizes.GetData(), Sizes.Num()), options));
	return Tensor;
}

UTorcherTensorInt* UTorcherTensorUtilities::CreateEmptyIntTensor(const TArray<int64> Sizes, const ETorcherTensorDeviceType DeviceType)
{
	UTorcherTensorInt* const Tensor = NewObject<UTorcherTensorInt>();
	Tensor->SetTensorDevice(DeviceType);
	c10::DeviceType TensorDevice = TorcherEnums::Cast(DeviceType);
	torch::TensorOptions options = torch::TensorOptions().device(TensorDevice);
	
	Tensor->SetData(torch::empty(at::IntArrayRef(Sizes.GetData(), Sizes.Num()), options));
	return Tensor;
}

UTorcherTensorByte* UTorcherTensorUtilities::CreateEmptyByteTensor(const TArray<int64> Sizes, const ETorcherTensorDeviceType DeviceType)
{
	UTorcherTensorByte* const Tensor = NewObject<UTorcherTensorByte>();
	c10::DeviceType TensorDevice = TorcherEnums::Cast(DeviceType);
	torch::TensorOptions options = torch::TensorOptions().device(TensorDevice);
	
	Tensor->SetData(torch::empty(at::IntArrayRef(Sizes.GetData(), Sizes.Num()), options));
	return Tensor;
}

UTorcherTensorFloat* UTorcherTensorUtilities::CreateRandnFloatTensor(const TArray<int64> Sizes,
	const ETorcherTensorDeviceType DeviceType)
{
	UTorcherTensorFloat* const Tensor = NewObject<UTorcherTensorFloat>();
	Tensor->SetTensorDevice(DeviceType);
	c10::DeviceType TensorDevice = TorcherEnums::Cast(DeviceType);
	torch::TensorOptions options = torch::TensorOptions().device(TensorDevice);
	
	Tensor->SetData(torch::randn(at::IntArrayRef(Sizes.GetData(), Sizes.Num()), options));
	return Tensor;
}

UTorcherTensorFloat* UTorcherTensorUtilities::CreateRandFloatTensor(const TArray<int64> Sizes,
	const ETorcherTensorDeviceType DeviceType)
{
	UTorcherTensorFloat* const Tensor = NewObject<UTorcherTensorFloat>();
	Tensor->SetTensorDevice(DeviceType);
	c10::DeviceType TensorDevice = TorcherEnums::Cast(DeviceType);
	torch::TensorOptions options = torch::TensorOptions().device(TensorDevice);
	
	Tensor->SetData(torch::rand(at::IntArrayRef(Sizes.GetData(), Sizes.Num()), options));
	return Tensor;
}

UTorcherTensorInt* UTorcherTensorUtilities::CreateRandIntTensor(const TArray<int64> Sizes,
	const ETorcherTensorDeviceType DeviceType)
{
	UTorcherTensorInt* const Tensor = NewObject<UTorcherTensorInt>();
	Tensor->SetTensorDevice(DeviceType);
	c10::DeviceType TensorDevice = TorcherEnums::Cast(DeviceType);
	torch::TensorOptions options = torch::TensorOptions().device(TensorDevice);
	
	Tensor->SetData(torch::randn(at::IntArrayRef(Sizes.GetData(), Sizes.Num()), options));
	return Tensor;
}

UTorcherTensorByte* UTorcherTensorUtilities::CreateRandByteTensor(const TArray<int64> Sizes,
	const ETorcherTensorDeviceType DeviceType)
{
	UTorcherTensorByte* const Tensor = NewObject<UTorcherTensorByte>();
	Tensor->SetTensorDevice(DeviceType);
	c10::DeviceType TensorDevice = TorcherEnums::Cast(DeviceType);
	torch::TensorOptions options = torch::TensorOptions().device(TensorDevice);
	
	Tensor->SetData(torch::randn(at::IntArrayRef(Sizes.GetData(), Sizes.Num()), options));
	return Tensor;
}

