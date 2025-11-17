#include "gfx/legato/generated/screen/le_gen_screen_SWallControlScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* SWallControlScreen_Panel_0;
leWidget* SWallControlScreen_PanelWidget0;
leLineWidget* SWallControlScreen_LineWidget0;
leImageWidget* SWallControlScreen_ImageMicrochipWidget;
leLabelWidget* SWallControlScreen_LabelSustainabilityWall;
leLabelWidget* SWallControlScreen_SolarInverterStatusLabel;
leLabelWidget* SWallControlScreen_BatteryChargerStatusLabel;
leLabelWidget* SWallControlScreen_LiquidDetectionStatusLabel;
leLabelWidget* SWallControlScreen_EnergyStorageStatusLabel;
leLabelWidget* SWallControlScreen_HeatPumpStatusLabel;
leLabelWidget* SWallControlScreen_EVChargerStatusLabel;
leButtonWidget* SWallControlScreen_BatteryChargerRefreshButtonWidget;
leButtonWidget* SWallControlScreen_EnergyStorageRefreshButtonWidget;
leButtonWidget* SWallControlScreen_EVChargerRefreshButtonWidget;
leButtonWidget* SWallControlScreen_SolarInverterRefreshButtonWidget;
leButtonWidget* SWallControlScreen_LiquidDetectionRefreshButtonWidget;
leButtonWidget* SWallControlScreen_HeatPumpRefreshButtonWidget;
leLabelWidget* SWallControlScreen_ElectricityMeterStatusLabel;
leButtonWidget* SWallControlScreen_ElectricityMeterRefreshButtonWidget;
leButtonWidget* SWallControlScreen_NextSWButtonWidget;
leLabelWidget* SWallControlScreen_NextSWStatusLabel;
leImageWidget* SWallControlScreen_SolarInverterConnIcon;
leImageWidget* SWallControlScreen_LiquidDetectionConnIcon;
leImageWidget* SWallControlScreen_HeatPumpConnIcon;
leImageWidget* SWallControlScreen_ElectricityMeterConnIcon;
leImageWidget* SWallControlScreen_BatteryChargerConnIcon;
leImageWidget* SWallControlScreen_EnergyStorageConnIcon;
leImageWidget* SWallControlScreen_EVChargerConnIcon;
leImageWidget* SWallControlScreen_WifiWidget;
leImageWidget* SWallControlScreen_CloudWidget;
leImageWidget* SWallControlScreen_G3Widget;
leImageWidget* SWallControlScreen_AlarmWidget;

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
    SWallControlScreen_PanelWidget0->fn->setPosition(SWallControlScreen_PanelWidget0, 0, 0);
    SWallControlScreen_PanelWidget0->fn->setSize(SWallControlScreen_PanelWidget0, 800, 480);
    SWallControlScreen_PanelWidget0->fn->setScheme(SWallControlScreen_PanelWidget0, &BackScheme);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_PanelWidget0);

    SWallControlScreen_LineWidget0 = leLineWidget_New();
    SWallControlScreen_LineWidget0->fn->setPosition(SWallControlScreen_LineWidget0, 97, 53);
    SWallControlScreen_LineWidget0->fn->setSize(SWallControlScreen_LineWidget0, 700, 15);
    SWallControlScreen_LineWidget0->fn->setScheme(SWallControlScreen_LineWidget0, &WhiteScheme);
    SWallControlScreen_LineWidget0->fn->setBackgroundType(SWallControlScreen_LineWidget0, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_LineWidget0->fn->setStartPoint(SWallControlScreen_LineWidget0, 0, 5);
    SWallControlScreen_LineWidget0->fn->setEndPoint(SWallControlScreen_LineWidget0, 700, 5);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_LineWidget0);

    SWallControlScreen_ImageMicrochipWidget = leImageWidget_New();
    SWallControlScreen_ImageMicrochipWidget->fn->setPosition(SWallControlScreen_ImageMicrochipWidget, 12, 38);
    SWallControlScreen_ImageMicrochipWidget->fn->setSize(SWallControlScreen_ImageMicrochipWidget, 100, 40);
    SWallControlScreen_ImageMicrochipWidget->fn->setBackgroundType(SWallControlScreen_ImageMicrochipWidget, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_ImageMicrochipWidget->fn->setBorderType(SWallControlScreen_ImageMicrochipWidget, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_ImageMicrochipWidget->fn->setImage(SWallControlScreen_ImageMicrochipWidget, (leImage*)&MchpLogo_100);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_ImageMicrochipWidget);

    SWallControlScreen_LabelSustainabilityWall = leLabelWidget_New();
    SWallControlScreen_LabelSustainabilityWall->fn->setPosition(SWallControlScreen_LabelSustainabilityWall, 288, 14);
    SWallControlScreen_LabelSustainabilityWall->fn->setSize(SWallControlScreen_LabelSustainabilityWall, 238, 25);
    SWallControlScreen_LabelSustainabilityWall->fn->setScheme(SWallControlScreen_LabelSustainabilityWall, &TextScheme);
    SWallControlScreen_LabelSustainabilityWall->fn->setHAlignment(SWallControlScreen_LabelSustainabilityWall, LE_HALIGN_CENTER);
    SWallControlScreen_LabelSustainabilityWall->fn->setString(SWallControlScreen_LabelSustainabilityWall, (leString*)&string_SWallConnectionStatus);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_LabelSustainabilityWall);

    SWallControlScreen_SolarInverterStatusLabel = leLabelWidget_New();
    SWallControlScreen_SolarInverterStatusLabel->fn->setPosition(SWallControlScreen_SolarInverterStatusLabel, 51, 69);
    SWallControlScreen_SolarInverterStatusLabel->fn->setSize(SWallControlScreen_SolarInverterStatusLabel, 154, 53);
    SWallControlScreen_SolarInverterStatusLabel->fn->setScheme(SWallControlScreen_SolarInverterStatusLabel, &TextScheme);
    SWallControlScreen_SolarInverterStatusLabel->fn->setBackgroundType(SWallControlScreen_SolarInverterStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_SolarInverterStatusLabel->fn->setHAlignment(SWallControlScreen_SolarInverterStatusLabel, LE_HALIGN_CENTER);
    SWallControlScreen_SolarInverterStatusLabel->fn->setString(SWallControlScreen_SolarInverterStatusLabel, (leString*)&string_SolarInverterString);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_SolarInverterStatusLabel);

    SWallControlScreen_BatteryChargerStatusLabel = leLabelWidget_New();
    SWallControlScreen_BatteryChargerStatusLabel->fn->setPosition(SWallControlScreen_BatteryChargerStatusLabel, 46, 395);
    SWallControlScreen_BatteryChargerStatusLabel->fn->setSize(SWallControlScreen_BatteryChargerStatusLabel, 154, 60);
    SWallControlScreen_BatteryChargerStatusLabel->fn->setScheme(SWallControlScreen_BatteryChargerStatusLabel, &TextScheme);
    SWallControlScreen_BatteryChargerStatusLabel->fn->setBackgroundType(SWallControlScreen_BatteryChargerStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_BatteryChargerStatusLabel->fn->setHAlignment(SWallControlScreen_BatteryChargerStatusLabel, LE_HALIGN_CENTER);
    SWallControlScreen_BatteryChargerStatusLabel->fn->setString(SWallControlScreen_BatteryChargerStatusLabel, (leString*)&string_BatteryChargerString);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_BatteryChargerStatusLabel);

    SWallControlScreen_LiquidDetectionStatusLabel = leLabelWidget_New();
    SWallControlScreen_LiquidDetectionStatusLabel->fn->setPosition(SWallControlScreen_LiquidDetectionStatusLabel, 235, 68);
    SWallControlScreen_LiquidDetectionStatusLabel->fn->setSize(SWallControlScreen_LiquidDetectionStatusLabel, 154, 57);
    SWallControlScreen_LiquidDetectionStatusLabel->fn->setScheme(SWallControlScreen_LiquidDetectionStatusLabel, &TextScheme);
    SWallControlScreen_LiquidDetectionStatusLabel->fn->setBackgroundType(SWallControlScreen_LiquidDetectionStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_LiquidDetectionStatusLabel->fn->setHAlignment(SWallControlScreen_LiquidDetectionStatusLabel, LE_HALIGN_CENTER);
    SWallControlScreen_LiquidDetectionStatusLabel->fn->setString(SWallControlScreen_LiquidDetectionStatusLabel, (leString*)&string_LiquidDetectionString);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_LiquidDetectionStatusLabel);

    SWallControlScreen_EnergyStorageStatusLabel = leLabelWidget_New();
    SWallControlScreen_EnergyStorageStatusLabel->fn->setPosition(SWallControlScreen_EnergyStorageStatusLabel, 237, 396);
    SWallControlScreen_EnergyStorageStatusLabel->fn->setSize(SWallControlScreen_EnergyStorageStatusLabel, 154, 62);
    SWallControlScreen_EnergyStorageStatusLabel->fn->setScheme(SWallControlScreen_EnergyStorageStatusLabel, &TextScheme);
    SWallControlScreen_EnergyStorageStatusLabel->fn->setBackgroundType(SWallControlScreen_EnergyStorageStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_EnergyStorageStatusLabel->fn->setHAlignment(SWallControlScreen_EnergyStorageStatusLabel, LE_HALIGN_CENTER);
    SWallControlScreen_EnergyStorageStatusLabel->fn->setString(SWallControlScreen_EnergyStorageStatusLabel, (leString*)&string_EnergyStorageString);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_EnergyStorageStatusLabel);

    SWallControlScreen_HeatPumpStatusLabel = leLabelWidget_New();
    SWallControlScreen_HeatPumpStatusLabel->fn->setPosition(SWallControlScreen_HeatPumpStatusLabel, 417, 74);
    SWallControlScreen_HeatPumpStatusLabel->fn->setSize(SWallControlScreen_HeatPumpStatusLabel, 154, 52);
    SWallControlScreen_HeatPumpStatusLabel->fn->setScheme(SWallControlScreen_HeatPumpStatusLabel, &TextScheme);
    SWallControlScreen_HeatPumpStatusLabel->fn->setBackgroundType(SWallControlScreen_HeatPumpStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_HeatPumpStatusLabel->fn->setHAlignment(SWallControlScreen_HeatPumpStatusLabel, LE_HALIGN_CENTER);
    SWallControlScreen_HeatPumpStatusLabel->fn->setString(SWallControlScreen_HeatPumpStatusLabel, (leString*)&string_HeatPumpString);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_HeatPumpStatusLabel);

    SWallControlScreen_EVChargerStatusLabel = leLabelWidget_New();
    SWallControlScreen_EVChargerStatusLabel->fn->setPosition(SWallControlScreen_EVChargerStatusLabel, 416, 396);
    SWallControlScreen_EVChargerStatusLabel->fn->setSize(SWallControlScreen_EVChargerStatusLabel, 154, 60);
    SWallControlScreen_EVChargerStatusLabel->fn->setScheme(SWallControlScreen_EVChargerStatusLabel, &TextScheme);
    SWallControlScreen_EVChargerStatusLabel->fn->setBackgroundType(SWallControlScreen_EVChargerStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_EVChargerStatusLabel->fn->setHAlignment(SWallControlScreen_EVChargerStatusLabel, LE_HALIGN_CENTER);
    SWallControlScreen_EVChargerStatusLabel->fn->setString(SWallControlScreen_EVChargerStatusLabel, (leString*)&string_EVChargerString);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_EVChargerStatusLabel);

    SWallControlScreen_BatteryChargerRefreshButtonWidget = leButtonWidget_New();
    SWallControlScreen_BatteryChargerRefreshButtonWidget->fn->setPosition(SWallControlScreen_BatteryChargerRefreshButtonWidget, 64, 278);
    SWallControlScreen_BatteryChargerRefreshButtonWidget->fn->setSize(SWallControlScreen_BatteryChargerRefreshButtonWidget, 120, 120);
    SWallControlScreen_BatteryChargerRefreshButtonWidget->fn->setBackgroundType(SWallControlScreen_BatteryChargerRefreshButtonWidget, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_BatteryChargerRefreshButtonWidget->fn->setBorderType(SWallControlScreen_BatteryChargerRefreshButtonWidget, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_BatteryChargerRefreshButtonWidget->fn->setPressedImage(SWallControlScreen_BatteryChargerRefreshButtonWidget, (leImage*)&BatteryCharger);
    SWallControlScreen_BatteryChargerRefreshButtonWidget->fn->setReleasedImage(SWallControlScreen_BatteryChargerRefreshButtonWidget, (leImage*)&BatteryCharger);
    SWallControlScreen_BatteryChargerRefreshButtonWidget->fn->setPressedEventCallback(SWallControlScreen_BatteryChargerRefreshButtonWidget, event_SWallControlScreen_BatteryChargerRefreshButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_BatteryChargerRefreshButtonWidget);

    SWallControlScreen_EnergyStorageRefreshButtonWidget = leButtonWidget_New();
    SWallControlScreen_EnergyStorageRefreshButtonWidget->fn->setPosition(SWallControlScreen_EnergyStorageRefreshButtonWidget, 253, 280);
    SWallControlScreen_EnergyStorageRefreshButtonWidget->fn->setSize(SWallControlScreen_EnergyStorageRefreshButtonWidget, 120, 120);
    SWallControlScreen_EnergyStorageRefreshButtonWidget->fn->setBackgroundType(SWallControlScreen_EnergyStorageRefreshButtonWidget, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_EnergyStorageRefreshButtonWidget->fn->setBorderType(SWallControlScreen_EnergyStorageRefreshButtonWidget, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_EnergyStorageRefreshButtonWidget->fn->setPressedImage(SWallControlScreen_EnergyStorageRefreshButtonWidget, (leImage*)&EnergyStorage);
    SWallControlScreen_EnergyStorageRefreshButtonWidget->fn->setReleasedImage(SWallControlScreen_EnergyStorageRefreshButtonWidget, (leImage*)&EnergyStorage);
    SWallControlScreen_EnergyStorageRefreshButtonWidget->fn->setPressedEventCallback(SWallControlScreen_EnergyStorageRefreshButtonWidget, event_SWallControlScreen_EnergyStorageRefreshButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_EnergyStorageRefreshButtonWidget);

    SWallControlScreen_EVChargerRefreshButtonWidget = leButtonWidget_New();
    SWallControlScreen_EVChargerRefreshButtonWidget->fn->setPosition(SWallControlScreen_EVChargerRefreshButtonWidget, 433, 280);
    SWallControlScreen_EVChargerRefreshButtonWidget->fn->setSize(SWallControlScreen_EVChargerRefreshButtonWidget, 120, 120);
    SWallControlScreen_EVChargerRefreshButtonWidget->fn->setBackgroundType(SWallControlScreen_EVChargerRefreshButtonWidget, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_EVChargerRefreshButtonWidget->fn->setBorderType(SWallControlScreen_EVChargerRefreshButtonWidget, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_EVChargerRefreshButtonWidget->fn->setPressedImage(SWallControlScreen_EVChargerRefreshButtonWidget, (leImage*)&EVCharger);
    SWallControlScreen_EVChargerRefreshButtonWidget->fn->setReleasedImage(SWallControlScreen_EVChargerRefreshButtonWidget, (leImage*)&EVCharger);
    SWallControlScreen_EVChargerRefreshButtonWidget->fn->setPressedEventCallback(SWallControlScreen_EVChargerRefreshButtonWidget, event_SWallControlScreen_EVChargerRefreshButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_EVChargerRefreshButtonWidget);

    SWallControlScreen_SolarInverterRefreshButtonWidget = leButtonWidget_New();
    SWallControlScreen_SolarInverterRefreshButtonWidget->fn->setPosition(SWallControlScreen_SolarInverterRefreshButtonWidget, 66, 133);
    SWallControlScreen_SolarInverterRefreshButtonWidget->fn->setSize(SWallControlScreen_SolarInverterRefreshButtonWidget, 120, 120);
    SWallControlScreen_SolarInverterRefreshButtonWidget->fn->setBackgroundType(SWallControlScreen_SolarInverterRefreshButtonWidget, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_SolarInverterRefreshButtonWidget->fn->setBorderType(SWallControlScreen_SolarInverterRefreshButtonWidget, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_SolarInverterRefreshButtonWidget->fn->setPressedImage(SWallControlScreen_SolarInverterRefreshButtonWidget, (leImage*)&InverterBlue);
    SWallControlScreen_SolarInverterRefreshButtonWidget->fn->setReleasedImage(SWallControlScreen_SolarInverterRefreshButtonWidget, (leImage*)&InverterBlue);
    SWallControlScreen_SolarInverterRefreshButtonWidget->fn->setPressedEventCallback(SWallControlScreen_SolarInverterRefreshButtonWidget, event_SWallControlScreen_SolarInverterRefreshButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_SolarInverterRefreshButtonWidget);

    SWallControlScreen_LiquidDetectionRefreshButtonWidget = leButtonWidget_New();
    SWallControlScreen_LiquidDetectionRefreshButtonWidget->fn->setPosition(SWallControlScreen_LiquidDetectionRefreshButtonWidget, 251, 132);
    SWallControlScreen_LiquidDetectionRefreshButtonWidget->fn->setSize(SWallControlScreen_LiquidDetectionRefreshButtonWidget, 120, 120);
    SWallControlScreen_LiquidDetectionRefreshButtonWidget->fn->setBackgroundType(SWallControlScreen_LiquidDetectionRefreshButtonWidget, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_LiquidDetectionRefreshButtonWidget->fn->setBorderType(SWallControlScreen_LiquidDetectionRefreshButtonWidget, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_LiquidDetectionRefreshButtonWidget->fn->setPressedImage(SWallControlScreen_LiquidDetectionRefreshButtonWidget, (leImage*)&LiquidDetector);
    SWallControlScreen_LiquidDetectionRefreshButtonWidget->fn->setReleasedImage(SWallControlScreen_LiquidDetectionRefreshButtonWidget, (leImage*)&LiquidDetector);
    SWallControlScreen_LiquidDetectionRefreshButtonWidget->fn->setPressedEventCallback(SWallControlScreen_LiquidDetectionRefreshButtonWidget, event_SWallControlScreen_LiquidDetectionRefreshButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_LiquidDetectionRefreshButtonWidget);

    SWallControlScreen_HeatPumpRefreshButtonWidget = leButtonWidget_New();
    SWallControlScreen_HeatPumpRefreshButtonWidget->fn->setPosition(SWallControlScreen_HeatPumpRefreshButtonWidget, 432, 137);
    SWallControlScreen_HeatPumpRefreshButtonWidget->fn->setSize(SWallControlScreen_HeatPumpRefreshButtonWidget, 120, 120);
    SWallControlScreen_HeatPumpRefreshButtonWidget->fn->setBackgroundType(SWallControlScreen_HeatPumpRefreshButtonWidget, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_HeatPumpRefreshButtonWidget->fn->setBorderType(SWallControlScreen_HeatPumpRefreshButtonWidget, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_HeatPumpRefreshButtonWidget->fn->setPressedImage(SWallControlScreen_HeatPumpRefreshButtonWidget, (leImage*)&HeatPump);
    SWallControlScreen_HeatPumpRefreshButtonWidget->fn->setReleasedImage(SWallControlScreen_HeatPumpRefreshButtonWidget, (leImage*)&HeatPump);
    SWallControlScreen_HeatPumpRefreshButtonWidget->fn->setPressedEventCallback(SWallControlScreen_HeatPumpRefreshButtonWidget, event_SWallControlScreen_HeatPumpRefreshButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_HeatPumpRefreshButtonWidget);

    SWallControlScreen_ElectricityMeterStatusLabel = leLabelWidget_New();
    SWallControlScreen_ElectricityMeterStatusLabel->fn->setPosition(SWallControlScreen_ElectricityMeterStatusLabel, 595, 76);
    SWallControlScreen_ElectricityMeterStatusLabel->fn->setSize(SWallControlScreen_ElectricityMeterStatusLabel, 154, 49);
    SWallControlScreen_ElectricityMeterStatusLabel->fn->setScheme(SWallControlScreen_ElectricityMeterStatusLabel, &TextScheme);
    SWallControlScreen_ElectricityMeterStatusLabel->fn->setBackgroundType(SWallControlScreen_ElectricityMeterStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_ElectricityMeterStatusLabel->fn->setHAlignment(SWallControlScreen_ElectricityMeterStatusLabel, LE_HALIGN_CENTER);
    SWallControlScreen_ElectricityMeterStatusLabel->fn->setString(SWallControlScreen_ElectricityMeterStatusLabel, (leString*)&string_ElectricityMeterString);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_ElectricityMeterStatusLabel);

    SWallControlScreen_ElectricityMeterRefreshButtonWidget = leButtonWidget_New();
    SWallControlScreen_ElectricityMeterRefreshButtonWidget->fn->setPosition(SWallControlScreen_ElectricityMeterRefreshButtonWidget, 610, 138);
    SWallControlScreen_ElectricityMeterRefreshButtonWidget->fn->setSize(SWallControlScreen_ElectricityMeterRefreshButtonWidget, 120, 120);
    SWallControlScreen_ElectricityMeterRefreshButtonWidget->fn->setBackgroundType(SWallControlScreen_ElectricityMeterRefreshButtonWidget, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_ElectricityMeterRefreshButtonWidget->fn->setBorderType(SWallControlScreen_ElectricityMeterRefreshButtonWidget, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_ElectricityMeterRefreshButtonWidget->fn->setPressedImage(SWallControlScreen_ElectricityMeterRefreshButtonWidget, (leImage*)&ElectricityMeter);
    SWallControlScreen_ElectricityMeterRefreshButtonWidget->fn->setReleasedImage(SWallControlScreen_ElectricityMeterRefreshButtonWidget, (leImage*)&ElectricityMeter);
    SWallControlScreen_ElectricityMeterRefreshButtonWidget->fn->setPressedEventCallback(SWallControlScreen_ElectricityMeterRefreshButtonWidget, event_SWallControlScreen_ElectricityMeterRefreshButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_ElectricityMeterRefreshButtonWidget);

    SWallControlScreen_NextSWButtonWidget = leButtonWidget_New();
    SWallControlScreen_NextSWButtonWidget->fn->setPosition(SWallControlScreen_NextSWButtonWidget, 614, 286);
    SWallControlScreen_NextSWButtonWidget->fn->setSize(SWallControlScreen_NextSWButtonWidget, 120, 120);
    SWallControlScreen_NextSWButtonWidget->fn->setBackgroundType(SWallControlScreen_NextSWButtonWidget, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_NextSWButtonWidget->fn->setBorderType(SWallControlScreen_NextSWButtonWidget, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_NextSWButtonWidget->fn->setPressedImage(SWallControlScreen_NextSWButtonWidget, (leImage*)&NextPage);
    SWallControlScreen_NextSWButtonWidget->fn->setReleasedImage(SWallControlScreen_NextSWButtonWidget, (leImage*)&NextPage);
    SWallControlScreen_NextSWButtonWidget->fn->setPressedEventCallback(SWallControlScreen_NextSWButtonWidget, event_SWallControlScreen_NextSWButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_NextSWButtonWidget);

    SWallControlScreen_NextSWStatusLabel = leLabelWidget_New();
    SWallControlScreen_NextSWStatusLabel->fn->setPosition(SWallControlScreen_NextSWStatusLabel, 597, 400);
    SWallControlScreen_NextSWStatusLabel->fn->setSize(SWallControlScreen_NextSWStatusLabel, 154, 49);
    SWallControlScreen_NextSWStatusLabel->fn->setScheme(SWallControlScreen_NextSWStatusLabel, &TextScheme);
    SWallControlScreen_NextSWStatusLabel->fn->setBackgroundType(SWallControlScreen_NextSWStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_NextSWStatusLabel->fn->setHAlignment(SWallControlScreen_NextSWStatusLabel, LE_HALIGN_CENTER);
    SWallControlScreen_NextSWStatusLabel->fn->setString(SWallControlScreen_NextSWStatusLabel, (leString*)&string_NextLabel);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_NextSWStatusLabel);

    SWallControlScreen_SolarInverterConnIcon = leImageWidget_New();
    SWallControlScreen_SolarInverterConnIcon->fn->setPosition(SWallControlScreen_SolarInverterConnIcon, 177, 134);
    SWallControlScreen_SolarInverterConnIcon->fn->setSize(SWallControlScreen_SolarInverterConnIcon, 25, 25);
    SWallControlScreen_SolarInverterConnIcon->fn->setBackgroundType(SWallControlScreen_SolarInverterConnIcon, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_SolarInverterConnIcon->fn->setBorderType(SWallControlScreen_SolarInverterConnIcon, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_SolarInverterConnIcon->fn->setImage(SWallControlScreen_SolarInverterConnIcon, (leImage*)&ConnectIcon);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_SolarInverterConnIcon);

    SWallControlScreen_LiquidDetectionConnIcon = leImageWidget_New();
    SWallControlScreen_LiquidDetectionConnIcon->fn->setPosition(SWallControlScreen_LiquidDetectionConnIcon, 364, 132);
    SWallControlScreen_LiquidDetectionConnIcon->fn->setSize(SWallControlScreen_LiquidDetectionConnIcon, 25, 25);
    SWallControlScreen_LiquidDetectionConnIcon->fn->setBackgroundType(SWallControlScreen_LiquidDetectionConnIcon, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_LiquidDetectionConnIcon->fn->setBorderType(SWallControlScreen_LiquidDetectionConnIcon, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_LiquidDetectionConnIcon->fn->setImage(SWallControlScreen_LiquidDetectionConnIcon, (leImage*)&ConnectIcon);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_LiquidDetectionConnIcon);

    SWallControlScreen_HeatPumpConnIcon = leImageWidget_New();
    SWallControlScreen_HeatPumpConnIcon->fn->setPosition(SWallControlScreen_HeatPumpConnIcon, 542, 133);
    SWallControlScreen_HeatPumpConnIcon->fn->setSize(SWallControlScreen_HeatPumpConnIcon, 25, 25);
    SWallControlScreen_HeatPumpConnIcon->fn->setBackgroundType(SWallControlScreen_HeatPumpConnIcon, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_HeatPumpConnIcon->fn->setBorderType(SWallControlScreen_HeatPumpConnIcon, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_HeatPumpConnIcon->fn->setImage(SWallControlScreen_HeatPumpConnIcon, (leImage*)&ConnectIcon);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_HeatPumpConnIcon);

    SWallControlScreen_ElectricityMeterConnIcon = leImageWidget_New();
    SWallControlScreen_ElectricityMeterConnIcon->fn->setPosition(SWallControlScreen_ElectricityMeterConnIcon, 717, 131);
    SWallControlScreen_ElectricityMeterConnIcon->fn->setSize(SWallControlScreen_ElectricityMeterConnIcon, 25, 25);
    SWallControlScreen_ElectricityMeterConnIcon->fn->setBackgroundType(SWallControlScreen_ElectricityMeterConnIcon, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_ElectricityMeterConnIcon->fn->setBorderType(SWallControlScreen_ElectricityMeterConnIcon, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_ElectricityMeterConnIcon->fn->setImage(SWallControlScreen_ElectricityMeterConnIcon, (leImage*)&ConnectIcon);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_ElectricityMeterConnIcon);

    SWallControlScreen_BatteryChargerConnIcon = leImageWidget_New();
    SWallControlScreen_BatteryChargerConnIcon->fn->setPosition(SWallControlScreen_BatteryChargerConnIcon, 176, 273);
    SWallControlScreen_BatteryChargerConnIcon->fn->setSize(SWallControlScreen_BatteryChargerConnIcon, 25, 25);
    SWallControlScreen_BatteryChargerConnIcon->fn->setBackgroundType(SWallControlScreen_BatteryChargerConnIcon, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_BatteryChargerConnIcon->fn->setBorderType(SWallControlScreen_BatteryChargerConnIcon, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_BatteryChargerConnIcon->fn->setImage(SWallControlScreen_BatteryChargerConnIcon, (leImage*)&ConnectIcon);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_BatteryChargerConnIcon);

    SWallControlScreen_EnergyStorageConnIcon = leImageWidget_New();
    SWallControlScreen_EnergyStorageConnIcon->fn->setPosition(SWallControlScreen_EnergyStorageConnIcon, 362, 273);
    SWallControlScreen_EnergyStorageConnIcon->fn->setSize(SWallControlScreen_EnergyStorageConnIcon, 25, 25);
    SWallControlScreen_EnergyStorageConnIcon->fn->setBackgroundType(SWallControlScreen_EnergyStorageConnIcon, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_EnergyStorageConnIcon->fn->setBorderType(SWallControlScreen_EnergyStorageConnIcon, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_EnergyStorageConnIcon->fn->setImage(SWallControlScreen_EnergyStorageConnIcon, (leImage*)&ConnectIcon);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_EnergyStorageConnIcon);

    SWallControlScreen_EVChargerConnIcon = leImageWidget_New();
    SWallControlScreen_EVChargerConnIcon->fn->setPosition(SWallControlScreen_EVChargerConnIcon, 543, 273);
    SWallControlScreen_EVChargerConnIcon->fn->setSize(SWallControlScreen_EVChargerConnIcon, 25, 25);
    SWallControlScreen_EVChargerConnIcon->fn->setBackgroundType(SWallControlScreen_EVChargerConnIcon, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_EVChargerConnIcon->fn->setBorderType(SWallControlScreen_EVChargerConnIcon, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_EVChargerConnIcon->fn->setImage(SWallControlScreen_EVChargerConnIcon, (leImage*)&ConnectIcon);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_EVChargerConnIcon);

    SWallControlScreen_WifiWidget = leImageWidget_New();
    SWallControlScreen_WifiWidget->fn->setPosition(SWallControlScreen_WifiWidget, 684, 3);
    SWallControlScreen_WifiWidget->fn->setSize(SWallControlScreen_WifiWidget, 50, 50);
    SWallControlScreen_WifiWidget->fn->setVisible(SWallControlScreen_WifiWidget, LE_FALSE);
    SWallControlScreen_WifiWidget->fn->setBackgroundType(SWallControlScreen_WifiWidget, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_WifiWidget->fn->setBorderType(SWallControlScreen_WifiWidget, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_WifiWidget->fn->setImage(SWallControlScreen_WifiWidget, (leImage*)&WifiYellow);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_WifiWidget);

    SWallControlScreen_CloudWidget = leImageWidget_New();
    SWallControlScreen_CloudWidget->fn->setPosition(SWallControlScreen_CloudWidget, 739, 4);
    SWallControlScreen_CloudWidget->fn->setSize(SWallControlScreen_CloudWidget, 50, 50);
    SWallControlScreen_CloudWidget->fn->setVisible(SWallControlScreen_CloudWidget, LE_FALSE);
    SWallControlScreen_CloudWidget->fn->setBackgroundType(SWallControlScreen_CloudWidget, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_CloudWidget->fn->setBorderType(SWallControlScreen_CloudWidget, LE_WIDGET_BORDER_NONE);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_CloudWidget);

    SWallControlScreen_G3Widget = leImageWidget_New();
    SWallControlScreen_G3Widget->fn->setPosition(SWallControlScreen_G3Widget, 629, 2);
    SWallControlScreen_G3Widget->fn->setSize(SWallControlScreen_G3Widget, 50, 50);
    SWallControlScreen_G3Widget->fn->setVisible(SWallControlScreen_G3Widget, LE_FALSE);
    SWallControlScreen_G3Widget->fn->setBackgroundType(SWallControlScreen_G3Widget, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_G3Widget->fn->setBorderType(SWallControlScreen_G3Widget, LE_WIDGET_BORDER_NONE);
    SWallControlScreen_G3Widget->fn->setImage(SWallControlScreen_G3Widget, (leImage*)&g3Red);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_G3Widget);

    SWallControlScreen_AlarmWidget = leImageWidget_New();
    SWallControlScreen_AlarmWidget->fn->setPosition(SWallControlScreen_AlarmWidget, 572, 2);
    SWallControlScreen_AlarmWidget->fn->setSize(SWallControlScreen_AlarmWidget, 50, 50);
    SWallControlScreen_AlarmWidget->fn->setBackgroundType(SWallControlScreen_AlarmWidget, LE_WIDGET_BACKGROUND_NONE);
    SWallControlScreen_AlarmWidget->fn->setBorderType(SWallControlScreen_AlarmWidget, LE_WIDGET_BORDER_NONE);
    root0->fn->addChild(root0, (leWidget*)SWallControlScreen_AlarmWidget);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);
    
    APP_SCREEN_SWALL_OnShow();

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_SWallControlScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
    
    APP_SCREEN_SWALL_screenUpdate();
}

void screenHide_SWallControlScreen(void)
{

    APP_SCREEN_SWALL_screenHide();
    
    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    SWallControlScreen_Panel_0 = NULL;
    SWallControlScreen_PanelWidget0 = NULL;
    SWallControlScreen_LineWidget0 = NULL;
    SWallControlScreen_ImageMicrochipWidget = NULL;
    SWallControlScreen_LabelSustainabilityWall = NULL;
    SWallControlScreen_SolarInverterStatusLabel = NULL;
    SWallControlScreen_BatteryChargerStatusLabel = NULL;
    SWallControlScreen_LiquidDetectionStatusLabel = NULL;
    SWallControlScreen_EnergyStorageStatusLabel = NULL;
    SWallControlScreen_HeatPumpStatusLabel = NULL;
    SWallControlScreen_EVChargerStatusLabel = NULL;
    SWallControlScreen_BatteryChargerRefreshButtonWidget = NULL;
    SWallControlScreen_EnergyStorageRefreshButtonWidget = NULL;
    SWallControlScreen_EVChargerRefreshButtonWidget = NULL;
    SWallControlScreen_SolarInverterRefreshButtonWidget = NULL;
    SWallControlScreen_LiquidDetectionRefreshButtonWidget = NULL;
    SWallControlScreen_HeatPumpRefreshButtonWidget = NULL;
    SWallControlScreen_ElectricityMeterStatusLabel = NULL;
    SWallControlScreen_ElectricityMeterRefreshButtonWidget = NULL;
    SWallControlScreen_NextSWButtonWidget = NULL;
    SWallControlScreen_NextSWStatusLabel = NULL;
    SWallControlScreen_SolarInverterConnIcon = NULL;
    SWallControlScreen_LiquidDetectionConnIcon = NULL;
    SWallControlScreen_HeatPumpConnIcon = NULL;
    SWallControlScreen_ElectricityMeterConnIcon = NULL;
    SWallControlScreen_BatteryChargerConnIcon = NULL;
    SWallControlScreen_EnergyStorageConnIcon = NULL;
    SWallControlScreen_EVChargerConnIcon = NULL;
    SWallControlScreen_WifiWidget = NULL;
    SWallControlScreen_CloudWidget = NULL;
    SWallControlScreen_G3Widget = NULL;
    SWallControlScreen_AlarmWidget = NULL;


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

