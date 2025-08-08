#include "gfx/legato/generated/screen/le_gen_screen_MainMenu.h"

// screen member widget declarations
static leWidget* root0;

leWidget* MainMenu_BackPanel;
leLabelWidget* MainMenu_LabelWidget0;
leLineWidget* MainMenu_LineWidget0;
leImageWidget* MainMenu_ImageWidget0;
leButtonWidget* MainMenu_ConnectButton;
leButtonWidget* MainMenu_ControlButton;
leButtonWidget* MainMenu_ConfigButton;
leLabelWidget* MainMenu_LabelWidget1;
leLabelWidget* MainMenu_ControlLabel;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_MainMenu(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_MainMenu(void)
{
    if(showing == LE_TRUE)
        return LE_FAILURE;

    // layer 0
    root0 = leWidget_New();
    root0->fn->setSize(root0, 800, 480);
    root0->fn->setBackgroundType(root0, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->setMargins(root0, 0, 0, 0, 0);
    root0->flags |= LE_WIDGET_IGNOREEVENTS;
    root0->flags |= LE_WIDGET_IGNOREPICK;

    MainMenu_BackPanel = leWidget_New();
    MainMenu_BackPanel->fn->setPosition(MainMenu_BackPanel, 0, 0);
    MainMenu_BackPanel->fn->setSize(MainMenu_BackPanel, 800, 480);
    MainMenu_BackPanel->fn->setScheme(MainMenu_BackPanel, &BackScheme);
    root0->fn->addChild(root0, (leWidget*)MainMenu_BackPanel);

    MainMenu_LabelWidget0 = leLabelWidget_New();
    MainMenu_LabelWidget0->fn->setPosition(MainMenu_LabelWidget0, 410, 2);
    MainMenu_LabelWidget0->fn->setSize(MainMenu_LabelWidget0, 380, 25);
    MainMenu_LabelWidget0->fn->setScheme(MainMenu_LabelWidget0, &TextScheme);
    MainMenu_LabelWidget0->fn->setHAlignment(MainMenu_LabelWidget0, LE_HALIGN_CENTER);
    MainMenu_LabelWidget0->fn->setString(MainMenu_LabelWidget0, (leString*)&string_DemoName);
    root0->fn->addChild(root0, (leWidget*)MainMenu_LabelWidget0);

    MainMenu_LineWidget0 = leLineWidget_New();
    MainMenu_LineWidget0->fn->setPosition(MainMenu_LineWidget0, 97, 25);
    MainMenu_LineWidget0->fn->setSize(MainMenu_LineWidget0, 703, 15);
    MainMenu_LineWidget0->fn->setScheme(MainMenu_LineWidget0, &WhiteScheme);
    MainMenu_LineWidget0->fn->setBackgroundType(MainMenu_LineWidget0, LE_WIDGET_BACKGROUND_NONE);
    MainMenu_LineWidget0->fn->setStartPoint(MainMenu_LineWidget0, 0, 5);
    MainMenu_LineWidget0->fn->setEndPoint(MainMenu_LineWidget0, 700, 5);
    root0->fn->addChild(root0, (leWidget*)MainMenu_LineWidget0);

    MainMenu_ImageWidget0 = leImageWidget_New();
    MainMenu_ImageWidget0->fn->setPosition(MainMenu_ImageWidget0, 10, 10);
    MainMenu_ImageWidget0->fn->setSize(MainMenu_ImageWidget0, 100, 40);
    MainMenu_ImageWidget0->fn->setBackgroundType(MainMenu_ImageWidget0, LE_WIDGET_BACKGROUND_NONE);
    MainMenu_ImageWidget0->fn->setBorderType(MainMenu_ImageWidget0, LE_WIDGET_BORDER_NONE);
    MainMenu_ImageWidget0->fn->setImage(MainMenu_ImageWidget0, (leImage*)&MchpLogo_100);
    root0->fn->addChild(root0, (leWidget*)MainMenu_ImageWidget0);

    MainMenu_ConnectButton = leButtonWidget_New();
    MainMenu_ConnectButton->fn->setPosition(MainMenu_ConnectButton, 341, 194);
    MainMenu_ConnectButton->fn->setSize(MainMenu_ConnectButton, 120, 150);
    MainMenu_ConnectButton->fn->setBackgroundType(MainMenu_ConnectButton, LE_WIDGET_BACKGROUND_NONE);
    MainMenu_ConnectButton->fn->setBorderType(MainMenu_ConnectButton, LE_WIDGET_BORDER_NONE);
    MainMenu_ConnectButton->fn->setVAlignment(MainMenu_ConnectButton, LE_VALIGN_TOP);
    MainMenu_ConnectButton->fn->setPressedImage(MainMenu_ConnectButton, (leImage*)&ConnectButton_100);
    MainMenu_ConnectButton->fn->setReleasedImage(MainMenu_ConnectButton, (leImage*)&ConnectButton_100);
    MainMenu_ConnectButton->fn->setPressedEventCallback(MainMenu_ConnectButton, event_MainMenu_ConnectButton_OnPressed);
    MainMenu_ConnectButton->fn->setReleasedEventCallback(MainMenu_ConnectButton, event_MainMenu_ConnectButton_OnReleased);
    root0->fn->addChild(root0, (leWidget*)MainMenu_ConnectButton);

    MainMenu_LabelWidget1 = leLabelWidget_New();
    MainMenu_LabelWidget1->fn->setPosition(MainMenu_LabelWidget1, 27, 114);
    MainMenu_LabelWidget1->fn->setSize(MainMenu_LabelWidget1, 70, 23);
    MainMenu_LabelWidget1->fn->setScheme(MainMenu_LabelWidget1, &WhiteScheme);
    MainMenu_LabelWidget1->fn->setBackgroundType(MainMenu_LabelWidget1, LE_WIDGET_BACKGROUND_NONE);
    MainMenu_LabelWidget1->fn->setHAlignment(MainMenu_LabelWidget1, LE_HALIGN_CENTER);
    MainMenu_LabelWidget1->fn->setString(MainMenu_LabelWidget1, (leString*)&string_StartString);
    MainMenu_ConnectButton->fn->addChild(MainMenu_ConnectButton, (leWidget*)MainMenu_LabelWidget1);

    MainMenu_ControlButton = leButtonWidget_New();
    MainMenu_ControlButton->fn->setPosition(MainMenu_ControlButton, 346, 483);
    MainMenu_ControlButton->fn->setSize(MainMenu_ControlButton, 120, 150);
    MainMenu_ControlButton->fn->setVisible(MainMenu_ControlButton, LE_FALSE);
    MainMenu_ControlButton->fn->setBackgroundType(MainMenu_ControlButton, LE_WIDGET_BACKGROUND_NONE);
    MainMenu_ControlButton->fn->setBorderType(MainMenu_ControlButton, LE_WIDGET_BORDER_NONE);
    MainMenu_ControlButton->fn->setVAlignment(MainMenu_ControlButton, LE_VALIGN_TOP);
    MainMenu_ControlButton->fn->setPressedImage(MainMenu_ControlButton, (leImage*)&ControlButton_100);
    MainMenu_ControlButton->fn->setReleasedImage(MainMenu_ControlButton, (leImage*)&ControlButton_100);
    MainMenu_ControlButton->fn->setReleasedEventCallback(MainMenu_ControlButton, event_MainMenu_ControlButton_OnReleased);
    root0->fn->addChild(root0, (leWidget*)MainMenu_ControlButton);

    MainMenu_ControlLabel = leLabelWidget_New();
    MainMenu_ControlLabel->fn->setPosition(MainMenu_ControlLabel, 24, 114);
    MainMenu_ControlLabel->fn->setSize(MainMenu_ControlLabel, 70, 23);
    MainMenu_ControlLabel->fn->setScheme(MainMenu_ControlLabel, &TextScheme);
    MainMenu_ControlLabel->fn->setBackgroundType(MainMenu_ControlLabel, LE_WIDGET_BACKGROUND_NONE);
    MainMenu_ControlLabel->fn->setHAlignment(MainMenu_ControlLabel, LE_HALIGN_CENTER);
    MainMenu_ControlLabel->fn->setString(MainMenu_ControlLabel, (leString*)&string_ControlString);
    MainMenu_ControlButton->fn->addChild(MainMenu_ControlButton, (leWidget*)MainMenu_ControlLabel);

    MainMenu_ConfigButton = leButtonWidget_New();
    MainMenu_ConfigButton->fn->setPosition(MainMenu_ConfigButton, 0, 420);
    MainMenu_ConfigButton->fn->setSize(MainMenu_ConfigButton, 60, 60);
    MainMenu_ConfigButton->fn->setScheme(MainMenu_ConfigButton, &BackScheme);
    MainMenu_ConfigButton->fn->setBorderType(MainMenu_ConfigButton, LE_WIDGET_BORDER_NONE);
    MainMenu_ConfigButton->fn->setReleasedEventCallback(MainMenu_ConfigButton, event_MainMenu_ConfigButton_OnReleased);
    root0->fn->addChild(root0, (leWidget*)MainMenu_ConfigButton);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    MainMenu_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_MainMenu(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    MainMenu_OnUpdate(); // raise event
}

void screenHide_MainMenu(void)
{
    MainMenu_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    MainMenu_BackPanel = NULL;
    MainMenu_LabelWidget0 = NULL;
    MainMenu_LineWidget0 = NULL;
    MainMenu_ImageWidget0 = NULL;
    MainMenu_ConnectButton = NULL;
    MainMenu_ControlButton = NULL;
    MainMenu_ConfigButton = NULL;
    MainMenu_LabelWidget1 = NULL;
    MainMenu_ControlLabel = NULL;


    showing = LE_FALSE;
}

void screenDestroy_MainMenu(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_MainMenu(uint32_t lyrIdx)
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

