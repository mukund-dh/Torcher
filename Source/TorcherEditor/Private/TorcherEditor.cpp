#include "TorcherEditor.h"
#include "IAssetTools.h"
#include "Models/TorcherModelAssetTypeActions.h"
#include "AssetToolsModule.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FTorcherEditorModule"

void FTorcherEditorModule::StartupModule()
{
	IAssetTools& AssetTools = IAssetTools::Get();
	EAssetTypeCategories::Type assetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Torcher")), FText::FromString("Torcher Models"));
	TSharedPtr<FTorcherModelAssetTypeActions> TorcherModelAssetTypeActions = MakeShared<FTorcherModelAssetTypeActions>(assetCategory);
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(TorcherModelAssetTypeActions.ToSharedRef());

	TorcherStyleSet = MakeShareable(new FSlateStyleSet(TEXT("TorcherEditorStyle")));
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin("Torcher");
	FString ContentDir = Plugin->GetContentDir();
	TorcherStyleSet->SetContentRoot(ContentDir);

	FSlateImageBrush* ThumbnailBrush = new FSlateImageBrush(TorcherStyleSet->RootToContentDir(TEXT("torcher_thumb"), TEXT(".png")), FVector2D(512, 512));
	FSlateImageBrush* IconBrush = new FSlateImageBrush(TorcherStyleSet->RootToContentDir(TEXT("torcher_icon"), TEXT(".png")), FVector2D(512, 512));

	TorcherStyleSet->Set(TEXT("ClassThumbnail.TorcherModelBase"), ThumbnailBrush);
	TorcherStyleSet->Set(TEXT("ClassIcon.TorcherModelBase"), IconBrush);
	FSlateStyleRegistry::RegisterSlateStyle(*TorcherStyleSet);
}

void FTorcherEditorModule::ShutdownModule()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*TorcherStyleSet);
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FTorcherEditorModule, TorcherEditor)