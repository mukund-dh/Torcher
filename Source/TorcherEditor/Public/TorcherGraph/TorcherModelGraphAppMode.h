// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

/**
 * 
 */
class TorcherModelGraphAppMode : public FApplicationMode
{
public:
	TorcherModelGraphAppMode(TSharedPtr<class TorcherModelGraph> App);

	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;

private:
	TWeakPtr<class TorcherModelGraph> _app;
	FWorkflowAllowedTabSet _tabs;
};
