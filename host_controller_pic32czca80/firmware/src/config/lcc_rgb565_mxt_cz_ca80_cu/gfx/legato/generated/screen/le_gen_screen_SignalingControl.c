#include "gfx/legato/generated/screen/le_gen_screen_SignalingControl.h"

// screen member widget declarations
static leWidget* root0;

leWidget* SignalingControl_Panel_0;
leWidget* SignalingControl_PanelWidget0;
leLineWidget* SignalingControl_LineWidget0_0;
leImageWidget* SignalingControl_ImageMicrochipWidget;
leImageWidget* SignalingControl_CloudWidget;
leImageWidget* SignalingControl_WifiWidget;
leLabelWidget* SignalingControl_PanelLedStatusLabel;
leLabelWidget* SignalingControl_EmergencyButtonStatusLabel;
leButtonWidget* SignalingControl_PanelLedRefreshButtonWidget;
leButtonWidget* SignalingControl_EmergencyButtonRefreshButtonWidget;
leButtonWidget* SignalingControl_NextSignalingButtonWidget;
leImageWidget* SignalingControl_PanelLedConnIcon;
leImageWidget* SignalingControl_EmergencyButtonConnIcon;
leButtonWidget* SignalingControl_SignalingAlarmOnOffButtonWidget;
leLabelWidget* SignalingControl_LightingOutdoorOffStatusLabel;
leLabelWidget* SignalingControl_LightingOutdoorOnStatusLabel;
leImageWidget* SignalingControl_G3Widget;
leImageWidget* SignalingControl_AlarmWidget;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_SignalingControl(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_SignalingControl(void)
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

    SignalingControl_Panel_0 = leWidget_New();
    SignalingControl_Panel_0->fn->setPosition(SignalingControl_Panel_0, 0, 0);
    SignalingControl_Panel_0->fn->setSize(SignalingControl_Panel_0, 800, 480);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_Panel_0);

    SignalingControl_PanelWidget0 = leWidget_New();
    SignalingControl_PanelWidget0->fn->setPosition(SignalingControl_PanelWidget0, 1, -4);
    SignalingControl_PanelWidget0->fn->setSize(SignalingControl_PanelWidget0, 800, 484);
    SignalingControl_PanelWidget0->fn->setScheme(SignalingControl_PanelWidget0, &BackScheme);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_PanelWidget0);

    SignalingControl_LineWidget0_0 = leLineWidget_New();
    SignalingControl_LineWidget0_0->fn->setPosition(SignalingControl_LineWidget0_0, 98, 58);
    SignalingControl_LineWidget0_0->fn->setSize(SignalingControl_LineWidget0_0, 700, 15);
    SignalingControl_LineWidget0_0->fn->setScheme(SignalingControl_LineWidget0_0, &WhiteScheme);
    SignalingControl_LineWidget0_0->fn->setBackgroundType(SignalingControl_LineWidget0_0, LE_WIDGET_BACKGROUND_NONE);
    SignalingControl_LineWidget0_0->fn->setStartPoint(SignalingControl_LineWidget0_0, 0, 5);
    SignalingControl_LineWidget0_0->fn->setEndPoint(SignalingControl_LineWidget0_0, 700, 5);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_LineWidget0_0);

    SignalingControl_ImageMicrochipWidget = leImageWidget_New();
    SignalingControl_ImageMicrochipWidget->fn->setPosition(SignalingControl_ImageMicrochipWidget, 7, 41);
    SignalingControl_ImageMicrochipWidget->fn->setSize(SignalingControl_ImageMicrochipWidget, 100, 40);
    SignalingControl_ImageMicrochipWidget->fn->setBackgroundType(SignalingControl_ImageMicrochipWidget, LE_WIDGET_BACKGROUND_NONE);
    SignalingControl_ImageMicrochipWidget->fn->setBorderType(SignalingControl_ImageMicrochipWidget, LE_WIDGET_BORDER_NONE);
    SignalingControl_ImageMicrochipWidget->fn->setImage(SignalingControl_ImageMicrochipWidget, (leImage*)&MchpLogo_100);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_ImageMicrochipWidget);

    SignalingControl_CloudWidget = leImageWidget_New();
    SignalingControl_CloudWidget->fn->setPosition(SignalingControl_CloudWidget, 739, 4);
    SignalingControl_CloudWidget->fn->setSize(SignalingControl_CloudWidget, 50, 50);
    SignalingControl_CloudWidget->fn->setVisible(SignalingControl_CloudWidget, LE_FALSE);
    SignalingControl_CloudWidget->fn->setBackgroundType(SignalingControl_CloudWidget, LE_WIDGET_BACKGROUND_NONE);
    SignalingControl_CloudWidget->fn->setBorderType(SignalingControl_CloudWidget, LE_WIDGET_BORDER_NONE);
    SignalingControl_CloudWidget->fn->setImage(SignalingControl_CloudWidget, (leImage*)&CloudRed);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_CloudWidget);

    SignalingControl_WifiWidget = leImageWidget_New();
    SignalingControl_WifiWidget->fn->setPosition(SignalingControl_WifiWidget, 685, 4);
    SignalingControl_WifiWidget->fn->setSize(SignalingControl_WifiWidget, 50, 50);
    SignalingControl_WifiWidget->fn->setVisible(SignalingControl_WifiWidget, LE_FALSE);
    SignalingControl_WifiWidget->fn->setBackgroundType(SignalingControl_WifiWidget, LE_WIDGET_BACKGROUND_NONE);
    SignalingControl_WifiWidget->fn->setBorderType(SignalingControl_WifiWidget, LE_WIDGET_BORDER_NONE);
    SignalingControl_WifiWidget->fn->setImage(SignalingControl_WifiWidget, (leImage*)&WifiRed);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_WifiWidget);

    SignalingControl_PanelLedStatusLabel = leLabelWidget_New();
    SignalingControl_PanelLedStatusLabel->fn->setPosition(SignalingControl_PanelLedStatusLabel, 82, 131);
    SignalingControl_PanelLedStatusLabel->fn->setSize(SignalingControl_PanelLedStatusLabel, 154, 57);
    SignalingControl_PanelLedStatusLabel->fn->setScheme(SignalingControl_PanelLedStatusLabel, &TextScheme);
    SignalingControl_PanelLedStatusLabel->fn->setBackgroundType(SignalingControl_PanelLedStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SignalingControl_PanelLedStatusLabel->fn->setHAlignment(SignalingControl_PanelLedStatusLabel, LE_HALIGN_CENTER);
    SignalingControl_PanelLedStatusLabel->fn->setString(SignalingControl_PanelLedStatusLabel, (leString*)&string_LabelPanelLedWidget);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_PanelLedStatusLabel);

    SignalingControl_EmergencyButtonStatusLabel = leLabelWidget_New();
    SignalingControl_EmergencyButtonStatusLabel->fn->setPosition(SignalingControl_EmergencyButtonStatusLabel, 318, 135);
    SignalingControl_EmergencyButtonStatusLabel->fn->setSize(SignalingControl_EmergencyButtonStatusLabel, 198, 57);
    SignalingControl_EmergencyButtonStatusLabel->fn->setScheme(SignalingControl_EmergencyButtonStatusLabel, &TextScheme);
    SignalingControl_EmergencyButtonStatusLabel->fn->setBackgroundType(SignalingControl_EmergencyButtonStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SignalingControl_EmergencyButtonStatusLabel->fn->setHAlignment(SignalingControl_EmergencyButtonStatusLabel, LE_HALIGN_CENTER);
    SignalingControl_EmergencyButtonStatusLabel->fn->setString(SignalingControl_EmergencyButtonStatusLabel, (leString*)&string_EmergencyButtonString);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_EmergencyButtonStatusLabel);

    SignalingControl_PanelLedRefreshButtonWidget = leButtonWidget_New();
    SignalingControl_PanelLedRefreshButtonWidget->fn->setPosition(SignalingControl_PanelLedRefreshButtonWidget, 96, 195);
    SignalingControl_PanelLedRefreshButtonWidget->fn->setSize(SignalingControl_PanelLedRefreshButtonWidget, 120, 120);
    SignalingControl_PanelLedRefreshButtonWidget->fn->setBackgroundType(SignalingControl_PanelLedRefreshButtonWidget, LE_WIDGET_BACKGROUND_NONE);
    SignalingControl_PanelLedRefreshButtonWidget->fn->setBorderType(SignalingControl_PanelLedRefreshButtonWidget, LE_WIDGET_BORDER_NONE);
    SignalingControl_PanelLedRefreshButtonWidget->fn->setPressedImage(SignalingControl_PanelLedRefreshButtonWidget, (leImage*)&PanelLed);
    SignalingControl_PanelLedRefreshButtonWidget->fn->setReleasedImage(SignalingControl_PanelLedRefreshButtonWidget, (leImage*)&PanelLed);
    SignalingControl_PanelLedRefreshButtonWidget->fn->setPressedEventCallback(SignalingControl_PanelLedRefreshButtonWidget, event_SignalingControl_PanelLedRefreshButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_PanelLedRefreshButtonWidget);

    SignalingControl_EmergencyButtonRefreshButtonWidget = leButtonWidget_New();
    SignalingControl_EmergencyButtonRefreshButtonWidget->fn->setPosition(SignalingControl_EmergencyButtonRefreshButtonWidget, 357, 187);
    SignalingControl_EmergencyButtonRefreshButtonWidget->fn->setSize(SignalingControl_EmergencyButtonRefreshButtonWidget, 123, 128);
    SignalingControl_EmergencyButtonRefreshButtonWidget->fn->setBackgroundType(SignalingControl_EmergencyButtonRefreshButtonWidget, LE_WIDGET_BACKGROUND_NONE);
    SignalingControl_EmergencyButtonRefreshButtonWidget->fn->setBorderType(SignalingControl_EmergencyButtonRefreshButtonWidget, LE_WIDGET_BORDER_NONE);
    SignalingControl_EmergencyButtonRefreshButtonWidget->fn->setPressedImage(SignalingControl_EmergencyButtonRefreshButtonWidget, (leImage*)&EmergencyButton);
    SignalingControl_EmergencyButtonRefreshButtonWidget->fn->setReleasedImage(SignalingControl_EmergencyButtonRefreshButtonWidget, (leImage*)&EmergencyButton);
    SignalingControl_EmergencyButtonRefreshButtonWidget->fn->setPressedEventCallback(SignalingControl_EmergencyButtonRefreshButtonWidget, event_SignalingControl_EmergencyButtonRefreshButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_EmergencyButtonRefreshButtonWidget);

    SignalingControl_NextSignalingButtonWidget = leButtonWidget_New();
    SignalingControl_NextSignalingButtonWidget->fn->setPosition(SignalingControl_NextSignalingButtonWidget, 607, 189);
    SignalingControl_NextSignalingButtonWidget->fn->setSize(SignalingControl_NextSignalingButtonWidget, 120, 120);
    SignalingControl_NextSignalingButtonWidget->fn->setBackgroundType(SignalingControl_NextSignalingButtonWidget, LE_WIDGET_BACKGROUND_NONE);
    SignalingControl_NextSignalingButtonWidget->fn->setBorderType(SignalingControl_NextSignalingButtonWidget, LE_WIDGET_BORDER_NONE);
    SignalingControl_NextSignalingButtonWidget->fn->setPressedImage(SignalingControl_NextSignalingButtonWidget, (leImage*)&NextPage);
    SignalingControl_NextSignalingButtonWidget->fn->setReleasedImage(SignalingControl_NextSignalingButtonWidget, (leImage*)&NextPage);
    SignalingControl_NextSignalingButtonWidget->fn->setPressedEventCallback(SignalingControl_NextSignalingButtonWidget, event_SignalingControl_NextSignalingButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_NextSignalingButtonWidget);

    SignalingControl_PanelLedConnIcon = leImageWidget_New();
    SignalingControl_PanelLedConnIcon->fn->setPosition(SignalingControl_PanelLedConnIcon, 214, 194);
    SignalingControl_PanelLedConnIcon->fn->setSize(SignalingControl_PanelLedConnIcon, 25, 25);
    SignalingControl_PanelLedConnIcon->fn->setBackgroundType(SignalingControl_PanelLedConnIcon, LE_WIDGET_BACKGROUND_NONE);
    SignalingControl_PanelLedConnIcon->fn->setBorderType(SignalingControl_PanelLedConnIcon, LE_WIDGET_BORDER_NONE);
    SignalingControl_PanelLedConnIcon->fn->setImage(SignalingControl_PanelLedConnIcon, (leImage*)&ConnectIcon);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_PanelLedConnIcon);

    SignalingControl_EmergencyButtonConnIcon = leImageWidget_New();
    SignalingControl_EmergencyButtonConnIcon->fn->setPosition(SignalingControl_EmergencyButtonConnIcon, 480, 192);
    SignalingControl_EmergencyButtonConnIcon->fn->setSize(SignalingControl_EmergencyButtonConnIcon, 25, 25);
    SignalingControl_EmergencyButtonConnIcon->fn->setBackgroundType(SignalingControl_EmergencyButtonConnIcon, LE_WIDGET_BACKGROUND_NONE);
    SignalingControl_EmergencyButtonConnIcon->fn->setBorderType(SignalingControl_EmergencyButtonConnIcon, LE_WIDGET_BORDER_NONE);
    SignalingControl_EmergencyButtonConnIcon->fn->setImage(SignalingControl_EmergencyButtonConnIcon, (leImage*)&ConnectIcon);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_EmergencyButtonConnIcon);

    SignalingControl_SignalingAlarmOnOffButtonWidget = leButtonWidget_New();
    SignalingControl_SignalingAlarmOnOffButtonWidget->fn->setPosition(SignalingControl_SignalingAlarmOnOffButtonWidget, 337, 326);
    SignalingControl_SignalingAlarmOnOffButtonWidget->fn->setSize(SignalingControl_SignalingAlarmOnOffButtonWidget, 161, 128);
    SignalingControl_SignalingAlarmOnOffButtonWidget->fn->setBackgroundType(SignalingControl_SignalingAlarmOnOffButtonWidget, LE_WIDGET_BACKGROUND_NONE);
    SignalingControl_SignalingAlarmOnOffButtonWidget->fn->setBorderType(SignalingControl_SignalingAlarmOnOffButtonWidget, LE_WIDGET_BORDER_NONE);
    SignalingControl_SignalingAlarmOnOffButtonWidget->fn->setToggleable(SignalingControl_SignalingAlarmOnOffButtonWidget, LE_TRUE);
    SignalingControl_SignalingAlarmOnOffButtonWidget->fn->setPressedImage(SignalingControl_SignalingAlarmOnOffButtonWidget, (leImage*)&LightOn);
    SignalingControl_SignalingAlarmOnOffButtonWidget->fn->setReleasedImage(SignalingControl_SignalingAlarmOnOffButtonWidget, (leImage*)&LightOff);
    SignalingControl_SignalingAlarmOnOffButtonWidget->fn->setPressedEventCallback(SignalingControl_SignalingAlarmOnOffButtonWidget, event_SignalingControl_SignalingAlarmOnOffButtonWidget_OnPressed);
    SignalingControl_SignalingAlarmOnOffButtonWidget->fn->setReleasedEventCallback(SignalingControl_SignalingAlarmOnOffButtonWidget, event_SignalingControl_SignalingAlarmOnOffButtonWidget_OnReleased);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_SignalingAlarmOnOffButtonWidget);

    SignalingControl_LightingOutdoorOffStatusLabel = leLabelWidget_New();
    SignalingControl_LightingOutdoorOffStatusLabel->fn->setPosition(SignalingControl_LightingOutdoorOffStatusLabel, 271, 355);
    SignalingControl_LightingOutdoorOffStatusLabel->fn->setSize(SignalingControl_LightingOutdoorOffStatusLabel, 88, 62);
    SignalingControl_LightingOutdoorOffStatusLabel->fn->setScheme(SignalingControl_LightingOutdoorOffStatusLabel, &TextScheme);
    SignalingControl_LightingOutdoorOffStatusLabel->fn->setBackgroundType(SignalingControl_LightingOutdoorOffStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SignalingControl_LightingOutdoorOffStatusLabel->fn->setHAlignment(SignalingControl_LightingOutdoorOffStatusLabel, LE_HALIGN_CENTER);
    SignalingControl_LightingOutdoorOffStatusLabel->fn->setString(SignalingControl_LightingOutdoorOffStatusLabel, (leString*)&string_PressedLabel);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_LightingOutdoorOffStatusLabel);

    SignalingControl_LightingOutdoorOnStatusLabel = leLabelWidget_New();
    SignalingControl_LightingOutdoorOnStatusLabel->fn->setPosition(SignalingControl_LightingOutdoorOnStatusLabel, 483, 353);
    SignalingControl_LightingOutdoorOnStatusLabel->fn->setSize(SignalingControl_LightingOutdoorOnStatusLabel, 92, 62);
    SignalingControl_LightingOutdoorOnStatusLabel->fn->setScheme(SignalingControl_LightingOutdoorOnStatusLabel, &TextScheme);
    SignalingControl_LightingOutdoorOnStatusLabel->fn->setBackgroundType(SignalingControl_LightingOutdoorOnStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    SignalingControl_LightingOutdoorOnStatusLabel->fn->setHAlignment(SignalingControl_LightingOutdoorOnStatusLabel, LE_HALIGN_CENTER);
    SignalingControl_LightingOutdoorOnStatusLabel->fn->setString(SignalingControl_LightingOutdoorOnStatusLabel, (leString*)&string_ReleasedLabel);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_LightingOutdoorOnStatusLabel);

    SignalingControl_G3Widget = leImageWidget_New();
    SignalingControl_G3Widget->fn->setPosition(SignalingControl_G3Widget, 630, 4);
    SignalingControl_G3Widget->fn->setSize(SignalingControl_G3Widget, 50, 50);
    SignalingControl_G3Widget->fn->setVisible(SignalingControl_G3Widget, LE_FALSE);
    SignalingControl_G3Widget->fn->setBackgroundType(SignalingControl_G3Widget, LE_WIDGET_BACKGROUND_NONE);
    SignalingControl_G3Widget->fn->setBorderType(SignalingControl_G3Widget, LE_WIDGET_BORDER_NONE);
    SignalingControl_G3Widget->fn->setImage(SignalingControl_G3Widget, (leImage*)&g3Red);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_G3Widget);

    SignalingControl_AlarmWidget = leImageWidget_New();
    SignalingControl_AlarmWidget->fn->setPosition(SignalingControl_AlarmWidget, 571, 5);
    SignalingControl_AlarmWidget->fn->setSize(SignalingControl_AlarmWidget, 50, 50);
    SignalingControl_AlarmWidget->fn->setBackgroundType(SignalingControl_AlarmWidget, LE_WIDGET_BACKGROUND_NONE);
    SignalingControl_AlarmWidget->fn->setBorderType(SignalingControl_AlarmWidget, LE_WIDGET_BORDER_NONE);
    root0->fn->addChild(root0, (leWidget*)SignalingControl_AlarmWidget);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    APP_SCREEN_SIGNALING_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_SignalingControl(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    APP_SCREEN_SIGNALING_OnUpdate(); // raise event
}

