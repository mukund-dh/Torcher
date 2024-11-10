// Fill out your copyright notice in the Description page of Project Settings.


#include "MakeMore/MMTokenizer.h"
#include "Misc/FileHelper.h"

TORCH_INCLUDES_START
#include "torch/csrc/autograd/generated/variable_factories.h"
TORCH_INCLUDES_END

bigramLookups UMMTokenizer::bgl;

UMMTokenizer::UMMTokenizer() : FilePath("")
{
}


void UMMTokenizer::GetWordsList()
{
	FString FileContent;
	if (FFileHelper::LoadFileToString(FileContent, *FilePath))
	{
		FileContent.ParseIntoArrayLines(WordsList);		
	}

	at::Tensor bgCounts = GetBigramCounts();
	UE_LOG(LogTemp, Warning, TEXT("The bigram value at 4,5 is %d"), bgCounts[4][5].item<int32>());
}

at::Tensor UMMTokenizer::GetBigramCounts() const noexcept
{
	auto opt = at::TensorOptions().dtype(at::ScalarType::Int);
	
	at::Tensor CountTensor = torch::zeros({27, 27}, opt);

	for (FString Word : WordsList)
	{
		Word = "." + Word + ".";
		TArray<TCHAR> CharArr = Word.GetCharArray();

		for (size_t i = 0; i < CharArr.Num() - 1; ++i)
		{
			TCHAR ch1 = CharArr[i];
			TCHAR ch2 = CharArr[i + 1];
			int32 ix1 = bgl.getIndexOfChar(ch1);
			int32 ix2 = bgl.getIndexOfChar(ch2);
			CountTensor[ix1][ix2] += 1;
		}
	}
	
	return CountTensor;
}
