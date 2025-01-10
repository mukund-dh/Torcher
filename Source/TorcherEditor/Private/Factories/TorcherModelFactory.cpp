// Fill out your copyright notice in the Description page of Project Settings.


#include "Factories/TorcherModelFactory.h"
#include "Models/TorcherModelBase.h"


UTorcherModelFactory::UTorcherModelFactory()
{
	SupportedClass = UTorcherModelBase::StaticClass();
	bCreateNew = true;
}

UObject* UTorcherModelFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UTorcherModelBase>(InParent, InClass, InName, Flags);
}

