#include "gfx/legato/generated/screen/le_gen_screen_LightControlScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* LightControlScreen_Panel_0;
leLabelWidget* LightControlScreen_LabelWidget_0;
leImageWidget* LightControlScreen_ImageWidget0;
leLineWidget* LightControlScreen_LineWidget0;
leWidget* LightControlScreen_PanelWidget0;
leLabelWidget* LightControlScreen_LabelSmartLighting;
leLineWidget* LightControlScreen_LineWidget0_0;
leImageWidget* LightControlScreen_ImageMicrochipWidget;
leLabelWidget* LightControlScreen_LightingIndoorStatusLabel;
leLabelWidget* LightControlScreen_LightingOutdoorStatusLabel;
leButtonWidget* LightControlScreen_LightingIndoorRefreshButtonWidget;
leButtonWidget* LightControlScreen_LightingOutdoorRefreshButtonWidget;
leButtonWidget* LightControlScreen_LightingOutdoorOnOffButtonWidget;
leLabelWidget* LightControlScreen_LightingOutdoorOnStatusLabel;
leLabelWidget* LightControlScreen_LightingOutdoorOffStatusLabel;
leLabelWidget* LightControlScreen_LightingIndoorOffStatusLabel;
leLabelWidget* LightControlScreen_LightingIndoorOnStatusLabel;
leButtonWidget* LightControlScreen_NextLightingButtonWidget;
leLabelWidget* LightControlScreen_NextLightingStatusLabel;
leButtonWidget* LightControlScreen_LightingIndoorOnOffButtonWidget;
leImageWidget* LightControlScreen_LightingIndoorConnIcon;
leImageWidget* LightControlScreen_LightingOutdoorConnIcon;
leImageWidget* LightControlScreen_CloudWidget;
leImageWidget* LightControlScreen_WifiWidget;
leImageWidget* LightControlScreen_G3Widget;
leImageWidget* LightControlScreen_AlarmWidget;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_LightControlScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_LightControlScreen(void)
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

    LightControlScreen_Panel_0 = leWidget_New();
    LightControlScreen_Panel_0->fn->setPosition(LightControlScreen_Panel_0, 0, 0);
    LightControlScreen_Panel_0->fn->setSize(LightControlScreen_Panel_0, 800, 480);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_Panel_0);

    LightControlScreen_LabelWidget_0 = leLabelWidget_New();
    LightControlScreen_LabelWidget_0->fn->setPosition(LightControlScreen_LabelWidget_0, 410, 2);
    LightControlScreen_LabelWidget_0->fn->setSize(LightControlScreen_LabelWidget_0, 380, 25);
    LightControlScreen_LabelWidget_0->fn->setScheme(LightControlScreen_LabelWidget_0, &TextScheme);
    LightControlScreen_LabelWidget_0->fn->setHAlignment(LightControlScreen_LabelWidget_0, LE_HALIGN_CENTER);
    LightControlScreen_LabelWidget_0->fn->setString(LightControlScreen_LabelWidget_0, (leString*)&string_DemoName);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LabelWidget_0);

    LightControlScreen_ImageWidget0 = leImageWidget_New();
    LightControlScreen_ImageWidget0->fn->setPosition(LightControlScreen_ImageWidget0, 10, 10);
    LightControlScreen_ImageWidget0->fn->setSize(LightControlScreen_ImageWidget0, 100, 40);
    LightControlScreen_ImageWidget0->fn->setBackgroundType(LightControlScreen_ImageWidget0, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_ImageWidget0->fn->setBorderType(LightControlScreen_ImageWidget0, LE_WIDGET_BORDER_NONE);
    LightControlScreen_ImageWidget0->fn->setImage(LightControlScreen_ImageWidget0, (leImage*)&MchpLogo_100);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_ImageWidget0);

    LightControlScreen_LineWidget0 = leLineWidget_New();
    LightControlScreen_LineWidget0->fn->setPosition(LightControlScreen_LineWidget0, 97, 25);
    LightControlScreen_LineWidget0->fn->setSize(LightControlScreen_LineWidget0, 700, 15);
    LightControlScreen_LineWidget0->fn->setScheme(LightControlScreen_LineWidget0, &WhiteScheme);
    LightControlScreen_LineWidget0->fn->setBackgroundType(LightControlScreen_LineWidget0, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LineWidget0->fn->setStartPoint(LightControlScreen_LineWidget0, 0, 5);
    LightControlScreen_LineWidget0->fn->setEndPoint(LightControlScreen_LineWidget0, 700, 5);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LineWidget0);

    LightControlScreen_PanelWidget0 = leWidget_New();
    LightControlScreen_PanelWidget0->fn->setPosition(LightControlScreen_PanelWidget0, 0, -3);
    LightControlScreen_PanelWidget0->fn->setSize(LightControlScreen_PanelWidget0, 800, 484);
    LightControlScreen_PanelWidget0->fn->setScheme(LightControlScreen_PanelWidget0, &BackScheme);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_PanelWidget0);

    LightControlScreen_LabelSmartLighting = leLabelWidget_New();
    LightControlScreen_LabelSmartLighting->fn->setPosition(LightControlScreen_LabelSmartLighting, 304, 9);
    LightControlScreen_LabelSmartLighting->fn->setSize(LightControlScreen_LabelSmartLighting, 236, 32);
    LightControlScreen_LabelSmartLighting->fn->setScheme(LightControlScreen_LabelSmartLighting, &TextScheme);
    LightControlScreen_LabelSmartLighting->fn->setHAlignment(LightControlScreen_LabelSmartLighting, LE_HALIGN_CENTER);
    LightControlScreen_LabelSmartLighting->fn->setString(LightControlScreen_LabelSmartLighting, (leString*)&string_LightingWallConnectionStatus);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LabelSmartLighting);

    LightControlScreen_LineWidget0_0 = leLineWidget_New();
    LightControlScreen_LineWidget0_0->fn->setPosition(LightControlScreen_LineWidget0_0, 98, 58);
    LightControlScreen_LineWidget0_0->fn->setSize(LightControlScreen_LineWidget0_0, 700, 15);
    LightControlScreen_LineWidget0_0->fn->setScheme(LightControlScreen_LineWidget0_0, &WhiteScheme);
    LightControlScreen_LineWidget0_0->fn->setBackgroundType(LightControlScreen_LineWidget0_0, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LineWidget0_0->fn->setStartPoint(LightControlScreen_LineWidget0_0, 0, 5);
    LightControlScreen_LineWidget0_0->fn->setEndPoint(LightControlScreen_LineWidget0_0, 700, 5);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LineWidget0_0);

    LightControlScreen_ImageMicrochipWidget = leImageWidget_New();
    LightControlScreen_ImageMicrochipWidget->fn->setPosition(LightControlScreen_ImageMicrochipWidget, 7, 41);
    LightControlScreen_ImageMicrochipWidget->fn->setSize(LightControlScreen_ImageMicrochipWidget, 100, 40);
    LightControlScreen_ImageMicrochipWidget->fn->setBackgroundType(LightControlScreen_ImageMicrochipWidget, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_ImageMicrochipWidget->fn->setBorderType(LightControlScreen_ImageMicrochipWidget, LE_WIDGET_BORDER_NONE);
    LightControlScreen_ImageMicrochipWidget->fn->setImage(LightControlScreen_ImageMicrochipWidget, (leImage*)&MchpLogo_100);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_ImageMicrochipWidget);

    LightControlScreen_LightingIndoorStatusLabel = leLabelWidget_New();
    LightControlScreen_LightingIndoorStatusLabel->fn->setPosition(LightControlScreen_LightingIndoorStatusLabel, 79, 107);
    LightControlScreen_LightingIndoorStatusLabel->fn->setSize(LightControlScreen_LightingIndoorStatusLabel, 154, 57);
    LightControlScreen_LightingIndoorStatusLabel->fn->setScheme(LightControlScreen_LightingIndoorStatusLabel, &TextScheme);
    LightControlScreen_LightingIndoorStatusLabel->fn->setBackgroundType(LightControlScreen_LightingIndoorStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LightingIndoorStatusLabel->fn->setHAlignment(LightControlScreen_LightingIndoorStatusLabel, LE_HALIGN_CENTER);
    LightControlScreen_LightingIndoorStatusLabel->fn->setString(LightControlScreen_LightingIndoorStatusLabel, (leString*)&string_LightingIndoorString);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LightingIndoorStatusLabel);

    LightControlScreen_LightingOutdoorStatusLabel = leLabelWidget_New();
    LightControlScreen_LightingOutdoorStatusLabel->fn->setPosition(LightControlScreen_LightingOutdoorStatusLabel, 326, 103);
    LightControlScreen_LightingOutdoorStatusLabel->fn->setSize(LightControlScreen_LightingOutdoorStatusLabel, 199, 62);
    LightControlScreen_LightingOutdoorStatusLabel->fn->setScheme(LightControlScreen_LightingOutdoorStatusLabel, &TextScheme);
    LightControlScreen_LightingOutdoorStatusLabel->fn->setBackgroundType(LightControlScreen_LightingOutdoorStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LightingOutdoorStatusLabel->fn->setHAlignment(LightControlScreen_LightingOutdoorStatusLabel, LE_HALIGN_CENTER);
    LightControlScreen_LightingOutdoorStatusLabel->fn->setString(LightControlScreen_LightingOutdoorStatusLabel, (leString*)&string_LightingOutdoorString);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LightingOutdoorStatusLabel);

    LightControlScreen_LightingIndoorRefreshButtonWidget = leButtonWidget_New();
    LightControlScreen_LightingIndoorRefreshButtonWidget->fn->setPosition(LightControlScreen_LightingIndoorRefreshButtonWidget, 96, 187);
    LightControlScreen_LightingIndoorRefreshButtonWidget->fn->setSize(LightControlScreen_LightingIndoorRefreshButtonWidget, 120, 120);
    LightControlScreen_LightingIndoorRefreshButtonWidget->fn->setBackgroundType(LightControlScreen_LightingIndoorRefreshButtonWidget, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LightingIndoorRefreshButtonWidget->fn->setBorderType(LightControlScreen_LightingIndoorRefreshButtonWidget, LE_WIDGET_BORDER_NONE);
    LightControlScreen_LightingIndoorRefreshButtonWidget->fn->setPressedImage(LightControlScreen_LightingIndoorRefreshButtonWidget, (leImage*)&IndoorLight);
    LightControlScreen_LightingIndoorRefreshButtonWidget->fn->setReleasedImage(LightControlScreen_LightingIndoorRefreshButtonWidget, (leImage*)&IndoorLight);
    LightControlScreen_LightingIndoorRefreshButtonWidget->fn->setPressedEventCallback(LightControlScreen_LightingIndoorRefreshButtonWidget, event_LightControlScreen_LightingIndoorRefreshButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LightingIndoorRefreshButtonWidget);

    LightControlScreen_LightingOutdoorRefreshButtonWidget = leButtonWidget_New();
    LightControlScreen_LightingOutdoorRefreshButtonWidget->fn->setPosition(LightControlScreen_LightingOutdoorRefreshButtonWidget, 357, 187);
    LightControlScreen_LightingOutdoorRefreshButtonWidget->fn->setSize(LightControlScreen_LightingOutdoorRefreshButtonWidget, 123, 128);
    LightControlScreen_LightingOutdoorRefreshButtonWidget->fn->setBackgroundType(LightControlScreen_LightingOutdoorRefreshButtonWidget, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LightingOutdoorRefreshButtonWidget->fn->setBorderType(LightControlScreen_LightingOutdoorRefreshButtonWidget, LE_WIDGET_BORDER_NONE);
    LightControlScreen_LightingOutdoorRefreshButtonWidget->fn->setPressedImage(LightControlScreen_LightingOutdoorRefreshButtonWidget, (leImage*)&OutdoorLight);
    LightControlScreen_LightingOutdoorRefreshButtonWidget->fn->setReleasedImage(LightControlScreen_LightingOutdoorRefreshButtonWidget, (leImage*)&OutdoorLight);
    LightControlScreen_LightingOutdoorRefreshButtonWidget->fn->setPressedEventCallback(LightControlScreen_LightingOutdoorRefreshButtonWidget, event_LightControlScreen_LightingOutdoorRefreshButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LightingOutdoorRefreshButtonWidget);

    LightControlScreen_LightingOutdoorOnOffButtonWidget = leButtonWidget_New();
    LightControlScreen_LightingOutdoorOnOffButtonWidget->fn->setPosition(LightControlScreen_LightingOutdoorOnOffButtonWidget, 335, 285);
    LightControlScreen_LightingOutdoorOnOffButtonWidget->fn->setSize(LightControlScreen_LightingOutdoorOnOffButtonWidget, 161, 128);
    LightControlScreen_LightingOutdoorOnOffButtonWidget->fn->setBackgroundType(LightControlScreen_LightingOutdoorOnOffButtonWidget, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LightingOutdoorOnOffButtonWidget->fn->setBorderType(LightControlScreen_LightingOutdoorOnOffButtonWidget, LE_WIDGET_BORDER_NONE);
    LightControlScreen_LightingOutdoorOnOffButtonWidget->fn->setToggleable(LightControlScreen_LightingOutdoorOnOffButtonWidget, LE_TRUE);
    LightControlScreen_LightingOutdoorOnOffButtonWidget->fn->setPressed(LightControlScreen_LightingOutdoorOnOffButtonWidget, LE_TRUE);
    LightControlScreen_LightingOutdoorOnOffButtonWidget->fn->setPressedImage(LightControlScreen_LightingOutdoorOnOffButtonWidget, (leImage*)&LightOn);
    LightControlScreen_LightingOutdoorOnOffButtonWidget->fn->setReleasedImage(LightControlScreen_LightingOutdoorOnOffButtonWidget, (leImage*)&LightOff);
    LightControlScreen_LightingOutdoorOnOffButtonWidget->fn->setPressedEventCallback(LightControlScreen_LightingOutdoorOnOffButtonWidget, event_LightControlScreen_LightingOutdoorOnOffButtonWidget_OnPressed);
    LightControlScreen_LightingOutdoorOnOffButtonWidget->fn->setReleasedEventCallback(LightControlScreen_LightingOutdoorOnOffButtonWidget, event_LightControlScreen_LightingOutdoorOnOffButtonWidget_OnReleased);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LightingOutdoorOnOffButtonWidget);

    LightControlScreen_LightingOutdoorOnStatusLabel = leLabelWidget_New();
    LightControlScreen_LightingOutdoorOnStatusLabel->fn->setPosition(LightControlScreen_LightingOutdoorOnStatusLabel, 471, 318);
    LightControlScreen_LightingOutdoorOnStatusLabel->fn->setSize(LightControlScreen_LightingOutdoorOnStatusLabel, 64, 62);
    LightControlScreen_LightingOutdoorOnStatusLabel->fn->setScheme(LightControlScreen_LightingOutdoorOnStatusLabel, &TextScheme);
    LightControlScreen_LightingOutdoorOnStatusLabel->fn->setBackgroundType(LightControlScreen_LightingOutdoorOnStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LightingOutdoorOnStatusLabel->fn->setHAlignment(LightControlScreen_LightingOutdoorOnStatusLabel, LE_HALIGN_CENTER);
    LightControlScreen_LightingOutdoorOnStatusLabel->fn->setString(LightControlScreen_LightingOutdoorOnStatusLabel, (leString*)&string_LightOnLabel);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LightingOutdoorOnStatusLabel);

    LightControlScreen_LightingOutdoorOffStatusLabel = leLabelWidget_New();
    LightControlScreen_LightingOutdoorOffStatusLabel->fn->setPosition(LightControlScreen_LightingOutdoorOffStatusLabel, 295, 314);
    LightControlScreen_LightingOutdoorOffStatusLabel->fn->setSize(LightControlScreen_LightingOutdoorOffStatusLabel, 64, 62);
    LightControlScreen_LightingOutdoorOffStatusLabel->fn->setScheme(LightControlScreen_LightingOutdoorOffStatusLabel, &TextScheme);
    LightControlScreen_LightingOutdoorOffStatusLabel->fn->setBackgroundType(LightControlScreen_LightingOutdoorOffStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LightingOutdoorOffStatusLabel->fn->setHAlignment(LightControlScreen_LightingOutdoorOffStatusLabel, LE_HALIGN_CENTER);
    LightControlScreen_LightingOutdoorOffStatusLabel->fn->setString(LightControlScreen_LightingOutdoorOffStatusLabel, (leString*)&string_LightOffLabel);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LightingOutdoorOffStatusLabel);

    LightControlScreen_LightingIndoorOffStatusLabel = leLabelWidget_New();
    LightControlScreen_LightingIndoorOffStatusLabel->fn->setPosition(LightControlScreen_LightingIndoorOffStatusLabel, 39, 314);
    LightControlScreen_LightingIndoorOffStatusLabel->fn->setSize(LightControlScreen_LightingIndoorOffStatusLabel, 64, 62);
    LightControlScreen_LightingIndoorOffStatusLabel->fn->setScheme(LightControlScreen_LightingIndoorOffStatusLabel, &TextScheme);
    LightControlScreen_LightingIndoorOffStatusLabel->fn->setBackgroundType(LightControlScreen_LightingIndoorOffStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LightingIndoorOffStatusLabel->fn->setHAlignment(LightControlScreen_LightingIndoorOffStatusLabel, LE_HALIGN_CENTER);
    LightControlScreen_LightingIndoorOffStatusLabel->fn->setString(LightControlScreen_LightingIndoorOffStatusLabel, (leString*)&string_LightOffLabel);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LightingIndoorOffStatusLabel);

    LightControlScreen_LightingIndoorOnStatusLabel = leLabelWidget_New();
    LightControlScreen_LightingIndoorOnStatusLabel->fn->setPosition(LightControlScreen_LightingIndoorOnStatusLabel, 205, 314);
    LightControlScreen_LightingIndoorOnStatusLabel->fn->setSize(LightControlScreen_LightingIndoorOnStatusLabel, 64, 62);
    LightControlScreen_LightingIndoorOnStatusLabel->fn->setScheme(LightControlScreen_LightingIndoorOnStatusLabel, &TextScheme);
    LightControlScreen_LightingIndoorOnStatusLabel->fn->setBackgroundType(LightControlScreen_LightingIndoorOnStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LightingIndoorOnStatusLabel->fn->setHAlignment(LightControlScreen_LightingIndoorOnStatusLabel, LE_HALIGN_CENTER);
    LightControlScreen_LightingIndoorOnStatusLabel->fn->setString(LightControlScreen_LightingIndoorOnStatusLabel, (leString*)&string_LightOnLabel);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LightingIndoorOnStatusLabel);

    LightControlScreen_NextLightingButtonWidget = leButtonWidget_New();
    LightControlScreen_NextLightingButtonWidget->fn->setPosition(LightControlScreen_NextLightingButtonWidget, 612, 197);
    LightControlScreen_NextLightingButtonWidget->fn->setSize(LightControlScreen_NextLightingButtonWidget, 120, 120);
    LightControlScreen_NextLightingButtonWidget->fn->setBackgroundType(LightControlScreen_NextLightingButtonWidget, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_NextLightingButtonWidget->fn->setBorderType(LightControlScreen_NextLightingButtonWidget, LE_WIDGET_BORDER_NONE);
    LightControlScreen_NextLightingButtonWidget->fn->setPressedImage(LightControlScreen_NextLightingButtonWidget, (leImage*)&NextPage);
    LightControlScreen_NextLightingButtonWidget->fn->setReleasedImage(LightControlScreen_NextLightingButtonWidget, (leImage*)&NextPage);
    LightControlScreen_NextLightingButtonWidget->fn->setPressedEventCallback(LightControlScreen_NextLightingButtonWidget, event_LightControlScreen_NextLightingButtonWidget_OnPressed);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_NextLightingButtonWidget);

    LightControlScreen_NextLightingStatusLabel = leLabelWidget_New();
    LightControlScreen_NextLightingStatusLabel->fn->setPosition(LightControlScreen_NextLightingStatusLabel, 589, 323);
    LightControlScreen_NextLightingStatusLabel->fn->setSize(LightControlScreen_NextLightingStatusLabel, 154, 49);
    LightControlScreen_NextLightingStatusLabel->fn->setScheme(LightControlScreen_NextLightingStatusLabel, &TextScheme);
    LightControlScreen_NextLightingStatusLabel->fn->setBackgroundType(LightControlScreen_NextLightingStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_NextLightingStatusLabel->fn->setHAlignment(LightControlScreen_NextLightingStatusLabel, LE_HALIGN_CENTER);
    LightControlScreen_NextLightingStatusLabel->fn->setString(LightControlScreen_NextLightingStatusLabel, (leString*)&string_NextLabel);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_NextLightingStatusLabel);

    LightControlScreen_LightingIndoorOnOffButtonWidget = leButtonWidget_New();
    LightControlScreen_LightingIndoorOnOffButtonWidget->fn->setPosition(LightControlScreen_LightingIndoorOnOffButtonWidget, 73, 284);
    LightControlScreen_LightingIndoorOnOffButtonWidget->fn->setSize(LightControlScreen_LightingIndoorOnOffButtonWidget, 161, 128);
    LightControlScreen_LightingIndoorOnOffButtonWidget->fn->setBackgroundType(LightControlScreen_LightingIndoorOnOffButtonWidget, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LightingIndoorOnOffButtonWidget->fn->setBorderType(LightControlScreen_LightingIndoorOnOffButtonWidget, LE_WIDGET_BORDER_NONE);
    LightControlScreen_LightingIndoorOnOffButtonWidget->fn->setToggleable(LightControlScreen_LightingIndoorOnOffButtonWidget, LE_TRUE);
    LightControlScreen_LightingIndoorOnOffButtonWidget->fn->setPressed(LightControlScreen_LightingIndoorOnOffButtonWidget, LE_TRUE);
    LightControlScreen_LightingIndoorOnOffButtonWidget->fn->setPressedImage(LightControlScreen_LightingIndoorOnOffButtonWidget, (leImage*)&LightOn);
    LightControlScreen_LightingIndoorOnOffButtonWidget->fn->setReleasedImage(LightControlScreen_LightingIndoorOnOffButtonWidget, (leImage*)&LightOff);
    LightControlScreen_LightingIndoorOnOffButtonWidget->fn->setPressedEventCallback(LightControlScreen_LightingIndoorOnOffButtonWidget, event_LightControlScreen_LightingIndoorOnOffButtonWidget_OnPressed);
    LightControlScreen_LightingIndoorOnOffButtonWidget->fn->setReleasedEventCallback(LightControlScreen_LightingIndoorOnOffButtonWidget, event_LightControlScreen_LightingIndoorOnOffButtonWidget_OnReleased);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LightingIndoorOnOffButtonWidget);

    LightControlScreen_LightingIndoorConnIcon = leImageWidget_New();
    LightControlScreen_LightingIndoorConnIcon->fn->setPosition(LightControlScreen_LightingIndoorConnIcon, 214, 194);
    LightControlScreen_LightingIndoorConnIcon->fn->setSize(LightControlScreen_LightingIndoorConnIcon, 25, 25);
    LightControlScreen_LightingIndoorConnIcon->fn->setBackgroundType(LightControlScreen_LightingIndoorConnIcon, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LightingIndoorConnIcon->fn->setBorderType(LightControlScreen_LightingIndoorConnIcon, LE_WIDGET_BORDER_NONE);
    LightControlScreen_LightingIndoorConnIcon->fn->setImage(LightControlScreen_LightingIndoorConnIcon, (leImage*)&ConnectIcon);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LightingIndoorConnIcon);

    LightControlScreen_LightingOutdoorConnIcon = leImageWidget_New();
    LightControlScreen_LightingOutdoorConnIcon->fn->setPosition(LightControlScreen_LightingOutdoorConnIcon, 474, 194);
    LightControlScreen_LightingOutdoorConnIcon->fn->setSize(LightControlScreen_LightingOutdoorConnIcon, 25, 25);
    LightControlScreen_LightingOutdoorConnIcon->fn->setBackgroundType(LightControlScreen_LightingOutdoorConnIcon, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LightingOutdoorConnIcon->fn->setBorderType(LightControlScreen_LightingOutdoorConnIcon, LE_WIDGET_BORDER_NONE);
    LightControlScreen_LightingOutdoorConnIcon->fn->setImage(LightControlScreen_LightingOutdoorConnIcon, (leImage*)&ConnectIcon);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LightingOutdoorConnIcon);

    LightControlScreen_CloudWidget = leImageWidget_New();
    LightControlScreen_CloudWidget->fn->setPosition(LightControlScreen_CloudWidget, 739, 4);
    LightControlScreen_CloudWidget->fn->setSize(LightControlScreen_CloudWidget, 50, 50);
    LightControlScreen_CloudWidget->fn->setVisible(LightControlScreen_CloudWidget, LE_FALSE);
    LightControlScreen_CloudWidget->fn->setBackgroundType(LightControlScreen_CloudWidget, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_CloudWidget->fn->setBorderType(LightControlScreen_CloudWidget, LE_WIDGET_BORDER_NONE);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_CloudWidget);

    LightControlScreen_WifiWidget = leImageWidget_New();
    LightControlScreen_WifiWidget->fn->setPosition(LightControlScreen_WifiWidget, 685, 4);
    LightControlScreen_WifiWidget->fn->setSize(LightControlScreen_WifiWidget, 50, 50);
    LightControlScreen_WifiWidget->fn->setVisible(LightControlScreen_WifiWidget, LE_FALSE);
    LightControlScreen_WifiWidget->fn->setBackgroundType(LightControlScreen_WifiWidget, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_WifiWidget->fn->setBorderType(LightControlScreen_WifiWidget, LE_WIDGET_BORDER_NONE);
    LightControlScreen_WifiWidget->fn->setImage(LightControlScreen_WifiWidget, (leImage*)&WifiRed);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_WifiWidget);

    LightControlScreen_G3Widget = leImageWidget_New();
    LightControlScreen_G3Widget->fn->setPosition(LightControlScreen_G3Widget, 630, 3);
    LightControlScreen_G3Widget->fn->setSize(LightControlScreen_G3Widget, 50, 50);
    LightControlScreen_G3Widget->fn->setVisible(LightControlScreen_G3Widget, LE_FALSE);
    LightControlScreen_G3Widget->fn->setBackgroundType(LightControlScreen_G3Widget, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_G3Widget->fn->setBorderType(LightControlScreen_G3Widget, LE_WIDGET_BORDER_NONE);
    LightControlScreen_G3Widget->fn->setImage(LightControlScreen_G3Widget, (leImage*)&g3Red);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_G3Widget);

    LightControlScreen_AlarmWidget = leImageWidget_New();
    LightControlScreen_AlarmWidget->fn->setPosition(LightControlScreen_AlarmWidget, 573, 4);
    LightControlScreen_AlarmWidget->fn->setSize(LightControlScreen_AlarmWidget, 50, 50);
    LightControlScreen_AlarmWidget->fn->setBackgroundType(LightControlScreen_AlarmWidget, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_AlarmWidget->fn->setBorderType(LightControlScreen_AlarmWidget, LE_WIDGET_BORDER_NONE);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_AlarmWidget);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    APP_SCREEN_LIGHTING_OnShow(); // raise event
    
    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_LightControlScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
    
    APP_SCREEN_LIGHTING_screenUpdate();
}

void screenHide_LightControlScreen(void)
{

    APP_SCREEN_LIGHTING_screenHide();
    
    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    LightControlScreen_Panel_0 = NULL;
    LightControlScreen_LabelWidget_0 = NULL;
    LightControlScreen_ImageWidget0 = NULL;
    LightControlScreen_LineWidget0 = NULL;
    LightControlScreen_PanelWidget0 = NULL;
    LightControlScreen_LabelSmartLighting = NULL;
    LightControlScreen_LineWidget0_0 = NULL;
    LightControlScreen_ImageMicrochipWidget = NULL;
    LightControlScreen_LightingIndoorStatusLabel = NULL;
    LightControlScreen_LightingOutdoorStatusLabel = NULL;
    LightControlScreen_LightingIndoorRefreshButtonWidget = NULL;
    LightControlScreen_LightingOutdoorRefreshButtonWidget = NULL;
    LightControlScreen_LightingOutdoorOnOffButtonWidget = NULL;
    LightControlScreen_LightingOutdoorOnStatusLabel = NULL;
    LightControlScreen_LightingOutdoorOffStatusLabel = NULL;
    LightControlScreen_LightingIndoorOffStatusLabel = NULL;
    LightControlScreen_LightingIndoorOnStatusLabel = NULL;
    LightControlScreen_NextLightingButtonWidget = NULL;
    LightControlScreen_NextLightingStatusLabel = NULL;
    LightControlScreen_LightingIndoorOnOffButtonWidget = NULL;
    LightControlScreen_LightingIndoorConnIcon = NULL;
    LightControlScreen_LightingOutdoorConnIcon = NULL;
    LightControlScreen_CloudWidget = NULL;
    LightControlScreen_WifiWidget = NULL;
    LightControlScreen_G3Widget = NULL;
    LightControlScreen_AlarmWidget = NULL;


    showing = LE_FALSE;
}

void screenDestroy_LightControlScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_LightControlScreen(uint32_t lyrIdx)
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

