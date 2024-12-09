// Fill out your copyright notice in the Description page of Project Settings.


#include "Layers/ITorcherLayer.h"

#include "Tensors/TorcherDeviceType.h"
#include "Tensors/TorcherTensorByte.h"
#include "Tensors/TorcherTensorFloat.h"
#include "Tensors/TorcherTensorInt.h"
#include "Macros/TorcherPreProcMacros.h"

TORCH_INCLUDES_START
#include <torch/nn/module.h>
TORCH_INCLUDES_END

#define LOCTEXT_NAMESPACE "IITorcherLayer"

// Add default functionality here for any IITorcherLayer functions that are not pure virtual.
IITorcherLayer::IITorcherLayer() noexcept
	: bInitialized(false)
	, LayerDeviceType(ETorcherTensorDeviceType::Cpu)
{
}

void IITorcherLayer::SetBaseModule(torch::nn::Module* Value) noexcept
{
}

bool IITorcherLayer::OnForward_Implementation(const UTorcherTensorBase* InTensor,
	UTorcherTensorBase*& OutTensor)
{
	OutTensor = DuplicateObject(InTensor, nullptr);
	throw std::logic_error(TCHAR_TO_UTF8(*FString::Printf(
		TEXT("OnForward is not implemented in: `%ls`"),
		*GetNameSafe(_getUObject()->GetClass()))));
}

bool IITorcherLayer::OnInitializeData_Implementation()
{
	throw std::logic_error(TCHAR_TO_UTF8(*FString::Printf(
		TEXT("OnInitializeData is not implemented in: `%ls`"),
		*GetNameSafe(_getUObject()->GetClass())
	)));
}

bool IITorcherLayer::InitializeData_Implementation()
{
	if (bInitialized)
		// The layer is already initialized
		return true;

	UObject* const LayerObject = _getUObject();
	try
	{
		bInitialized = Execute_OnInitializeData(LayerObject);
	}
	catch (const std::exception& Exception)
	{
		bInitialized = false;

		const std::string& ExceptionString = Exception.what();
		UE_LOG(LogTorcherLayer,
			Error,
			TEXT("Unhandled Exception - %hs\nFailed to initialize layer of type `%ls`"),
			ExceptionString.substr(0, ExceptionString.find("\n")).c_str(),
			*GetNameSafe(LayerObject->GetClass())
			);
	}

	if(!bInitialized)
		return false;
	
	torch::nn::Module* const BaseModule = GetBaseModule();
	if (UNLIKELY(BaseModule == nullptr))
	{
		bInitialized = false;
		UE_LOG(LogTorcherLayer, Error, TEXT("Pointer in Torcher Layer `%ls` is not initialized"), *GetNameSafe(_getUObject()->GetClass()));
		return bInitialized;
	}

	BaseModule->to(TorcherEnums::Cast(LayerDeviceType));
	bInitialized = true;
	return bInitialized;
}

void IITorcherLayer::SetLayerDeviceType_Implementation(ETorcherTensorDeviceType NewDeviceType)
{
	LayerDeviceType = NewDeviceType;
}

bool IITorcherLayer::SetGradientToZero_Implementation(bool bSetToZero)
{
	torch::nn::Module* const BaseModule = GetBaseModule();
	if (BaseModule == nullptr)
		return false;

	BaseModule->zero_grad(bSetToZero);
	return true;
}

bool IITorcherLayer::Forward_Implementation(const UTorcherTensorBase* InTensor, UTorcherTensorBase*& OutTensor)
{
	UObject* const LayerObject = _getUObject();
	const ANSICHAR* const LayerClassName = TCHAR_TO_UTF8(*GetNameSafe(LayerObject->GetClass()));

	const at::Tensor* const Data = InTensor ? InTensor->GetData() : nullptr;
	const at::IntArrayRef& Sizes = Data ? Data->sizes() : at::IntArrayRef();

	if (Data == nullptr || Sizes.empty())
	{
		UE_LOG(LogTorcherLayer, Error, TEXT("Input had no data at Torcher Layer of type `%hs"), LayerClassName);
		return false;
	}

	for (const int64 Size : Sizes)
	{
		if (UNLIKELY(Size == 0LL))
		{
			UE_LOG(LogTorcherLayer, Error, TEXT("Input Contains 0D dimension torcher layer."));
			return false;
		}
	}

	if (!bInitialized)
	{
		UE_LOG(LogTorcherLayer, Error, TEXT("Layer has not been initialized"));
		return false;
	}

	try
	{
		Execute_OnForward(LayerObject, InTensor, OutTensor);
	}
	catch (const std::exception& Exception)
	{
		const std::string& ExceptionString = Exception.what();
		UE_LOG(LogTorcherLayer,
			Error,
			TEXT("Unhandled exception - %hs\nFailed to forward in Torcher Layer of type `%hs`"),
			ExceptionString.substr(0, ExceptionString.find("\n")).c_str(),
			LayerClassName
			);
		return false;
	}
	
	return true;
}

void IITorcherLayer::GetParameters_Implementation(const UClass* Class,
	TMap<FString, UTorcherTensorBase*>& OutValues) const
{
	const torch::nn::Module* BaseModule = GetBaseModule();
	if (BaseModule == nullptr)
		return;

	for (const torch::OrderedDict<std::string, at::Tensor>::Item& Parameter : BaseModule->named_parameters())
	{
		const at::Tensor& Value = Parameter.value();
		if (!Value.defined())
			continue;

		ETorcherTensorScalarType TensorScalarType = TorcherEnums::Cast(Value.scalar_type());
		if (TensorScalarType == ETorcherTensorScalarType::Undefined)
		{
			UE_LOG(LogTorcherLayer, Warning, TEXT("Incompatible Tensor. Skipping"));
			continue;
		}

		if (TensorScalarType == ETorcherTensorScalarType::Int)
		{
			UTorcherTensorInt* IntTensor = NewObject<UTorcherTensorInt>();
			IntTensor->SetData(Value);
			OutValues.Add(Parameter.key().c_str(), MoveTemp(IntTensor));
		}
		else if (TensorScalarType == ETorcherTensorScalarType::Float)
		{
			UTorcherTensorFloat* FloatTensor = NewObject<UTorcherTensorFloat>();
			FloatTensor->SetData(Value);
			OutValues.Add(Parameter.key().c_str(), MoveTemp(FloatTensor));
		}
		else if (TensorScalarType == ETorcherTensorScalarType::Byte)
		{
			UTorcherTensorByte* ByteTensor = NewObject<UTorcherTensorByte>();
			ByteTensor->SetData(Value);
			OutValues.Add(Parameter.key().c_str(), MoveTemp(ByteTensor));
		}
		else
		{
			UE_LOG(LogTorcherLayer, Warning, TEXT("Tensors of type long, double and bool haven't been implemented yet."));
			continue;
		}
	}
}

const torch::nn::Module* IITorcherLayer::GetBaseModule() const noexcept
{
	return nullptr;
}

#undef LOCTEXT_NAMESPACE