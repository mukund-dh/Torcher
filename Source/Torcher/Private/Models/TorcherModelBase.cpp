// Fill out your copyright notice in the Description page of Project Settings.


#include "Models/TorcherModelBase.h"
#include "UObject/Package.h"
#include "UObject/ObjectSaveContext.h"

UTorcherModelBase::UTorcherModelBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UTorcherModelBase::PreSave(FObjectPreSaveContext SaveContext)
{
	if (_onPreSaveListener)
		_onPreSaveListener();
}
