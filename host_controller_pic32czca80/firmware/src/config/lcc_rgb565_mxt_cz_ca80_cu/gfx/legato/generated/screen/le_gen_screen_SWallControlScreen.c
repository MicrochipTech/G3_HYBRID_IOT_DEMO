#include "gfx/legato/generated/screen/le_gen_screen_SWallControlScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* SWallControlScreen_Panel_0;
leWidget* SWallControlScreen_PanelWidget0;
leLineWidget* SWallControlScreen_LineWidget0;
leImageWidget* SWallControlScreen_ImageWidget0;
leLabelWidget* SWallControlScreen_LabelWidget_0;
leButtonWidget* SWallControlScreen_DeviceAButton;
leLabelWidget* SWallControlScreen_SolarInverterStatusLabel;
leLabelWidget* SWallControlScreen_SolarInverterStatusLabel_0;
leLabelWidget* SWallControlScreen_BatteryChargerStatusLabel;
leLabelWidget* SWallControlScreen_LeakDetectorStatusLabel;
leLabelWidget* SWallControlScreen_EnergyStorageStatusLabel;
leLabelWidget* SWallControlScreen_HeatPumpStatusLabel;
leLabelWidget* SWallControlScreen_EVChargerStatusLabel;
leProgressBarWidget* SWallControlScreen_EVChargerProgressBarWidget;
leProgressBarWidget* SWallControlScreen_StorageProgressBarWidget;
leProgressBarWidget* SWallControlScreen_BatteryProgressBarWidget;
leButtonWidget* SWallControlScreen_BatteryChargerRefreshButtonWidget;
leButtonWidget* SWallControlScreen_EnergyStorageRefreshButtonWidget;
leButtonWidget* SWallControlScreen_EVChargerRefreshButtonWidget;
leButtonWidget* SWallControlScreen_SolarInverterRefreshButtonWidget;
leButtonWidget* SWallControlScreen_LeakDetectorRefreshButtonWidget;
leButtonWidget* SWallControlScreen_HeatPumpRefreshButtonWidget;
leTextFieldWidget* SWallControlScreen_SolarInverterTextFieldWidget;
leTextFieldWidget* SWallControlScreen_LeakDetectorTextFieldWidget;
leTextFieldWidget* SWallControlScreen_HeatPumpTextFieldWidget;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_SWallControlScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_SWallControlScreen(void)
{
    if(showing == LE_TRUE)
        return LE_FAILURE;

    // layer 0
    root0 = leWidget_New();
    root0->fn->setSize(root0, LE_DEFAULT_SCREEN_WIDTH, LE_DEFAULT_SCREEN_HEIGHT);
    root0->fn->setBackgroundType(root0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->setMargins(root0, 0, 0, 0, 0);
    root0->flags |= LE_WIDGET_IGNOREEVENTS;
    root0->flags |= LE_WIDGET_IGNOREPICK;

    SWallControlScreen_Panel_0 = leWidget_New();
    SWallControlScreen_Panel_0->fn->setPosition(SWallControlScreen_Panel_0, 0, 0);
    SWallControlScreen_Panel_0->fn->setSize(SWallControlScreen_Panel_0, 800, 480);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_Panel_0);

    SWallControlScreen_PanelWidget0 = leWidget_New();
    SWallControlScreen_PanelWidget0->fn->setPosition(SWallControlScreen_PanelWidget0, 1, 1);
    SWallControlScreen_PanelWidget0->fn->setSize(SWallControlScreen_PanelWidget0, 800, 480);
    SWallControlScreen_PanelWidget0->fn->setScheme(SWallControlScreen_PanelWidget0, &BackScheme);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_PanelWidget0);

    SWallControlScreen_LineWidget0 = leLineWidget_New();
    SWallControlScreen_LineWidget0->fn->setPosition(SWallControlScreen_LineWidget0, 97, 25);
    SWallControlScreen_LineWidget0->fn->setSize(SWallControlScreen_LineWidget0, 700, 15);
    SWallControlScreen_LineWidget0->fn->setScheme(SWallControlScreen_LineWidget0, &WhiteScheme);
    SWallControlScreen_LineWidget0->fn->setBackgroundType(SWallControlScreen_LineWidget0, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_LineWidget0->fn->setStartPoint(SWallControlScreen_LineWidget0, 0, 5);
    SWallControlScreen_LineWidget0->fn->setEndPoint(SWallControlScreen_LineWidget0, 700, 5);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_LineWidget0);

    SWallControlScreen_ImageWidget0 = leImageWidget_New();
    SWallControlScreen_ImageWidget0->fn->setPosition(SWallControlScreen_ImageWidget0, 10, 10);
    SWallControlScreen_ImageWidget0->fn->setSize(SWallControlScreen_ImageWidget0, 100, 40);
    SWallControlScreen_ImageWidget0->fn->setBackgroundType(SWallControlScreen_ImageWidget0, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_ImageWidget0->fn->setBorderType(SWallControlScreen_ImageWidget0, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_ImageWidget0->fn->setImage(SWallControlScreen_ImageWidget0, (leImage*)&MchpLogo_100);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_ImageWidget0);

    SWallControlScreen_LabelWidget_0 = leLabelWidget_New();
    SWallControlScreen_LabelWidget_0->fn->setPosition(SWallControlScreen_LabelWidget_0, 410, 2);
    SWallControlScreen_LabelWidget_0->fn->setSize(SWallControlScreen_LabelWidget_0, 380, 25);
    SWallControlScreen_LabelWidget_0->fn->setScheme(SWallControlScreen_LabelWidget_0, &TextScheme);
    SWallControlScreen_LabelWidget_0->fn->setHAlignment(SWallControlScreen_LabelWidget_0, LE_HALIGN_CENTER);
    SWallControlScreen_LabelWidget_0->fn->setString(SWallControlScreen_LabelWidget_0, (leString*)&string_DemoName);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_LabelWidget_0);

    SWallControlScreen_DeviceAButton = leButtonWidget_New();
    SWallControlScreen_DeviceAButton->fn->setPosition(SWallControlScreen_DeviceAButton, 440, 120);
    SWallControlScreen_DeviceAButton->fn->setSize(SWallControlScreen_DeviceAButton, 65, 65);
    SWallControlScreen_DeviceAButton->fn->setBackgroundType(SWallControlScreen_DeviceAButton, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_DeviceAButton->fn->setBorderType(SWallControlScreen_DeviceAButton, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_DeviceAButton->fn->setPressedOffset(SWallControlScreen_DeviceAButton, 0);
    SWallControlScreen_DeviceAButton->fn->setPressedEventCallback(SWallControlScreen_DeviceAButton, NULL /*event_SWallControlScreen_DeviceAButton_OnPressed*/);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_DeviceAButton);

    SWallControlScreen_SolarInverterStatusLabel = leLabelWidget_New();
    SWallControlScreen_SolarInverterStatusLabel->fn->setPosition(SWallControlScreen_SolarInverterStatusLabel, 63, 97);
    SWallControlScreen_SolarInverterStatusLabel->fn->setSize(SWallControlScreen_SolarInverterStatusLabel, 154, 36);
    SWallControlScreen_SolarInverterStatusLabel->fn->setScheme(SWallControlScreen_SolarInverterStatusLabel, &TextScheme);
    SWallControlScreen_SolarInverterStatusLabel->fn->setBackgroundType(SWallControlScreen_SolarInverterStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_SolarInverterStatusLabel->fn->setHAlignment(SWallControlScreen_SolarInverterStatusLabel, LE_HALIGN_CENTER);
    SWallControlScreen_SolarInverterStatusLabel->fn->setString(SWallControlScreen_SolarInverterStatusLabel, (leString*)&string_SolarInvertedLabel);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_SolarInverterStatusLabel);

    SWallControlScreen_SolarInverterStatusLabel_0 = leLabelWidget_New();
    SWallControlScreen_SolarInverterStatusLabel_0->fn->setPosition(SWallControlScreen_SolarInverterStatusLabel_0, 63, 97);
    SWallControlScreen_SolarInverterStatusLabel_0->fn->setSize(SWallControlScreen_SolarInverterStatusLabel_0, 154, 36);
    SWallControlScreen_SolarInverterStatusLabel_0->fn->setScheme(SWallControlScreen_SolarInverterStatusLabel_0, &TextScheme);
    SWallControlScreen_SolarInverterStatusLabel_0->fn->setBackgroundType(SWallControlScreen_SolarInverterStatusLabel_0, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_SolarInverterStatusLabel_0->fn->setHAlignment(SWallControlScreen_SolarInverterStatusLabel_0, LE_HALIGN_CENTER);
    SWallControlScreen_SolarInverterStatusLabel_0->fn->setString(SWallControlScreen_SolarInverterStatusLabel_0, (leString*)&string_SolarInvertedLabel);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_SolarInverterStatusLabel_0);

    SWallControlScreen_BatteryChargerStatusLabel = leLabelWidget_New();
    SWallControlScreen_BatteryChargerStatusLabel->fn->setPosition(SWallControlScreen_BatteryChargerStatusLabel, 72, 269);
    SWallControlScreen_BatteryChargerStatusLabel->fn->setSize(SWallControlScreen_BatteryChargerStatusLabel, 154, 28);
    SWallControlScreen_BatteryChargerStatusLabel->fn->setScheme(SWallControlScreen_BatteryChargerStatusLabel, &TextScheme);
    SWallControlScreen_BatteryChargerStatusLabel->fn->setBackgroundType(SWallControlScreen_BatteryChargerStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_BatteryChargerStatusLabel->fn->setHAlignment(SWallControlScreen_BatteryChargerStatusLabel, LE_HALIGN_CENTER);
    SWallControlScreen_BatteryChargerStatusLabel->fn->setString(SWallControlScreen_BatteryChargerStatusLabel, (leString*)&string_BatteryChargerString);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_BatteryChargerStatusLabel);

    SWallControlScreen_LeakDetectorStatusLabel = leLabelWidget_New();
    SWallControlScreen_LeakDetectorStatusLabel->fn->setPosition(SWallControlScreen_LeakDetectorStatusLabel, 286, 100);
    SWallControlScreen_LeakDetectorStatusLabel->fn->setSize(SWallControlScreen_LeakDetectorStatusLabel, 154, 28);
    SWallControlScreen_LeakDetectorStatusLabel->fn->setScheme(SWallControlScreen_LeakDetectorStatusLabel, &TextScheme);
    SWallControlScreen_LeakDetectorStatusLabel->fn->setBackgroundType(SWallControlScreen_LeakDetectorStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_LeakDetectorStatusLabel->fn->setHAlignment(SWallControlScreen_LeakDetectorStatusLabel, LE_HALIGN_CENTER);
    SWallControlScreen_LeakDetectorStatusLabel->fn->setString(SWallControlScreen_LeakDetectorStatusLabel, (leString*)&string_LeakDetectorString);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_LeakDetectorStatusLabel);

    SWallControlScreen_EnergyStorageStatusLabel = leLabelWidget_New();
    SWallControlScreen_EnergyStorageStatusLabel->fn->setPosition(SWallControlScreen_EnergyStorageStatusLabel, 291, 271);
    SWallControlScreen_EnergyStorageStatusLabel->fn->setSize(SWallControlScreen_EnergyStorageStatusLabel, 154, 28);
    SWallControlScreen_EnergyStorageStatusLabel->fn->setScheme(SWallControlScreen_EnergyStorageStatusLabel, &TextScheme);
    SWallControlScreen_EnergyStorageStatusLabel->fn->setBackgroundType(SWallControlScreen_EnergyStorageStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_EnergyStorageStatusLabel->fn->setHAlignment(SWallControlScreen_EnergyStorageStatusLabel, LE_HALIGN_CENTER);
    SWallControlScreen_EnergyStorageStatusLabel->fn->setString(SWallControlScreen_EnergyStorageStatusLabel, (leString*)&string_EnergyStorageString);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_EnergyStorageStatusLabel);

    SWallControlScreen_HeatPumpStatusLabel = leLabelWidget_New();
    SWallControlScreen_HeatPumpStatusLabel->fn->setPosition(SWallControlScreen_HeatPumpStatusLabel, 523, 101);
    SWallControlScreen_HeatPumpStatusLabel->fn->setSize(SWallControlScreen_HeatPumpStatusLabel, 154, 28);
    SWallControlScreen_HeatPumpStatusLabel->fn->setScheme(SWallControlScreen_HeatPumpStatusLabel, &TextScheme);
    SWallControlScreen_HeatPumpStatusLabel->fn->setBackgroundType(SWallControlScreen_HeatPumpStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_HeatPumpStatusLabel->fn->setHAlignment(SWallControlScreen_HeatPumpStatusLabel, LE_HALIGN_CENTER);
    SWallControlScreen_HeatPumpStatusLabel->fn->setString(SWallControlScreen_HeatPumpStatusLabel, (leString*)&string_HeatPumpString);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_HeatPumpStatusLabel);

    SWallControlScreen_EVChargerStatusLabel = leLabelWidget_New();
    SWallControlScreen_EVChargerStatusLabel->fn->setPosition(SWallControlScreen_EVChargerStatusLabel, 521, 274);
    SWallControlScreen_EVChargerStatusLabel->fn->setSize(SWallControlScreen_EVChargerStatusLabel, 154, 28);
    SWallControlScreen_EVChargerStatusLabel->fn->setScheme(SWallControlScreen_EVChargerStatusLabel, &TextScheme);
    SWallControlScreen_EVChargerStatusLabel->fn->setBackgroundType(SWallControlScreen_EVChargerStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_EVChargerStatusLabel->fn->setHAlignment(SWallControlScreen_EVChargerStatusLabel, LE_HALIGN_CENTER);
    SWallControlScreen_EVChargerStatusLabel->fn->setString(SWallControlScreen_EVChargerStatusLabel, (leString*)&string_EVChargerString);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_EVChargerStatusLabel);

    SWallControlScreen_EVChargerProgressBarWidget = leProgressBarWidget_New();
    SWallControlScreen_EVChargerProgressBarWidget->fn->setPosition(SWallControlScreen_EVChargerProgressBarWidget, 550, 326);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_EVChargerProgressBarWidget);

    SWallControlScreen_StorageProgressBarWidget = leProgressBarWidget_New();
    SWallControlScreen_StorageProgressBarWidget->fn->setPosition(SWallControlScreen_StorageProgressBarWidget, 319, 329);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_StorageProgressBarWidget);

    SWallControlScreen_BatteryProgressBarWidget = leProgressBarWidget_New();
    SWallControlScreen_BatteryProgressBarWidget->fn->setPosition(SWallControlScreen_BatteryProgressBarWidget, 103, 331);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_BatteryProgressBarWidget);

    SWallControlScreen_BatteryChargerRefreshButtonWidget = leButtonWidget_New();
    SWallControlScreen_BatteryChargerRefreshButtonWidget->fn->setPosition(SWallControlScreen_BatteryChargerRefreshButtonWidget, 137, 381);
    SWallControlScreen_BatteryChargerRefreshButtonWidget->fn->setSize(SWallControlScreen_BatteryChargerRefreshButtonWidget, 37, 38);
    SWallControlScreen_BatteryChargerRefreshButtonWidget->fn->setReleasedImage(SWallControlScreen_BatteryChargerRefreshButtonWidget, (leImage*)&Scan40);
    SWallControlScreen_BatteryChargerRefreshButtonWidget->fn->setPressedEventCallback(SWallControlScreen_BatteryChargerRefreshButtonWidget, event_SWallControlScreen_BatteryChargerRefreshButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_BatteryChargerRefreshButtonWidget);

    SWallControlScreen_EnergyStorageRefreshButtonWidget = leButtonWidget_New();
    SWallControlScreen_EnergyStorageRefreshButtonWidget->fn->setPosition(SWallControlScreen_EnergyStorageRefreshButtonWidget, 356, 385);
    SWallControlScreen_EnergyStorageRefreshButtonWidget->fn->setSize(SWallControlScreen_EnergyStorageRefreshButtonWidget, 37, 38);
    SWallControlScreen_EnergyStorageRefreshButtonWidget->fn->setReleasedImage(SWallControlScreen_EnergyStorageRefreshButtonWidget, (leImage*)&Scan40);
    SWallControlScreen_EnergyStorageRefreshButtonWidget->fn->setPressedEventCallback(SWallControlScreen_EnergyStorageRefreshButtonWidget, event_SWallControlScreen_EnergyStorageRefreshButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_EnergyStorageRefreshButtonWidget);

    SWallControlScreen_EVChargerRefreshButtonWidget = leButtonWidget_New();
    SWallControlScreen_EVChargerRefreshButtonWidget->fn->setPosition(SWallControlScreen_EVChargerRefreshButtonWidget, 591, 382);
    SWallControlScreen_EVChargerRefreshButtonWidget->fn->setSize(SWallControlScreen_EVChargerRefreshButtonWidget, 37, 38);
    SWallControlScreen_EVChargerRefreshButtonWidget->fn->setReleasedImage(SWallControlScreen_EVChargerRefreshButtonWidget, (leImage*)&Scan40);
    SWallControlScreen_EVChargerRefreshButtonWidget->fn->setPressedEventCallback(SWallControlScreen_EVChargerRefreshButtonWidget, event_SWallControlScreen_EVChargerRefreshButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_EVChargerRefreshButtonWidget);

    SWallControlScreen_SolarInverterRefreshButtonWidget = leButtonWidget_New();
    SWallControlScreen_SolarInverterRefreshButtonWidget->fn->setPosition(SWallControlScreen_SolarInverterRefreshButtonWidget, 132, 196);
    SWallControlScreen_SolarInverterRefreshButtonWidget->fn->setSize(SWallControlScreen_SolarInverterRefreshButtonWidget, 41, 41);
    SWallControlScreen_SolarInverterRefreshButtonWidget->fn->setReleasedImage(SWallControlScreen_SolarInverterRefreshButtonWidget, (leImage*)&Scan40);
    SWallControlScreen_SolarInverterRefreshButtonWidget->fn->setPressedEventCallback(SWallControlScreen_SolarInverterRefreshButtonWidget, event_SWallControlScreen_SolarInverterRefreshButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_SolarInverterRefreshButtonWidget);

    SWallControlScreen_LeakDetectorRefreshButtonWidget = leButtonWidget_New();
    SWallControlScreen_LeakDetectorRefreshButtonWidget->fn->setPosition(SWallControlScreen_LeakDetectorRefreshButtonWidget, 350, 198);
    SWallControlScreen_LeakDetectorRefreshButtonWidget->fn->setSize(SWallControlScreen_LeakDetectorRefreshButtonWidget, 37, 38);
    SWallControlScreen_LeakDetectorRefreshButtonWidget->fn->setReleasedImage(SWallControlScreen_LeakDetectorRefreshButtonWidget, (leImage*)&Scan40);
    SWallControlScreen_LeakDetectorRefreshButtonWidget->fn->setPressedEventCallback(SWallControlScreen_LeakDetectorRefreshButtonWidget, event_SWallControlScreen_LeakDetectorRefreshButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_LeakDetectorRefreshButtonWidget);

    SWallControlScreen_HeatPumpRefreshButtonWidget = leButtonWidget_New();
    SWallControlScreen_HeatPumpRefreshButtonWidget->fn->setPosition(SWallControlScreen_HeatPumpRefreshButtonWidget, 588, 200);
    SWallControlScreen_HeatPumpRefreshButtonWidget->fn->setSize(SWallControlScreen_HeatPumpRefreshButtonWidget, 37, 38);
    SWallControlScreen_HeatPumpRefreshButtonWidget->fn->setReleasedImage(SWallControlScreen_HeatPumpRefreshButtonWidget, (leImage*)&Scan40);
    SWallControlScreen_HeatPumpRefreshButtonWidget->fn->setPressedEventCallback(SWallControlScreen_HeatPumpRefreshButtonWidget, event_SWallControlScreen_HeatPumpRefreshButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_HeatPumpRefreshButtonWidget);

    SWallControlScreen_SolarInverterTextFieldWidget = leTextFieldWidget_New();
    SWallControlScreen_SolarInverterTextFieldWidget->fn->setPosition(SWallControlScreen_SolarInverterTextFieldWidget, 101, 153);
    SWallControlScreen_SolarInverterTextFieldWidget->fn->setHAlignment(SWallControlScreen_SolarInverterTextFieldWidget, LE_HALIGN_LEFT);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_SolarInverterTextFieldWidget);

    SWallControlScreen_LeakDetectorTextFieldWidget = leTextFieldWidget_New();
    SWallControlScreen_LeakDetectorTextFieldWidget->fn->setPosition(SWallControlScreen_LeakDetectorTextFieldWidget, 320, 156);
    SWallControlScreen_LeakDetectorTextFieldWidget->fn->setHAlignment(SWallControlScreen_LeakDetectorTextFieldWidget, LE_HALIGN_LEFT);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_LeakDetectorTextFieldWidget);

    SWallControlScreen_HeatPumpTextFieldWidget = leTextFieldWidget_New();
    SWallControlScreen_HeatPumpTextFieldWidget->fn->setPosition(SWallControlScreen_HeatPumpTextFieldWidget, 554, 157);
    SWallControlScreen_HeatPumpTextFieldWidget->fn->setHAlignment(SWallControlScreen_HeatPumpTextFieldWidget, LE_HALIGN_LEFT);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_HeatPumpTextFieldWidget);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_SWallControlScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_SWallControlScreen(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    SWallControlScreen_Panel_0 = NULL;
    SWallControlScreen_PanelWidget0 = NULL;
    SWallControlScreen_LineWidget0 = NULL;
    SWallControlScreen_ImageWidget0 = NULL;
    SWallControlScreen_LabelWidget_0 = NULL;
    SWallControlScreen_DeviceAButton = NULL;
    SWallControlScreen_SolarInverterStatusLabel = NULL;
    SWallControlScreen_SolarInverterStatusLabel_0 = NULL;
    SWallControlScreen_BatteryChargerStatusLabel = NULL;
    SWallControlScreen_LeakDetectorStatusLabel = NULL;
    SWallControlScreen_EnergyStorageStatusLabel = NULL;
    SWallControlScreen_HeatPumpStatusLabel = NULL;
    SWallControlScreen_EVChargerStatusLabel = NULL;
    SWallControlScreen_EVChargerProgressBarWidget = NULL;
    SWallControlScreen_StorageProgressBarWidget = NULL;
    SWallControlScreen_BatteryProgressBarWidget = NULL;
    SWallControlScreen_BatteryChargerRefreshButtonWidget = NULL;
    SWallControlScreen_EnergyStorageRefreshButtonWidget = NULL;
    SWallControlScreen_EVChargerRefreshButtonWidget = NULL;
    SWallControlScreen_SolarInverterRefreshButtonWidget = NULL;
    SWallControlScreen_LeakDetectorRefreshButtonWidget = NULL;
    SWallControlScreen_HeatPumpRefreshButtonWidget = NULL;
    SWallControlScreen_SolarInverterTextFieldWidget = NULL;
    SWallControlScreen_LeakDetectorTextFieldWidget = NULL;
    SWallControlScreen_HeatPumpTextFieldWidget = NULL;


    showing = LE_FALSE;
}

void screenDestroy_SWallControlScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_SWallControlScreen(uint32_t lyrIdx)
{
    if(lyrIdx >= LE_LAYER_COUNT)
        return NULL;

    switch(lyrIdx)
    {
        case 0:
        {
            return root0;
        }
        default:
        {
            return NULL;
        }
    }
}

