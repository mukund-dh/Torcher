// Fill out your copyright notice in the Description page of Project Settings.


#include "Models/TorcherModelBase.h"
#include "UObject/Package.h"

const TArray<const UClass*>& UTorcherModelBase::GetLayerTypes() const
{
	LayerTypesConst.Empty(LayerTypes.Num());
	for (const TObjectPtr<const UClass> LayerType : LayerTypes)
	{
		LayerTypesConst.Add(DuplicateObject<const UClass>(LayerType, GetTransientPackage()));
	}
	return LayerTypesConst;
}

void UTorcherModelBase::execGetLayerTypes(UObject* Context, FFrame& Stack, void* const Z_Param__Result)
{
	P_FINISH

	P_NATIVE_BEGIN
	*static_cast<TArray<const UClass*>*>(Z_Param__Result) = P_THIS->LayerTypes;
	P_NATIVE_END
}
