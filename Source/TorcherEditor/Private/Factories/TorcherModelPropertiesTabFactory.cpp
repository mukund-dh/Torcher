// Fill out your copyright notice in the Description page of Project Settings.


#include "Factories/TorcherModelPropertiesTabFactory.h"
#include "TorcherGraph/TorcherModelGraph.h"
#include "PropertyEditorModule.h"


TorcherModelPropertiesTabFactory::TorcherModelPropertiesTabFactory(TSharedPtr<TorcherModelGraph> App)
	: FWorkflowTabFactory(FName("TorcherModelGraphPropertiesTab"), App)
{
	_app = App;
	TabLabel = FText::FromString("Properties");
	ViewMenuDescription = FText::FromString("View Menu Description");
	ViewMenuTooltip = FText::FromString("Show the properties view");
}

TSharedRef<SWidget> TorcherModelPropertiesTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
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

	TSharedPtr<IDetailsView> selectedNodeDetailsView = propertyEditorModule.CreateDetailView(detailsViewArgs);
	selectedNodeDetailsView->SetObject(nullptr);
	app->SetSelectedNodeDetailView(selectedNodeDetailsView);
	
	return SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				.HAlign(HAlign_Fill)
				[
					detailsView.ToSharedRef()
				]
				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				.HAlign(HAlign_Fill)
				[
					selectedNodeDetailsView.ToSharedRef()
				];
}

FText TorcherModelPropertiesTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString("The Properties View");
}
