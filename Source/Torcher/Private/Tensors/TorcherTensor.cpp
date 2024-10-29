// Based on the Atum Project by Kaya Adrian

#include "Tensors/TorcherTensor.h"

#include "TorcherModule.h"
#include "UObject/Package.h"

TORCH_INCLUDES_START
#include <torch/serialize.h>
TORCH_INCLUDES_END

#define LOCTEXT_NAMESPACE "ITorcherTensor"

// Let the default device be the CPU
ETorcherTensorDeviceType ITorcherTensor::DefaultDevice = ETorcherTensorDeviceType::Cpu;

ITorcherTensor::ITorcherTensor() noexcept : Data(nullptr), ScalarType(ETorcherTensorScalarType::Undefined)
{
}

bool ITorcherTensor::IsDefined() const noexcept
{
	return Data && Data->defined();
}

bool ITorcherTensor::IsBroadcastableWith(const TScriptInterface<ITorcherTensor>& BroadcastTensor) const noexcept
{
	if (!IsDefined() || BroadcastTensor == nullptr || !BroadcastTensor->IsDefined())
		return false;

	TArray<int64> Sizes;
	GetSizes(Sizes);
	const int32 SizeCount = Sizes.Num();

	TArray<int64> BroadcastSizes;
	BroadcastTensor->GetSizes(BroadcastSizes);
	int32 BroadcastSizeCount = BroadcastSizes.Num();

	// Ensure that the Size of this tensor is equal to or greater than the one we want to
	// broadcast with. In which case, do the reverse broadcast.
	if (SizeCount < BroadcastSizeCount)
		return BroadcastTensor->IsBroadcastableWith(_getUObject());

	// If the Broadcast tensor is smaller than this tensor, expand it
	while (SizeCount != BroadcastSizeCount)
	{
		BroadcastSizes.Insert(1LL, 0);
		++BroadcastSizeCount;
	}

	for (int32 Index = SizeCount - 1; Index >= 0; --Index)
	{
		const int32 BroadcastSize = BroadcastSizes[Index];
		if (
			const int32 Size = Sizes[Index];
			Size == 0LL || BroadcastSize == 0LL || (Size != BroadcastSize && Size != 1LL && BroadcastSize != 1LL)
			)
			return false;
	}

	return true;
}

bool ITorcherTensor::BroadcastTo(const TScriptInterface<ITorcherTensor>& BroadcastTensor) noexcept
{
	if (!IsBroadcastableWith(BroadcastTensor))
		return false;

	TArray<int64> BroadcastSizes;
	BroadcastTensor->GetSizes(BroadcastSizes);

	const int64* const SizeData = BroadcastSizes.GetData();
	*Data = broadcast_to(*Data, at::IntArrayRef(SizeData, SizeData+BroadcastSizes.Num()));
	return true;
}

void ITorcherTensor::Detach(TScriptInterface<ITorcherTensor>& OutDetachedTensor) const noexcept
{
	if (OutDetachedTensor = IsDefined() ? DuplicateObject(_getUObject(), nullptr) : nullptr; OutDetachedTensor)
	{
		OutDetachedTensor->SetData(Data->detach());
	}
}

void ITorcherTensor::GetGradient(TScriptInterface<ITorcherTensor>& OutGradient) const noexcept
{
	if (OutGradient = IsDefined() ? DuplicateObject(_getUObject(), nullptr) : nullptr; OutGradient)
	{
		OutGradient->SetData(Data->grad());
	}
}

bool ITorcherTensor::DoesRequireGradient() const noexcept
{
	return Data && Data->requires_grad();
}

ITorcherTensor* ITorcherTensor::SetRequireGradient(const bool bValue) noexcept
{
	if (Data)
	{
		SetData(Data->set_requires_grad(bValue));
	}

	return this;
}

void ITorcherTensor::GetSizes(TArray<int64>& OutSizes) const noexcept
{
	const c10::IntArrayRef DataSizes = Data->sizes();
	OutSizes = TArray(DataSizes.data(), DataSizes.size());
}

ETorcherTensorDeviceType ITorcherTensor::GetDeviceType() const noexcept
{
	return Data ? TorcherEnums::Cast(Data->device().type()) : DefaultDevice;
}

void ITorcherTensor::SetDeviceType(ETorcherTensorDeviceType NewDevice) noexcept
{
	if (Data)
	{
		Data->to(TorcherEnums::Cast(NewDevice));
	}
}

void ITorcherTensor::SetScalarType(ETorcherTensorScalarType NewScalarType) noexcept
{
	if (Data)
	{
		Data->to(TorcherEnums::Cast(NewScalarType));
	}
	else
	{
		ScalarType = NewScalarType;
	}
}

ETorcherTensorScalarType ITorcherTensor::GetScalarType() const noexcept
{
	return ScalarType == ETorcherTensorScalarType::Undefined ? TorcherEnums::Cast(Data->scalar_type()) : ScalarType;
}

int64 ITorcherTensor::GetElementCount() const noexcept
{
	return IsDefined() ? Data->numel() : 0LL;
}

