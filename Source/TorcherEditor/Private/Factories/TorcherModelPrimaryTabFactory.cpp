// Fill out your copyright notice in the Description page of Project Settings.


#include "Factories/TorcherModelPrimaryTabFactory.h"
#include "TorcherGraph/TorcherModelGraph.h"
#include "PropertyEditorModule.h"
#include "GraphEditor.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"

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
	return SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				.HAlign(HAlign_Fill)
				[
					SNew(SGraphEditor)
					.IsEditable(true)
					.GraphToEdit(app->GetWorkingGraph())
				];
}

FText TorcherModelPrimaryTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString("The Primary View");
}
