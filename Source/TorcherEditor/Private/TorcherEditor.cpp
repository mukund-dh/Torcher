#include "TorcherEditor.h"
#include "IAssetTools.h"

#define LOCTEXT_NAMESPACE "FTorcherEditorModule"

void FTorcherEditorModule::StartupModule()
{
	IAssetTools& AssetTools = IAssetTools::Get();
	EAssetTypeCategories::Type assetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Torcher")), FText::FromString("Torcher Models"));
	TorcherModelAssetTypeActions = MakeShared<FTorcherModelAssetTypeActions>(assetCategory);
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(TorcherModelAssetTypeActions.ToSharedRef());
}

void FTorcherEditorModule::ShutdownModule()
{
	if (!FModuleManager::Get().IsModuleLoaded("AssetTools")) return;
	FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(TorcherModelAssetTypeActions.ToSharedRef());
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FTorcherEditorModule, TorcherEditor)