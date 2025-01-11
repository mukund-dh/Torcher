// Fill out your copyright notice in the Description page of Project Settings.


#include "Factories/TorcherModelPrimaryTabFactory.h"
#include "TorcherGraph/TorcherModelGraph.h"
// #include "Models/TorcherModelBase.h"
#include "PropertyEditorModule.h"


TorcherModelPrimaryTabFactory::TorcherModelPrimaryTabFactory(TSharedPtr<TorcherModelGraph> App)
	: FWorkflowTabFactory(FName("TorcherModelGraphPrimaryTab"), App)
{
	_app = App;
	TabLabel = FText::FromString("Primary");
	ViewMenuDescription = FText::FromString("View Menu Description");
	ViewMenuTooltip = FText::FromString("Show the primary view");
}

TSharedRef<SWidget> TorcherModelPrimaryTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	TSharedPtr<TorcherModelGraph> app = _app.Pin();
	FPropertyEditorModule& propertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));

	FDetailsViewArgs detailsViewArgs;
	{
		detailsViewArgs.bAllowSearch = false;
		detailsViewArgs.bHideSelectionTip = true;
		detailsViewArgs.bLockable = false;
		detailsViewArgs.bSearchInitialKeyFocus = true;
		detailsViewArgs.bUpdatesFromSelection = false;
		detailsViewArgs.NotifyHook = nullptr;
		detailsViewArgs.bShowOptions = true;
		detailsViewArgs.bShowModifiedPropertiesOption = false;
		detailsViewArgs.bShowScrollBar = false;
	}

	TSharedPtr<IDetailsView> detailsView = propertyEditorModule.CreateDetailView(detailsViewArgs);
	detailsView->SetObject(app->GetWorkingAsset());
	return SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				.HAlign(HAlign_Fill)
				[
					detailsView.ToSharedRef()
				];
}

FText TorcherModelPrimaryTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString("The Primary View");
}
