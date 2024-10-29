// Based on the Atum Project by Kaya Adrian

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "UObject/Interface.h"

#include "Tensors/TorcherDeviceType.h"
#include "Tensors/TorcherTensorScalarType.h"
#include "Tensors/TorcherTensorRetainGraphMode.h"
#include "Serializable/TorcherSerializable.h"

TORCH_INCLUDES_START
#include <torch/csrc/autograd/generated/variable_factories.h>
TORCH_INCLUDES_END

#include "TorcherTensor.generated.h"

#define LOCTEXT_NAMESPACE "ITorcherTensor"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable, BlueprintType, DisplayName = "Torcher Tensor")
class UTorcherTensor : public UInterface
{
	GENERATED_BODY()
};

/**
 * Multidimensional array to be used in linear algebra problems
 */
class TORCHER_API ITorcherTensor : public ITorcherSerializable
{
	GENERATED_BODY()

protected:

	// Device on which tensors will be created
	static ETorcherTensorDeviceType DefaultDevice;

	// Pointer to the Libtorch Tensor object
	TUniquePtr<at::Tensor> Data;

	// Type of scalar which represents the data here
	ETorcherTensorScalarType ScalarType;
	
public:

	// Constructor
	UE_NODISCARD_CTOR
	ITorcherTensor() noexcept;

	// Check if the tensor object can be used
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor")
	virtual bool IsDefined() const noexcept;

	// Check if it's possible to perform ops between two tensors
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor")
	virtual bool IsBroadcastableWith(const TScriptInterface<ITorcherTensor>& BroadcastTensor) const noexcept;

	// Changes the first tensor's name in order to make it broadcastable
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor")
	virtual bool BroadcastTo(const TScriptInterface<ITorcherTensor>& BroadcastTensor) noexcept;

	// Remove the tensor from the global gradient graph
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor")
	virtual void Detach(TScriptInterface<ITorcherTensor>& OutDetachedTensor) const noexcept;

	// Get the current gradient
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor")
	virtual void GetGradient(TScriptInterface<ITorcherTensor>& OutGradient) const noexcept;

	// Check if the current tensor's gradient is necessary
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor")
	virtual bool DoesRequireGradient() const noexcept;

	// Set whether the gradient is required or not
	virtual ITorcherTensor* SetRequireGradient(const bool bValue) noexcept;

	// Get this tensor's sizes
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor")
	virtual void GetSizes(TArray<int64>& OutSizes) const noexcept;

	// Get the device of this tensor
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor")
	virtual ETorcherTensorDeviceType GetDeviceType() const noexcept;

	// Move tensor to the specified device
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor")
	virtual void SetDeviceType(ETorcherTensorDeviceType NewDevice) noexcept;

	// Get the type of value this tensor holds
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor")
	virtual ETorcherTensorScalarType GetScalarType() const noexcept;

	// Set the scalar type
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor")
	virtual void SetScalarType(ETorcherTensorScalarType NewScalarType) noexcept;

	// Get num scalar values
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor")
	virtual int64 GetElementCount() const noexcept;

	// Get memory occupied by one element
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor")
	virtual int64 GetElementSize() const noexcept;

	// Get the tensor's values in the form of raw bytes
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor")
	virtual void GetSerializedValues(TArray<uint8>& OutValues, TArray<int64>& OutSizes) const noexcept;

	// Set the tensor's values using serialized bytes
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor")
	virtual void SetSerializedValues(const TArray<uint8>& Values, const TArray<int64>& Sizes) noexcept;

	// Creates a new tensor and copies over data from the input
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor")
	virtual void CloneData(TScriptInterface<ITorcherTensor>& OutClone, UObject* Outer = nullptr) const noexcept;

	// Compute this tensor's gradient
	UFUNCTION(BlueprintPure=false, Category="Torcher|Tensor", meta=(
		AdvancedDisplay = "Gradient, Inputs, RetainGraphMode, bCreateGraph",
		AutoCreateRefTerm = "Gradient, Inputs"
		))
	virtual bool Backward(
		const TScriptInterface<ITorcherTensor>& Gradient,
		const TArray<TScriptInterface<ITorcherTensor>>& Inputs,
		ETorcherTensorRetainGraphMode RetainGraphMode = ETorcherTensorRetainGraphMode::IfCreated,
		bool bCreateGraph = false
	) const noexcept;

	// Get the Libtorch device on which this tensor sits
	[[nodiscard]]
	FORCEINLINE c10::DeviceType GetTorchDeviceType() const noexcept
	{ return TorcherEnums::Cast(GetDeviceType()); }

	// Get the Libtorch scalar type
	[[nodiscard]]
	FORCEINLINE c10::ScalarType GetTorchScalarType() const noexcept
	{ return Data ? Data->scalar_type() : TorcherEnums::Cast(GetScalarType()); }

	// Add two tensors together
	[[nodiscard]]
	TScriptInterface<ITorcherTensor> Add(
		const TScriptInterface<ITorcherTensor>& Other,
		UPARAM(meta = (MustImplement = "/Script/Torcher.TorcherTensor")) const UClass* Class = nullptr
		) const noexcept;

	// Add two tensors by overloading the + operator
	[[nodiscard]]
	FORCEINLINE TScriptInterface<ITorcherTensor> operator+(const TScriptInterface<ITorcherTensor>& Other) const noexcept
	{ return Add(Other); }

	// Return the tensor as a FString by overloading the FString cast operator
	[[nodiscard]]
	explicit operator FString() const noexcept;

