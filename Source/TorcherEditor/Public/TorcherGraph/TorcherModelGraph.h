// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

/**
 * 
 */
class TorcherModelGraph : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook
{
public:
	// Tells parent class what tabs to spawn
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& tabManager) override;
	
	// Initialize
	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UObject* InObject);

private:
	class UTorcherModelBase* _workingAsset = nullptr;

public: // FAssetEditorToolkit interface
	virtual FName GetToolkitFName() const override { return FName(TEXT("TorcherGraphApp")); }
	virtual FText GetBaseToolkitName() const override { return FText::FromString("Torcher Graph App"); }
	virtual FString GetWorldCentricTabPrefix() const override { return TEXT("TorcherGraphApp"); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f); }
	virtual FString GetDocumentationLink() const override { return TEXT(""); }

	class UTorcherModelBase* GetWorkingAsset() { return _workingAsset; }
	
	virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override { }
	virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override { }
};
