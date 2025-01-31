#include "TorcherEditor.h"
#include "IAssetTools.h"
#include "Models/TorcherModelAssetTypeActions.h"
#include "AssetToolsModule.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"
#include "EdGraphUtilities.h"
#include "KismetPins/SGraphPinColor.h"
#include "EdGraph/EdGraphPin.h"

#define LOCTEXT_NAMESPACE "FTorcherEditorModule"

class STorcherGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(STorcherGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}

protected:

	virtual FSlateColor GetPinColor() const override
	{
		return FLinearColor(0.2f, 1.0f, 0.2f);
	}
};

class STorcherGraphStartPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(STorcherGraphStartPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}

protected:

	virtual FSlateColor GetPinColor() const override
	{
		return FLinearColor(1.0f, 0.2f, 0.2f);
	}
};

struct FTorcherPinFactory : public FGraphPanelPinFactory
{
public:
	virtual ~FTorcherPinFactory() {}

	virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* Pin) const override
	{
		if (FName(TEXT("TorcherPin")) == Pin->PinType.PinSubCategory)
		{
			return SNew(STorcherGraphPin, Pin);
		} else if (FName(TEXT("TorcherStartPin")) == Pin->PinType.PinSubCategory)
		{
			return SNew(STorcherGraphStartPin, Pin);
		}

		return nullptr;
	}
};

void FTorcherEditorModule::StartupModule()
{
	IAssetTools& AssetTools = IAssetTools::Get();
	EAssetTypeCategories::Type assetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("TorcherModels")), FText::FromString("Torcher Models"));
	TSharedPtr<FTorcherModelAssetTypeActions> TorcherModelAssetTypeActions = MakeShared<FTorcherModelAssetTypeActions>(assetCategory);
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(TorcherModelAssetTypeActions.ToSharedRef());

	TorcherStyleSet = MakeShareable(new FSlateStyleSet(TEXT("TorcherEditorStyle")));
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin("Torcher");
	FString ContentDir = Plugin->GetContentDir();
	TorcherStyleSet->SetContentRoot(ContentDir);

	FSlateImageBrush* ThumbnailBrush = new FSlateImageBrush(TorcherStyleSet->RootToContentDir(TEXT("torcher_thumb"), TEXT(".png")), FVector2D(512, 512));
	FSlateImageBrush* IconBrush = new FSlateImageBrush(TorcherStyleSet->RootToContentDir(TEXT("torcher_icon"), TEXT(".png")), FVector2D(512, 512));

	FSlateImageBrush* AddNodeBrush = new FSlateImageBrush(TorcherStyleSet->RootToContentDir(TEXT("add_node_icon"), TEXT(".png")), FVector2D(512, 512));
	FSlateImageBrush* AddNodePinBrush = new FSlateImageBrush(TorcherStyleSet->RootToContentDir(TEXT("add_pin_icon"), TEXT(".png")), FVector2D(512, 512));
	FSlateImageBrush* DeleteNodePinBrush = new FSlateImageBrush(TorcherStyleSet->RootToContentDir(TEXT("delete_pin_icon"), TEXT(".png")), FVector2D(512, 512));
	FSlateImageBrush* DeleteNodeBrush = new FSlateImageBrush(TorcherStyleSet->RootToContentDir(TEXT("delete_node_icon"), TEXT(".png")), FVector2D(512, 512));

	TorcherStyleSet->Set(TEXT("ClassThumbnail.TorcherModelBase"), ThumbnailBrush);
	TorcherStyleSet->Set(TEXT("ClassIcon.TorcherModelBase"), IconBrush);

	TorcherStyleSet->Set(TEXT("TorcherGraph.AddNodeIcon"), AddNodeBrush);
	TorcherStyleSet->Set(TEXT("TorcherGraph.AddNodePinIcon"), AddNodePinBrush);
	TorcherStyleSet->Set(TEXT("TorcherGraph.DeleteNodePinIcon"), DeleteNodePinBrush);
	TorcherStyleSet->Set(TEXT("TorcherGraph.DeleteNodeIcon"), DeleteNodeBrush);
	
	FSlateStyleRegistry::RegisterSlateStyle(*TorcherStyleSet);

	PinFactory = MakeShareable(new FTorcherPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(PinFactory);
}

void FTorcherEditorModule::ShutdownModule()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*TorcherStyleSet);
	FEdGraphUtilities::UnregisterVisualPinFactory(PinFactory);
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FTorcherEditorModule, TorcherEditor)