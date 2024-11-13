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
}

void UMMTokenizer::DoBigramLikelihoods(float& LogLikelihood, int32& Num)
{
	at::Tensor bgCounts = GetBigramCounts();
	at::Tensor Probabilities = GetProbabilitiesFromBigrams(bgCounts);
	GetLogLikelihood(Probabilities, LogLikelihood, Num);
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

at::Tensor UMMTokenizer::GetProbabilitiesFromBigrams(const at::Tensor& BigramCounts) const noexcept
{
	at::Tensor Probabilities = (BigramCounts.add(1)).to(at::kFloat);
	Probabilities /= Probabilities.sum(1, true);
	return Probabilities;
}

void UMMTokenizer::GetLogLikelihood(
	const at::Tensor& Probabilites,
	float& LogLikelihood, int32& Num,
	bool bNegate/* = true*/, bool bNormalize/* = true*/) const noexcept
{
	// Init these to 0.0 and 0
	LogLikelihood = 0.0f;
	Num = 0;

	for (FString Word : WordsList)
	{
		Word = "." + Word + ".";
		TArray<TCHAR> CharArr = Word.GetCharArray();
		for (int32 i = 0; i < CharArr.Num() - 1; i++)
		{
			int32 ix1 = bgl.getIndexOfChar(CharArr[i]);
			int32 ix2 = bgl.getIndexOfChar(CharArr[i + 1]);
			at::Tensor prob = Probabilites[ix1][ix2];
			at::Tensor log_prob = at::log(prob);
			LogLikelihood += log_prob.item<float>();
			Num += 1;
		}
	}

	if (bNegate)
		LogLikelihood = -1 * LogLikelihood;

	if (bNormalize)
		LogLikelihood = LogLikelihood / Num;
}