void screenHide_SignalingControl(void)
{
    APP_SCREEN_SIGNALING_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    SignalingControl_Panel_0 = NULL;
    SignalingControl_PanelWidget0 = NULL;
    SignalingControl_LineWidget0_0 = NULL;
    SignalingControl_ImageMicrochipWidget = NULL;
    SignalingControl_CloudWidget = NULL;
    SignalingControl_WifiWidget = NULL;
    SignalingControl_PanelLedStatusLabel = NULL;
    SignalingControl_EmergencyButtonStatusLabel = NULL;
    SignalingControl_PanelLedRefreshButtonWidget = NULL;
    SignalingControl_EmergencyButtonRefreshButtonWidget = NULL;
    SignalingControl_NextSignalingButtonWidget = NULL;
    SignalingControl_PanelLedConnIcon = NULL;
    SignalingControl_EmergencyButtonConnIcon = NULL;
    SignalingControl_SignalingAlarmOnOffButtonWidget = NULL;
    SignalingControl_LightingOutdoorOffStatusLabel = NULL;
    SignalingControl_LightingOutdoorOnStatusLabel = NULL;
    SignalingControl_G3Widget = NULL;
    SignalingControl_AlarmWidget = NULL;


    showing = LE_FALSE;
}

void screenDestroy_SignalingControl(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_SignalingControl(uint32_t lyrIdx)
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

