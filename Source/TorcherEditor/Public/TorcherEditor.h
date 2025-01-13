#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Styling/SlateStyle.h"


class FTorcherEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
private:
    TSharedPtr<FSlateStyleSet> TorcherStyleSet = nullptr;
    TSharedPtr<struct FTorcherPinFactory> PinFactory = nullptr;
};
