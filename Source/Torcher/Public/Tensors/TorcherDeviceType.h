// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Macros/TorcherPreProcMacros.h"
#include <c10/core/DeviceType.h>

#include "TorcherDeviceType.generated.h"

#define LOCTEXT_NAMESPACE "TorcherTensorDeviceType"

/*
 * Represents the device type of sensors which can be used. For now, keeping it down to the limited
 * cases of
 *
 * CPU
 * CUDA
 * ONNX
 * META
 * LAZY
 * MTIA
 * 
 */
UENUM(BlueprintType, Category = "Torcher|Tensor", DisplayName = "Torcher Tensor Device Type", meta = (
	Keywords = "Torcher Tensor Device Type"
))
enum class ETorcherTensorDeviceType : uint8
{
	// CPU
	Cpu = c10::DeviceType::CPU UMETA(DisplayName = "CPU"),
	// CUDA
	Cuda = c10::DeviceType::CUDA UMETA(DisplayName = "CUDA"),
	// Explicit MklDnn
	MklDnn = c10::DeviceType::MKLDNN UMETA(DisplayName = "MKLDNN"),
	// OpenGL
	OpenGL = c10::DeviceType::OPENGL UMETA(DisplayName = "OGL"),
	// OpenCL
	OpenCL = c10::DeviceType::OPENCL UMETA(DisplayName = "OCL"),
	// IDeep
	IDeep = c10::DeviceType::IDEEP UMETA(DisplayName = "IDEEP"),
	// AMD Hip
	Hip = c10::DeviceType::HIP UMETA(DisplayName = "HIP"),
	// FPGA
	Fpga = c10::DeviceType::FPGA UMETA(DisplayName = "FPGA"),
	// ONNX
	Ort = c10::DeviceType::ORT UMETA(DisplayName = "ONNX"),
	// Xla / Tpu
	Xla = c10::DeviceType::XLA UMETA(DisplayName = "XLA"),
	// Vulkan
	Vulkan = c10::DeviceType::Vulkan UMETA(DisplayName = "VULKAN"),
	// Metal
	Metal = c10::DeviceType::Metal UMETA(DisplayName = "METAL"),
	// XPU
	Xpu = c10::DeviceType::XPU UMETA(DisplayName = "XPU"),
	// Mps
	Mps = c10::DeviceType::MPS UMETA(DisplayName = "MPS"),
	// META
	Meta = c10::DeviceType::Meta UMETA(DisplayName = "META"),
	// HPU / Habana
	Hpu = c10::DeviceType::HPU UMETA(DisplayName = "HPU"),
	// SX-Aurora / NEC
	Ve = c10::DeviceType::VE UMETA(DisplayName = "VE"),
	// LAZY
	Lazy = c10::DeviceType::Lazy UMETA(DisplayName = "LAZY"),
	// Ipu
	Ipu = c10::DeviceType::IPU UMETA(DisplayName = "IPU"),
	// META Training and Inference
	Mtia = c10::DeviceType::MTIA UMETA(DisplayName = "MTIA"),
	// Private Use
	PrivateUse1 = c10::DeviceType::PrivateUse1 UMETA(DisplayName = "Private1"),
	// Number of types
	TypesCount = c10::DeviceType::COMPILE_TIME_MAX_DEVICE_TYPES UMETA(Hidden, DisplayName = "Types Count")
};


namespace TorcherEnums
{
	/*
	 * Transform a Torcher Enum into a Libtorch Enum value
	 * 
	 */
	[[nodiscard]]
	static FORCEINLINE constexpr c10::DeviceType Cast(const ETorcherTensorDeviceType DeviceType) noexcept
	{ return static_cast<c10::DeviceType>(DeviceType); }

	/*
	 * Transform a Libtorch Enum into a Torcher Device Type Enum
	 */
	[[nodiscard]]
	static FORCEINLINE constexpr ETorcherTensorDeviceType Cast(const c10::DeviceType DeviceType) noexcept
	{ return static_cast<ETorcherTensorDeviceType>(DeviceType); }
}

#undef LOCTEXT_NAMESPACE