	// Casts a tensor to a string
	[[nodiscard]]
	FORCEINLINE FString ToString() const noexcept { return static_cast<FString>(*this); }

	// Get the tensor one dimension lower at a specific index 
	FORCEINLINE at::Tensor operator[](const int64 index) { return (*Data)[index]; }

	// Get the tensor one dimension lower at a specific index
	FORCEINLINE at::Tensor operator[](const c10::Scalar& Scalar) { return (*Data)[Scalar]; }

	// Get the tensor one dimension lower at a specific index
	FORCEINLINE at::Tensor operator[](const at::Tensor& Tensor) { return (*Data)[Tensor]; }

	// Get the tensor one dimension lower at a specific index
	FORCEINLINE at::Tensor operator[](const ITorcherTensor& TorcherTensor) { return (*Data)[*TorcherTensor.Data]; }

	// Gets the values and sizes of this tensor regardless of the scalar type
	template<typename T>
	void GetValues(TArray<T>& OutValues, TArray<int64>& OutSizes) const noexcept;

	// Sets the values of a tensor regardless of the tensor type
	template<typename T>
	void SetValues(T* const Values, const TArray<int64>& Sizes) noexcept
	{
		try
		{
			SetData(torch::from_blob(
				Values,
				c10::IntArrayRef(Sizes.GetData(), Sizes.Num()),
					GetTorchScalarType()
					).to(GetTorchDeviceType()));
		}
		catch (const std::exception& Exception)
		{
			UE_LOG(LogTemp, Fatal, TEXT("%hs"), Exception.what());
		}
	}

protected:
	// Blueprint function to call the ITorcherTensor::SetRequireGradient
	UFUNCTION(BlueprintCallable, Category="Torcher|Tensor", DisplayName="Set Requires Gradient")
	virtual void K2_SetRequireGradient(bool bValue, TScriptInterface<ITorcherTensor>& OutSelf) noexcept;

	// Saves the tensor data to a file
	virtual bool SaveToFile_Implementation(const FString& Path) const override;

	// Loads the tensor data from a file
	virtual bool LoadFromFile_Implementation(const FString& Path) override;

private:
	// Get the values as any scalar type
	[[nodiscard]]
	FORCEINLINE void* GetUncastedValues(const c10::ScalarType Type) const noexcept
	{ return IsDefined() ? Data->to(Type).data_ptr() : nullptr; }

	// Get the values as any scalar type
	[[nodiscard]]
	FORCEINLINE void* GetUncastedValues(const ETorcherTensorScalarType Type) const noexcept
	{ return GetUncastedValues(TorcherEnums::Cast(Type)); }

	// Write this tensor as a string inside a stream by overloading the << operator
	friend std::ostream& operator<<(std::ostream& OutStream, const ITorcherTensor& TorcherTensor) noexcept;

	// Write this tensor as a string inside a stream by overloading the << operator
	friend std::ostream& operator<<(std::ostream& OutStream, const TScriptInterface<ITorcherTensor>& TorcherTensor) noexcept;

public:
	// Getter for default device type
	[[nodiscard]]
	static FORCEINLINE ETorcherTensorDeviceType GetDefaultDeviceType() noexcept { return DefaultDevice; }

	// Setter for default device type
	static FORCEINLINE void SetDefaultDeviceType(const ETorcherTensorDeviceType Type) noexcept
	{ DefaultDevice = Type; }

	// Getter for Data as a pointer
	[[nodiscard]]
	FORCEINLINE const at::Tensor* GetData() const noexcept { return Data.Get(); }

	// Getter for Data as a reference
	[[nodiscard]]
	FORCEINLINE const at::Tensor& GetDataChecked() const noexcept { return *GetData(); }

	// Setter for Data
	FORCEINLINE void SetData(const at::Tensor& Value) noexcept
	{
		Data.Reset(Value.defined() ?
			new at::Tensor(Value.to(GetTorchDeviceType()).to(GetTorchScalarType())) :
			nullptr
		);
	}
};

/*
 * Templated part of the Tensor Interface
 */
template <typename T>
class TTorcherSensor
{
protected:
	// Container for values after being set with templates to maintain the reference
	mutable TArray<T> InternalValues = TArray<T>();

	// Sets the internal values and keeps the input array
	void SetInternalValues(ITorcherTensor& TorcherTensor, const TArray<T>& Values, const TArray<int64>& Sizes) noexcept;

public:
	// Getter for internal values
	[[nodiscard]]
	FORCEINLINE const TArray<T>& GetInternalValues() const noexcept { return InternalValues; }

	// Getter for internal values
	FORCEINLINE void GetInternalValues(TArray<T>& OutValues) noexcept { OutValues = InternalValues; }
};

template <typename T>
void ITorcherTensor::GetValues(TArray<T>& OutValues, TArray<int64>& OutSizes) const noexcept
{
	if (!IsDefined())
		return;

	OutValues.Append(static_cast<T*>(GetUncastedValues(GetScalarType())), Data->numel());

	const c10::IntArrayRef DataSizes = Data->sizes();
	OutSizes = TArray(DataSizes.data(), DataSizes.size());
}

template <typename T>
void TTorcherSensor<T>::SetInternalValues(
	ITorcherTensor& TorcherTensor,
	const TArray<T>& Values,
	const TArray<int64>& Sizes) noexcept
{
	InternalValues = Values;
	TorcherTensor.SetValues<T>(InternalValues.GetData(), Sizes);
}

#undef LOCTEXT_NAMESPACE