int64 ITorcherTensor::GetElementSize() const noexcept
{
	return IsDefined() ? Data->element_size() : 0LL;
}

void ITorcherTensor::GetSerializedValues(TArray<uint8>& OutValues, TArray<int64>& OutSizes) const noexcept
{
	const uint64 ByteCount = Data ? Data->numel() * Data->element_size() : 0ULL;
	if (ByteCount == 0ULL)
	{
		OutSizes.AddZeroed();
		return;
	}

	OutValues.AddUninitialized(ByteCount);
	FMemory::Memcpy(OutValues.GetData(), Data->data_ptr(), ByteCount);
	GetSizes(OutSizes);
}

void ITorcherTensor::SetSerializedValues(const TArray<uint8>& Values, const TArray<int64>& Sizes) noexcept
{
	SetData(torch::empty(c10::IntArrayRef(Sizes.GetData(), Sizes.Num())));

	uint64 MaxSize = Data->element_size();
	for (const int64 Size : Sizes)
	{
		MaxSize *= Size;
	}

	FMemory::Memcpy(
		Data->data_ptr(),
		Values.GetData(),
		std::min(static_cast<uint64>(Values.Num()), MaxSize));
}

void ITorcherTensor::CloneData(TScriptInterface<ITorcherTensor>& OutClone, UObject* Outer) const noexcept
{
	if (OutClone = DuplicateObject(_getUObject(), Outer); Outer && Data)
	{
		OutClone->SetData(*Data);
	}
}

bool ITorcherTensor::Backward(
	const TScriptInterface<ITorcherTensor>& Gradient,
	const TArray<TScriptInterface<ITorcherTensor>>& Inputs,
	ETorcherTensorRetainGraphMode RetainGraphMode, bool bCreateGraph) const noexcept
{
	if (!DoesRequireGradient())
		return false;

	at::Tensor GradientTensor = Gradient && Gradient->IsDefined() ?
		Gradient->GetDataChecked() : torch::ones_like(*Data, c10::TensorOptions().requires_grad(true));
	if (!Data->is_same_size(GradientTensor))
		return false;

	std::vector<at::Tensor> TensorList;
	TensorList.reserve(Inputs.Num());
	for (const TScriptInterface<ITorcherTensor>& Input : Inputs)
	{
		if (Input->IsDefined() && Input->GetDataChecked().requires_grad())
		{
			TensorList.push_back(Input->GetDataChecked().to(c10::kFloat).set_requires_grad(true));
		}
	}

	const bool bRetainGraph = RetainGraphMode == ETorcherTensorRetainGraphMode::Always;
	Data->backward(
		MoveTemp(GradientTensor),
		RetainGraphMode == ETorcherTensorRetainGraphMode::IfCreated ? c10::nullopt : c10::optional<bool>(bRetainGraph),
		bCreateGraph,
		TensorList.empty() ? c10::nullopt : c10::optional<at::TensorList>(MoveTemp(TensorList))
	);

	return true;
}

TScriptInterface<ITorcherTensor> ITorcherTensor::Add(
	const TScriptInterface<ITorcherTensor>& Other,
	const UClass* Class) const noexcept
{
	auto* const Result = NewObject<UObject>(
		GetTransientPackage(),
		Class && Class->ImplementsInterface(UTorcherTensor::StaticClass()) ? Class : _getUObject()->GetClass()
		);

	if(IsBroadcastableWith(Other))
	{
		CastChecked<ITorcherTensor>(Result)->SetData(Data->add(*Other->Data));
	}
	return Result;
}

ITorcherTensor::operator FString() const noexcept
{
	std::ostringstream Stream;
	Stream << *this;
	return Stream.str().c_str();
}

void ITorcherTensor::K2_SetRequireGradient(bool bValue, TScriptInterface<ITorcherTensor>& OutSelf) noexcept
{
	OutSelf = SetRequireGradient(bValue)->_getUObject();
}

bool ITorcherTensor::SaveToFile_Implementation(const FString& Path) const
{
	if (!IsDefined())
		return false;

	torch::save(*Data, TCHAR_TO_UTF8(*ITorcherModule::GetContentDirectory(Path)));
	return true;
}

bool ITorcherTensor::LoadFromFile_Implementation(const FString& Path)
{
	at::Tensor LoadTensor;
	torch::load(LoadTensor, TCHAR_TO_UTF8(*ITorcherModule::GetContentDirectory(Path)));
	SetData(MoveTemp(LoadTensor));
	return IsDefined();
}

std::ostream& operator<<(std::ostream& OutStream, const ITorcherTensor& TorcherTensor) noexcept
{
	if (const at::Tensor* const Tensor = TorcherTensor.Data.Get())
	{
		OutStream << *Tensor;
	}

	return OutStream;
}

std::ostream& operator<<(std::ostream& OutStream, const TScriptInterface<ITorcherTensor>& TorcherTensor) noexcept
{
	if (const ITorcherTensor* const Interface = TorcherTensor.GetInterface())
	{
		OutStream << *Interface;
	}
	return OutStream;
}

#undef LOCTEXT_NAMESPACE