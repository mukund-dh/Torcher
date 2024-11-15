// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeMore/MLP.h"
#include "MakeMore/MMTokenizer.h"

UMLP::UMLP(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Tokenizer = CreateDefaultSubobject<UMMTokenizer>("Tokenizer");
}

