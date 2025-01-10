#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Models/TorcherModelAssetTypeActions.h"

// static EAssetTypeCategories::Type Torcher_AssetCategory;

class FTorcherEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
private:
    TSharedPtr<FTorcherModelAssetTypeActions>TorcherModelAssetTypeActions;
};
