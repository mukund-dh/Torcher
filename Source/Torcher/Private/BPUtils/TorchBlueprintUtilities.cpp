// Fill out your copyright notice in the Description page of Project Settings.


#include "BPUtils/TorchBlueprintUtilities.h"

void UTorchBlueprintUtilities::TestTorchTensor(const TScriptInterface<ITorcherTensorBase> InTensor) noexcept
{
	
	UE_LOG(LogTemp, Warning, TEXT("Tensor Initialized!"));
}

void UTorchBlueprintUtilities::InitTensorToRandn(TScriptInterface<ITorcherTensorBase> InTensor) noexcept
{
	if (!InTensor->IsDataDefined())
	{
		// Sanity check to ensure that the dimensions are, indeed, defined.
		if (InTensor->GetDimensions().IsEmpty())
		{
			InTensor->SetDimensions({4,4});
		}

		// Ensure that the Scalar Type is set to float, as int, bool or undefined don't make any sense
		InTensor->SetTensorScalarType(ETorcherTensorScalarType::Float);
		
		// Only init data if it isn't already defined.
		UE_LOG(LogTorcherTensor, Log, TEXT("Initializing torcher tensor to a normalized random tensor"));
		// Create a generator with a manual seed.
		auto gen = at::detail::createCPUGenerator(InTensor->GetSeed());

		std::vector<int64_t> dims = ConvertIntArrayToVector(InTensor->GetDimensions());
		const at::IntArrayRef TensorSize = at::IntArrayRef(dims);
		at::TensorOptions opt = at::TensorOptions().dtype(TorcherEnums::Cast(InTensor->GetTensorScalarType())).device(TorcherEnums::Cast(InTensor->GetTensorDevice()));
		
		// Set the Data. We will have to create a new at::Tensor initialized with a torch::randn
		at::Tensor RandTensor = torch::randn(TensorSize, gen, opt) / FMath::Pow(dims[0], 0.5);
		InTensor->SetData(RandTensor);
	}
}

void UTorchBlueprintUtilities::InitTensorToZeros(TScriptInterface<ITorcherTensorBase> InTensor) noexcept
{
	if (!InTensor->IsDataDefined())
	{
		// Sanity check to ensure that the dimensions are, indeed, defined.
		if (InTensor->GetDimensions().IsEmpty())
		{
			InTensor->SetDimensions({4,4});
		}

		// Ensure that the Scalar Type is not set to undefined
		if (InTensor->GetTensorScalarType() == ETorcherTensorScalarType::Undefined)
		{
			UE_LOG(LogTorcherTensor, Error, TEXT("TensorScalarType is undefined. Please set this to a supported type."))
			return;
		}
		
		// Only init data if it isn't already defined.
		UE_LOG(LogTorcherTensor, Log, TEXT("Initializing torcher tensor to a zeros tensor"));
		
		const std::vector<int64_t> dims = ConvertIntArrayToVector(InTensor->GetDimensions());
		const at::IntArrayRef TensorSize = at::IntArrayRef(dims);
		at::TensorOptions opt = at::TensorOptions().dtype(TorcherEnums::Cast(InTensor->GetTensorScalarType())).device(TorcherEnums::Cast(InTensor->GetTensorDevice()));
		
		// Set the Data. We will have to create a new at::Tensor initialized with a torch::zeros
		InTensor->SetData(torch::zeros(TensorSize, opt));
	}
}

void UTorchBlueprintUtilities::InitTensorToOnes(TScriptInterface<ITorcherTensorBase> InTensor) noexcept
{
	if (!InTensor->IsDataDefined())
	{
		// Sanity check to ensure that the dimensions are, indeed, defined.
		if (InTensor->GetDimensions().IsEmpty())
		{
			InTensor->SetDimensions({4,4});
		}

		// Ensure that the Scalar Type is not set to undefined
		if (InTensor->GetTensorScalarType() == ETorcherTensorScalarType::Undefined)
		{
			UE_LOG(LogTorcherTensor, Error, TEXT("TensorScalarType is undefined. Please set this to a supported type."))
			return;
		}
		
		// Only init data if it isn't already defined.
		UE_LOG(LogTorcherTensor, Log, TEXT("Initializing torcher tensor to a normalized random tensor"));

		const std::vector<int64_t> dims = ConvertIntArrayToVector(InTensor->GetDimensions());
		const at::IntArrayRef TensorSize = at::IntArrayRef(dims);
		at::TensorOptions opt = at::TensorOptions().dtype(TorcherEnums::Cast(InTensor->GetTensorScalarType())).device(TorcherEnums::Cast(InTensor->GetTensorDevice()));
		
		// Set the Data. We will have to create a new at::Tensor initialized with a torch::zeros
		InTensor->SetData(torch::ones(TensorSize, opt));
	}
}

void UTorchBlueprintUtilities::GetTensorAsFloatArray(TScriptInterface<ITorcherTensorBase> InTensor, TArray<float>& OutValues, TArray<int64>& OutSizes) noexcept
{
	if (!InTensor->IsDataDefined())
	{
		UE_LOG(LogTorcherTensor, Warning, TEXT("InTensor not defined"));
		return;
	}

	OutValues = InTensor->GetData<float>();
	OutSizes = InTensor->GetDimensions();
}

std::vector<int64_t> UTorchBlueprintUtilities::ConvertIntArrayToVector(const TArray<int64>& InArray)
{
	std::vector<int64_t> OutVector(InArray.Num());
	for (int32 i = 0; i < InArray.Num(); i++)
	{
		OutVector[i] = static_cast<int64_t>(InArray[i]);
	}
	return OutVector;
}
