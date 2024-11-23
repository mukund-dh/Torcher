// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Macros/TorcherPreProcMacros.h"

#include "GenericPlatform/GenericPlatformCompilerPreSetup.h"
TORCH_INCLUDES_START
#include <c10/core/ScalarType.h>
TORCH_INCLUDES_END

#include  "TorcherTensorScalarType.generated.h"

#define LOCTEXT_NAMESPACE "TorcherTensorScalarType"

/**
 * Represents all the scalars which can be used within the tensors
 * For blueprint compatibility in Unreal Engine, we are skipping the following types:
 *
 * Short - technically can use int16, but we can't expose that to blueprints.
 * Char
 * Half
 * ComplexHalf
 * ComplexFloat
 * ComplextDouble
 * QInt8
 * QUInt8
 * QInt32
 * BFloat16
 * QUInt4x2
 * QUInt2x4
 */
UENUM(BlueprintType, Category="Torcher|Tensor", DisplayName="Torcher Tensor Scalar Type", meta=(
    Keywords="Torcher Tensor Scalar Type"
))
enum class ETorcherTensorScalarType : uint8
{
	Byte = c10::ScalarType::Byte UMETA(DisplayName="Byte"),
	// Char = c10::ScalarType::Char UMETA(DisplayName="Char"),
	// Short = c10::ScalarType::Short UMETA(DisplayName="Short"),
	Int = c10::ScalarType::Int UMETA(DisplayName="Int"),
	Long = c10::ScalarType::Long UMETA(DisplayName="Long"),
	// Half = c10::ScalarType::Half UMETA(DisplayName="Half"),
	Float = c10::ScalarType::Float UMETA(DisplayName="Float"),
	Double = c10::ScalarType::Double UMETA(DisplayName="Double"),
	// ComplexHalf = c10::ScalarType::ComplexHalf UMETA(DisplayName="ComplexHalf"),
	// ComplexFloat = c10::ScalarType::ComplexFloat UMETA(DisplayName="ComplexFloat"),
	// ComplexDouble = c10::ScalarType::ComplexDouble UMETA(DisplayName="ComplexDouble"),
	Boolean = c10::ScalarType::Bool UMETA(DisplayName="Boolean"),
	// QChar = c10::ScalarType::QInt8 UMETA(DisplayName="QChar"),
	// QByte = c10::ScalarType::QUInt8 UMETA(DisplayName="QByte"),
	// QInt = c10::ScalarType::QInt32 UMETA(DisplayName="QInt"),
	// BHalf = c10::ScalarType::BFloat16 UMETA(DisplayName="BHalf"),
	// Q4X2 = c10::ScalarType::QUInt4x2 UMETA(DisplayName="QUInt4x2"),
	// Q2X4 = c10::ScalarType::QUInt2x4 UMETA(DisplayName="QUInt2x4"),
	Undefined = c10::ScalarType::Undefined UMETA(DisplayName="Undefined"),
	TypesCount = c10::ScalarType::NumOptions UMETA(Hidden, DisplayName="Types Count")
};

namespace TorcherEnums
{
	/*
	 * Transforms a Torcher Enum Value to a Libtorch Scalar Type Enum
	 */
	[[nodiscard]]
	static FORCEINLINE constexpr c10::ScalarType Cast(const ETorcherTensorScalarType ScalarType) noexcept
	{ return static_cast<c10::ScalarType>(ScalarType); }

	/*
	 * Transforms a Libtorch Scalar Type to a Torcher Enum value
	 */
	static FORCEINLINE constexpr ETorcherTensorScalarType Cast(const c10::ScalarType ScalarType) noexcept
	{
		switch (ScalarType)
		{
			case c10::ScalarType::Byte: return ETorcherTensorScalarType::Byte;
			case c10::ScalarType::Int: return ETorcherTensorScalarType::Int;
			case c10::ScalarType::Long: return ETorcherTensorScalarType::Long;
			case c10::ScalarType::Float: return ETorcherTensorScalarType::Float;
			case c10::ScalarType::Double: return ETorcherTensorScalarType::Double;
			case c10::ScalarType::Bool: return ETorcherTensorScalarType::Boolean;
			// Add cases for other c10::ScalarType values
			default:
				// Handle types without a direct match
				return ETorcherTensorScalarType::Undefined;
		}
	}
}

#undef LOCTEXT_NAMESPACE
