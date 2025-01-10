// Fill out your copyright notice in the Description page of Project Settings.


#include "TorcherGraph/TorcherModelGraphAppMode.h"
#include "TorcherGraph/TorcherModelGraph.h"
#include "Factories/TorcherModelPrimaryTabFactory.h"

TorcherModelGraphAppMode::TorcherModelGraphAppMode(TSharedPtr<TorcherModelGraph> App)
	: FApplicationMode(TEXT("TorcherModelGraphAppMode"))
{
	_app = App;
	_tabs.RegisterFactory(MakeShareable(new TorcherModelPrimaryTabFactory(App)));

	TabLayout = FTabManager::NewLayout("TorcherModelGraphAppModeV1")
	->AddArea(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split(
			FTabManager::NewStack()
			->AddTab(FName(TEXT("TorcherModelGraphPrimaryTab")), ETabState::OpenedTab)
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
