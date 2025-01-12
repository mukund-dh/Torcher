// Fill out your copyright notice in the Description page of Project Settings.


#include "TorcherGraph/TorcherModelGraphAppMode.h"
#include "TorcherGraph/TorcherModelGraph.h"
#include "Factories/TorcherModelPrimaryTabFactory.h"
#include "Factories/TorcherModelPropertiesTabFactory.h"

TorcherModelGraphAppMode::TorcherModelGraphAppMode(TSharedPtr<TorcherModelGraph> App)
	: FApplicationMode(TEXT("TorcherModelGraphAppMode"))
{
	_app = App;
	_tabs.RegisterFactory(MakeShareable(new TorcherModelPrimaryTabFactory(App)));
	_tabs.RegisterFactory(MakeShareable(new TorcherModelPropertiesTabFactory(App)));

	TabLayout = FTabManager::NewLayout("TorcherModelGraphAppModeV1")
	->AddArea(
		FTabManager::NewPrimaryArea()
		->SetOrientation(Orient_Vertical)
		->Split(
			FTabManager::NewSplitter()
			->SetOrientation(Orient_Horizontal)
			->Split(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.75)
				->AddTab(FName(TEXT("TorcherModelGraphPrimaryTab")), ETabState::OpenedTab)
			)
			->Split(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.25)
				->AddTab(FName(TEXT("TorcherModelGraphPropertiesTab")), ETabState::OpenedTab)
			)
		)
	);
}

void TorcherModelGraphAppMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	TSharedPtr<TorcherModelGraph> app = _app.Pin();
	app->PushTabFactories(_tabs);
	FApplicationMode::RegisterTabFactories(InTabManager);
}

void TorcherModelGraphAppMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();
}

void TorcherModelGraphAppMode::PostActivateMode()
{
	FApplicationMode::PostActivateMode();
}
