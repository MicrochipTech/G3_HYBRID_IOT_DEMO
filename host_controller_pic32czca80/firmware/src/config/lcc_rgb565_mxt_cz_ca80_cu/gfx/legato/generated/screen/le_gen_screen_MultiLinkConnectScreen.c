#include "gfx/legato/generated/screen/le_gen_screen_MultiLinkConnectScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* MultiLinkConnectScreen_PanelWidget0;
leLineWidget* MultiLinkConnectScreen_LineWidget0;
leImageWidget* MultiLinkConnectScreen_ImageWidget0;
leImageSequenceWidget* MultiLinkConnectScreen_ImageSequenceWidgetC;
leImageSequenceWidget* MultiLinkConnectScreen_ImageSequenceWidgetB;
leImageSequenceWidget* MultiLinkConnectScreen_ImageSequenceWidgetA;
leImageSequenceWidget* MultiLinkConnectScreen_ProgressAnimSequence;
leLabelWidget* MultiLinkConnectScreen_ConnectionStatusLabel;
leButtonWidget* MultiLinkConnectScreen_HomeButton;
leButtonWidget* MultiLinkConnectScreen_ControlButton;
leLabelWidget* MultiLinkConnectScreen_LabelWidget_0;
leLabelWidget* MultiLinkConnectScreen_SWallConnectionStatusLabel;
leLabelWidget* MultiLinkConnectScreen_LightingWallConnectionStatusLabel;
leLabelWidget* MultiLinkConnectScreen_SignalingWallConnectionStatusLabel;
leLabelWidget* MultiLinkConnectScreen_LabelWidgetC;
leImageWidget* MultiLinkConnectScreen_CheckImageC;
leLabelWidget* MultiLinkConnectScreen_LabelWidgetB;
leImageWidget* MultiLinkConnectScreen_CheckImageB;
leLabelWidget* MultiLinkConnectScreen_LabelWidgetA;
leImageWidget* MultiLinkConnectScreen_CheckImageA;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_MultiLinkConnectScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_MultiLinkConnectScreen(void)
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

    MultiLinkConnectScreen_PanelWidget0 = leWidget_New();
    MultiLinkConnectScreen_PanelWidget0->fn->setPosition(MultiLinkConnectScreen_PanelWidget0, 0, 0);
    MultiLinkConnectScreen_PanelWidget0->fn->setSize(MultiLinkConnectScreen_PanelWidget0, 800, 480);
    MultiLinkConnectScreen_PanelWidget0->fn->setScheme(MultiLinkConnectScreen_PanelWidget0, &BackScheme);
    root0->fn->addChild(root0, (leWidget*)MultiLinkConnectScreen_PanelWidget0);

    MultiLinkConnectScreen_LineWidget0 = leLineWidget_New();
    MultiLinkConnectScreen_LineWidget0->fn->setPosition(MultiLinkConnectScreen_LineWidget0, 97, 25);
    MultiLinkConnectScreen_LineWidget0->fn->setSize(MultiLinkConnectScreen_LineWidget0, 700, 15);
    MultiLinkConnectScreen_LineWidget0->fn->setScheme(MultiLinkConnectScreen_LineWidget0, &WhiteScheme);
    MultiLinkConnectScreen_LineWidget0->fn->setBackgroundType(MultiLinkConnectScreen_LineWidget0, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_LineWidget0->fn->setStartPoint(MultiLinkConnectScreen_LineWidget0, 0, 5);
    MultiLinkConnectScreen_LineWidget0->fn->setEndPoint(MultiLinkConnectScreen_LineWidget0, 700, 5);
    root0->fn->addChild(root0, (leWidget*)MultiLinkConnectScreen_LineWidget0);

    MultiLinkConnectScreen_ImageWidget0 = leImageWidget_New();
    MultiLinkConnectScreen_ImageWidget0->fn->setPosition(MultiLinkConnectScreen_ImageWidget0, 10, 10);
    MultiLinkConnectScreen_ImageWidget0->fn->setSize(MultiLinkConnectScreen_ImageWidget0, 100, 40);
    MultiLinkConnectScreen_ImageWidget0->fn->setBackgroundType(MultiLinkConnectScreen_ImageWidget0, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_ImageWidget0->fn->setBorderType(MultiLinkConnectScreen_ImageWidget0, LE_WIDGET_BORDER_NONE);
    MultiLinkConnectScreen_ImageWidget0->fn->setImage(MultiLinkConnectScreen_ImageWidget0, (leImage*)&MchpLogo_100);
    root0->fn->addChild(root0, (leWidget*)MultiLinkConnectScreen_ImageWidget0);

    MultiLinkConnectScreen_ImageSequenceWidgetC = leImageSequenceWidget_New();
    MultiLinkConnectScreen_ImageSequenceWidgetC->fn->setPosition(MultiLinkConnectScreen_ImageSequenceWidgetC, 441, 361);
    MultiLinkConnectScreen_ImageSequenceWidgetC->fn->setSize(MultiLinkConnectScreen_ImageSequenceWidgetC, 65, 65);
    MultiLinkConnectScreen_ImageSequenceWidgetC->fn->setEnabled(MultiLinkConnectScreen_ImageSequenceWidgetC, LE_FALSE);
    MultiLinkConnectScreen_ImageSequenceWidgetC->fn->setBackgroundType(MultiLinkConnectScreen_ImageSequenceWidgetC, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_ImageSequenceWidgetC->fn->setRepeat(MultiLinkConnectScreen_ImageSequenceWidgetC, LE_TRUE);
    MultiLinkConnectScreen_ImageSequenceWidgetC->fn->setImageCount(MultiLinkConnectScreen_ImageSequenceWidgetC, 2);
    MultiLinkConnectScreen_ImageSequenceWidgetC->fn->setImage(MultiLinkConnectScreen_ImageSequenceWidgetC, 0, &DeviceSelect60);
    MultiLinkConnectScreen_ImageSequenceWidgetC->fn->setImageDelay(MultiLinkConnectScreen_ImageSequenceWidgetC, 0, 1000);
    MultiLinkConnectScreen_ImageSequenceWidgetC->fn->setImage(MultiLinkConnectScreen_ImageSequenceWidgetC, 1, &DeviceNoSelect60);
    MultiLinkConnectScreen_ImageSequenceWidgetC->fn->setImageDelay(MultiLinkConnectScreen_ImageSequenceWidgetC, 1, 1000);
    root0->fn->addChild(root0, (leWidget*)MultiLinkConnectScreen_ImageSequenceWidgetC);

    MultiLinkConnectScreen_LabelWidgetC = leLabelWidget_New();
    MultiLinkConnectScreen_LabelWidgetC->fn->setPosition(MultiLinkConnectScreen_LabelWidgetC, 0, 0);
    MultiLinkConnectScreen_LabelWidgetC->fn->setSize(MultiLinkConnectScreen_LabelWidgetC, 25, 25);
    MultiLinkConnectScreen_LabelWidgetC->fn->setEnabled(MultiLinkConnectScreen_LabelWidgetC, LE_FALSE);
    MultiLinkConnectScreen_LabelWidgetC->fn->setScheme(MultiLinkConnectScreen_LabelWidgetC, &TextScheme);
    MultiLinkConnectScreen_LabelWidgetC->fn->setBackgroundType(MultiLinkConnectScreen_LabelWidgetC, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_LabelWidgetC->fn->setHAlignment(MultiLinkConnectScreen_LabelWidgetC, LE_HALIGN_CENTER);
    MultiLinkConnectScreen_LabelWidgetC->fn->setString(MultiLinkConnectScreen_LabelWidgetC, (leString*)&string_DeviceC);
    MultiLinkConnectScreen_ImageSequenceWidgetC->fn->addChild(MultiLinkConnectScreen_ImageSequenceWidgetC, (leWidget*)MultiLinkConnectScreen_LabelWidgetC);

    MultiLinkConnectScreen_CheckImageC = leImageWidget_New();
    MultiLinkConnectScreen_CheckImageC->fn->setPosition(MultiLinkConnectScreen_CheckImageC, 19, 21);
    MultiLinkConnectScreen_CheckImageC->fn->setSize(MultiLinkConnectScreen_CheckImageC, 30, 30);
    MultiLinkConnectScreen_CheckImageC->fn->setBackgroundType(MultiLinkConnectScreen_CheckImageC, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_CheckImageC->fn->setBorderType(MultiLinkConnectScreen_CheckImageC, LE_WIDGET_BORDER_NONE);
    MultiLinkConnectScreen_CheckImageC->fn->setImage(MultiLinkConnectScreen_CheckImageC, (leImage*)&Check30);
    MultiLinkConnectScreen_ImageSequenceWidgetC->fn->addChild(MultiLinkConnectScreen_ImageSequenceWidgetC, (leWidget*)MultiLinkConnectScreen_CheckImageC);

    MultiLinkConnectScreen_ImageSequenceWidgetB = leImageSequenceWidget_New();
    MultiLinkConnectScreen_ImageSequenceWidgetB->fn->setPosition(MultiLinkConnectScreen_ImageSequenceWidgetB, 371, 241);
    MultiLinkConnectScreen_ImageSequenceWidgetB->fn->setSize(MultiLinkConnectScreen_ImageSequenceWidgetB, 65, 65);
    MultiLinkConnectScreen_ImageSequenceWidgetB->fn->setEnabled(MultiLinkConnectScreen_ImageSequenceWidgetB, LE_FALSE);
    MultiLinkConnectScreen_ImageSequenceWidgetB->fn->setBackgroundType(MultiLinkConnectScreen_ImageSequenceWidgetB, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_ImageSequenceWidgetB->fn->setRepeat(MultiLinkConnectScreen_ImageSequenceWidgetB, LE_TRUE);
    MultiLinkConnectScreen_ImageSequenceWidgetB->fn->setImageCount(MultiLinkConnectScreen_ImageSequenceWidgetB, 2);
    MultiLinkConnectScreen_ImageSequenceWidgetB->fn->setImage(MultiLinkConnectScreen_ImageSequenceWidgetB, 0, &DeviceSelect60);
    MultiLinkConnectScreen_ImageSequenceWidgetB->fn->setImageDelay(MultiLinkConnectScreen_ImageSequenceWidgetB, 0, 1000);
    MultiLinkConnectScreen_ImageSequenceWidgetB->fn->setImage(MultiLinkConnectScreen_ImageSequenceWidgetB, 1, &DeviceNoSelect60);
    MultiLinkConnectScreen_ImageSequenceWidgetB->fn->setImageDelay(MultiLinkConnectScreen_ImageSequenceWidgetB, 1, 1000);
    root0->fn->addChild(root0, (leWidget*)MultiLinkConnectScreen_ImageSequenceWidgetB);

    MultiLinkConnectScreen_LabelWidgetB = leLabelWidget_New();
    MultiLinkConnectScreen_LabelWidgetB->fn->setPosition(MultiLinkConnectScreen_LabelWidgetB, 0, -1);
    MultiLinkConnectScreen_LabelWidgetB->fn->setSize(MultiLinkConnectScreen_LabelWidgetB, 25, 25);
    MultiLinkConnectScreen_LabelWidgetB->fn->setEnabled(MultiLinkConnectScreen_LabelWidgetB, LE_FALSE);
    MultiLinkConnectScreen_LabelWidgetB->fn->setScheme(MultiLinkConnectScreen_LabelWidgetB, &TextScheme);
    MultiLinkConnectScreen_LabelWidgetB->fn->setBackgroundType(MultiLinkConnectScreen_LabelWidgetB, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_LabelWidgetB->fn->setHAlignment(MultiLinkConnectScreen_LabelWidgetB, LE_HALIGN_CENTER);
    MultiLinkConnectScreen_LabelWidgetB->fn->setString(MultiLinkConnectScreen_LabelWidgetB, (leString*)&string_DeviceB);
    MultiLinkConnectScreen_ImageSequenceWidgetB->fn->addChild(MultiLinkConnectScreen_ImageSequenceWidgetB, (leWidget*)MultiLinkConnectScreen_LabelWidgetB);

    MultiLinkConnectScreen_CheckImageB = leImageWidget_New();
    MultiLinkConnectScreen_CheckImageB->fn->setPosition(MultiLinkConnectScreen_CheckImageB, 19, 21);
    MultiLinkConnectScreen_CheckImageB->fn->setSize(MultiLinkConnectScreen_CheckImageB, 30, 30);
    MultiLinkConnectScreen_CheckImageB->fn->setBackgroundType(MultiLinkConnectScreen_CheckImageB, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_CheckImageB->fn->setBorderType(MultiLinkConnectScreen_CheckImageB, LE_WIDGET_BORDER_NONE);
    MultiLinkConnectScreen_CheckImageB->fn->setImage(MultiLinkConnectScreen_CheckImageB, (leImage*)&Check30);
    MultiLinkConnectScreen_ImageSequenceWidgetB->fn->addChild(MultiLinkConnectScreen_ImageSequenceWidgetB, (leWidget*)MultiLinkConnectScreen_CheckImageB);

    MultiLinkConnectScreen_ImageSequenceWidgetA = leImageSequenceWidget_New();
    MultiLinkConnectScreen_ImageSequenceWidgetA->fn->setPosition(MultiLinkConnectScreen_ImageSequenceWidgetA, 441, 121);
    MultiLinkConnectScreen_ImageSequenceWidgetA->fn->setSize(MultiLinkConnectScreen_ImageSequenceWidgetA, 65, 65);
    MultiLinkConnectScreen_ImageSequenceWidgetA->fn->setEnabled(MultiLinkConnectScreen_ImageSequenceWidgetA, LE_FALSE);
    MultiLinkConnectScreen_ImageSequenceWidgetA->fn->setBackgroundType(MultiLinkConnectScreen_ImageSequenceWidgetA, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_ImageSequenceWidgetA->fn->setRepeat(MultiLinkConnectScreen_ImageSequenceWidgetA, LE_TRUE);
    MultiLinkConnectScreen_ImageSequenceWidgetA->fn->setImageCount(MultiLinkConnectScreen_ImageSequenceWidgetA, 2);
    MultiLinkConnectScreen_ImageSequenceWidgetA->fn->setImage(MultiLinkConnectScreen_ImageSequenceWidgetA, 0, &DeviceSelect60);
    MultiLinkConnectScreen_ImageSequenceWidgetA->fn->setImageDelay(MultiLinkConnectScreen_ImageSequenceWidgetA, 0, 1000);
    MultiLinkConnectScreen_ImageSequenceWidgetA->fn->setImage(MultiLinkConnectScreen_ImageSequenceWidgetA, 1, &DeviceNoSelect60);
    MultiLinkConnectScreen_ImageSequenceWidgetA->fn->setImageDelay(MultiLinkConnectScreen_ImageSequenceWidgetA, 1, 1000);
    root0->fn->addChild(root0, (leWidget*)MultiLinkConnectScreen_ImageSequenceWidgetA);

    MultiLinkConnectScreen_LabelWidgetA = leLabelWidget_New();
    MultiLinkConnectScreen_LabelWidgetA->fn->setPosition(MultiLinkConnectScreen_LabelWidgetA, 0, -1);
    MultiLinkConnectScreen_LabelWidgetA->fn->setSize(MultiLinkConnectScreen_LabelWidgetA, 25, 25);
    MultiLinkConnectScreen_LabelWidgetA->fn->setEnabled(MultiLinkConnectScreen_LabelWidgetA, LE_FALSE);
    MultiLinkConnectScreen_LabelWidgetA->fn->setScheme(MultiLinkConnectScreen_LabelWidgetA, &TextScheme);
    MultiLinkConnectScreen_LabelWidgetA->fn->setBackgroundType(MultiLinkConnectScreen_LabelWidgetA, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_LabelWidgetA->fn->setHAlignment(MultiLinkConnectScreen_LabelWidgetA, LE_HALIGN_CENTER);
    MultiLinkConnectScreen_LabelWidgetA->fn->setString(MultiLinkConnectScreen_LabelWidgetA, (leString*)&string_DeviceA);
    MultiLinkConnectScreen_ImageSequenceWidgetA->fn->addChild(MultiLinkConnectScreen_ImageSequenceWidgetA, (leWidget*)MultiLinkConnectScreen_LabelWidgetA);

    MultiLinkConnectScreen_CheckImageA = leImageWidget_New();
    MultiLinkConnectScreen_CheckImageA->fn->setPosition(MultiLinkConnectScreen_CheckImageA, 19, 21);
    MultiLinkConnectScreen_CheckImageA->fn->setSize(MultiLinkConnectScreen_CheckImageA, 30, 30);
    MultiLinkConnectScreen_CheckImageA->fn->setBackgroundType(MultiLinkConnectScreen_CheckImageA, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_CheckImageA->fn->setBorderType(MultiLinkConnectScreen_CheckImageA, LE_WIDGET_BORDER_NONE);
    MultiLinkConnectScreen_CheckImageA->fn->setImage(MultiLinkConnectScreen_CheckImageA, (leImage*)&Check30);
    MultiLinkConnectScreen_ImageSequenceWidgetA->fn->addChild(MultiLinkConnectScreen_ImageSequenceWidgetA, (leWidget*)MultiLinkConnectScreen_CheckImageA);

    MultiLinkConnectScreen_ProgressAnimSequence = leImageSequenceWidget_New();
    MultiLinkConnectScreen_ProgressAnimSequence->fn->setPosition(MultiLinkConnectScreen_ProgressAnimSequence, 541, 294);
    MultiLinkConnectScreen_ProgressAnimSequence->fn->setSize(MultiLinkConnectScreen_ProgressAnimSequence, 100, 20);
    MultiLinkConnectScreen_ProgressAnimSequence->fn->setBackgroundType(MultiLinkConnectScreen_ProgressAnimSequence, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_ProgressAnimSequence->fn->setRepeat(MultiLinkConnectScreen_ProgressAnimSequence, LE_TRUE);
    MultiLinkConnectScreen_ProgressAnimSequence->fn->setImageCount(MultiLinkConnectScreen_ProgressAnimSequence, 4);
    MultiLinkConnectScreen_ProgressAnimSequence->fn->setImage(MultiLinkConnectScreen_ProgressAnimSequence, 0, &progress_anim0);
    MultiLinkConnectScreen_ProgressAnimSequence->fn->setImageDelay(MultiLinkConnectScreen_ProgressAnimSequence, 0, 1000);
    MultiLinkConnectScreen_ProgressAnimSequence->fn->setImage(MultiLinkConnectScreen_ProgressAnimSequence, 1, &progress_anim1);
    MultiLinkConnectScreen_ProgressAnimSequence->fn->setImageDelay(MultiLinkConnectScreen_ProgressAnimSequence, 1, 1000);
    MultiLinkConnectScreen_ProgressAnimSequence->fn->setImage(MultiLinkConnectScreen_ProgressAnimSequence, 2, &progress_anim2);
    MultiLinkConnectScreen_ProgressAnimSequence->fn->setImageDelay(MultiLinkConnectScreen_ProgressAnimSequence, 2, 1000);
    MultiLinkConnectScreen_ProgressAnimSequence->fn->setImage(MultiLinkConnectScreen_ProgressAnimSequence, 3, &progress_anim3);
    MultiLinkConnectScreen_ProgressAnimSequence->fn->setImageDelay(MultiLinkConnectScreen_ProgressAnimSequence, 3, 1000);
    root0->fn->addChild(root0, (leWidget*)MultiLinkConnectScreen_ProgressAnimSequence);

    MultiLinkConnectScreen_ConnectionStatusLabel = leLabelWidget_New();
    MultiLinkConnectScreen_ConnectionStatusLabel->fn->setPosition(MultiLinkConnectScreen_ConnectionStatusLabel, 518, 236);
    MultiLinkConnectScreen_ConnectionStatusLabel->fn->setSize(MultiLinkConnectScreen_ConnectionStatusLabel, 154, 38);
    MultiLinkConnectScreen_ConnectionStatusLabel->fn->setScheme(MultiLinkConnectScreen_ConnectionStatusLabel, &TextScheme);
    MultiLinkConnectScreen_ConnectionStatusLabel->fn->setBackgroundType(MultiLinkConnectScreen_ConnectionStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_ConnectionStatusLabel->fn->setHAlignment(MultiLinkConnectScreen_ConnectionStatusLabel, LE_HALIGN_CENTER);
    MultiLinkConnectScreen_ConnectionStatusLabel->fn->setString(MultiLinkConnectScreen_ConnectionStatusLabel, (leString*)&string_ConnectingString);
    root0->fn->addChild(root0, (leWidget*)MultiLinkConnectScreen_ConnectionStatusLabel);

    MultiLinkConnectScreen_HomeButton = leButtonWidget_New();
    MultiLinkConnectScreen_HomeButton->fn->setPosition(MultiLinkConnectScreen_HomeButton, 0, 430);
    MultiLinkConnectScreen_HomeButton->fn->setSize(MultiLinkConnectScreen_HomeButton, 60, 50);
    MultiLinkConnectScreen_HomeButton->fn->setScheme(MultiLinkConnectScreen_HomeButton, &TextInactiveScheme);
    MultiLinkConnectScreen_HomeButton->fn->setBackgroundType(MultiLinkConnectScreen_HomeButton, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_HomeButton->fn->setBorderType(MultiLinkConnectScreen_HomeButton, LE_WIDGET_BORDER_NONE);
    MultiLinkConnectScreen_HomeButton->fn->setString(MultiLinkConnectScreen_HomeButton, (leString*)&string_DisconnectString);
    MultiLinkConnectScreen_HomeButton->fn->setPressedImage(MultiLinkConnectScreen_HomeButton, (leImage*)&Disconnect20);
    MultiLinkConnectScreen_HomeButton->fn->setReleasedImage(MultiLinkConnectScreen_HomeButton, (leImage*)&Disconnect20);
    MultiLinkConnectScreen_HomeButton->fn->setImagePosition(MultiLinkConnectScreen_HomeButton, LE_RELATIVE_POSITION_ABOVE);
    MultiLinkConnectScreen_HomeButton->fn->setImageMargin(MultiLinkConnectScreen_HomeButton, 5);
    MultiLinkConnectScreen_HomeButton->fn->setPressedEventCallback(MultiLinkConnectScreen_HomeButton, event_MultiLinkConnectScreen_HomeButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)MultiLinkConnectScreen_HomeButton);

    MultiLinkConnectScreen_ControlButton = leButtonWidget_New();
    MultiLinkConnectScreen_ControlButton->fn->setPosition(MultiLinkConnectScreen_ControlButton, 546, 480);
    MultiLinkConnectScreen_ControlButton->fn->setSize(MultiLinkConnectScreen_ControlButton, 100, 100);
    MultiLinkConnectScreen_ControlButton->fn->setBackgroundType(MultiLinkConnectScreen_ControlButton, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_ControlButton->fn->setBorderType(MultiLinkConnectScreen_ControlButton, LE_WIDGET_BORDER_NONE);
    MultiLinkConnectScreen_ControlButton->fn->setPressedImage(MultiLinkConnectScreen_ControlButton, (leImage*)&ControlButton_100);
    MultiLinkConnectScreen_ControlButton->fn->setReleasedImage(MultiLinkConnectScreen_ControlButton, (leImage*)&ControlButton_100);
    MultiLinkConnectScreen_ControlButton->fn->setPressedEventCallback(MultiLinkConnectScreen_ControlButton, event_MultiLinkConnectScreen_ControlButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)MultiLinkConnectScreen_ControlButton);

    MultiLinkConnectScreen_LabelWidget_0 = leLabelWidget_New();
    MultiLinkConnectScreen_LabelWidget_0->fn->setPosition(MultiLinkConnectScreen_LabelWidget_0, 410, 2);
    MultiLinkConnectScreen_LabelWidget_0->fn->setSize(MultiLinkConnectScreen_LabelWidget_0, 380, 25);
    MultiLinkConnectScreen_LabelWidget_0->fn->setScheme(MultiLinkConnectScreen_LabelWidget_0, &TextScheme);
    MultiLinkConnectScreen_LabelWidget_0->fn->setHAlignment(MultiLinkConnectScreen_LabelWidget_0, LE_HALIGN_CENTER);
    MultiLinkConnectScreen_LabelWidget_0->fn->setString(MultiLinkConnectScreen_LabelWidget_0, (leString*)&string_DemoName);
    root0->fn->addChild(root0, (leWidget*)MultiLinkConnectScreen_LabelWidget_0);

    MultiLinkConnectScreen_SWallConnectionStatusLabel = leLabelWidget_New();
    MultiLinkConnectScreen_SWallConnectionStatusLabel->fn->setPosition(MultiLinkConnectScreen_SWallConnectionStatusLabel, 190, 138);
    MultiLinkConnectScreen_SWallConnectionStatusLabel->fn->setSize(MultiLinkConnectScreen_SWallConnectionStatusLabel, 232, 36);
    MultiLinkConnectScreen_SWallConnectionStatusLabel->fn->setScheme(MultiLinkConnectScreen_SWallConnectionStatusLabel, &TextScheme);
    MultiLinkConnectScreen_SWallConnectionStatusLabel->fn->setBackgroundType(MultiLinkConnectScreen_SWallConnectionStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_SWallConnectionStatusLabel->fn->setHAlignment(MultiLinkConnectScreen_SWallConnectionStatusLabel, LE_HALIGN_CENTER);
    MultiLinkConnectScreen_SWallConnectionStatusLabel->fn->setString(MultiLinkConnectScreen_SWallConnectionStatusLabel, (leString*)&string_SWallConnectionStatus);
    root0->fn->addChild(root0, (leWidget*)MultiLinkConnectScreen_SWallConnectionStatusLabel);

    MultiLinkConnectScreen_LightingWallConnectionStatusLabel = leLabelWidget_New();
    MultiLinkConnectScreen_LightingWallConnectionStatusLabel->fn->setPosition(MultiLinkConnectScreen_LightingWallConnectionStatusLabel, 144, 256);
    MultiLinkConnectScreen_LightingWallConnectionStatusLabel->fn->setSize(MultiLinkConnectScreen_LightingWallConnectionStatusLabel, 232, 36);
    MultiLinkConnectScreen_LightingWallConnectionStatusLabel->fn->setScheme(MultiLinkConnectScreen_LightingWallConnectionStatusLabel, &TextScheme);
    MultiLinkConnectScreen_LightingWallConnectionStatusLabel->fn->setBackgroundType(MultiLinkConnectScreen_LightingWallConnectionStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_LightingWallConnectionStatusLabel->fn->setHAlignment(MultiLinkConnectScreen_LightingWallConnectionStatusLabel, LE_HALIGN_CENTER);
    MultiLinkConnectScreen_LightingWallConnectionStatusLabel->fn->setString(MultiLinkConnectScreen_LightingWallConnectionStatusLabel, (leString*)&string_LightingWallConnectionStatus);
    root0->fn->addChild(root0, (leWidget*)MultiLinkConnectScreen_LightingWallConnectionStatusLabel);

    MultiLinkConnectScreen_SignalingWallConnectionStatusLabel = leLabelWidget_New();
    MultiLinkConnectScreen_SignalingWallConnectionStatusLabel->fn->setPosition(MultiLinkConnectScreen_SignalingWallConnectionStatusLabel, 210, 378);
    MultiLinkConnectScreen_SignalingWallConnectionStatusLabel->fn->setSize(MultiLinkConnectScreen_SignalingWallConnectionStatusLabel, 232, 36);
    MultiLinkConnectScreen_SignalingWallConnectionStatusLabel->fn->setScheme(MultiLinkConnectScreen_SignalingWallConnectionStatusLabel, &TextScheme);
    MultiLinkConnectScreen_SignalingWallConnectionStatusLabel->fn->setBackgroundType(MultiLinkConnectScreen_SignalingWallConnectionStatusLabel, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkConnectScreen_SignalingWallConnectionStatusLabel->fn->setHAlignment(MultiLinkConnectScreen_SignalingWallConnectionStatusLabel, LE_HALIGN_CENTER);
    MultiLinkConnectScreen_SignalingWallConnectionStatusLabel->fn->setString(MultiLinkConnectScreen_SignalingWallConnectionStatusLabel, (leString*)&string_SignalingWallConnectionStatus);
    root0->fn->addChild(root0, (leWidget*)MultiLinkConnectScreen_SignalingWallConnectionStatusLabel);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    MultiLinkConnectScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_MultiLinkConnectScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    MultiLinkConnectScreen_OnUpdate(); // raise event
}

void screenHide_MultiLinkConnectScreen(void)
{
    MultiLinkConnectScreen_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    MultiLinkConnectScreen_PanelWidget0 = NULL;
    MultiLinkConnectScreen_LineWidget0 = NULL;
    MultiLinkConnectScreen_ImageWidget0 = NULL;
    MultiLinkConnectScreen_ImageSequenceWidgetC = NULL;
    MultiLinkConnectScreen_ImageSequenceWidgetB = NULL;
    MultiLinkConnectScreen_ImageSequenceWidgetA = NULL;
    MultiLinkConnectScreen_ProgressAnimSequence = NULL;
    MultiLinkConnectScreen_ConnectionStatusLabel = NULL;
    MultiLinkConnectScreen_HomeButton = NULL;
    MultiLinkConnectScreen_ControlButton = NULL;
    MultiLinkConnectScreen_LabelWidget_0 = NULL;
    MultiLinkConnectScreen_SWallConnectionStatusLabel = NULL;
    MultiLinkConnectScreen_LightingWallConnectionStatusLabel = NULL;
    MultiLinkConnectScreen_SignalingWallConnectionStatusLabel = NULL;
    MultiLinkConnectScreen_LabelWidgetC = NULL;
    MultiLinkConnectScreen_CheckImageC = NULL;
    MultiLinkConnectScreen_LabelWidgetB = NULL;
    MultiLinkConnectScreen_CheckImageB = NULL;
    MultiLinkConnectScreen_LabelWidgetA = NULL;
    MultiLinkConnectScreen_CheckImageA = NULL;


    showing = LE_FALSE;
}

void screenDestroy_MultiLinkConnectScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_MultiLinkConnectScreen(uint32_t lyrIdx)
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

