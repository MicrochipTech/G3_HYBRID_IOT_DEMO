#include "gfx/legato/generated/screen/le_gen_screen_ControlScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* ControlScreen_PanelWidget0;
leLineWidget* ControlScreen_LineWidget0;
leImageWidget* ControlScreen_ImageWidget0;
leButtonWidget* ControlScreen_DisconnectButton;
leImageWidget* ControlScreen_ColorPickerImage;
leButtonWidget* ControlScreen_DeviceCButton;
leButtonWidget* ControlScreen_DeviceBButton;
leButtonWidget* ControlScreen_DeviceAButton;
leImageWidget* ControlScreen_SliderImageWidget;
leWidget* ControlScreen_SliderControlPanel;
leImageWidget* ControlScreen_ScrollKnobImageWidget;
leWidget* ControlScreen_SelectedColorPanelA;
leButtonWidget* ControlScreen_AllDevicesButton;
leLabelWidget* ControlScreen_LabelWidget_0;
leWidget* ControlScreen_SelectedColorPanelB;
leWidget* ControlScreen_SelectedColorPanelC;
leWidget* ControlScreen_DeviceDataPanelA;
leLineGraphWidget* ControlScreen_LineGraphWidget_0;
leBarGraphWidget* ControlScreen_BarGraphWidget_0;
leButtonWidget* ControlScreen_DeviceInfoButton;
leButtonWidget* ControlScreen_BLEInfoButton;
leButtonWidget* ControlScreen_WiFiInfoButton;
leWidget* ControlScreen_ColorWheelSelectColor;
leImageSequenceWidget* ControlScreen_AnimImageWidget;
leImageSequenceWidget* ControlScreen_ImageSequenceWidgetC;
leLabelWidget* ControlScreen_LabelWidget2;
leLabelWidget* ControlScreen_TempLabelC;
leImageSequenceWidget* ControlScreen_ImageSequenceWidgetB;
leLabelWidget* ControlScreen_LabelWidget1;
leLabelWidget* ControlScreen_TempLabelB;
leImageSequenceWidget* ControlScreen_ImageSequenceWidgetA;
leLabelWidget* ControlScreen_LabelWidget0;
leLabelWidget* ControlScreen_TempLabelA;
leLabelWidget* ControlScreen_ColorGraphLabel;
leLabelWidget* ControlScreen_TempSensorGraphLabel;
leLabelWidget* ControlScreen_LineGraphLabelA;
leLabelWidget* ControlScreen_LineGraphLabelB;
leLabelWidget* ControlScreen_LineGraphLabelC;
leLabelWidget* ControlScreen_DeviceInfoLabel;
leLabelWidget* ControlScreen_BLEDeviceAName;
leLabelWidget* ControlScreen_BLEDeviceBName;
leLabelWidget* ControlScreen_BLEDeviceCName;
leImageWidget* ControlScreen_BLEDeviceAOK;
leImageWidget* ControlScreen_BLEDeviceBOK;
leImageWidget* ControlScreen_BLEDeviceCOK;
leWidget* ControlScreen_NetInfoPanel;
leWidget* ControlScreen_PanelWidget_0;
leWidget* ControlScreen_PanelWidget_1;
leWidget* ControlScreen_PanelWidget_2;
leLabelWidget* ControlScreen_NetInfString;
leLabelWidget* ControlScreen_NetSSIDString;
leLabelWidget* ControlScreen_NetIPString;
leLabelWidget* ControlScreen_NetConnString;
leLabelWidget* ControlScreen_NetURLString;
leImageWidget* ControlScreen_NetWebURLQR;
leLabelWidget* ControlScreen_NetInterfaceInfo;
leLabelWidget* ControlScreen_NetSSIDInfo;
leLabelWidget* ControlScreen_NetIPInfo;
leLabelWidget* ControlScreen_NetConnInfo;
leLabelWidget* ControlScreen_NetURLInfo;
leWidget* ControlScreen_MfgBlock;
leWidget* ControlScreen_BldgBlock;
leWidget* ControlScreen_EnergyBlock;
leWidget* ControlScreen_EnvBlock;
leWidget* ControlScreen_AgriBlock;
leWidget* ControlScreen_LogiBlock;
leWidget* ControlScreen_HomeAutoBlock;
leWidget* ControlScreen_SmartCityBlock;
leWidget* ControlScreen_SmartConSecLogoBlock;
leWidget* ControlScreen_SmartBlock;
leWidget* ControlScreen_ConnectedBlock;
leWidget* ControlScreen_SecureBlock;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_ControlScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_ControlScreen(void)
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

    ControlScreen_PanelWidget0 = leWidget_New();
    ControlScreen_PanelWidget0->fn->setPosition(ControlScreen_PanelWidget0, 1, 1);
    ControlScreen_PanelWidget0->fn->setSize(ControlScreen_PanelWidget0, 800, 480);
    ControlScreen_PanelWidget0->fn->setScheme(ControlScreen_PanelWidget0, &BackScheme);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_PanelWidget0);

    ControlScreen_LineWidget0 = leLineWidget_New();
    ControlScreen_LineWidget0->fn->setPosition(ControlScreen_LineWidget0, 97, 25);
    ControlScreen_LineWidget0->fn->setSize(ControlScreen_LineWidget0, 700, 15);
    ControlScreen_LineWidget0->fn->setScheme(ControlScreen_LineWidget0, &WhiteScheme);
    ControlScreen_LineWidget0->fn->setBackgroundType(ControlScreen_LineWidget0, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_LineWidget0->fn->setStartPoint(ControlScreen_LineWidget0, 0, 5);
    ControlScreen_LineWidget0->fn->setEndPoint(ControlScreen_LineWidget0, 700, 5);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_LineWidget0);

    ControlScreen_ImageWidget0 = leImageWidget_New();
    ControlScreen_ImageWidget0->fn->setPosition(ControlScreen_ImageWidget0, 10, 10);
    ControlScreen_ImageWidget0->fn->setSize(ControlScreen_ImageWidget0, 100, 40);
    ControlScreen_ImageWidget0->fn->setBackgroundType(ControlScreen_ImageWidget0, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_ImageWidget0->fn->setBorderType(ControlScreen_ImageWidget0, LE_WIDGET_BORDER_NONE);
    ControlScreen_ImageWidget0->fn->setImage(ControlScreen_ImageWidget0, (leImage*)&MchpLogo_100);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_ImageWidget0);

    ControlScreen_DisconnectButton = leButtonWidget_New();
    ControlScreen_DisconnectButton->fn->setPosition(ControlScreen_DisconnectButton, 732, 418);
    ControlScreen_DisconnectButton->fn->setSize(ControlScreen_DisconnectButton, 60, 50);
    ControlScreen_DisconnectButton->fn->setScheme(ControlScreen_DisconnectButton, &TextInactiveScheme);
    ControlScreen_DisconnectButton->fn->setBorderType(ControlScreen_DisconnectButton, LE_WIDGET_BORDER_NONE);
    ControlScreen_DisconnectButton->fn->setString(ControlScreen_DisconnectButton, (leString*)&string_DisconnectString);
    ControlScreen_DisconnectButton->fn->setPressedImage(ControlScreen_DisconnectButton, (leImage*)&Disconnect20);
    ControlScreen_DisconnectButton->fn->setReleasedImage(ControlScreen_DisconnectButton, (leImage*)&Disconnect20);
    ControlScreen_DisconnectButton->fn->setImagePosition(ControlScreen_DisconnectButton, LE_RELATIVE_POSITION_ABOVE);
    ControlScreen_DisconnectButton->fn->setImageMargin(ControlScreen_DisconnectButton, 5);
    ControlScreen_DisconnectButton->fn->setPressedEventCallback(ControlScreen_DisconnectButton, event_ControlScreen_DisconnectButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_DisconnectButton);

    ControlScreen_ColorPickerImage = leImageWidget_New();
    ControlScreen_ColorPickerImage->fn->setPosition(ControlScreen_ColorPickerImage, 514, 173);
    ControlScreen_ColorPickerImage->fn->setSize(ControlScreen_ColorPickerImage, 200, 200);
    ControlScreen_ColorPickerImage->fn->setBackgroundType(ControlScreen_ColorPickerImage, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_ColorPickerImage->fn->setBorderType(ControlScreen_ColorPickerImage, LE_WIDGET_BORDER_NONE);
    ControlScreen_ColorPickerImage->fn->setMargins(ControlScreen_ColorPickerImage, 0, 0, 0, 0);
    ControlScreen_ColorPickerImage->fn->setImage(ControlScreen_ColorPickerImage, (leImage*)&ColorPickerBlueBack200_565);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_ColorPickerImage);

    ControlScreen_DeviceCButton = leButtonWidget_New();
    ControlScreen_DeviceCButton->fn->setPosition(ControlScreen_DeviceCButton, 440, 360);
    ControlScreen_DeviceCButton->fn->setSize(ControlScreen_DeviceCButton, 65, 65);
    ControlScreen_DeviceCButton->fn->setBackgroundType(ControlScreen_DeviceCButton, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_DeviceCButton->fn->setBorderType(ControlScreen_DeviceCButton, LE_WIDGET_BORDER_NONE);
    ControlScreen_DeviceCButton->fn->setPressedOffset(ControlScreen_DeviceCButton, 0);
    ControlScreen_DeviceCButton->fn->setPressedEventCallback(ControlScreen_DeviceCButton, event_ControlScreen_DeviceCButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_DeviceCButton);

    ControlScreen_ImageSequenceWidgetC = leImageSequenceWidget_New();
    ControlScreen_ImageSequenceWidgetC->fn->setPosition(ControlScreen_ImageSequenceWidgetC, 0, 0);
    ControlScreen_ImageSequenceWidgetC->fn->setSize(ControlScreen_ImageSequenceWidgetC, 65, 65);
    ControlScreen_ImageSequenceWidgetC->fn->setEnabled(ControlScreen_ImageSequenceWidgetC, LE_FALSE);
    ControlScreen_ImageSequenceWidgetC->fn->setBackgroundType(ControlScreen_ImageSequenceWidgetC, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_ImageSequenceWidgetC->fn->setImageCount(ControlScreen_ImageSequenceWidgetC, 2);
    ControlScreen_ImageSequenceWidgetC->fn->setImage(ControlScreen_ImageSequenceWidgetC, 0, &DeviceSelect60);
    ControlScreen_ImageSequenceWidgetC->fn->setImageDelay(ControlScreen_ImageSequenceWidgetC, 0, 1000);
    ControlScreen_ImageSequenceWidgetC->fn->setImage(ControlScreen_ImageSequenceWidgetC, 1, &DeviceNoSelect60);
    ControlScreen_ImageSequenceWidgetC->fn->setImageDelay(ControlScreen_ImageSequenceWidgetC, 1, 1000);
    ControlScreen_DeviceCButton->fn->addChild(ControlScreen_DeviceCButton, (leWidget*)ControlScreen_ImageSequenceWidgetC);

    ControlScreen_LabelWidget2 = leLabelWidget_New();
    ControlScreen_LabelWidget2->fn->setPosition(ControlScreen_LabelWidget2, -2, -1);
    ControlScreen_LabelWidget2->fn->setSize(ControlScreen_LabelWidget2, 25, 25);
    ControlScreen_LabelWidget2->fn->setEnabled(ControlScreen_LabelWidget2, LE_FALSE);
    ControlScreen_LabelWidget2->fn->setScheme(ControlScreen_LabelWidget2, &TextScheme);
    ControlScreen_LabelWidget2->fn->setBackgroundType(ControlScreen_LabelWidget2, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_LabelWidget2->fn->setHAlignment(ControlScreen_LabelWidget2, LE_HALIGN_CENTER);
    ControlScreen_LabelWidget2->fn->setString(ControlScreen_LabelWidget2, (leString*)&string_DeviceC);
    ControlScreen_DeviceCButton->fn->addChild(ControlScreen_DeviceCButton, (leWidget*)ControlScreen_LabelWidget2);

    ControlScreen_TempLabelC = leLabelWidget_New();
    ControlScreen_TempLabelC->fn->setPosition(ControlScreen_TempLabelC, 5, 18);
    ControlScreen_TempLabelC->fn->setSize(ControlScreen_TempLabelC, 55, 30);
    ControlScreen_TempLabelC->fn->setScheme(ControlScreen_TempLabelC, &TextScheme);
    ControlScreen_TempLabelC->fn->setBackgroundType(ControlScreen_TempLabelC, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_TempLabelC->fn->setHAlignment(ControlScreen_TempLabelC, LE_HALIGN_CENTER);
    ControlScreen_TempLabelC->fn->setString(ControlScreen_TempLabelC, (leString*)&string_DefaultTemp);
    ControlScreen_DeviceCButton->fn->addChild(ControlScreen_DeviceCButton, (leWidget*)ControlScreen_TempLabelC);

    ControlScreen_DeviceBButton = leButtonWidget_New();
    ControlScreen_DeviceBButton->fn->setPosition(ControlScreen_DeviceBButton, 370, 240);
    ControlScreen_DeviceBButton->fn->setSize(ControlScreen_DeviceBButton, 65, 65);
    ControlScreen_DeviceBButton->fn->setBackgroundType(ControlScreen_DeviceBButton, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_DeviceBButton->fn->setBorderType(ControlScreen_DeviceBButton, LE_WIDGET_BORDER_NONE);
    ControlScreen_DeviceBButton->fn->setPressedOffset(ControlScreen_DeviceBButton, 0);
    ControlScreen_DeviceBButton->fn->setPressedEventCallback(ControlScreen_DeviceBButton, event_ControlScreen_DeviceBButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_DeviceBButton);

    ControlScreen_ImageSequenceWidgetB = leImageSequenceWidget_New();
    ControlScreen_ImageSequenceWidgetB->fn->setPosition(ControlScreen_ImageSequenceWidgetB, 0, 0);
    ControlScreen_ImageSequenceWidgetB->fn->setSize(ControlScreen_ImageSequenceWidgetB, 65, 65);
    ControlScreen_ImageSequenceWidgetB->fn->setEnabled(ControlScreen_ImageSequenceWidgetB, LE_FALSE);
    ControlScreen_ImageSequenceWidgetB->fn->setBackgroundType(ControlScreen_ImageSequenceWidgetB, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_ImageSequenceWidgetB->fn->setImageCount(ControlScreen_ImageSequenceWidgetB, 2);
    ControlScreen_ImageSequenceWidgetB->fn->setImage(ControlScreen_ImageSequenceWidgetB, 0, &DeviceSelect60);
    ControlScreen_ImageSequenceWidgetB->fn->setImageDelay(ControlScreen_ImageSequenceWidgetB, 0, 1000);
    ControlScreen_ImageSequenceWidgetB->fn->setImage(ControlScreen_ImageSequenceWidgetB, 1, &DeviceNoSelect60);
    ControlScreen_ImageSequenceWidgetB->fn->setImageDelay(ControlScreen_ImageSequenceWidgetB, 1, 1000);
    ControlScreen_DeviceBButton->fn->addChild(ControlScreen_DeviceBButton, (leWidget*)ControlScreen_ImageSequenceWidgetB);

    ControlScreen_LabelWidget1 = leLabelWidget_New();
    ControlScreen_LabelWidget1->fn->setPosition(ControlScreen_LabelWidget1, -1, -2);
    ControlScreen_LabelWidget1->fn->setSize(ControlScreen_LabelWidget1, 25, 25);
    ControlScreen_LabelWidget1->fn->setEnabled(ControlScreen_LabelWidget1, LE_FALSE);
    ControlScreen_LabelWidget1->fn->setScheme(ControlScreen_LabelWidget1, &TextScheme);
    ControlScreen_LabelWidget1->fn->setBackgroundType(ControlScreen_LabelWidget1, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_LabelWidget1->fn->setHAlignment(ControlScreen_LabelWidget1, LE_HALIGN_CENTER);
    ControlScreen_LabelWidget1->fn->setString(ControlScreen_LabelWidget1, (leString*)&string_DeviceB);
    ControlScreen_DeviceBButton->fn->addChild(ControlScreen_DeviceBButton, (leWidget*)ControlScreen_LabelWidget1);

    ControlScreen_TempLabelB = leLabelWidget_New();
    ControlScreen_TempLabelB->fn->setPosition(ControlScreen_TempLabelB, 5, 18);
    ControlScreen_TempLabelB->fn->setSize(ControlScreen_TempLabelB, 55, 30);
    ControlScreen_TempLabelB->fn->setScheme(ControlScreen_TempLabelB, &TextScheme);
    ControlScreen_TempLabelB->fn->setBackgroundType(ControlScreen_TempLabelB, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_TempLabelB->fn->setHAlignment(ControlScreen_TempLabelB, LE_HALIGN_CENTER);
    ControlScreen_TempLabelB->fn->setString(ControlScreen_TempLabelB, (leString*)&string_DefaultTemp);
    ControlScreen_DeviceBButton->fn->addChild(ControlScreen_DeviceBButton, (leWidget*)ControlScreen_TempLabelB);

    ControlScreen_DeviceAButton = leButtonWidget_New();
    ControlScreen_DeviceAButton->fn->setPosition(ControlScreen_DeviceAButton, 440, 120);
    ControlScreen_DeviceAButton->fn->setSize(ControlScreen_DeviceAButton, 65, 65);
    ControlScreen_DeviceAButton->fn->setBackgroundType(ControlScreen_DeviceAButton, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_DeviceAButton->fn->setBorderType(ControlScreen_DeviceAButton, LE_WIDGET_BORDER_NONE);
    ControlScreen_DeviceAButton->fn->setPressedOffset(ControlScreen_DeviceAButton, 0);
    ControlScreen_DeviceAButton->fn->setPressedEventCallback(ControlScreen_DeviceAButton, event_ControlScreen_DeviceAButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_DeviceAButton);

    ControlScreen_ImageSequenceWidgetA = leImageSequenceWidget_New();
    ControlScreen_ImageSequenceWidgetA->fn->setPosition(ControlScreen_ImageSequenceWidgetA, 0, 0);
    ControlScreen_ImageSequenceWidgetA->fn->setSize(ControlScreen_ImageSequenceWidgetA, 65, 65);
    ControlScreen_ImageSequenceWidgetA->fn->setEnabled(ControlScreen_ImageSequenceWidgetA, LE_FALSE);
    ControlScreen_ImageSequenceWidgetA->fn->setBackgroundType(ControlScreen_ImageSequenceWidgetA, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_ImageSequenceWidgetA->fn->setImageCount(ControlScreen_ImageSequenceWidgetA, 2);
    ControlScreen_ImageSequenceWidgetA->fn->setImage(ControlScreen_ImageSequenceWidgetA, 0, &DeviceSelect60);
    ControlScreen_ImageSequenceWidgetA->fn->setImageDelay(ControlScreen_ImageSequenceWidgetA, 0, 1000);
    ControlScreen_ImageSequenceWidgetA->fn->setImage(ControlScreen_ImageSequenceWidgetA, 1, &DeviceNoSelect60);
    ControlScreen_ImageSequenceWidgetA->fn->setImageDelay(ControlScreen_ImageSequenceWidgetA, 1, 1000);
    ControlScreen_DeviceAButton->fn->addChild(ControlScreen_DeviceAButton, (leWidget*)ControlScreen_ImageSequenceWidgetA);

    ControlScreen_LabelWidget0 = leLabelWidget_New();
    ControlScreen_LabelWidget0->fn->setPosition(ControlScreen_LabelWidget0, 0, -1);
    ControlScreen_LabelWidget0->fn->setSize(ControlScreen_LabelWidget0, 25, 25);
    ControlScreen_LabelWidget0->fn->setEnabled(ControlScreen_LabelWidget0, LE_FALSE);
    ControlScreen_LabelWidget0->fn->setScheme(ControlScreen_LabelWidget0, &TextScheme);
    ControlScreen_LabelWidget0->fn->setBackgroundType(ControlScreen_LabelWidget0, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_LabelWidget0->fn->setHAlignment(ControlScreen_LabelWidget0, LE_HALIGN_CENTER);
    ControlScreen_LabelWidget0->fn->setString(ControlScreen_LabelWidget0, (leString*)&string_DeviceA);
    ControlScreen_DeviceAButton->fn->addChild(ControlScreen_DeviceAButton, (leWidget*)ControlScreen_LabelWidget0);

    ControlScreen_TempLabelA = leLabelWidget_New();
    ControlScreen_TempLabelA->fn->setPosition(ControlScreen_TempLabelA, 5, 18);
    ControlScreen_TempLabelA->fn->setSize(ControlScreen_TempLabelA, 55, 30);
    ControlScreen_TempLabelA->fn->setScheme(ControlScreen_TempLabelA, &WhiteScheme);
    ControlScreen_TempLabelA->fn->setBackgroundType(ControlScreen_TempLabelA, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_TempLabelA->fn->setHAlignment(ControlScreen_TempLabelA, LE_HALIGN_CENTER);
    ControlScreen_TempLabelA->fn->setString(ControlScreen_TempLabelA, (leString*)&string_DefaultTemp);
    ControlScreen_DeviceAButton->fn->addChild(ControlScreen_DeviceAButton, (leWidget*)ControlScreen_TempLabelA);

    ControlScreen_SliderImageWidget = leImageWidget_New();
    ControlScreen_SliderImageWidget->fn->setPosition(ControlScreen_SliderImageWidget, 730, 150);
    ControlScreen_SliderImageWidget->fn->setSize(ControlScreen_SliderImageWidget, 60, 250);
    ControlScreen_SliderImageWidget->fn->setBackgroundType(ControlScreen_SliderImageWidget, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_SliderImageWidget->fn->setBorderType(ControlScreen_SliderImageWidget, LE_WIDGET_BORDER_NONE);
    ControlScreen_SliderImageWidget->fn->setImage(ControlScreen_SliderImageWidget, (leImage*)&Slider50);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_SliderImageWidget);

    ControlScreen_SliderControlPanel = leWidget_New();
    ControlScreen_SliderControlPanel->fn->setPosition(ControlScreen_SliderControlPanel, 726, 205);
    ControlScreen_SliderControlPanel->fn->setSize(ControlScreen_SliderControlPanel, 67, 147);
    ControlScreen_SliderControlPanel->fn->setBackgroundType(ControlScreen_SliderControlPanel, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_SliderControlPanel);

    ControlScreen_ScrollKnobImageWidget = leImageWidget_New();
    ControlScreen_ScrollKnobImageWidget->fn->setPosition(ControlScreen_ScrollKnobImageWidget, 745, 261);
    ControlScreen_ScrollKnobImageWidget->fn->setSize(ControlScreen_ScrollKnobImageWidget, 30, 30);
    ControlScreen_ScrollKnobImageWidget->fn->setEnabled(ControlScreen_ScrollKnobImageWidget, LE_FALSE);
    ControlScreen_ScrollKnobImageWidget->fn->setBackgroundType(ControlScreen_ScrollKnobImageWidget, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_ScrollKnobImageWidget->fn->setBorderType(ControlScreen_ScrollKnobImageWidget, LE_WIDGET_BORDER_NONE);
    ControlScreen_ScrollKnobImageWidget->fn->setImage(ControlScreen_ScrollKnobImageWidget, (leImage*)&Knob30);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_ScrollKnobImageWidget);

    ControlScreen_SelectedColorPanelA = leWidget_New();
    ControlScreen_SelectedColorPanelA->fn->setPosition(ControlScreen_SelectedColorPanelA, 510, 144);
    ControlScreen_SelectedColorPanelA->fn->setSize(ControlScreen_SelectedColorPanelA, 20, 20);
    ControlScreen_SelectedColorPanelA->fn->setScheme(ControlScreen_SelectedColorPanelA, &BlueScheme);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_SelectedColorPanelA);

    ControlScreen_AllDevicesButton = leButtonWidget_New();
    ControlScreen_AllDevicesButton->fn->setPosition(ControlScreen_AllDevicesButton, 585, 391);
    ControlScreen_AllDevicesButton->fn->setSize(ControlScreen_AllDevicesButton, 60, 60);
    ControlScreen_AllDevicesButton->fn->setScheme(ControlScreen_AllDevicesButton, &TextScheme);
    ControlScreen_AllDevicesButton->fn->setBorderType(ControlScreen_AllDevicesButton, LE_WIDGET_BORDER_NONE);
    ControlScreen_AllDevicesButton->fn->setToggleable(ControlScreen_AllDevicesButton, LE_TRUE);
    ControlScreen_AllDevicesButton->fn->setString(ControlScreen_AllDevicesButton, (leString*)&string_AllString);
    ControlScreen_AllDevicesButton->fn->setPressedImage(ControlScreen_AllDevicesButton, (leImage*)&DeviceNoSelect40);
    ControlScreen_AllDevicesButton->fn->setReleasedImage(ControlScreen_AllDevicesButton, (leImage*)&DeviceSelect40Bulb);
    ControlScreen_AllDevicesButton->fn->setImagePosition(ControlScreen_AllDevicesButton, LE_RELATIVE_POSITION_BEHIND);
    ControlScreen_AllDevicesButton->fn->setPressedOffset(ControlScreen_AllDevicesButton, 0);
    ControlScreen_AllDevicesButton->fn->setPressedEventCallback(ControlScreen_AllDevicesButton, event_ControlScreen_AllDevicesButton_OnPressed);
    ControlScreen_AllDevicesButton->fn->setReleasedEventCallback(ControlScreen_AllDevicesButton, event_ControlScreen_AllDevicesButton_OnReleased);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_AllDevicesButton);

    ControlScreen_LabelWidget_0 = leLabelWidget_New();
    ControlScreen_LabelWidget_0->fn->setPosition(ControlScreen_LabelWidget_0, 410, 2);
    ControlScreen_LabelWidget_0->fn->setSize(ControlScreen_LabelWidget_0, 380, 25);
    ControlScreen_LabelWidget_0->fn->setScheme(ControlScreen_LabelWidget_0, &TextScheme);
    ControlScreen_LabelWidget_0->fn->setHAlignment(ControlScreen_LabelWidget_0, LE_HALIGN_CENTER);
    ControlScreen_LabelWidget_0->fn->setString(ControlScreen_LabelWidget_0, (leString*)&string_DemoName);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_LabelWidget_0);

    ControlScreen_SelectedColorPanelB = leWidget_New();
    ControlScreen_SelectedColorPanelB->fn->setPosition(ControlScreen_SelectedColorPanelB, 439, 264);
    ControlScreen_SelectedColorPanelB->fn->setSize(ControlScreen_SelectedColorPanelB, 20, 20);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_SelectedColorPanelB);

    ControlScreen_SelectedColorPanelC = leWidget_New();
    ControlScreen_SelectedColorPanelC->fn->setPosition(ControlScreen_SelectedColorPanelC, 511, 388);
    ControlScreen_SelectedColorPanelC->fn->setSize(ControlScreen_SelectedColorPanelC, 20, 20);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_SelectedColorPanelC);

    ControlScreen_DeviceDataPanelA = leWidget_New();
    ControlScreen_DeviceDataPanelA->fn->setPosition(ControlScreen_DeviceDataPanelA, 37, 114);
    ControlScreen_DeviceDataPanelA->fn->setSize(ControlScreen_DeviceDataPanelA, 300, 340);
    ControlScreen_DeviceDataPanelA->fn->setScheme(ControlScreen_DeviceDataPanelA, &WhiteScheme);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_DeviceDataPanelA);

    ControlScreen_ColorGraphLabel = leLabelWidget_New();
    ControlScreen_ColorGraphLabel->fn->setPosition(ControlScreen_ColorGraphLabel, 90, 49);
    ControlScreen_ColorGraphLabel->fn->setSize(ControlScreen_ColorGraphLabel, 123, 19);
    ControlScreen_ColorGraphLabel->fn->setScheme(ControlScreen_ColorGraphLabel, &BackScheme);
    ControlScreen_ColorGraphLabel->fn->setBackgroundType(ControlScreen_ColorGraphLabel, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_ColorGraphLabel->fn->setHAlignment(ControlScreen_ColorGraphLabel, LE_HALIGN_CENTER);
    ControlScreen_ColorGraphLabel->fn->setString(ControlScreen_ColorGraphLabel, (leString*)&string_ColorChannels);
    ControlScreen_DeviceDataPanelA->fn->addChild(ControlScreen_DeviceDataPanelA, (leWidget*)ControlScreen_ColorGraphLabel);

    ControlScreen_TempSensorGraphLabel = leLabelWidget_New();
    ControlScreen_TempSensorGraphLabel->fn->setPosition(ControlScreen_TempSensorGraphLabel, 71, 181);
    ControlScreen_TempSensorGraphLabel->fn->setSize(ControlScreen_TempSensorGraphLabel, 170, 25);
    ControlScreen_TempSensorGraphLabel->fn->setScheme(ControlScreen_TempSensorGraphLabel, &BackScheme);
    ControlScreen_TempSensorGraphLabel->fn->setBackgroundType(ControlScreen_TempSensorGraphLabel, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_TempSensorGraphLabel->fn->setHAlignment(ControlScreen_TempSensorGraphLabel, LE_HALIGN_CENTER);
    ControlScreen_TempSensorGraphLabel->fn->setString(ControlScreen_TempSensorGraphLabel, (leString*)&string_TempSensor);
    ControlScreen_DeviceDataPanelA->fn->addChild(ControlScreen_DeviceDataPanelA, (leWidget*)ControlScreen_TempSensorGraphLabel);

    ControlScreen_LineGraphLabelA = leLabelWidget_New();
    ControlScreen_LineGraphLabelA->fn->setPosition(ControlScreen_LineGraphLabelA, 66, 314);
    ControlScreen_LineGraphLabelA->fn->setSize(ControlScreen_LineGraphLabelA, 40, 25);
    ControlScreen_LineGraphLabelA->fn->setBackgroundType(ControlScreen_LineGraphLabelA, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_LineGraphLabelA->fn->setHAlignment(ControlScreen_LineGraphLabelA, LE_HALIGN_RIGHT);
    ControlScreen_LineGraphLabelA->fn->setString(ControlScreen_LineGraphLabelA, (leString*)&string_DeviceA);
    ControlScreen_DeviceDataPanelA->fn->addChild(ControlScreen_DeviceDataPanelA, (leWidget*)ControlScreen_LineGraphLabelA);

    ControlScreen_PanelWidget_0 = leWidget_New();
    ControlScreen_PanelWidget_0->fn->setPosition(ControlScreen_PanelWidget_0, 10, 8);
    ControlScreen_PanelWidget_0->fn->setSize(ControlScreen_PanelWidget_0, 10, 10);
    ControlScreen_PanelWidget_0->fn->setScheme(ControlScreen_PanelWidget_0, &RedScheme);
    ControlScreen_LineGraphLabelA->fn->addChild(ControlScreen_LineGraphLabelA, (leWidget*)ControlScreen_PanelWidget_0);

    ControlScreen_LineGraphLabelB = leLabelWidget_New();
    ControlScreen_LineGraphLabelB->fn->setPosition(ControlScreen_LineGraphLabelB, 129, 314);
    ControlScreen_LineGraphLabelB->fn->setSize(ControlScreen_LineGraphLabelB, 40, 25);
    ControlScreen_LineGraphLabelB->fn->setBackgroundType(ControlScreen_LineGraphLabelB, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_LineGraphLabelB->fn->setHAlignment(ControlScreen_LineGraphLabelB, LE_HALIGN_RIGHT);
    ControlScreen_LineGraphLabelB->fn->setString(ControlScreen_LineGraphLabelB, (leString*)&string_DeviceB);
    ControlScreen_DeviceDataPanelA->fn->addChild(ControlScreen_DeviceDataPanelA, (leWidget*)ControlScreen_LineGraphLabelB);

    ControlScreen_PanelWidget_1 = leWidget_New();
    ControlScreen_PanelWidget_1->fn->setPosition(ControlScreen_PanelWidget_1, 9, 8);
    ControlScreen_PanelWidget_1->fn->setSize(ControlScreen_PanelWidget_1, 10, 10);
    ControlScreen_PanelWidget_1->fn->setScheme(ControlScreen_PanelWidget_1, &GreenScheme);
    ControlScreen_LineGraphLabelB->fn->addChild(ControlScreen_LineGraphLabelB, (leWidget*)ControlScreen_PanelWidget_1);

    ControlScreen_LineGraphLabelC = leLabelWidget_New();
    ControlScreen_LineGraphLabelC->fn->setPosition(ControlScreen_LineGraphLabelC, 192, 314);
    ControlScreen_LineGraphLabelC->fn->setSize(ControlScreen_LineGraphLabelC, 40, 25);
    ControlScreen_LineGraphLabelC->fn->setBackgroundType(ControlScreen_LineGraphLabelC, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_LineGraphLabelC->fn->setHAlignment(ControlScreen_LineGraphLabelC, LE_HALIGN_RIGHT);
    ControlScreen_LineGraphLabelC->fn->setString(ControlScreen_LineGraphLabelC, (leString*)&string_DeviceC);
    ControlScreen_DeviceDataPanelA->fn->addChild(ControlScreen_DeviceDataPanelA, (leWidget*)ControlScreen_LineGraphLabelC);

    ControlScreen_PanelWidget_2 = leWidget_New();
    ControlScreen_PanelWidget_2->fn->setPosition(ControlScreen_PanelWidget_2, 9, 8);
    ControlScreen_PanelWidget_2->fn->setSize(ControlScreen_PanelWidget_2, 10, 10);
    ControlScreen_PanelWidget_2->fn->setScheme(ControlScreen_PanelWidget_2, &BlueScheme);
    ControlScreen_LineGraphLabelC->fn->addChild(ControlScreen_LineGraphLabelC, (leWidget*)ControlScreen_PanelWidget_2);

    ControlScreen_DeviceInfoLabel = leLabelWidget_New();
    ControlScreen_DeviceInfoLabel->fn->setPosition(ControlScreen_DeviceInfoLabel, 4, 4);
    ControlScreen_DeviceInfoLabel->fn->setSize(ControlScreen_DeviceInfoLabel, 294, 25);
    ControlScreen_DeviceInfoLabel->fn->setScheme(ControlScreen_DeviceInfoLabel, &BackScheme);
    ControlScreen_DeviceInfoLabel->fn->setBackgroundType(ControlScreen_DeviceInfoLabel, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_DeviceInfoLabel->fn->setHAlignment(ControlScreen_DeviceInfoLabel, LE_HALIGN_CENTER);
    ControlScreen_DeviceInfoLabel->fn->setString(ControlScreen_DeviceInfoLabel, (leString*)&string_WiFiDeviceInfo);
    ControlScreen_DeviceDataPanelA->fn->addChild(ControlScreen_DeviceDataPanelA, (leWidget*)ControlScreen_DeviceInfoLabel);

    ControlScreen_BLEDeviceAName = leLabelWidget_New();
    ControlScreen_BLEDeviceAName->fn->setPosition(ControlScreen_BLEDeviceAName, 48, 56);
    ControlScreen_BLEDeviceAName->fn->setSize(ControlScreen_BLEDeviceAName, 200, 30);
    ControlScreen_BLEDeviceAName->fn->setScheme(ControlScreen_BLEDeviceAName, &BLEPanelScheme);
    ControlScreen_BLEDeviceAName->fn->setBackgroundType(ControlScreen_BLEDeviceAName, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_BLEDeviceAName->fn->setString(ControlScreen_BLEDeviceAName, (leString*)&string_BLEDeviceInfo);
    ControlScreen_DeviceDataPanelA->fn->addChild(ControlScreen_DeviceDataPanelA, (leWidget*)ControlScreen_BLEDeviceAName);

    ControlScreen_BLEDeviceBName = leLabelWidget_New();
    ControlScreen_BLEDeviceBName->fn->setPosition(ControlScreen_BLEDeviceBName, 48, 96);
    ControlScreen_BLEDeviceBName->fn->setSize(ControlScreen_BLEDeviceBName, 200, 30);
    ControlScreen_BLEDeviceBName->fn->setScheme(ControlScreen_BLEDeviceBName, &BLEPanelScheme);
    ControlScreen_BLEDeviceBName->fn->setBackgroundType(ControlScreen_BLEDeviceBName, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_BLEDeviceBName->fn->setString(ControlScreen_BLEDeviceBName, (leString*)&string_BLEDeviceInfo);
    ControlScreen_DeviceDataPanelA->fn->addChild(ControlScreen_DeviceDataPanelA, (leWidget*)ControlScreen_BLEDeviceBName);

    ControlScreen_BLEDeviceCName = leLabelWidget_New();
    ControlScreen_BLEDeviceCName->fn->setPosition(ControlScreen_BLEDeviceCName, 48, 136);
    ControlScreen_BLEDeviceCName->fn->setSize(ControlScreen_BLEDeviceCName, 200, 30);
    ControlScreen_BLEDeviceCName->fn->setBackgroundType(ControlScreen_BLEDeviceCName, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_BLEDeviceCName->fn->setString(ControlScreen_BLEDeviceCName, (leString*)&string_BLEDeviceInfo);
    ControlScreen_DeviceDataPanelA->fn->addChild(ControlScreen_DeviceDataPanelA, (leWidget*)ControlScreen_BLEDeviceCName);

    ControlScreen_BLEDeviceAOK = leImageWidget_New();
    ControlScreen_BLEDeviceAOK->fn->setPosition(ControlScreen_BLEDeviceAOK, 12, 63);
    ControlScreen_BLEDeviceAOK->fn->setSize(ControlScreen_BLEDeviceAOK, 35, 25);
    ControlScreen_BLEDeviceAOK->fn->setBackgroundType(ControlScreen_BLEDeviceAOK, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_BLEDeviceAOK->fn->setBorderType(ControlScreen_BLEDeviceAOK, LE_WIDGET_BORDER_NONE);
    ControlScreen_BLEDeviceAOK->fn->setImage(ControlScreen_BLEDeviceAOK, (leImage*)&Check30);
    ControlScreen_DeviceDataPanelA->fn->addChild(ControlScreen_DeviceDataPanelA, (leWidget*)ControlScreen_BLEDeviceAOK);

    ControlScreen_BLEDeviceBOK = leImageWidget_New();
    ControlScreen_BLEDeviceBOK->fn->setPosition(ControlScreen_BLEDeviceBOK, 12, 101);
    ControlScreen_BLEDeviceBOK->fn->setSize(ControlScreen_BLEDeviceBOK, 35, 25);
    ControlScreen_BLEDeviceBOK->fn->setBackgroundType(ControlScreen_BLEDeviceBOK, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_BLEDeviceBOK->fn->setBorderType(ControlScreen_BLEDeviceBOK, LE_WIDGET_BORDER_NONE);
    ControlScreen_BLEDeviceBOK->fn->setImage(ControlScreen_BLEDeviceBOK, (leImage*)&Check30);
    ControlScreen_DeviceDataPanelA->fn->addChild(ControlScreen_DeviceDataPanelA, (leWidget*)ControlScreen_BLEDeviceBOK);

    ControlScreen_BLEDeviceCOK = leImageWidget_New();
    ControlScreen_BLEDeviceCOK->fn->setPosition(ControlScreen_BLEDeviceCOK, 12, 141);
    ControlScreen_BLEDeviceCOK->fn->setSize(ControlScreen_BLEDeviceCOK, 35, 25);
    ControlScreen_BLEDeviceCOK->fn->setBackgroundType(ControlScreen_BLEDeviceCOK, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_BLEDeviceCOK->fn->setBorderType(ControlScreen_BLEDeviceCOK, LE_WIDGET_BORDER_NONE);
    ControlScreen_BLEDeviceCOK->fn->setImage(ControlScreen_BLEDeviceCOK, (leImage*)&Check30);
    ControlScreen_DeviceDataPanelA->fn->addChild(ControlScreen_DeviceDataPanelA, (leWidget*)ControlScreen_BLEDeviceCOK);

    ControlScreen_NetInfoPanel = leWidget_New();
    ControlScreen_NetInfoPanel->fn->setPosition(ControlScreen_NetInfoPanel, 9, 32);
    ControlScreen_NetInfoPanel->fn->setSize(ControlScreen_NetInfoPanel, 285, 303);
    ControlScreen_NetInfoPanel->fn->setBackgroundType(ControlScreen_NetInfoPanel, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_DeviceDataPanelA->fn->addChild(ControlScreen_DeviceDataPanelA, (leWidget*)ControlScreen_NetInfoPanel);

    ControlScreen_NetInfString = leLabelWidget_New();
    ControlScreen_NetInfString->fn->setPosition(ControlScreen_NetInfString, 4, 6);
    ControlScreen_NetInfString->fn->setSize(ControlScreen_NetInfString, 80, 25);
    ControlScreen_NetInfString->fn->setBackgroundType(ControlScreen_NetInfString, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_NetInfString->fn->setString(ControlScreen_NetInfString, (leString*)&string_InterfaceStr);
    ControlScreen_NetInfoPanel->fn->addChild(ControlScreen_NetInfoPanel, (leWidget*)ControlScreen_NetInfString);

    ControlScreen_NetSSIDString = leLabelWidget_New();
    ControlScreen_NetSSIDString->fn->setPosition(ControlScreen_NetSSIDString, 4, 33);
    ControlScreen_NetSSIDString->fn->setSize(ControlScreen_NetSSIDString, 73, 25);
    ControlScreen_NetSSIDString->fn->setBackgroundType(ControlScreen_NetSSIDString, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_NetSSIDString->fn->setString(ControlScreen_NetSSIDString, (leString*)&string_SSIDStr);
    ControlScreen_NetInfoPanel->fn->addChild(ControlScreen_NetInfoPanel, (leWidget*)ControlScreen_NetSSIDString);

    ControlScreen_NetIPString = leLabelWidget_New();
    ControlScreen_NetIPString->fn->setPosition(ControlScreen_NetIPString, 4, 59);
    ControlScreen_NetIPString->fn->setSize(ControlScreen_NetIPString, 86, 25);
    ControlScreen_NetIPString->fn->setBackgroundType(ControlScreen_NetIPString, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_NetIPString->fn->setString(ControlScreen_NetIPString, (leString*)&string_IPAddrStr);
    ControlScreen_NetInfoPanel->fn->addChild(ControlScreen_NetInfoPanel, (leWidget*)ControlScreen_NetIPString);

    ControlScreen_NetConnString = leLabelWidget_New();
    ControlScreen_NetConnString->fn->setPosition(ControlScreen_NetConnString, 4, 86);
    ControlScreen_NetConnString->fn->setSize(ControlScreen_NetConnString, 96, 25);
    ControlScreen_NetConnString->fn->setBackgroundType(ControlScreen_NetConnString, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_NetConnString->fn->setString(ControlScreen_NetConnString, (leString*)&string_Connections);
    ControlScreen_NetInfoPanel->fn->addChild(ControlScreen_NetInfoPanel, (leWidget*)ControlScreen_NetConnString);

    ControlScreen_NetURLString = leLabelWidget_New();
    ControlScreen_NetURLString->fn->setPosition(ControlScreen_NetURLString, 4, 112);
    ControlScreen_NetURLString->fn->setSize(ControlScreen_NetURLString, 79, 25);
    ControlScreen_NetURLString->fn->setBackgroundType(ControlScreen_NetURLString, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_NetURLString->fn->setString(ControlScreen_NetURLString, (leString*)&string_NetWebURLStr);
    ControlScreen_NetInfoPanel->fn->addChild(ControlScreen_NetInfoPanel, (leWidget*)ControlScreen_NetURLString);

    ControlScreen_NetWebURLQR = leImageWidget_New();
    ControlScreen_NetWebURLQR->fn->setPosition(ControlScreen_NetWebURLQR, 63, 146);
    ControlScreen_NetWebURLQR->fn->setSize(ControlScreen_NetWebURLQR, 160, 160);
    ControlScreen_NetWebURLQR->fn->setBackgroundType(ControlScreen_NetWebURLQR, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_NetWebURLQR->fn->setBorderType(ControlScreen_NetWebURLQR, LE_WIDGET_BORDER_NONE);
    ControlScreen_NetWebURLQR->fn->setImage(ControlScreen_NetWebURLQR, (leImage*)&QRCode2);
    ControlScreen_NetInfoPanel->fn->addChild(ControlScreen_NetInfoPanel, (leWidget*)ControlScreen_NetWebURLQR);

    ControlScreen_NetInterfaceInfo = leLabelWidget_New();
    ControlScreen_NetInterfaceInfo->fn->setPosition(ControlScreen_NetInterfaceInfo, 114, 6);
    ControlScreen_NetInterfaceInfo->fn->setSize(ControlScreen_NetInterfaceInfo, 170, 25);
    ControlScreen_NetInterfaceInfo->fn->setScheme(ControlScreen_NetInterfaceInfo, &BlueScheme);
    ControlScreen_NetInterfaceInfo->fn->setBackgroundType(ControlScreen_NetInterfaceInfo, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_NetInterfaceInfo->fn->setHAlignment(ControlScreen_NetInterfaceInfo, LE_HALIGN_CENTER);
    ControlScreen_NetInterfaceInfo->fn->setString(ControlScreen_NetInterfaceInfo, (leString*)&string_IntfValueStr);
    ControlScreen_NetInfoPanel->fn->addChild(ControlScreen_NetInfoPanel, (leWidget*)ControlScreen_NetInterfaceInfo);

    ControlScreen_NetSSIDInfo = leLabelWidget_New();
    ControlScreen_NetSSIDInfo->fn->setPosition(ControlScreen_NetSSIDInfo, 114, 33);
    ControlScreen_NetSSIDInfo->fn->setSize(ControlScreen_NetSSIDInfo, 170, 25);
    ControlScreen_NetSSIDInfo->fn->setScheme(ControlScreen_NetSSIDInfo, &BlueScheme);
    ControlScreen_NetSSIDInfo->fn->setBackgroundType(ControlScreen_NetSSIDInfo, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_NetSSIDInfo->fn->setHAlignment(ControlScreen_NetSSIDInfo, LE_HALIGN_CENTER);
    ControlScreen_NetSSIDInfo->fn->setString(ControlScreen_NetSSIDInfo, (leString*)&string_SSIDValueStr);
    ControlScreen_NetInfoPanel->fn->addChild(ControlScreen_NetInfoPanel, (leWidget*)ControlScreen_NetSSIDInfo);

    ControlScreen_NetIPInfo = leLabelWidget_New();
    ControlScreen_NetIPInfo->fn->setPosition(ControlScreen_NetIPInfo, 114, 59);
    ControlScreen_NetIPInfo->fn->setSize(ControlScreen_NetIPInfo, 170, 25);
    ControlScreen_NetIPInfo->fn->setScheme(ControlScreen_NetIPInfo, &BlueScheme);
    ControlScreen_NetIPInfo->fn->setBackgroundType(ControlScreen_NetIPInfo, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_NetIPInfo->fn->setHAlignment(ControlScreen_NetIPInfo, LE_HALIGN_CENTER);
    ControlScreen_NetIPInfo->fn->setString(ControlScreen_NetIPInfo, (leString*)&string_IPAddrValueStr);
    ControlScreen_NetInfoPanel->fn->addChild(ControlScreen_NetInfoPanel, (leWidget*)ControlScreen_NetIPInfo);

    ControlScreen_NetConnInfo = leLabelWidget_New();
    ControlScreen_NetConnInfo->fn->setPosition(ControlScreen_NetConnInfo, 114, 86);
    ControlScreen_NetConnInfo->fn->setSize(ControlScreen_NetConnInfo, 170, 25);
    ControlScreen_NetConnInfo->fn->setScheme(ControlScreen_NetConnInfo, &BlueScheme);
    ControlScreen_NetConnInfo->fn->setBackgroundType(ControlScreen_NetConnInfo, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_NetConnInfo->fn->setHAlignment(ControlScreen_NetConnInfo, LE_HALIGN_CENTER);
    ControlScreen_NetConnInfo->fn->setString(ControlScreen_NetConnInfo, (leString*)&string_ZeroValueStr);
    ControlScreen_NetInfoPanel->fn->addChild(ControlScreen_NetInfoPanel, (leWidget*)ControlScreen_NetConnInfo);

    ControlScreen_NetURLInfo = leLabelWidget_New();
    ControlScreen_NetURLInfo->fn->setPosition(ControlScreen_NetURLInfo, 114, 111);
    ControlScreen_NetURLInfo->fn->setSize(ControlScreen_NetURLInfo, 170, 25);
    ControlScreen_NetURLInfo->fn->setScheme(ControlScreen_NetURLInfo, &BlueScheme);
    ControlScreen_NetURLInfo->fn->setBackgroundType(ControlScreen_NetURLInfo, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_NetURLInfo->fn->setHAlignment(ControlScreen_NetURLInfo, LE_HALIGN_CENTER);
    ControlScreen_NetURLInfo->fn->setString(ControlScreen_NetURLInfo, (leString*)&string_NetWebURLValue);
    ControlScreen_NetInfoPanel->fn->addChild(ControlScreen_NetInfoPanel, (leWidget*)ControlScreen_NetURLInfo);

    ControlScreen_LineGraphWidget_0 = leLineGraphWidget_New();
    ControlScreen_LineGraphWidget_0->fn->setPosition(ControlScreen_LineGraphWidget_0, 60, 306);
    ControlScreen_LineGraphWidget_0->fn->setSize(ControlScreen_LineGraphWidget_0, 260, 122);
    ControlScreen_LineGraphWidget_0->fn->setScheme(ControlScreen_LineGraphWidget_0, &GraphScheme);
    ControlScreen_LineGraphWidget_0->fn->setFillGraphArea(ControlScreen_LineGraphWidget_0, LE_FALSE);
    ControlScreen_LineGraphWidget_0->fn->setMinValue(ControlScreen_LineGraphWidget_0, LINE_GRAPH_AXIS_0, 10);
    ControlScreen_LineGraphWidget_0->fn->setMaxValue(ControlScreen_LineGraphWidget_0, LINE_GRAPH_AXIS_0, 60);
    ControlScreen_LineGraphWidget_0->fn->setTicksLabelFont(ControlScreen_LineGraphWidget_0, (leFont*)&Tiny);
    ControlScreen_LineGraphWidget_0->fn->setCategoryAxisLabelsVisible(ControlScreen_LineGraphWidget_0, LE_FALSE);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_LineGraphWidget_0);

    ControlScreen_BarGraphWidget_0 = leBarGraphWidget_New();
    ControlScreen_BarGraphWidget_0->fn->setPosition(ControlScreen_BarGraphWidget_0, 58, 169);
    ControlScreen_BarGraphWidget_0->fn->setSize(ControlScreen_BarGraphWidget_0, 258, 123);
    ControlScreen_BarGraphWidget_0->fn->setMaxValue(ControlScreen_BarGraphWidget_0, BAR_GRAPH_AXIS_0, 255);
    ControlScreen_BarGraphWidget_0->fn->setValueAxisTicksInterval(ControlScreen_BarGraphWidget_0, BAR_GRAPH_AXIS_0, 100);
    ControlScreen_BarGraphWidget_0->fn->setValueAxisTicksVisible(ControlScreen_BarGraphWidget_0, BAR_GRAPH_AXIS_0, LE_FALSE);
    ControlScreen_BarGraphWidget_0->fn->setValueAxisSubticksInterval(ControlScreen_BarGraphWidget_0, BAR_GRAPH_AXIS_0, BAR_GRAPH_TICK_IN);
    ControlScreen_BarGraphWidget_0->fn->setTicksLabelFont(ControlScreen_BarGraphWidget_0, (leFont*)&Tiny);
    ControlScreen_BarGraphWidget_0->fn->addCategory(ControlScreen_BarGraphWidget_0, NULL);    ControlScreen_BarGraphWidget_0->fn->setCategoryString(ControlScreen_BarGraphWidget_0, 0, (leString*)&string_DeviceA);
    ControlScreen_BarGraphWidget_0->fn->addCategory(ControlScreen_BarGraphWidget_0, NULL);    ControlScreen_BarGraphWidget_0->fn->setCategoryString(ControlScreen_BarGraphWidget_0, 1, (leString*)&string_DeviceB);
    ControlScreen_BarGraphWidget_0->fn->addCategory(ControlScreen_BarGraphWidget_0, NULL);    ControlScreen_BarGraphWidget_0->fn->setCategoryString(ControlScreen_BarGraphWidget_0, 2, (leString*)&string_DeviceC);
    ControlScreen_BarGraphWidget_0->fn->addSeries(ControlScreen_BarGraphWidget_0, NULL);
    ControlScreen_BarGraphWidget_0->fn->setSeriesScheme(ControlScreen_BarGraphWidget_0, 0, &RedScheme);
    ControlScreen_BarGraphWidget_0->fn->addDataToSeries(ControlScreen_BarGraphWidget_0, 0, 10, NULL);
    ControlScreen_BarGraphWidget_0->fn->addDataToSeries(ControlScreen_BarGraphWidget_0, 0, 10, NULL);
    ControlScreen_BarGraphWidget_0->fn->addDataToSeries(ControlScreen_BarGraphWidget_0, 0, 10, NULL);
    ControlScreen_BarGraphWidget_0->fn->addSeries(ControlScreen_BarGraphWidget_0, NULL);
    ControlScreen_BarGraphWidget_0->fn->setSeriesScheme(ControlScreen_BarGraphWidget_0, 1, &GreenScheme);
    ControlScreen_BarGraphWidget_0->fn->addDataToSeries(ControlScreen_BarGraphWidget_0, 1, 10, NULL);
    ControlScreen_BarGraphWidget_0->fn->addDataToSeries(ControlScreen_BarGraphWidget_0, 1, 10, NULL);
    ControlScreen_BarGraphWidget_0->fn->addDataToSeries(ControlScreen_BarGraphWidget_0, 1, 10, NULL);
    ControlScreen_BarGraphWidget_0->fn->addSeries(ControlScreen_BarGraphWidget_0, NULL);
    ControlScreen_BarGraphWidget_0->fn->setSeriesScheme(ControlScreen_BarGraphWidget_0, 2, &BlueScheme);
    ControlScreen_BarGraphWidget_0->fn->addDataToSeries(ControlScreen_BarGraphWidget_0, 2, 10, NULL);
    ControlScreen_BarGraphWidget_0->fn->addDataToSeries(ControlScreen_BarGraphWidget_0, 2, 10, NULL);
    ControlScreen_BarGraphWidget_0->fn->addDataToSeries(ControlScreen_BarGraphWidget_0, 2, 10, NULL);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_BarGraphWidget_0);

    ControlScreen_DeviceInfoButton = leButtonWidget_New();
    ControlScreen_DeviceInfoButton->fn->setPosition(ControlScreen_DeviceInfoButton, 73, 72);
    ControlScreen_DeviceInfoButton->fn->setSize(ControlScreen_DeviceInfoButton, 80, 60);
    ControlScreen_DeviceInfoButton->fn->setBackgroundType(ControlScreen_DeviceInfoButton, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_DeviceInfoButton->fn->setBorderType(ControlScreen_DeviceInfoButton, LE_WIDGET_BORDER_NONE);
    ControlScreen_DeviceInfoButton->fn->setVAlignment(ControlScreen_DeviceInfoButton, LE_VALIGN_TOP);
    ControlScreen_DeviceInfoButton->fn->setPressedImage(ControlScreen_DeviceInfoButton, (leImage*)&GraphTabA60);
    ControlScreen_DeviceInfoButton->fn->setReleasedImage(ControlScreen_DeviceInfoButton, (leImage*)&graphtab60);
    ControlScreen_DeviceInfoButton->fn->setPressedOffset(ControlScreen_DeviceInfoButton, 0);
    ControlScreen_DeviceInfoButton->fn->setPressedEventCallback(ControlScreen_DeviceInfoButton, event_ControlScreen_DeviceInfoButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_DeviceInfoButton);

    ControlScreen_BLEInfoButton = leButtonWidget_New();
    ControlScreen_BLEInfoButton->fn->setPosition(ControlScreen_BLEInfoButton, 150, 67);
    ControlScreen_BLEInfoButton->fn->setSize(ControlScreen_BLEInfoButton, 80, 66);
    ControlScreen_BLEInfoButton->fn->setBackgroundType(ControlScreen_BLEInfoButton, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_BLEInfoButton->fn->setBorderType(ControlScreen_BLEInfoButton, LE_WIDGET_BORDER_NONE);
    ControlScreen_BLEInfoButton->fn->setVAlignment(ControlScreen_BLEInfoButton, LE_VALIGN_TOP);
    ControlScreen_BLEInfoButton->fn->setPressedImage(ControlScreen_BLEInfoButton, (leImage*)&bleTabA60);
    ControlScreen_BLEInfoButton->fn->setReleasedImage(ControlScreen_BLEInfoButton, (leImage*)&bleTab60);
    ControlScreen_BLEInfoButton->fn->setPressedOffset(ControlScreen_BLEInfoButton, 0);
    ControlScreen_BLEInfoButton->fn->setPressedEventCallback(ControlScreen_BLEInfoButton, event_ControlScreen_BLEInfoButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_BLEInfoButton);

    ControlScreen_WiFiInfoButton = leButtonWidget_New();
    ControlScreen_WiFiInfoButton->fn->setPosition(ControlScreen_WiFiInfoButton, 228, 72);
    ControlScreen_WiFiInfoButton->fn->setSize(ControlScreen_WiFiInfoButton, 80, 60);
    ControlScreen_WiFiInfoButton->fn->setBackgroundType(ControlScreen_WiFiInfoButton, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_WiFiInfoButton->fn->setBorderType(ControlScreen_WiFiInfoButton, LE_WIDGET_BORDER_NONE);
    ControlScreen_WiFiInfoButton->fn->setVAlignment(ControlScreen_WiFiInfoButton, LE_VALIGN_TOP);
    ControlScreen_WiFiInfoButton->fn->setPressedImage(ControlScreen_WiFiInfoButton, (leImage*)&WifiTabA60);
    ControlScreen_WiFiInfoButton->fn->setReleasedImage(ControlScreen_WiFiInfoButton, (leImage*)&WifiTab60);
    ControlScreen_WiFiInfoButton->fn->setPressedOffset(ControlScreen_WiFiInfoButton, 0);
    ControlScreen_WiFiInfoButton->fn->setPressedEventCallback(ControlScreen_WiFiInfoButton, event_ControlScreen_WiFiInfoButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_WiFiInfoButton);

    ControlScreen_ColorWheelSelectColor = leWidget_New();
    ControlScreen_ColorWheelSelectColor->fn->setPosition(ControlScreen_ColorWheelSelectColor, 567, 102);
    ControlScreen_ColorWheelSelectColor->fn->setSize(ControlScreen_ColorWheelSelectColor, 86, 25);
    ControlScreen_ColorWheelSelectColor->fn->setScheme(ControlScreen_ColorWheelSelectColor, &WhiteScheme);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_ColorWheelSelectColor);

    ControlScreen_AnimImageWidget = leImageSequenceWidget_New();
    ControlScreen_AnimImageWidget->fn->setPosition(ControlScreen_AnimImageWidget, 48, 138);
    ControlScreen_AnimImageWidget->fn->setSize(ControlScreen_AnimImageWidget, 280, 280);
    ControlScreen_AnimImageWidget->fn->setBackgroundType(ControlScreen_AnimImageWidget, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_AnimImageWidget->fn->setImageCount(ControlScreen_AnimImageWidget, 1);
    ControlScreen_AnimImageWidget->fn->setImage(ControlScreen_AnimImageWidget, 0, &InfoGraphic);
    ControlScreen_AnimImageWidget->fn->setImageDelay(ControlScreen_AnimImageWidget, 0, 1000);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_AnimImageWidget);

    ControlScreen_MfgBlock = leWidget_New();
    ControlScreen_MfgBlock->fn->setPosition(ControlScreen_MfgBlock, 83, 33);
    ControlScreen_MfgBlock->fn->setSize(ControlScreen_MfgBlock, 49, 46);
    ControlScreen_MfgBlock->fn->setScheme(ControlScreen_MfgBlock, &InfoGraphicBackScheme);
    ControlScreen_AnimImageWidget->fn->addChild(ControlScreen_AnimImageWidget, (leWidget*)ControlScreen_MfgBlock);

    ControlScreen_BldgBlock = leWidget_New();
    ControlScreen_BldgBlock->fn->setPosition(ControlScreen_BldgBlock, 149, 30);
    ControlScreen_BldgBlock->fn->setSize(ControlScreen_BldgBlock, 50, 47);
    ControlScreen_BldgBlock->fn->setScheme(ControlScreen_BldgBlock, &InfoGraphicBackScheme);
    ControlScreen_AnimImageWidget->fn->addChild(ControlScreen_AnimImageWidget, (leWidget*)ControlScreen_BldgBlock);

    ControlScreen_EnergyBlock = leWidget_New();
    ControlScreen_EnergyBlock->fn->setPosition(ControlScreen_EnergyBlock, 214, 74);
    ControlScreen_EnergyBlock->fn->setSize(ControlScreen_EnergyBlock, 31, 56);
    ControlScreen_EnergyBlock->fn->setScheme(ControlScreen_EnergyBlock, &InfoGraphicBackScheme);
    ControlScreen_AnimImageWidget->fn->addChild(ControlScreen_AnimImageWidget, (leWidget*)ControlScreen_EnergyBlock);

    ControlScreen_EnvBlock = leWidget_New();
    ControlScreen_EnvBlock->fn->setPosition(ControlScreen_EnvBlock, 205, 146);
    ControlScreen_EnvBlock->fn->setSize(ControlScreen_EnvBlock, 51, 47);
    ControlScreen_EnvBlock->fn->setScheme(ControlScreen_EnvBlock, &InfoGraphicBackScheme);
    ControlScreen_AnimImageWidget->fn->addChild(ControlScreen_AnimImageWidget, (leWidget*)ControlScreen_EnvBlock);

    ControlScreen_AgriBlock = leWidget_New();
    ControlScreen_AgriBlock->fn->setPosition(ControlScreen_AgriBlock, 149, 199);
    ControlScreen_AgriBlock->fn->setSize(ControlScreen_AgriBlock, 44, 53);
    ControlScreen_AgriBlock->fn->setScheme(ControlScreen_AgriBlock, &InfoGraphicBackScheme);
    ControlScreen_AnimImageWidget->fn->addChild(ControlScreen_AnimImageWidget, (leWidget*)ControlScreen_AgriBlock);

    ControlScreen_LogiBlock = leWidget_New();
    ControlScreen_LogiBlock->fn->setPosition(ControlScreen_LogiBlock, 77, 211);
    ControlScreen_LogiBlock->fn->setSize(ControlScreen_LogiBlock, 51, 41);
    ControlScreen_LogiBlock->fn->setScheme(ControlScreen_LogiBlock, &InfoGraphicBackScheme);
    ControlScreen_AnimImageWidget->fn->addChild(ControlScreen_AnimImageWidget, (leWidget*)ControlScreen_LogiBlock);

    ControlScreen_HomeAutoBlock = leWidget_New();
    ControlScreen_HomeAutoBlock->fn->setPosition(ControlScreen_HomeAutoBlock, 26, 148);
    ControlScreen_HomeAutoBlock->fn->setSize(ControlScreen_HomeAutoBlock, 61, 43);
    ControlScreen_HomeAutoBlock->fn->setScheme(ControlScreen_HomeAutoBlock, &InfoGraphicBackScheme);
    ControlScreen_AnimImageWidget->fn->addChild(ControlScreen_AnimImageWidget, (leWidget*)ControlScreen_HomeAutoBlock);

    ControlScreen_SmartCityBlock = leWidget_New();
    ControlScreen_SmartCityBlock->fn->setPosition(ControlScreen_SmartCityBlock, 32, 79);
    ControlScreen_SmartCityBlock->fn->setSize(ControlScreen_SmartCityBlock, 41, 48);
    ControlScreen_SmartCityBlock->fn->setScheme(ControlScreen_SmartCityBlock, &InfoGraphicBackScheme);
    ControlScreen_AnimImageWidget->fn->addChild(ControlScreen_AnimImageWidget, (leWidget*)ControlScreen_SmartCityBlock);

    ControlScreen_SmartConSecLogoBlock = leWidget_New();
    ControlScreen_SmartConSecLogoBlock->fn->setPosition(ControlScreen_SmartConSecLogoBlock, 102, 89);
    ControlScreen_SmartConSecLogoBlock->fn->setSize(ControlScreen_SmartConSecLogoBlock, 75, 75);
    ControlScreen_SmartConSecLogoBlock->fn->setScheme(ControlScreen_SmartConSecLogoBlock, &InfoGraphicBackScheme);
    ControlScreen_AnimImageWidget->fn->addChild(ControlScreen_AnimImageWidget, (leWidget*)ControlScreen_SmartConSecLogoBlock);

    ControlScreen_SmartBlock = leWidget_New();
    ControlScreen_SmartBlock->fn->setPosition(ControlScreen_SmartBlock, 88, 163);
    ControlScreen_SmartBlock->fn->setSize(ControlScreen_SmartBlock, 28, 17);
    ControlScreen_SmartBlock->fn->setScheme(ControlScreen_SmartBlock, &InfoGraphicBackScheme);
    ControlScreen_AnimImageWidget->fn->addChild(ControlScreen_AnimImageWidget, (leWidget*)ControlScreen_SmartBlock);

    ControlScreen_ConnectedBlock = leWidget_New();
    ControlScreen_ConnectedBlock->fn->setPosition(ControlScreen_ConnectedBlock, 121, 164);
    ControlScreen_ConnectedBlock->fn->setSize(ControlScreen_ConnectedBlock, 37, 16);
    ControlScreen_ConnectedBlock->fn->setScheme(ControlScreen_ConnectedBlock, &InfoGraphicBackScheme);
    ControlScreen_AnimImageWidget->fn->addChild(ControlScreen_AnimImageWidget, (leWidget*)ControlScreen_ConnectedBlock);

    ControlScreen_SecureBlock = leWidget_New();
    ControlScreen_SecureBlock->fn->setPosition(ControlScreen_SecureBlock, 163, 164);
    ControlScreen_SecureBlock->fn->setSize(ControlScreen_SecureBlock, 28, 20);
    ControlScreen_SecureBlock->fn->setScheme(ControlScreen_SecureBlock, &InfoGraphicBackScheme);
    ControlScreen_AnimImageWidget->fn->addChild(ControlScreen_AnimImageWidget, (leWidget*)ControlScreen_SecureBlock);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    ControlScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_ControlScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    ControlScreen_OnUpdate(); // raise event
}

void screenHide_ControlScreen(void)
{
    ControlScreen_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    ControlScreen_PanelWidget0 = NULL;
    ControlScreen_LineWidget0 = NULL;
    ControlScreen_ImageWidget0 = NULL;
    ControlScreen_DisconnectButton = NULL;
    ControlScreen_ColorPickerImage = NULL;
    ControlScreen_DeviceCButton = NULL;
    ControlScreen_DeviceBButton = NULL;
    ControlScreen_DeviceAButton = NULL;
    ControlScreen_SliderImageWidget = NULL;
    ControlScreen_SliderControlPanel = NULL;
    ControlScreen_ScrollKnobImageWidget = NULL;
    ControlScreen_SelectedColorPanelA = NULL;
    ControlScreen_AllDevicesButton = NULL;
    ControlScreen_LabelWidget_0 = NULL;
    ControlScreen_SelectedColorPanelB = NULL;
    ControlScreen_SelectedColorPanelC = NULL;
    ControlScreen_DeviceDataPanelA = NULL;
    ControlScreen_LineGraphWidget_0 = NULL;
    ControlScreen_BarGraphWidget_0 = NULL;
    ControlScreen_DeviceInfoButton = NULL;
    ControlScreen_BLEInfoButton = NULL;
    ControlScreen_WiFiInfoButton = NULL;
    ControlScreen_ColorWheelSelectColor = NULL;
    ControlScreen_AnimImageWidget = NULL;
    ControlScreen_ImageSequenceWidgetC = NULL;
    ControlScreen_LabelWidget2 = NULL;
    ControlScreen_TempLabelC = NULL;
    ControlScreen_ImageSequenceWidgetB = NULL;
    ControlScreen_LabelWidget1 = NULL;
    ControlScreen_TempLabelB = NULL;
    ControlScreen_ImageSequenceWidgetA = NULL;
    ControlScreen_LabelWidget0 = NULL;
    ControlScreen_TempLabelA = NULL;
    ControlScreen_ColorGraphLabel = NULL;
    ControlScreen_TempSensorGraphLabel = NULL;
    ControlScreen_LineGraphLabelA = NULL;
    ControlScreen_LineGraphLabelB = NULL;
    ControlScreen_LineGraphLabelC = NULL;
    ControlScreen_DeviceInfoLabel = NULL;
    ControlScreen_BLEDeviceAName = NULL;
    ControlScreen_BLEDeviceBName = NULL;
    ControlScreen_BLEDeviceCName = NULL;
    ControlScreen_BLEDeviceAOK = NULL;
    ControlScreen_BLEDeviceBOK = NULL;
    ControlScreen_BLEDeviceCOK = NULL;
    ControlScreen_NetInfoPanel = NULL;
    ControlScreen_PanelWidget_0 = NULL;
    ControlScreen_PanelWidget_1 = NULL;
    ControlScreen_PanelWidget_2 = NULL;
    ControlScreen_NetInfString = NULL;
    ControlScreen_NetSSIDString = NULL;
    ControlScreen_NetIPString = NULL;
    ControlScreen_NetConnString = NULL;
    ControlScreen_NetURLString = NULL;
    ControlScreen_NetWebURLQR = NULL;
    ControlScreen_NetInterfaceInfo = NULL;
    ControlScreen_NetSSIDInfo = NULL;
    ControlScreen_NetIPInfo = NULL;
    ControlScreen_NetConnInfo = NULL;
    ControlScreen_NetURLInfo = NULL;
    ControlScreen_MfgBlock = NULL;
    ControlScreen_BldgBlock = NULL;
    ControlScreen_EnergyBlock = NULL;
    ControlScreen_EnvBlock = NULL;
    ControlScreen_AgriBlock = NULL;
    ControlScreen_LogiBlock = NULL;
    ControlScreen_HomeAutoBlock = NULL;
    ControlScreen_SmartCityBlock = NULL;
    ControlScreen_SmartConSecLogoBlock = NULL;
    ControlScreen_SmartBlock = NULL;
    ControlScreen_ConnectedBlock = NULL;
    ControlScreen_SecureBlock = NULL;


    showing = LE_FALSE;
}

void screenDestroy_ControlScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_ControlScreen(uint32_t lyrIdx)
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

