#include "gfx/legato/generated/screen/le_gen_screen_LightControlScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* LightControlScreen_PanelWidget0;
leLineWidget* LightControlScreen_LineWidget0;
leImageWidget* LightControlScreen_ImageWidget0;
leButtonWidget* LightControlScreen_DisconnectButton;
leImageWidget* LightControlScreen_ColorPickerImage;
leButtonWidget* LightControlScreen_DeviceCButton;
leButtonWidget* LightControlScreen_DeviceBButton;
leButtonWidget* LightControlScreen_DeviceAButton;
leImageWidget* LightControlScreen_SliderImageWidget;
leWidget* LightControlScreen_SliderControlPanel;
leImageWidget* LightControlScreen_ScrollKnobImageWidget;
leWidget* LightControlScreen_SelectedColorPanelA;
leButtonWidget* LightControlScreen_AllDevicesButton;
leLabelWidget* LightControlScreen_LabelWidget_0;
leWidget* LightControlScreen_SelectedColorPanelB;
leWidget* LightControlScreen_SelectedColorPanelC;
leWidget* LightControlScreen_DeviceDataPanelA;
leLineGraphWidget* LightControlScreen_LineGraphWidget_0;
leBarGraphWidget* LightControlScreen_BarGraphWidget_0;
leButtonWidget* LightControlScreen_DeviceInfoButton;
leButtonWidget* LightControlScreen_BLEInfoButton;
leButtonWidget* LightControlScreen_WiFiInfoButton;
leWidget* LightControlScreen_ColorWheelSelectColor;
leImageSequenceWidget* LightControlScreen_AnimImageWidget;
leImageSequenceWidget* LightControlScreen_ImageSequenceWidgetC;
leLabelWidget* LightControlScreen_LabelWidget2;
leLabelWidget* LightControlScreen_TempLabelC;
leImageSequenceWidget* LightControlScreen_ImageSequenceWidgetB;
leLabelWidget* LightControlScreen_LabelWidget1;
leLabelWidget* LightControlScreen_TempLabelB;
leImageSequenceWidget* LightControlScreen_ImageSequenceWidgetA;
leLabelWidget* LightControlScreen_LabelWidget0;
leLabelWidget* LightControlScreen_TempLabelA;
leLabelWidget* LightControlScreen_ColorGraphLabel;
leLabelWidget* LightControlScreen_TempSensorGraphLabel;
leLabelWidget* LightControlScreen_LineGraphLabelA;
leLabelWidget* LightControlScreen_LineGraphLabelB;
leLabelWidget* LightControlScreen_LineGraphLabelC;
leLabelWidget* LightControlScreen_DeviceInfoLabel;
leLabelWidget* LightControlScreen_BLEDeviceAName;
leLabelWidget* LightControlScreen_BLEDeviceBName;
leLabelWidget* LightControlScreen_BLEDeviceCName;
leImageWidget* LightControlScreen_BLEDeviceAOK;
leImageWidget* LightControlScreen_BLEDeviceBOK;
leImageWidget* LightControlScreen_BLEDeviceCOK;
leWidget* LightControlScreen_NetInfoPanel;
leWidget* LightControlScreen_PanelWidget_0;
leWidget* LightControlScreen_PanelWidget_1;
leWidget* LightControlScreen_PanelWidget_2;
leLabelWidget* LightControlScreen_NetInfString;
leLabelWidget* LightControlScreen_NetSSIDString;
leLabelWidget* LightControlScreen_NetIPString;
leLabelWidget* LightControlScreen_NetConnString;
leLabelWidget* LightControlScreen_NetURLString;
leImageWidget* LightControlScreen_NetWebURLQR;
leLabelWidget* LightControlScreen_NetInterfaceInfo;
leLabelWidget* LightControlScreen_NetSSIDInfo;
leLabelWidget* LightControlScreen_NetIPInfo;
leLabelWidget* LightControlScreen_NetConnInfo;
leLabelWidget* LightControlScreen_NetURLInfo;
leWidget* LightControlScreen_MfgBlock;
leWidget* LightControlScreen_BldgBlock;
leWidget* LightControlScreen_EnergyBlock;
leWidget* LightControlScreen_EnvBlock;
leWidget* LightControlScreen_AgriBlock;
leWidget* LightControlScreen_LogiBlock;
leWidget* LightControlScreen_HomeAutoBlock;
leWidget* LightControlScreen_SmartCityBlock;
leWidget* LightControlScreen_SmartConSecLogoBlock;
leWidget* LightControlScreen_SmartBlock;
leWidget* LightControlScreen_ConnectedBlock;
leWidget* LightControlScreen_SecureBlock;

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

    LightControlScreen_PanelWidget0 = leWidget_New();
    LightControlScreen_PanelWidget0->fn->setPosition(LightControlScreen_PanelWidget0, 1, 0);
    LightControlScreen_PanelWidget0->fn->setSize(LightControlScreen_PanelWidget0, 800, 480);
    LightControlScreen_PanelWidget0->fn->setScheme(LightControlScreen_PanelWidget0, &BackScheme);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_PanelWidget0);

    LightControlScreen_LineWidget0 = leLineWidget_New();
    LightControlScreen_LineWidget0->fn->setPosition(LightControlScreen_LineWidget0, 97, 25);
    LightControlScreen_LineWidget0->fn->setSize(LightControlScreen_LineWidget0, 700, 15);
    LightControlScreen_LineWidget0->fn->setScheme(LightControlScreen_LineWidget0, &WhiteScheme);
    LightControlScreen_LineWidget0->fn->setBackgroundType(LightControlScreen_LineWidget0, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LineWidget0->fn->setStartPoint(LightControlScreen_LineWidget0, 0, 5);
    LightControlScreen_LineWidget0->fn->setEndPoint(LightControlScreen_LineWidget0, 700, 5);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LineWidget0);

    LightControlScreen_ImageWidget0 = leImageWidget_New();
    LightControlScreen_ImageWidget0->fn->setPosition(LightControlScreen_ImageWidget0, 10, 10);
    LightControlScreen_ImageWidget0->fn->setSize(LightControlScreen_ImageWidget0, 100, 40);
    LightControlScreen_ImageWidget0->fn->setBackgroundType(LightControlScreen_ImageWidget0, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_ImageWidget0->fn->setBorderType(LightControlScreen_ImageWidget0, LE_WIDGET_BORDER_NONE);
    LightControlScreen_ImageWidget0->fn->setImage(LightControlScreen_ImageWidget0, (leImage*)&MchpLogo_100);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_ImageWidget0);

    LightControlScreen_DisconnectButton = leButtonWidget_New();
    LightControlScreen_DisconnectButton->fn->setPosition(LightControlScreen_DisconnectButton, 732, 418);
    LightControlScreen_DisconnectButton->fn->setSize(LightControlScreen_DisconnectButton, 60, 50);
    LightControlScreen_DisconnectButton->fn->setScheme(LightControlScreen_DisconnectButton, &TextInactiveScheme);
    LightControlScreen_DisconnectButton->fn->setBorderType(LightControlScreen_DisconnectButton, LE_WIDGET_BORDER_NONE);
    LightControlScreen_DisconnectButton->fn->setString(LightControlScreen_DisconnectButton, (leString*)&string_DisconnectString);
    LightControlScreen_DisconnectButton->fn->setPressedImage(LightControlScreen_DisconnectButton, (leImage*)&Disconnect20);
    LightControlScreen_DisconnectButton->fn->setReleasedImage(LightControlScreen_DisconnectButton, (leImage*)&Disconnect20);
    LightControlScreen_DisconnectButton->fn->setImagePosition(LightControlScreen_DisconnectButton, LE_RELATIVE_POSITION_ABOVE);
    LightControlScreen_DisconnectButton->fn->setImageMargin(LightControlScreen_DisconnectButton, 5);
    LightControlScreen_DisconnectButton->fn->setPressedEventCallback(LightControlScreen_DisconnectButton, event_LightControlScreen_DisconnectButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_DisconnectButton);

    LightControlScreen_ColorPickerImage = leImageWidget_New();
    LightControlScreen_ColorPickerImage->fn->setPosition(LightControlScreen_ColorPickerImage, 514, 173);
    LightControlScreen_ColorPickerImage->fn->setSize(LightControlScreen_ColorPickerImage, 200, 200);
    LightControlScreen_ColorPickerImage->fn->setBackgroundType(LightControlScreen_ColorPickerImage, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_ColorPickerImage->fn->setBorderType(LightControlScreen_ColorPickerImage, LE_WIDGET_BORDER_NONE);
    LightControlScreen_ColorPickerImage->fn->setMargins(LightControlScreen_ColorPickerImage, 0, 0, 0, 0);
    LightControlScreen_ColorPickerImage->fn->setImage(LightControlScreen_ColorPickerImage, (leImage*)&ColorPickerBlueBack200_565);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_ColorPickerImage);

    LightControlScreen_DeviceCButton = leButtonWidget_New();
    LightControlScreen_DeviceCButton->fn->setPosition(LightControlScreen_DeviceCButton, 440, 360);
    LightControlScreen_DeviceCButton->fn->setSize(LightControlScreen_DeviceCButton, 65, 65);
    LightControlScreen_DeviceCButton->fn->setBackgroundType(LightControlScreen_DeviceCButton, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_DeviceCButton->fn->setBorderType(LightControlScreen_DeviceCButton, LE_WIDGET_BORDER_NONE);
    LightControlScreen_DeviceCButton->fn->setPressedOffset(LightControlScreen_DeviceCButton, 0);
    LightControlScreen_DeviceCButton->fn->setPressedEventCallback(LightControlScreen_DeviceCButton, event_LightControlScreen_DeviceCButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_DeviceCButton);

    LightControlScreen_ImageSequenceWidgetC = leImageSequenceWidget_New();
    LightControlScreen_ImageSequenceWidgetC->fn->setPosition(LightControlScreen_ImageSequenceWidgetC, 0, 0);
    LightControlScreen_ImageSequenceWidgetC->fn->setSize(LightControlScreen_ImageSequenceWidgetC, 65, 65);
    LightControlScreen_ImageSequenceWidgetC->fn->setEnabled(LightControlScreen_ImageSequenceWidgetC, LE_FALSE);
    LightControlScreen_ImageSequenceWidgetC->fn->setBackgroundType(LightControlScreen_ImageSequenceWidgetC, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_ImageSequenceWidgetC->fn->setImageCount(LightControlScreen_ImageSequenceWidgetC, 2);
    LightControlScreen_ImageSequenceWidgetC->fn->setImage(LightControlScreen_ImageSequenceWidgetC, 0, &DeviceSelect60);
    LightControlScreen_ImageSequenceWidgetC->fn->setImageDelay(LightControlScreen_ImageSequenceWidgetC, 0, 1000);
    LightControlScreen_ImageSequenceWidgetC->fn->setImage(LightControlScreen_ImageSequenceWidgetC, 1, &DeviceNoSelect60);
    LightControlScreen_ImageSequenceWidgetC->fn->setImageDelay(LightControlScreen_ImageSequenceWidgetC, 1, 1000);
    LightControlScreen_DeviceCButton->fn->addChild(LightControlScreen_DeviceCButton, (leWidget*)LightControlScreen_ImageSequenceWidgetC);

    LightControlScreen_LabelWidget2 = leLabelWidget_New();
    LightControlScreen_LabelWidget2->fn->setPosition(LightControlScreen_LabelWidget2, -2, -1);
    LightControlScreen_LabelWidget2->fn->setSize(LightControlScreen_LabelWidget2, 25, 25);
    LightControlScreen_LabelWidget2->fn->setEnabled(LightControlScreen_LabelWidget2, LE_FALSE);
    LightControlScreen_LabelWidget2->fn->setScheme(LightControlScreen_LabelWidget2, &TextScheme);
    LightControlScreen_LabelWidget2->fn->setBackgroundType(LightControlScreen_LabelWidget2, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LabelWidget2->fn->setHAlignment(LightControlScreen_LabelWidget2, LE_HALIGN_CENTER);
    LightControlScreen_LabelWidget2->fn->setString(LightControlScreen_LabelWidget2, (leString*)&string_DeviceC);
    LightControlScreen_DeviceCButton->fn->addChild(LightControlScreen_DeviceCButton, (leWidget*)LightControlScreen_LabelWidget2);

    LightControlScreen_TempLabelC = leLabelWidget_New();
    LightControlScreen_TempLabelC->fn->setPosition(LightControlScreen_TempLabelC, 5, 18);
    LightControlScreen_TempLabelC->fn->setSize(LightControlScreen_TempLabelC, 55, 30);
    LightControlScreen_TempLabelC->fn->setScheme(LightControlScreen_TempLabelC, &TextScheme);
    LightControlScreen_TempLabelC->fn->setBackgroundType(LightControlScreen_TempLabelC, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_TempLabelC->fn->setHAlignment(LightControlScreen_TempLabelC, LE_HALIGN_CENTER);
    LightControlScreen_TempLabelC->fn->setString(LightControlScreen_TempLabelC, (leString*)&string_DefaultTemp);
    LightControlScreen_DeviceCButton->fn->addChild(LightControlScreen_DeviceCButton, (leWidget*)LightControlScreen_TempLabelC);

    LightControlScreen_DeviceBButton = leButtonWidget_New();
    LightControlScreen_DeviceBButton->fn->setPosition(LightControlScreen_DeviceBButton, 370, 240);
    LightControlScreen_DeviceBButton->fn->setSize(LightControlScreen_DeviceBButton, 65, 65);
    LightControlScreen_DeviceBButton->fn->setBackgroundType(LightControlScreen_DeviceBButton, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_DeviceBButton->fn->setBorderType(LightControlScreen_DeviceBButton, LE_WIDGET_BORDER_NONE);
    LightControlScreen_DeviceBButton->fn->setPressedOffset(LightControlScreen_DeviceBButton, 0);
    LightControlScreen_DeviceBButton->fn->setPressedEventCallback(LightControlScreen_DeviceBButton, event_LightControlScreen_DeviceBButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_DeviceBButton);

    LightControlScreen_ImageSequenceWidgetB = leImageSequenceWidget_New();
    LightControlScreen_ImageSequenceWidgetB->fn->setPosition(LightControlScreen_ImageSequenceWidgetB, 0, 0);
    LightControlScreen_ImageSequenceWidgetB->fn->setSize(LightControlScreen_ImageSequenceWidgetB, 65, 65);
    LightControlScreen_ImageSequenceWidgetB->fn->setEnabled(LightControlScreen_ImageSequenceWidgetB, LE_FALSE);
    LightControlScreen_ImageSequenceWidgetB->fn->setBackgroundType(LightControlScreen_ImageSequenceWidgetB, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_ImageSequenceWidgetB->fn->setImageCount(LightControlScreen_ImageSequenceWidgetB, 2);
    LightControlScreen_ImageSequenceWidgetB->fn->setImage(LightControlScreen_ImageSequenceWidgetB, 0, &DeviceSelect60);
    LightControlScreen_ImageSequenceWidgetB->fn->setImageDelay(LightControlScreen_ImageSequenceWidgetB, 0, 1000);
    LightControlScreen_ImageSequenceWidgetB->fn->setImage(LightControlScreen_ImageSequenceWidgetB, 1, &DeviceNoSelect60);
    LightControlScreen_ImageSequenceWidgetB->fn->setImageDelay(LightControlScreen_ImageSequenceWidgetB, 1, 1000);
    LightControlScreen_DeviceBButton->fn->addChild(LightControlScreen_DeviceBButton, (leWidget*)LightControlScreen_ImageSequenceWidgetB);

    LightControlScreen_LabelWidget1 = leLabelWidget_New();
    LightControlScreen_LabelWidget1->fn->setPosition(LightControlScreen_LabelWidget1, -1, -2);
    LightControlScreen_LabelWidget1->fn->setSize(LightControlScreen_LabelWidget1, 25, 25);
    LightControlScreen_LabelWidget1->fn->setEnabled(LightControlScreen_LabelWidget1, LE_FALSE);
    LightControlScreen_LabelWidget1->fn->setScheme(LightControlScreen_LabelWidget1, &TextScheme);
    LightControlScreen_LabelWidget1->fn->setBackgroundType(LightControlScreen_LabelWidget1, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LabelWidget1->fn->setHAlignment(LightControlScreen_LabelWidget1, LE_HALIGN_CENTER);
    LightControlScreen_LabelWidget1->fn->setString(LightControlScreen_LabelWidget1, (leString*)&string_DeviceB);
    LightControlScreen_DeviceBButton->fn->addChild(LightControlScreen_DeviceBButton, (leWidget*)LightControlScreen_LabelWidget1);

    LightControlScreen_TempLabelB = leLabelWidget_New();
    LightControlScreen_TempLabelB->fn->setPosition(LightControlScreen_TempLabelB, 5, 18);
    LightControlScreen_TempLabelB->fn->setSize(LightControlScreen_TempLabelB, 55, 30);
    LightControlScreen_TempLabelB->fn->setScheme(LightControlScreen_TempLabelB, &TextScheme);
    LightControlScreen_TempLabelB->fn->setBackgroundType(LightControlScreen_TempLabelB, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_TempLabelB->fn->setHAlignment(LightControlScreen_TempLabelB, LE_HALIGN_CENTER);
    LightControlScreen_TempLabelB->fn->setString(LightControlScreen_TempLabelB, (leString*)&string_DefaultTemp);
    LightControlScreen_DeviceBButton->fn->addChild(LightControlScreen_DeviceBButton, (leWidget*)LightControlScreen_TempLabelB);

    LightControlScreen_DeviceAButton = leButtonWidget_New();
    LightControlScreen_DeviceAButton->fn->setPosition(LightControlScreen_DeviceAButton, 440, 120);
    LightControlScreen_DeviceAButton->fn->setSize(LightControlScreen_DeviceAButton, 65, 65);
    LightControlScreen_DeviceAButton->fn->setBackgroundType(LightControlScreen_DeviceAButton, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_DeviceAButton->fn->setBorderType(LightControlScreen_DeviceAButton, LE_WIDGET_BORDER_NONE);
    LightControlScreen_DeviceAButton->fn->setPressedOffset(LightControlScreen_DeviceAButton, 0);
    LightControlScreen_DeviceAButton->fn->setPressedEventCallback(LightControlScreen_DeviceAButton, event_LightControlScreen_DeviceAButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_DeviceAButton);

    LightControlScreen_ImageSequenceWidgetA = leImageSequenceWidget_New();
    LightControlScreen_ImageSequenceWidgetA->fn->setPosition(LightControlScreen_ImageSequenceWidgetA, 0, 0);
    LightControlScreen_ImageSequenceWidgetA->fn->setSize(LightControlScreen_ImageSequenceWidgetA, 65, 65);
    LightControlScreen_ImageSequenceWidgetA->fn->setEnabled(LightControlScreen_ImageSequenceWidgetA, LE_FALSE);
    LightControlScreen_ImageSequenceWidgetA->fn->setBackgroundType(LightControlScreen_ImageSequenceWidgetA, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_ImageSequenceWidgetA->fn->setImageCount(LightControlScreen_ImageSequenceWidgetA, 2);
    LightControlScreen_ImageSequenceWidgetA->fn->setImage(LightControlScreen_ImageSequenceWidgetA, 0, &DeviceSelect60);
    LightControlScreen_ImageSequenceWidgetA->fn->setImageDelay(LightControlScreen_ImageSequenceWidgetA, 0, 1000);
    LightControlScreen_ImageSequenceWidgetA->fn->setImage(LightControlScreen_ImageSequenceWidgetA, 1, &DeviceNoSelect60);
    LightControlScreen_ImageSequenceWidgetA->fn->setImageDelay(LightControlScreen_ImageSequenceWidgetA, 1, 1000);
    LightControlScreen_DeviceAButton->fn->addChild(LightControlScreen_DeviceAButton, (leWidget*)LightControlScreen_ImageSequenceWidgetA);

    LightControlScreen_LabelWidget0 = leLabelWidget_New();
    LightControlScreen_LabelWidget0->fn->setPosition(LightControlScreen_LabelWidget0, 0, -1);
    LightControlScreen_LabelWidget0->fn->setSize(LightControlScreen_LabelWidget0, 25, 25);
    LightControlScreen_LabelWidget0->fn->setEnabled(LightControlScreen_LabelWidget0, LE_FALSE);
    LightControlScreen_LabelWidget0->fn->setScheme(LightControlScreen_LabelWidget0, &TextScheme);
    LightControlScreen_LabelWidget0->fn->setBackgroundType(LightControlScreen_LabelWidget0, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LabelWidget0->fn->setHAlignment(LightControlScreen_LabelWidget0, LE_HALIGN_CENTER);
    LightControlScreen_LabelWidget0->fn->setString(LightControlScreen_LabelWidget0, (leString*)&string_DeviceA);
    LightControlScreen_DeviceAButton->fn->addChild(LightControlScreen_DeviceAButton, (leWidget*)LightControlScreen_LabelWidget0);

    LightControlScreen_TempLabelA = leLabelWidget_New();
    LightControlScreen_TempLabelA->fn->setPosition(LightControlScreen_TempLabelA, 5, 18);
    LightControlScreen_TempLabelA->fn->setSize(LightControlScreen_TempLabelA, 55, 30);
    LightControlScreen_TempLabelA->fn->setScheme(LightControlScreen_TempLabelA, &WhiteScheme);
    LightControlScreen_TempLabelA->fn->setBackgroundType(LightControlScreen_TempLabelA, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_TempLabelA->fn->setHAlignment(LightControlScreen_TempLabelA, LE_HALIGN_CENTER);
    LightControlScreen_TempLabelA->fn->setString(LightControlScreen_TempLabelA, (leString*)&string_DefaultTemp);
    LightControlScreen_DeviceAButton->fn->addChild(LightControlScreen_DeviceAButton, (leWidget*)LightControlScreen_TempLabelA);

    LightControlScreen_SliderImageWidget = leImageWidget_New();
    LightControlScreen_SliderImageWidget->fn->setPosition(LightControlScreen_SliderImageWidget, 730, 150);
    LightControlScreen_SliderImageWidget->fn->setSize(LightControlScreen_SliderImageWidget, 60, 250);
    LightControlScreen_SliderImageWidget->fn->setBackgroundType(LightControlScreen_SliderImageWidget, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_SliderImageWidget->fn->setBorderType(LightControlScreen_SliderImageWidget, LE_WIDGET_BORDER_NONE);
    LightControlScreen_SliderImageWidget->fn->setImage(LightControlScreen_SliderImageWidget, (leImage*)&Slider50);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_SliderImageWidget);

    LightControlScreen_SliderControlPanel = leWidget_New();
    LightControlScreen_SliderControlPanel->fn->setPosition(LightControlScreen_SliderControlPanel, 726, 205);
    LightControlScreen_SliderControlPanel->fn->setSize(LightControlScreen_SliderControlPanel, 67, 147);
    LightControlScreen_SliderControlPanel->fn->setBackgroundType(LightControlScreen_SliderControlPanel, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_SliderControlPanel);

    LightControlScreen_ScrollKnobImageWidget = leImageWidget_New();
    LightControlScreen_ScrollKnobImageWidget->fn->setPosition(LightControlScreen_ScrollKnobImageWidget, 745, 261);
    LightControlScreen_ScrollKnobImageWidget->fn->setSize(LightControlScreen_ScrollKnobImageWidget, 30, 30);
    LightControlScreen_ScrollKnobImageWidget->fn->setEnabled(LightControlScreen_ScrollKnobImageWidget, LE_FALSE);
    LightControlScreen_ScrollKnobImageWidget->fn->setBackgroundType(LightControlScreen_ScrollKnobImageWidget, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_ScrollKnobImageWidget->fn->setBorderType(LightControlScreen_ScrollKnobImageWidget, LE_WIDGET_BORDER_NONE);
    LightControlScreen_ScrollKnobImageWidget->fn->setImage(LightControlScreen_ScrollKnobImageWidget, (leImage*)&Knob30);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_ScrollKnobImageWidget);

    LightControlScreen_SelectedColorPanelA = leWidget_New();
    LightControlScreen_SelectedColorPanelA->fn->setPosition(LightControlScreen_SelectedColorPanelA, 510, 144);
    LightControlScreen_SelectedColorPanelA->fn->setSize(LightControlScreen_SelectedColorPanelA, 20, 20);
    LightControlScreen_SelectedColorPanelA->fn->setScheme(LightControlScreen_SelectedColorPanelA, &BlueScheme);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_SelectedColorPanelA);

    LightControlScreen_AllDevicesButton = leButtonWidget_New();
    LightControlScreen_AllDevicesButton->fn->setPosition(LightControlScreen_AllDevicesButton, 585, 391);
    LightControlScreen_AllDevicesButton->fn->setSize(LightControlScreen_AllDevicesButton, 60, 60);
    LightControlScreen_AllDevicesButton->fn->setScheme(LightControlScreen_AllDevicesButton, &TextScheme);
    LightControlScreen_AllDevicesButton->fn->setBorderType(LightControlScreen_AllDevicesButton, LE_WIDGET_BORDER_NONE);
    LightControlScreen_AllDevicesButton->fn->setToggleable(LightControlScreen_AllDevicesButton, LE_TRUE);
    LightControlScreen_AllDevicesButton->fn->setString(LightControlScreen_AllDevicesButton, (leString*)&string_AllString);
    LightControlScreen_AllDevicesButton->fn->setPressedImage(LightControlScreen_AllDevicesButton, (leImage*)&DeviceNoSelect40);
    LightControlScreen_AllDevicesButton->fn->setReleasedImage(LightControlScreen_AllDevicesButton, (leImage*)&DeviceSelect40Bulb);
    LightControlScreen_AllDevicesButton->fn->setImagePosition(LightControlScreen_AllDevicesButton, LE_RELATIVE_POSITION_BEHIND);
    LightControlScreen_AllDevicesButton->fn->setPressedOffset(LightControlScreen_AllDevicesButton, 0);
    LightControlScreen_AllDevicesButton->fn->setPressedEventCallback(LightControlScreen_AllDevicesButton, event_LightControlScreen_AllDevicesButton_OnPressed);
    LightControlScreen_AllDevicesButton->fn->setReleasedEventCallback(LightControlScreen_AllDevicesButton, event_LightControlScreen_AllDevicesButton_OnReleased);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_AllDevicesButton);

    LightControlScreen_LabelWidget_0 = leLabelWidget_New();
    LightControlScreen_LabelWidget_0->fn->setPosition(LightControlScreen_LabelWidget_0, 410, 2);
    LightControlScreen_LabelWidget_0->fn->setSize(LightControlScreen_LabelWidget_0, 380, 25);
    LightControlScreen_LabelWidget_0->fn->setScheme(LightControlScreen_LabelWidget_0, &TextScheme);
    LightControlScreen_LabelWidget_0->fn->setHAlignment(LightControlScreen_LabelWidget_0, LE_HALIGN_CENTER);
    LightControlScreen_LabelWidget_0->fn->setString(LightControlScreen_LabelWidget_0, (leString*)&string_DemoName);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LabelWidget_0);

    LightControlScreen_SelectedColorPanelB = leWidget_New();
    LightControlScreen_SelectedColorPanelB->fn->setPosition(LightControlScreen_SelectedColorPanelB, 439, 264);
    LightControlScreen_SelectedColorPanelB->fn->setSize(LightControlScreen_SelectedColorPanelB, 20, 20);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_SelectedColorPanelB);

    LightControlScreen_SelectedColorPanelC = leWidget_New();
    LightControlScreen_SelectedColorPanelC->fn->setPosition(LightControlScreen_SelectedColorPanelC, 511, 388);
    LightControlScreen_SelectedColorPanelC->fn->setSize(LightControlScreen_SelectedColorPanelC, 20, 20);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_SelectedColorPanelC);

    LightControlScreen_DeviceDataPanelA = leWidget_New();
    LightControlScreen_DeviceDataPanelA->fn->setPosition(LightControlScreen_DeviceDataPanelA, 37, 114);
    LightControlScreen_DeviceDataPanelA->fn->setSize(LightControlScreen_DeviceDataPanelA, 300, 340);
    LightControlScreen_DeviceDataPanelA->fn->setScheme(LightControlScreen_DeviceDataPanelA, &WhiteScheme);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_DeviceDataPanelA);

    LightControlScreen_ColorGraphLabel = leLabelWidget_New();
    LightControlScreen_ColorGraphLabel->fn->setPosition(LightControlScreen_ColorGraphLabel, 90, 49);
    LightControlScreen_ColorGraphLabel->fn->setSize(LightControlScreen_ColorGraphLabel, 123, 19);
    LightControlScreen_ColorGraphLabel->fn->setScheme(LightControlScreen_ColorGraphLabel, &BackScheme);
    LightControlScreen_ColorGraphLabel->fn->setBackgroundType(LightControlScreen_ColorGraphLabel, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_ColorGraphLabel->fn->setHAlignment(LightControlScreen_ColorGraphLabel, LE_HALIGN_CENTER);
    LightControlScreen_ColorGraphLabel->fn->setString(LightControlScreen_ColorGraphLabel, (leString*)&string_ColorChannels);
    LightControlScreen_DeviceDataPanelA->fn->addChild(LightControlScreen_DeviceDataPanelA, (leWidget*)LightControlScreen_ColorGraphLabel);

    LightControlScreen_TempSensorGraphLabel = leLabelWidget_New();
    LightControlScreen_TempSensorGraphLabel->fn->setPosition(LightControlScreen_TempSensorGraphLabel, 71, 181);
    LightControlScreen_TempSensorGraphLabel->fn->setSize(LightControlScreen_TempSensorGraphLabel, 170, 25);
    LightControlScreen_TempSensorGraphLabel->fn->setScheme(LightControlScreen_TempSensorGraphLabel, &BackScheme);
    LightControlScreen_TempSensorGraphLabel->fn->setBackgroundType(LightControlScreen_TempSensorGraphLabel, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_TempSensorGraphLabel->fn->setHAlignment(LightControlScreen_TempSensorGraphLabel, LE_HALIGN_CENTER);
    LightControlScreen_TempSensorGraphLabel->fn->setString(LightControlScreen_TempSensorGraphLabel, (leString*)&string_TempSensor);
    LightControlScreen_DeviceDataPanelA->fn->addChild(LightControlScreen_DeviceDataPanelA, (leWidget*)LightControlScreen_TempSensorGraphLabel);

    LightControlScreen_LineGraphLabelA = leLabelWidget_New();
    LightControlScreen_LineGraphLabelA->fn->setPosition(LightControlScreen_LineGraphLabelA, 66, 314);
    LightControlScreen_LineGraphLabelA->fn->setSize(LightControlScreen_LineGraphLabelA, 40, 25);
    LightControlScreen_LineGraphLabelA->fn->setBackgroundType(LightControlScreen_LineGraphLabelA, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LineGraphLabelA->fn->setHAlignment(LightControlScreen_LineGraphLabelA, LE_HALIGN_RIGHT);
    LightControlScreen_LineGraphLabelA->fn->setString(LightControlScreen_LineGraphLabelA, (leString*)&string_DeviceA);
    LightControlScreen_DeviceDataPanelA->fn->addChild(LightControlScreen_DeviceDataPanelA, (leWidget*)LightControlScreen_LineGraphLabelA);

    LightControlScreen_PanelWidget_0 = leWidget_New();
    LightControlScreen_PanelWidget_0->fn->setPosition(LightControlScreen_PanelWidget_0, 10, 8);
    LightControlScreen_PanelWidget_0->fn->setSize(LightControlScreen_PanelWidget_0, 10, 10);
    LightControlScreen_PanelWidget_0->fn->setScheme(LightControlScreen_PanelWidget_0, &RedScheme);
    LightControlScreen_LineGraphLabelA->fn->addChild(LightControlScreen_LineGraphLabelA, (leWidget*)LightControlScreen_PanelWidget_0);

    LightControlScreen_LineGraphLabelB = leLabelWidget_New();
    LightControlScreen_LineGraphLabelB->fn->setPosition(LightControlScreen_LineGraphLabelB, 129, 314);
    LightControlScreen_LineGraphLabelB->fn->setSize(LightControlScreen_LineGraphLabelB, 40, 25);
    LightControlScreen_LineGraphLabelB->fn->setBackgroundType(LightControlScreen_LineGraphLabelB, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LineGraphLabelB->fn->setHAlignment(LightControlScreen_LineGraphLabelB, LE_HALIGN_RIGHT);
    LightControlScreen_LineGraphLabelB->fn->setString(LightControlScreen_LineGraphLabelB, (leString*)&string_DeviceB);
    LightControlScreen_DeviceDataPanelA->fn->addChild(LightControlScreen_DeviceDataPanelA, (leWidget*)LightControlScreen_LineGraphLabelB);

    LightControlScreen_PanelWidget_1 = leWidget_New();
    LightControlScreen_PanelWidget_1->fn->setPosition(LightControlScreen_PanelWidget_1, 9, 8);
    LightControlScreen_PanelWidget_1->fn->setSize(LightControlScreen_PanelWidget_1, 10, 10);
    LightControlScreen_PanelWidget_1->fn->setScheme(LightControlScreen_PanelWidget_1, &GreenScheme);
    LightControlScreen_LineGraphLabelB->fn->addChild(LightControlScreen_LineGraphLabelB, (leWidget*)LightControlScreen_PanelWidget_1);

    LightControlScreen_LineGraphLabelC = leLabelWidget_New();
    LightControlScreen_LineGraphLabelC->fn->setPosition(LightControlScreen_LineGraphLabelC, 192, 314);
    LightControlScreen_LineGraphLabelC->fn->setSize(LightControlScreen_LineGraphLabelC, 40, 25);
    LightControlScreen_LineGraphLabelC->fn->setBackgroundType(LightControlScreen_LineGraphLabelC, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_LineGraphLabelC->fn->setHAlignment(LightControlScreen_LineGraphLabelC, LE_HALIGN_RIGHT);
    LightControlScreen_LineGraphLabelC->fn->setString(LightControlScreen_LineGraphLabelC, (leString*)&string_DeviceC);
    LightControlScreen_DeviceDataPanelA->fn->addChild(LightControlScreen_DeviceDataPanelA, (leWidget*)LightControlScreen_LineGraphLabelC);

    LightControlScreen_PanelWidget_2 = leWidget_New();
    LightControlScreen_PanelWidget_2->fn->setPosition(LightControlScreen_PanelWidget_2, 9, 8);
    LightControlScreen_PanelWidget_2->fn->setSize(LightControlScreen_PanelWidget_2, 10, 10);
    LightControlScreen_PanelWidget_2->fn->setScheme(LightControlScreen_PanelWidget_2, &BlueScheme);
    LightControlScreen_LineGraphLabelC->fn->addChild(LightControlScreen_LineGraphLabelC, (leWidget*)LightControlScreen_PanelWidget_2);

    LightControlScreen_DeviceInfoLabel = leLabelWidget_New();
    LightControlScreen_DeviceInfoLabel->fn->setPosition(LightControlScreen_DeviceInfoLabel, 4, 4);
    LightControlScreen_DeviceInfoLabel->fn->setSize(LightControlScreen_DeviceInfoLabel, 294, 25);
    LightControlScreen_DeviceInfoLabel->fn->setScheme(LightControlScreen_DeviceInfoLabel, &BackScheme);
    LightControlScreen_DeviceInfoLabel->fn->setBackgroundType(LightControlScreen_DeviceInfoLabel, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_DeviceInfoLabel->fn->setHAlignment(LightControlScreen_DeviceInfoLabel, LE_HALIGN_CENTER);
    LightControlScreen_DeviceInfoLabel->fn->setString(LightControlScreen_DeviceInfoLabel, (leString*)&string_WiFiDeviceInfo);
    LightControlScreen_DeviceDataPanelA->fn->addChild(LightControlScreen_DeviceDataPanelA, (leWidget*)LightControlScreen_DeviceInfoLabel);

    LightControlScreen_BLEDeviceAName = leLabelWidget_New();
    LightControlScreen_BLEDeviceAName->fn->setPosition(LightControlScreen_BLEDeviceAName, 48, 56);
    LightControlScreen_BLEDeviceAName->fn->setSize(LightControlScreen_BLEDeviceAName, 200, 30);
    LightControlScreen_BLEDeviceAName->fn->setScheme(LightControlScreen_BLEDeviceAName, &BLEPanelScheme);
    LightControlScreen_BLEDeviceAName->fn->setBackgroundType(LightControlScreen_BLEDeviceAName, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_BLEDeviceAName->fn->setString(LightControlScreen_BLEDeviceAName, (leString*)&string_BLEDeviceInfo);
    LightControlScreen_DeviceDataPanelA->fn->addChild(LightControlScreen_DeviceDataPanelA, (leWidget*)LightControlScreen_BLEDeviceAName);

    LightControlScreen_BLEDeviceBName = leLabelWidget_New();
    LightControlScreen_BLEDeviceBName->fn->setPosition(LightControlScreen_BLEDeviceBName, 48, 96);
    LightControlScreen_BLEDeviceBName->fn->setSize(LightControlScreen_BLEDeviceBName, 200, 30);
    LightControlScreen_BLEDeviceBName->fn->setScheme(LightControlScreen_BLEDeviceBName, &BLEPanelScheme);
    LightControlScreen_BLEDeviceBName->fn->setBackgroundType(LightControlScreen_BLEDeviceBName, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_BLEDeviceBName->fn->setString(LightControlScreen_BLEDeviceBName, (leString*)&string_BLEDeviceInfo);
    LightControlScreen_DeviceDataPanelA->fn->addChild(LightControlScreen_DeviceDataPanelA, (leWidget*)LightControlScreen_BLEDeviceBName);

    LightControlScreen_BLEDeviceCName = leLabelWidget_New();
    LightControlScreen_BLEDeviceCName->fn->setPosition(LightControlScreen_BLEDeviceCName, 48, 136);
    LightControlScreen_BLEDeviceCName->fn->setSize(LightControlScreen_BLEDeviceCName, 200, 30);
    LightControlScreen_BLEDeviceCName->fn->setBackgroundType(LightControlScreen_BLEDeviceCName, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_BLEDeviceCName->fn->setString(LightControlScreen_BLEDeviceCName, (leString*)&string_BLEDeviceInfo);
    LightControlScreen_DeviceDataPanelA->fn->addChild(LightControlScreen_DeviceDataPanelA, (leWidget*)LightControlScreen_BLEDeviceCName);

    LightControlScreen_BLEDeviceAOK = leImageWidget_New();
    LightControlScreen_BLEDeviceAOK->fn->setPosition(LightControlScreen_BLEDeviceAOK, 12, 63);
    LightControlScreen_BLEDeviceAOK->fn->setSize(LightControlScreen_BLEDeviceAOK, 35, 25);
    LightControlScreen_BLEDeviceAOK->fn->setBackgroundType(LightControlScreen_BLEDeviceAOK, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_BLEDeviceAOK->fn->setBorderType(LightControlScreen_BLEDeviceAOK, LE_WIDGET_BORDER_NONE);
    LightControlScreen_BLEDeviceAOK->fn->setImage(LightControlScreen_BLEDeviceAOK, (leImage*)&Check30);
    LightControlScreen_DeviceDataPanelA->fn->addChild(LightControlScreen_DeviceDataPanelA, (leWidget*)LightControlScreen_BLEDeviceAOK);

    LightControlScreen_BLEDeviceBOK = leImageWidget_New();
    LightControlScreen_BLEDeviceBOK->fn->setPosition(LightControlScreen_BLEDeviceBOK, 12, 101);
    LightControlScreen_BLEDeviceBOK->fn->setSize(LightControlScreen_BLEDeviceBOK, 35, 25);
    LightControlScreen_BLEDeviceBOK->fn->setBackgroundType(LightControlScreen_BLEDeviceBOK, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_BLEDeviceBOK->fn->setBorderType(LightControlScreen_BLEDeviceBOK, LE_WIDGET_BORDER_NONE);
    LightControlScreen_BLEDeviceBOK->fn->setImage(LightControlScreen_BLEDeviceBOK, (leImage*)&Check30);
    LightControlScreen_DeviceDataPanelA->fn->addChild(LightControlScreen_DeviceDataPanelA, (leWidget*)LightControlScreen_BLEDeviceBOK);

    LightControlScreen_BLEDeviceCOK = leImageWidget_New();
    LightControlScreen_BLEDeviceCOK->fn->setPosition(LightControlScreen_BLEDeviceCOK, 12, 141);
    LightControlScreen_BLEDeviceCOK->fn->setSize(LightControlScreen_BLEDeviceCOK, 35, 25);
    LightControlScreen_BLEDeviceCOK->fn->setBackgroundType(LightControlScreen_BLEDeviceCOK, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_BLEDeviceCOK->fn->setBorderType(LightControlScreen_BLEDeviceCOK, LE_WIDGET_BORDER_NONE);
    LightControlScreen_BLEDeviceCOK->fn->setImage(LightControlScreen_BLEDeviceCOK, (leImage*)&Check30);
    LightControlScreen_DeviceDataPanelA->fn->addChild(LightControlScreen_DeviceDataPanelA, (leWidget*)LightControlScreen_BLEDeviceCOK);

    LightControlScreen_NetInfoPanel = leWidget_New();
    LightControlScreen_NetInfoPanel->fn->setPosition(LightControlScreen_NetInfoPanel, 9, 32);
    LightControlScreen_NetInfoPanel->fn->setSize(LightControlScreen_NetInfoPanel, 285, 303);
    LightControlScreen_NetInfoPanel->fn->setBackgroundType(LightControlScreen_NetInfoPanel, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_DeviceDataPanelA->fn->addChild(LightControlScreen_DeviceDataPanelA, (leWidget*)LightControlScreen_NetInfoPanel);

    LightControlScreen_NetInfString = leLabelWidget_New();
    LightControlScreen_NetInfString->fn->setPosition(LightControlScreen_NetInfString, 4, 6);
    LightControlScreen_NetInfString->fn->setSize(LightControlScreen_NetInfString, 80, 25);
    LightControlScreen_NetInfString->fn->setBackgroundType(LightControlScreen_NetInfString, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_NetInfString->fn->setString(LightControlScreen_NetInfString, (leString*)&string_InterfaceStr);
    LightControlScreen_NetInfoPanel->fn->addChild(LightControlScreen_NetInfoPanel, (leWidget*)LightControlScreen_NetInfString);

    LightControlScreen_NetSSIDString = leLabelWidget_New();
    LightControlScreen_NetSSIDString->fn->setPosition(LightControlScreen_NetSSIDString, 4, 33);
    LightControlScreen_NetSSIDString->fn->setSize(LightControlScreen_NetSSIDString, 73, 25);
    LightControlScreen_NetSSIDString->fn->setBackgroundType(LightControlScreen_NetSSIDString, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_NetSSIDString->fn->setString(LightControlScreen_NetSSIDString, (leString*)&string_SSIDStr);
    LightControlScreen_NetInfoPanel->fn->addChild(LightControlScreen_NetInfoPanel, (leWidget*)LightControlScreen_NetSSIDString);

    LightControlScreen_NetIPString = leLabelWidget_New();
    LightControlScreen_NetIPString->fn->setPosition(LightControlScreen_NetIPString, 4, 59);
    LightControlScreen_NetIPString->fn->setSize(LightControlScreen_NetIPString, 86, 25);
    LightControlScreen_NetIPString->fn->setBackgroundType(LightControlScreen_NetIPString, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_NetIPString->fn->setString(LightControlScreen_NetIPString, (leString*)&string_IPAddrStr);
    LightControlScreen_NetInfoPanel->fn->addChild(LightControlScreen_NetInfoPanel, (leWidget*)LightControlScreen_NetIPString);

    LightControlScreen_NetConnString = leLabelWidget_New();
    LightControlScreen_NetConnString->fn->setPosition(LightControlScreen_NetConnString, 4, 86);
    LightControlScreen_NetConnString->fn->setSize(LightControlScreen_NetConnString, 96, 25);
    LightControlScreen_NetConnString->fn->setBackgroundType(LightControlScreen_NetConnString, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_NetConnString->fn->setString(LightControlScreen_NetConnString, (leString*)&string_Connections);
    LightControlScreen_NetInfoPanel->fn->addChild(LightControlScreen_NetInfoPanel, (leWidget*)LightControlScreen_NetConnString);

    LightControlScreen_NetURLString = leLabelWidget_New();
    LightControlScreen_NetURLString->fn->setPosition(LightControlScreen_NetURLString, 4, 112);
    LightControlScreen_NetURLString->fn->setSize(LightControlScreen_NetURLString, 79, 25);
    LightControlScreen_NetURLString->fn->setBackgroundType(LightControlScreen_NetURLString, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_NetURLString->fn->setString(LightControlScreen_NetURLString, (leString*)&string_NetWebURLStr);
    LightControlScreen_NetInfoPanel->fn->addChild(LightControlScreen_NetInfoPanel, (leWidget*)LightControlScreen_NetURLString);

    LightControlScreen_NetWebURLQR = leImageWidget_New();
    LightControlScreen_NetWebURLQR->fn->setPosition(LightControlScreen_NetWebURLQR, 63, 146);
    LightControlScreen_NetWebURLQR->fn->setSize(LightControlScreen_NetWebURLQR, 160, 160);
    LightControlScreen_NetWebURLQR->fn->setBackgroundType(LightControlScreen_NetWebURLQR, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_NetWebURLQR->fn->setBorderType(LightControlScreen_NetWebURLQR, LE_WIDGET_BORDER_NONE);
    LightControlScreen_NetWebURLQR->fn->setImage(LightControlScreen_NetWebURLQR, (leImage*)&QRCode2);
    LightControlScreen_NetInfoPanel->fn->addChild(LightControlScreen_NetInfoPanel, (leWidget*)LightControlScreen_NetWebURLQR);

    LightControlScreen_NetInterfaceInfo = leLabelWidget_New();
    LightControlScreen_NetInterfaceInfo->fn->setPosition(LightControlScreen_NetInterfaceInfo, 114, 6);
    LightControlScreen_NetInterfaceInfo->fn->setSize(LightControlScreen_NetInterfaceInfo, 170, 25);
    LightControlScreen_NetInterfaceInfo->fn->setScheme(LightControlScreen_NetInterfaceInfo, &BlueScheme);
    LightControlScreen_NetInterfaceInfo->fn->setBackgroundType(LightControlScreen_NetInterfaceInfo, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_NetInterfaceInfo->fn->setHAlignment(LightControlScreen_NetInterfaceInfo, LE_HALIGN_CENTER);
    LightControlScreen_NetInterfaceInfo->fn->setString(LightControlScreen_NetInterfaceInfo, (leString*)&string_IntfValueStr);
    LightControlScreen_NetInfoPanel->fn->addChild(LightControlScreen_NetInfoPanel, (leWidget*)LightControlScreen_NetInterfaceInfo);

    LightControlScreen_NetSSIDInfo = leLabelWidget_New();
    LightControlScreen_NetSSIDInfo->fn->setPosition(LightControlScreen_NetSSIDInfo, 114, 33);
    LightControlScreen_NetSSIDInfo->fn->setSize(LightControlScreen_NetSSIDInfo, 170, 25);
    LightControlScreen_NetSSIDInfo->fn->setScheme(LightControlScreen_NetSSIDInfo, &BlueScheme);
    LightControlScreen_NetSSIDInfo->fn->setBackgroundType(LightControlScreen_NetSSIDInfo, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_NetSSIDInfo->fn->setHAlignment(LightControlScreen_NetSSIDInfo, LE_HALIGN_CENTER);
    LightControlScreen_NetSSIDInfo->fn->setString(LightControlScreen_NetSSIDInfo, (leString*)&string_SSIDValueStr);
    LightControlScreen_NetInfoPanel->fn->addChild(LightControlScreen_NetInfoPanel, (leWidget*)LightControlScreen_NetSSIDInfo);

    LightControlScreen_NetIPInfo = leLabelWidget_New();
    LightControlScreen_NetIPInfo->fn->setPosition(LightControlScreen_NetIPInfo, 114, 59);
    LightControlScreen_NetIPInfo->fn->setSize(LightControlScreen_NetIPInfo, 170, 25);
    LightControlScreen_NetIPInfo->fn->setScheme(LightControlScreen_NetIPInfo, &BlueScheme);
    LightControlScreen_NetIPInfo->fn->setBackgroundType(LightControlScreen_NetIPInfo, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_NetIPInfo->fn->setHAlignment(LightControlScreen_NetIPInfo, LE_HALIGN_CENTER);
    LightControlScreen_NetIPInfo->fn->setString(LightControlScreen_NetIPInfo, (leString*)&string_IPAddrValueStr);
    LightControlScreen_NetInfoPanel->fn->addChild(LightControlScreen_NetInfoPanel, (leWidget*)LightControlScreen_NetIPInfo);

    LightControlScreen_NetConnInfo = leLabelWidget_New();
    LightControlScreen_NetConnInfo->fn->setPosition(LightControlScreen_NetConnInfo, 114, 86);
    LightControlScreen_NetConnInfo->fn->setSize(LightControlScreen_NetConnInfo, 170, 25);
    LightControlScreen_NetConnInfo->fn->setScheme(LightControlScreen_NetConnInfo, &BlueScheme);
    LightControlScreen_NetConnInfo->fn->setBackgroundType(LightControlScreen_NetConnInfo, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_NetConnInfo->fn->setHAlignment(LightControlScreen_NetConnInfo, LE_HALIGN_CENTER);
    LightControlScreen_NetConnInfo->fn->setString(LightControlScreen_NetConnInfo, (leString*)&string_ZeroValueStr);
    LightControlScreen_NetInfoPanel->fn->addChild(LightControlScreen_NetInfoPanel, (leWidget*)LightControlScreen_NetConnInfo);

    LightControlScreen_NetURLInfo = leLabelWidget_New();
    LightControlScreen_NetURLInfo->fn->setPosition(LightControlScreen_NetURLInfo, 114, 111);
    LightControlScreen_NetURLInfo->fn->setSize(LightControlScreen_NetURLInfo, 170, 25);
    LightControlScreen_NetURLInfo->fn->setScheme(LightControlScreen_NetURLInfo, &BlueScheme);
    LightControlScreen_NetURLInfo->fn->setBackgroundType(LightControlScreen_NetURLInfo, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_NetURLInfo->fn->setHAlignment(LightControlScreen_NetURLInfo, LE_HALIGN_CENTER);
    LightControlScreen_NetURLInfo->fn->setString(LightControlScreen_NetURLInfo, (leString*)&string_NetWebURLValue);
    LightControlScreen_NetInfoPanel->fn->addChild(LightControlScreen_NetInfoPanel, (leWidget*)LightControlScreen_NetURLInfo);

    LightControlScreen_LineGraphWidget_0 = leLineGraphWidget_New();
    LightControlScreen_LineGraphWidget_0->fn->setPosition(LightControlScreen_LineGraphWidget_0, 60, 306);
    LightControlScreen_LineGraphWidget_0->fn->setSize(LightControlScreen_LineGraphWidget_0, 260, 122);
    LightControlScreen_LineGraphWidget_0->fn->setScheme(LightControlScreen_LineGraphWidget_0, &GraphScheme);
    LightControlScreen_LineGraphWidget_0->fn->setFillGraphArea(LightControlScreen_LineGraphWidget_0, LE_FALSE);
    LightControlScreen_LineGraphWidget_0->fn->setMinValue(LightControlScreen_LineGraphWidget_0, LINE_GRAPH_AXIS_0, 10);
    LightControlScreen_LineGraphWidget_0->fn->setMaxValue(LightControlScreen_LineGraphWidget_0, LINE_GRAPH_AXIS_0, 60);
    LightControlScreen_LineGraphWidget_0->fn->setTicksLabelFont(LightControlScreen_LineGraphWidget_0, (leFont*)&Tiny);
    LightControlScreen_LineGraphWidget_0->fn->setCategoryAxisLabelsVisible(LightControlScreen_LineGraphWidget_0, LE_FALSE);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_LineGraphWidget_0);

    LightControlScreen_BarGraphWidget_0 = leBarGraphWidget_New();
    LightControlScreen_BarGraphWidget_0->fn->setPosition(LightControlScreen_BarGraphWidget_0, 58, 169);
    LightControlScreen_BarGraphWidget_0->fn->setSize(LightControlScreen_BarGraphWidget_0, 258, 123);
    LightControlScreen_BarGraphWidget_0->fn->setMaxValue(LightControlScreen_BarGraphWidget_0, BAR_GRAPH_AXIS_0, 255);
    LightControlScreen_BarGraphWidget_0->fn->setValueAxisTicksInterval(LightControlScreen_BarGraphWidget_0, BAR_GRAPH_AXIS_0, 100);
    LightControlScreen_BarGraphWidget_0->fn->setValueAxisTicksVisible(LightControlScreen_BarGraphWidget_0, BAR_GRAPH_AXIS_0, LE_FALSE);
    LightControlScreen_BarGraphWidget_0->fn->setValueAxisSubticksInterval(LightControlScreen_BarGraphWidget_0, BAR_GRAPH_AXIS_0, BAR_GRAPH_TICK_IN);
    LightControlScreen_BarGraphWidget_0->fn->setTicksLabelFont(LightControlScreen_BarGraphWidget_0, (leFont*)&Tiny);
    LightControlScreen_BarGraphWidget_0->fn->addCategory(LightControlScreen_BarGraphWidget_0, NULL);    LightControlScreen_BarGraphWidget_0->fn->setCategoryString(LightControlScreen_BarGraphWidget_0, 0, (leString*)&string_DeviceA);
    LightControlScreen_BarGraphWidget_0->fn->addCategory(LightControlScreen_BarGraphWidget_0, NULL);    LightControlScreen_BarGraphWidget_0->fn->setCategoryString(LightControlScreen_BarGraphWidget_0, 1, (leString*)&string_DeviceB);
    LightControlScreen_BarGraphWidget_0->fn->addCategory(LightControlScreen_BarGraphWidget_0, NULL);    LightControlScreen_BarGraphWidget_0->fn->setCategoryString(LightControlScreen_BarGraphWidget_0, 2, (leString*)&string_DeviceC);
    LightControlScreen_BarGraphWidget_0->fn->addSeries(LightControlScreen_BarGraphWidget_0, NULL);
    LightControlScreen_BarGraphWidget_0->fn->setSeriesScheme(LightControlScreen_BarGraphWidget_0, 0, &RedScheme);
    LightControlScreen_BarGraphWidget_0->fn->addDataToSeries(LightControlScreen_BarGraphWidget_0, 0, 10, NULL);
    LightControlScreen_BarGraphWidget_0->fn->addDataToSeries(LightControlScreen_BarGraphWidget_0, 0, 10, NULL);
    LightControlScreen_BarGraphWidget_0->fn->addDataToSeries(LightControlScreen_BarGraphWidget_0, 0, 10, NULL);
    LightControlScreen_BarGraphWidget_0->fn->addSeries(LightControlScreen_BarGraphWidget_0, NULL);
    LightControlScreen_BarGraphWidget_0->fn->setSeriesScheme(LightControlScreen_BarGraphWidget_0, 1, &GreenScheme);
    LightControlScreen_BarGraphWidget_0->fn->addDataToSeries(LightControlScreen_BarGraphWidget_0, 1, 10, NULL);
    LightControlScreen_BarGraphWidget_0->fn->addDataToSeries(LightControlScreen_BarGraphWidget_0, 1, 10, NULL);
    LightControlScreen_BarGraphWidget_0->fn->addDataToSeries(LightControlScreen_BarGraphWidget_0, 1, 10, NULL);
    LightControlScreen_BarGraphWidget_0->fn->addSeries(LightControlScreen_BarGraphWidget_0, NULL);
    LightControlScreen_BarGraphWidget_0->fn->setSeriesScheme(LightControlScreen_BarGraphWidget_0, 2, &BlueScheme);
    LightControlScreen_BarGraphWidget_0->fn->addDataToSeries(LightControlScreen_BarGraphWidget_0, 2, 10, NULL);
    LightControlScreen_BarGraphWidget_0->fn->addDataToSeries(LightControlScreen_BarGraphWidget_0, 2, 10, NULL);
    LightControlScreen_BarGraphWidget_0->fn->addDataToSeries(LightControlScreen_BarGraphWidget_0, 2, 10, NULL);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_BarGraphWidget_0);

    LightControlScreen_DeviceInfoButton = leButtonWidget_New();
    LightControlScreen_DeviceInfoButton->fn->setPosition(LightControlScreen_DeviceInfoButton, 73, 72);
    LightControlScreen_DeviceInfoButton->fn->setSize(LightControlScreen_DeviceInfoButton, 80, 60);
    LightControlScreen_DeviceInfoButton->fn->setBackgroundType(LightControlScreen_DeviceInfoButton, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_DeviceInfoButton->fn->setBorderType(LightControlScreen_DeviceInfoButton, LE_WIDGET_BORDER_NONE);
    LightControlScreen_DeviceInfoButton->fn->setVAlignment(LightControlScreen_DeviceInfoButton, LE_VALIGN_TOP);
    LightControlScreen_DeviceInfoButton->fn->setPressedImage(LightControlScreen_DeviceInfoButton, (leImage*)&GraphTabA60);
    LightControlScreen_DeviceInfoButton->fn->setReleasedImage(LightControlScreen_DeviceInfoButton, (leImage*)&graphtab60);
    LightControlScreen_DeviceInfoButton->fn->setPressedOffset(LightControlScreen_DeviceInfoButton, 0);
    LightControlScreen_DeviceInfoButton->fn->setPressedEventCallback(LightControlScreen_DeviceInfoButton, event_LightControlScreen_DeviceInfoButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_DeviceInfoButton);

    LightControlScreen_BLEInfoButton = leButtonWidget_New();
    LightControlScreen_BLEInfoButton->fn->setPosition(LightControlScreen_BLEInfoButton, 150, 67);
    LightControlScreen_BLEInfoButton->fn->setSize(LightControlScreen_BLEInfoButton, 80, 66);
    LightControlScreen_BLEInfoButton->fn->setBackgroundType(LightControlScreen_BLEInfoButton, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_BLEInfoButton->fn->setBorderType(LightControlScreen_BLEInfoButton, LE_WIDGET_BORDER_NONE);
    LightControlScreen_BLEInfoButton->fn->setVAlignment(LightControlScreen_BLEInfoButton, LE_VALIGN_TOP);
    LightControlScreen_BLEInfoButton->fn->setPressedImage(LightControlScreen_BLEInfoButton, (leImage*)&bleTabA60);
    LightControlScreen_BLEInfoButton->fn->setReleasedImage(LightControlScreen_BLEInfoButton, (leImage*)&bleTab60);
    LightControlScreen_BLEInfoButton->fn->setPressedOffset(LightControlScreen_BLEInfoButton, 0);
    LightControlScreen_BLEInfoButton->fn->setPressedEventCallback(LightControlScreen_BLEInfoButton, event_LightControlScreen_BLEInfoButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_BLEInfoButton);

    LightControlScreen_WiFiInfoButton = leButtonWidget_New();
    LightControlScreen_WiFiInfoButton->fn->setPosition(LightControlScreen_WiFiInfoButton, 228, 72);
    LightControlScreen_WiFiInfoButton->fn->setSize(LightControlScreen_WiFiInfoButton, 80, 60);
    LightControlScreen_WiFiInfoButton->fn->setBackgroundType(LightControlScreen_WiFiInfoButton, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_WiFiInfoButton->fn->setBorderType(LightControlScreen_WiFiInfoButton, LE_WIDGET_BORDER_NONE);
    LightControlScreen_WiFiInfoButton->fn->setVAlignment(LightControlScreen_WiFiInfoButton, LE_VALIGN_TOP);
    LightControlScreen_WiFiInfoButton->fn->setPressedImage(LightControlScreen_WiFiInfoButton, (leImage*)&WifiTabA60);
    LightControlScreen_WiFiInfoButton->fn->setReleasedImage(LightControlScreen_WiFiInfoButton, (leImage*)&WifiTab60);
    LightControlScreen_WiFiInfoButton->fn->setPressedOffset(LightControlScreen_WiFiInfoButton, 0);
    LightControlScreen_WiFiInfoButton->fn->setPressedEventCallback(LightControlScreen_WiFiInfoButton, event_LightControlScreen_WiFiInfoButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_WiFiInfoButton);

    LightControlScreen_ColorWheelSelectColor = leWidget_New();
    LightControlScreen_ColorWheelSelectColor->fn->setPosition(LightControlScreen_ColorWheelSelectColor, 567, 102);
    LightControlScreen_ColorWheelSelectColor->fn->setSize(LightControlScreen_ColorWheelSelectColor, 86, 25);
    LightControlScreen_ColorWheelSelectColor->fn->setScheme(LightControlScreen_ColorWheelSelectColor, &WhiteScheme);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_ColorWheelSelectColor);

    LightControlScreen_AnimImageWidget = leImageSequenceWidget_New();
    LightControlScreen_AnimImageWidget->fn->setPosition(LightControlScreen_AnimImageWidget, 48, 138);
    LightControlScreen_AnimImageWidget->fn->setSize(LightControlScreen_AnimImageWidget, 280, 280);
    LightControlScreen_AnimImageWidget->fn->setBackgroundType(LightControlScreen_AnimImageWidget, LE_WIDGET_BACKGROUND_NONE);
    LightControlScreen_AnimImageWidget->fn->setImageCount(LightControlScreen_AnimImageWidget, 1);
    LightControlScreen_AnimImageWidget->fn->setImage(LightControlScreen_AnimImageWidget, 0, &InfoGraphic);
    LightControlScreen_AnimImageWidget->fn->setImageDelay(LightControlScreen_AnimImageWidget, 0, 1000);
    root0->fn->addChild(root0, (leWidget*)LightControlScreen_AnimImageWidget);

    LightControlScreen_MfgBlock = leWidget_New();
    LightControlScreen_MfgBlock->fn->setPosition(LightControlScreen_MfgBlock, 83, 33);
    LightControlScreen_MfgBlock->fn->setSize(LightControlScreen_MfgBlock, 49, 46);
    LightControlScreen_MfgBlock->fn->setScheme(LightControlScreen_MfgBlock, &InfoGraphicBackScheme);
    LightControlScreen_AnimImageWidget->fn->addChild(LightControlScreen_AnimImageWidget, (leWidget*)LightControlScreen_MfgBlock);

    LightControlScreen_BldgBlock = leWidget_New();
    LightControlScreen_BldgBlock->fn->setPosition(LightControlScreen_BldgBlock, 149, 30);
    LightControlScreen_BldgBlock->fn->setSize(LightControlScreen_BldgBlock, 50, 47);
    LightControlScreen_BldgBlock->fn->setScheme(LightControlScreen_BldgBlock, &InfoGraphicBackScheme);
    LightControlScreen_AnimImageWidget->fn->addChild(LightControlScreen_AnimImageWidget, (leWidget*)LightControlScreen_BldgBlock);

    LightControlScreen_EnergyBlock = leWidget_New();
    LightControlScreen_EnergyBlock->fn->setPosition(LightControlScreen_EnergyBlock, 214, 74);
    LightControlScreen_EnergyBlock->fn->setSize(LightControlScreen_EnergyBlock, 31, 56);
    LightControlScreen_EnergyBlock->fn->setScheme(LightControlScreen_EnergyBlock, &InfoGraphicBackScheme);
    LightControlScreen_AnimImageWidget->fn->addChild(LightControlScreen_AnimImageWidget, (leWidget*)LightControlScreen_EnergyBlock);

    LightControlScreen_EnvBlock = leWidget_New();
    LightControlScreen_EnvBlock->fn->setPosition(LightControlScreen_EnvBlock, 205, 146);
    LightControlScreen_EnvBlock->fn->setSize(LightControlScreen_EnvBlock, 51, 47);
    LightControlScreen_EnvBlock->fn->setScheme(LightControlScreen_EnvBlock, &InfoGraphicBackScheme);
    LightControlScreen_AnimImageWidget->fn->addChild(LightControlScreen_AnimImageWidget, (leWidget*)LightControlScreen_EnvBlock);

    LightControlScreen_AgriBlock = leWidget_New();
    LightControlScreen_AgriBlock->fn->setPosition(LightControlScreen_AgriBlock, 149, 199);
    LightControlScreen_AgriBlock->fn->setSize(LightControlScreen_AgriBlock, 44, 53);
    LightControlScreen_AgriBlock->fn->setScheme(LightControlScreen_AgriBlock, &InfoGraphicBackScheme);
    LightControlScreen_AnimImageWidget->fn->addChild(LightControlScreen_AnimImageWidget, (leWidget*)LightControlScreen_AgriBlock);

    LightControlScreen_LogiBlock = leWidget_New();
    LightControlScreen_LogiBlock->fn->setPosition(LightControlScreen_LogiBlock, 77, 211);
    LightControlScreen_LogiBlock->fn->setSize(LightControlScreen_LogiBlock, 51, 41);
    LightControlScreen_LogiBlock->fn->setScheme(LightControlScreen_LogiBlock, &InfoGraphicBackScheme);
    LightControlScreen_AnimImageWidget->fn->addChild(LightControlScreen_AnimImageWidget, (leWidget*)LightControlScreen_LogiBlock);

    LightControlScreen_HomeAutoBlock = leWidget_New();
    LightControlScreen_HomeAutoBlock->fn->setPosition(LightControlScreen_HomeAutoBlock, 26, 148);
    LightControlScreen_HomeAutoBlock->fn->setSize(LightControlScreen_HomeAutoBlock, 61, 43);
    LightControlScreen_HomeAutoBlock->fn->setScheme(LightControlScreen_HomeAutoBlock, &InfoGraphicBackScheme);
    LightControlScreen_AnimImageWidget->fn->addChild(LightControlScreen_AnimImageWidget, (leWidget*)LightControlScreen_HomeAutoBlock);

    LightControlScreen_SmartCityBlock = leWidget_New();
    LightControlScreen_SmartCityBlock->fn->setPosition(LightControlScreen_SmartCityBlock, 32, 79);
    LightControlScreen_SmartCityBlock->fn->setSize(LightControlScreen_SmartCityBlock, 41, 48);
    LightControlScreen_SmartCityBlock->fn->setScheme(LightControlScreen_SmartCityBlock, &InfoGraphicBackScheme);
    LightControlScreen_AnimImageWidget->fn->addChild(LightControlScreen_AnimImageWidget, (leWidget*)LightControlScreen_SmartCityBlock);

    LightControlScreen_SmartConSecLogoBlock = leWidget_New();
    LightControlScreen_SmartConSecLogoBlock->fn->setPosition(LightControlScreen_SmartConSecLogoBlock, 102, 89);
    LightControlScreen_SmartConSecLogoBlock->fn->setSize(LightControlScreen_SmartConSecLogoBlock, 75, 75);
    LightControlScreen_SmartConSecLogoBlock->fn->setScheme(LightControlScreen_SmartConSecLogoBlock, &InfoGraphicBackScheme);
    LightControlScreen_AnimImageWidget->fn->addChild(LightControlScreen_AnimImageWidget, (leWidget*)LightControlScreen_SmartConSecLogoBlock);

    LightControlScreen_SmartBlock = leWidget_New();
    LightControlScreen_SmartBlock->fn->setPosition(LightControlScreen_SmartBlock, 88, 163);
    LightControlScreen_SmartBlock->fn->setSize(LightControlScreen_SmartBlock, 28, 17);
    LightControlScreen_SmartBlock->fn->setScheme(LightControlScreen_SmartBlock, &InfoGraphicBackScheme);
    LightControlScreen_AnimImageWidget->fn->addChild(LightControlScreen_AnimImageWidget, (leWidget*)LightControlScreen_SmartBlock);

    LightControlScreen_ConnectedBlock = leWidget_New();
    LightControlScreen_ConnectedBlock->fn->setPosition(LightControlScreen_ConnectedBlock, 121, 164);
    LightControlScreen_ConnectedBlock->fn->setSize(LightControlScreen_ConnectedBlock, 37, 16);
    LightControlScreen_ConnectedBlock->fn->setScheme(LightControlScreen_ConnectedBlock, &InfoGraphicBackScheme);
    LightControlScreen_AnimImageWidget->fn->addChild(LightControlScreen_AnimImageWidget, (leWidget*)LightControlScreen_ConnectedBlock);

    LightControlScreen_SecureBlock = leWidget_New();
    LightControlScreen_SecureBlock->fn->setPosition(LightControlScreen_SecureBlock, 163, 164);
    LightControlScreen_SecureBlock->fn->setSize(LightControlScreen_SecureBlock, 28, 20);
    LightControlScreen_SecureBlock->fn->setScheme(LightControlScreen_SecureBlock, &InfoGraphicBackScheme);
    LightControlScreen_AnimImageWidget->fn->addChild(LightControlScreen_AnimImageWidget, (leWidget*)LightControlScreen_SecureBlock);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    LightControlScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_LightControlScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    LightControlScreen_OnUpdate(); // raise event
}

void screenHide_LightControlScreen(void)
{
    LightControlScreen_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    LightControlScreen_PanelWidget0 = NULL;
    LightControlScreen_LineWidget0 = NULL;
    LightControlScreen_ImageWidget0 = NULL;
    LightControlScreen_DisconnectButton = NULL;
    LightControlScreen_ColorPickerImage = NULL;
    LightControlScreen_DeviceCButton = NULL;
    LightControlScreen_DeviceBButton = NULL;
    LightControlScreen_DeviceAButton = NULL;
    LightControlScreen_SliderImageWidget = NULL;
    LightControlScreen_SliderControlPanel = NULL;
    LightControlScreen_ScrollKnobImageWidget = NULL;
    LightControlScreen_SelectedColorPanelA = NULL;
    LightControlScreen_AllDevicesButton = NULL;
    LightControlScreen_LabelWidget_0 = NULL;
    LightControlScreen_SelectedColorPanelB = NULL;
    LightControlScreen_SelectedColorPanelC = NULL;
    LightControlScreen_DeviceDataPanelA = NULL;
    LightControlScreen_LineGraphWidget_0 = NULL;
    LightControlScreen_BarGraphWidget_0 = NULL;
    LightControlScreen_DeviceInfoButton = NULL;
    LightControlScreen_BLEInfoButton = NULL;
    LightControlScreen_WiFiInfoButton = NULL;
    LightControlScreen_ColorWheelSelectColor = NULL;
    LightControlScreen_AnimImageWidget = NULL;
    LightControlScreen_ImageSequenceWidgetC = NULL;
    LightControlScreen_LabelWidget2 = NULL;
    LightControlScreen_TempLabelC = NULL;
    LightControlScreen_ImageSequenceWidgetB = NULL;
    LightControlScreen_LabelWidget1 = NULL;
    LightControlScreen_TempLabelB = NULL;
    LightControlScreen_ImageSequenceWidgetA = NULL;
    LightControlScreen_LabelWidget0 = NULL;
    LightControlScreen_TempLabelA = NULL;
    LightControlScreen_ColorGraphLabel = NULL;
    LightControlScreen_TempSensorGraphLabel = NULL;
    LightControlScreen_LineGraphLabelA = NULL;
    LightControlScreen_LineGraphLabelB = NULL;
    LightControlScreen_LineGraphLabelC = NULL;
    LightControlScreen_DeviceInfoLabel = NULL;
    LightControlScreen_BLEDeviceAName = NULL;
    LightControlScreen_BLEDeviceBName = NULL;
    LightControlScreen_BLEDeviceCName = NULL;
    LightControlScreen_BLEDeviceAOK = NULL;
    LightControlScreen_BLEDeviceBOK = NULL;
    LightControlScreen_BLEDeviceCOK = NULL;
    LightControlScreen_NetInfoPanel = NULL;
    LightControlScreen_PanelWidget_0 = NULL;
    LightControlScreen_PanelWidget_1 = NULL;
    LightControlScreen_PanelWidget_2 = NULL;
    LightControlScreen_NetInfString = NULL;
    LightControlScreen_NetSSIDString = NULL;
    LightControlScreen_NetIPString = NULL;
    LightControlScreen_NetConnString = NULL;
    LightControlScreen_NetURLString = NULL;
    LightControlScreen_NetWebURLQR = NULL;
    LightControlScreen_NetInterfaceInfo = NULL;
    LightControlScreen_NetSSIDInfo = NULL;
    LightControlScreen_NetIPInfo = NULL;
    LightControlScreen_NetConnInfo = NULL;
    LightControlScreen_NetURLInfo = NULL;
    LightControlScreen_MfgBlock = NULL;
    LightControlScreen_BldgBlock = NULL;
    LightControlScreen_EnergyBlock = NULL;
    LightControlScreen_EnvBlock = NULL;
    LightControlScreen_AgriBlock = NULL;
    LightControlScreen_LogiBlock = NULL;
    LightControlScreen_HomeAutoBlock = NULL;
    LightControlScreen_SmartCityBlock = NULL;
    LightControlScreen_SmartConSecLogoBlock = NULL;
    LightControlScreen_SmartBlock = NULL;
    LightControlScreen_ConnectedBlock = NULL;
    LightControlScreen_SecureBlock = NULL;


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

