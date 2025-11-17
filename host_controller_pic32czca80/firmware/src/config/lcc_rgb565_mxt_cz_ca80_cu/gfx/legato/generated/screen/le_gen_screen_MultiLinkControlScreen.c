#include "gfx/legato/generated/screen/le_gen_screen_MultiLinkControlScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* MultiLinkControlScreen_PanelWidget0;
leLineWidget* MultiLinkControlScreen_LineWidget0;
leImageWidget* MultiLinkControlScreen_ImageWidget0;
leButtonWidget* MultiLinkControlScreen_DisconnectButton;
leImageWidget* MultiLinkControlScreen_ColorPickerImage;
leButtonWidget* MultiLinkControlScreen_DeviceCButton;
leButtonWidget* MultiLinkControlScreen_DeviceBButton;
leButtonWidget* MultiLinkControlScreen_DeviceAButton;
leImageWidget* MultiLinkControlScreen_SliderImageWidget;
leWidget* MultiLinkControlScreen_SliderControlPanel;
leImageWidget* MultiLinkControlScreen_ScrollKnobImageWidget;
leWidget* MultiLinkControlScreen_SelectedColorPanelA;
leButtonWidget* MultiLinkControlScreen_AllDevicesButton;
leLabelWidget* MultiLinkControlScreen_LabelWidget_0;
leWidget* MultiLinkControlScreen_SelectedColorPanelB;
leWidget* MultiLinkControlScreen_SelectedColorPanelC;
leWidget* MultiLinkControlScreen_DeviceDataPanelA;
leLineGraphWidget* MultiLinkControlScreen_LineGraphWidget_0;
leBarGraphWidget* MultiLinkControlScreen_BarGraphWidget_0;
leButtonWidget* MultiLinkControlScreen_DeviceInfoButton;
leButtonWidget* MultiLinkControlScreen_BLEInfoButton;
leButtonWidget* MultiLinkControlScreen_WiFiInfoButton;
leWidget* MultiLinkControlScreen_ColorWheelSelectColor;
leImageSequenceWidget* MultiLinkControlScreen_AnimImageWidget;
leImageSequenceWidget* MultiLinkControlScreen_ImageSequenceWidgetC;
leLabelWidget* MultiLinkControlScreen_LabelWidget2;
leLabelWidget* MultiLinkControlScreen_TempLabelC;
leImageSequenceWidget* MultiLinkControlScreen_ImageSequenceWidgetB;
leLabelWidget* MultiLinkControlScreen_LabelWidget1;
leLabelWidget* MultiLinkControlScreen_TempLabelB;
leImageSequenceWidget* MultiLinkControlScreen_ImageSequenceWidgetA;
leLabelWidget* MultiLinkControlScreen_LabelWidget0;
leLabelWidget* MultiLinkControlScreen_TempLabelA;
leLabelWidget* MultiLinkControlScreen_ColorGraphLabel;
leLabelWidget* MultiLinkControlScreen_TempSensorGraphLabel;
leLabelWidget* MultiLinkControlScreen_LineGraphLabelA;
leLabelWidget* MultiLinkControlScreen_LineGraphLabelB;
leLabelWidget* MultiLinkControlScreen_LineGraphLabelC;
leLabelWidget* MultiLinkControlScreen_DeviceInfoLabel;
leLabelWidget* MultiLinkControlScreen_BLEDeviceAName;
leLabelWidget* MultiLinkControlScreen_BLEDeviceBName;
leLabelWidget* MultiLinkControlScreen_BLEDeviceCName;
leImageWidget* MultiLinkControlScreen_BLEDeviceAOK;
leImageWidget* MultiLinkControlScreen_BLEDeviceBOK;
leImageWidget* MultiLinkControlScreen_BLEDeviceCOK;
leWidget* MultiLinkControlScreen_NetInfoPanel;
leWidget* MultiLinkControlScreen_PanelWidget_0;
leWidget* MultiLinkControlScreen_PanelWidget_1;
leWidget* MultiLinkControlScreen_PanelWidget_2;
leLabelWidget* MultiLinkControlScreen_NetInfString;
leLabelWidget* MultiLinkControlScreen_NetSSIDString;
leLabelWidget* MultiLinkControlScreen_NetIPString;
leLabelWidget* MultiLinkControlScreen_NetConnString;
leLabelWidget* MultiLinkControlScreen_NetURLString;
leImageWidget* MultiLinkControlScreen_NetWebURLQR;
leLabelWidget* MultiLinkControlScreen_NetInterfaceInfo;
leLabelWidget* MultiLinkControlScreen_NetSSIDInfo;
leLabelWidget* MultiLinkControlScreen_NetIPInfo;
leLabelWidget* MultiLinkControlScreen_NetConnInfo;
leLabelWidget* MultiLinkControlScreen_NetURLInfo;
leWidget* MultiLinkControlScreen_MfgBlock;
leWidget* MultiLinkControlScreen_BldgBlock;
leWidget* MultiLinkControlScreen_EnergyBlock;
leWidget* MultiLinkControlScreen_EnvBlock;
leWidget* MultiLinkControlScreen_AgriBlock;
leWidget* MultiLinkControlScreen_LogiBlock;
leWidget* MultiLinkControlScreen_HomeAutoBlock;
leWidget* MultiLinkControlScreen_SmartCityBlock;
leWidget* MultiLinkControlScreen_SmartConSecLogoBlock;
leWidget* MultiLinkControlScreen_SmartBlock;
leWidget* MultiLinkControlScreen_ConnectedBlock;
leWidget* MultiLinkControlScreen_SecureBlock;

static leBool initialized = LE_FALSE;
static leBool showing = LE_FALSE;

leResult screenInit_MultiLinkControlScreen(void)
{
    if(initialized == LE_TRUE)
        return LE_FAILURE;

    initialized = LE_TRUE;

    return LE_SUCCESS;
}

leResult screenShow_MultiLinkControlScreen(void)
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

    MultiLinkControlScreen_PanelWidget0 = leWidget_New();
    MultiLinkControlScreen_PanelWidget0->fn->setPosition(MultiLinkControlScreen_PanelWidget0, 0, 0);
    MultiLinkControlScreen_PanelWidget0->fn->setSize(MultiLinkControlScreen_PanelWidget0, 800, 480);
    MultiLinkControlScreen_PanelWidget0->fn->setScheme(MultiLinkControlScreen_PanelWidget0, &BackScheme);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_PanelWidget0);

    MultiLinkControlScreen_LineWidget0 = leLineWidget_New();
    MultiLinkControlScreen_LineWidget0->fn->setPosition(MultiLinkControlScreen_LineWidget0, 97, 25);
    MultiLinkControlScreen_LineWidget0->fn->setSize(MultiLinkControlScreen_LineWidget0, 700, 15);
    MultiLinkControlScreen_LineWidget0->fn->setScheme(MultiLinkControlScreen_LineWidget0, &WhiteScheme);
    MultiLinkControlScreen_LineWidget0->fn->setBackgroundType(MultiLinkControlScreen_LineWidget0, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_LineWidget0->fn->setStartPoint(MultiLinkControlScreen_LineWidget0, 0, 5);
    MultiLinkControlScreen_LineWidget0->fn->setEndPoint(MultiLinkControlScreen_LineWidget0, 700, 5);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_LineWidget0);

    MultiLinkControlScreen_ImageWidget0 = leImageWidget_New();
    MultiLinkControlScreen_ImageWidget0->fn->setPosition(MultiLinkControlScreen_ImageWidget0, 10, 10);
    MultiLinkControlScreen_ImageWidget0->fn->setSize(MultiLinkControlScreen_ImageWidget0, 100, 40);
    MultiLinkControlScreen_ImageWidget0->fn->setBackgroundType(MultiLinkControlScreen_ImageWidget0, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_ImageWidget0->fn->setBorderType(MultiLinkControlScreen_ImageWidget0, LE_WIDGET_BORDER_NONE);
    MultiLinkControlScreen_ImageWidget0->fn->setImage(MultiLinkControlScreen_ImageWidget0, (leImage*)&MchpLogo_100);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_ImageWidget0);

    MultiLinkControlScreen_DisconnectButton = leButtonWidget_New();
    MultiLinkControlScreen_DisconnectButton->fn->setPosition(MultiLinkControlScreen_DisconnectButton, 732, 418);
    MultiLinkControlScreen_DisconnectButton->fn->setSize(MultiLinkControlScreen_DisconnectButton, 60, 50);
    MultiLinkControlScreen_DisconnectButton->fn->setScheme(MultiLinkControlScreen_DisconnectButton, &TextInactiveScheme);
    MultiLinkControlScreen_DisconnectButton->fn->setBorderType(MultiLinkControlScreen_DisconnectButton, LE_WIDGET_BORDER_NONE);
    MultiLinkControlScreen_DisconnectButton->fn->setString(MultiLinkControlScreen_DisconnectButton, (leString*)&string_DisconnectString);
    MultiLinkControlScreen_DisconnectButton->fn->setPressedImage(MultiLinkControlScreen_DisconnectButton, (leImage*)&Disconnect20);
    MultiLinkControlScreen_DisconnectButton->fn->setReleasedImage(MultiLinkControlScreen_DisconnectButton, (leImage*)&Disconnect20);
    MultiLinkControlScreen_DisconnectButton->fn->setImagePosition(MultiLinkControlScreen_DisconnectButton, LE_RELATIVE_POSITION_ABOVE);
    MultiLinkControlScreen_DisconnectButton->fn->setImageMargin(MultiLinkControlScreen_DisconnectButton, 5);
    MultiLinkControlScreen_DisconnectButton->fn->setPressedEventCallback(MultiLinkControlScreen_DisconnectButton, event_MultiLinkControlScreen_DisconnectButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_DisconnectButton);

    MultiLinkControlScreen_ColorPickerImage = leImageWidget_New();
    MultiLinkControlScreen_ColorPickerImage->fn->setPosition(MultiLinkControlScreen_ColorPickerImage, 514, 173);
    MultiLinkControlScreen_ColorPickerImage->fn->setSize(MultiLinkControlScreen_ColorPickerImage, 200, 200);
    MultiLinkControlScreen_ColorPickerImage->fn->setBackgroundType(MultiLinkControlScreen_ColorPickerImage, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_ColorPickerImage->fn->setBorderType(MultiLinkControlScreen_ColorPickerImage, LE_WIDGET_BORDER_NONE);
    MultiLinkControlScreen_ColorPickerImage->fn->setMargins(MultiLinkControlScreen_ColorPickerImage, 0, 0, 0, 0);
    MultiLinkControlScreen_ColorPickerImage->fn->setImage(MultiLinkControlScreen_ColorPickerImage, (leImage*)&ColorPickerBlueBack200_565);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_ColorPickerImage);

    MultiLinkControlScreen_DeviceCButton = leButtonWidget_New();
    MultiLinkControlScreen_DeviceCButton->fn->setPosition(MultiLinkControlScreen_DeviceCButton, 440, 360);
    MultiLinkControlScreen_DeviceCButton->fn->setSize(MultiLinkControlScreen_DeviceCButton, 65, 65);
    MultiLinkControlScreen_DeviceCButton->fn->setBackgroundType(MultiLinkControlScreen_DeviceCButton, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_DeviceCButton->fn->setBorderType(MultiLinkControlScreen_DeviceCButton, LE_WIDGET_BORDER_NONE);
    MultiLinkControlScreen_DeviceCButton->fn->setPressedOffset(MultiLinkControlScreen_DeviceCButton, 0);
    MultiLinkControlScreen_DeviceCButton->fn->setPressedEventCallback(MultiLinkControlScreen_DeviceCButton, event_MultiLinkControlScreen_DeviceCButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_DeviceCButton);

    MultiLinkControlScreen_ImageSequenceWidgetC = leImageSequenceWidget_New();
    MultiLinkControlScreen_ImageSequenceWidgetC->fn->setPosition(MultiLinkControlScreen_ImageSequenceWidgetC, 0, 0);
    MultiLinkControlScreen_ImageSequenceWidgetC->fn->setSize(MultiLinkControlScreen_ImageSequenceWidgetC, 65, 65);
    MultiLinkControlScreen_ImageSequenceWidgetC->fn->setEnabled(MultiLinkControlScreen_ImageSequenceWidgetC, LE_FALSE);
    MultiLinkControlScreen_ImageSequenceWidgetC->fn->setBackgroundType(MultiLinkControlScreen_ImageSequenceWidgetC, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_ImageSequenceWidgetC->fn->setImageCount(MultiLinkControlScreen_ImageSequenceWidgetC, 2);
    MultiLinkControlScreen_ImageSequenceWidgetC->fn->setImage(MultiLinkControlScreen_ImageSequenceWidgetC, 0, &DeviceSelect60);
    MultiLinkControlScreen_ImageSequenceWidgetC->fn->setImageDelay(MultiLinkControlScreen_ImageSequenceWidgetC, 0, 1000);
    MultiLinkControlScreen_ImageSequenceWidgetC->fn->setImage(MultiLinkControlScreen_ImageSequenceWidgetC, 1, &DeviceNoSelect60);
    MultiLinkControlScreen_ImageSequenceWidgetC->fn->setImageDelay(MultiLinkControlScreen_ImageSequenceWidgetC, 1, 1000);
    MultiLinkControlScreen_DeviceCButton->fn->addChild(MultiLinkControlScreen_DeviceCButton, (leWidget*)MultiLinkControlScreen_ImageSequenceWidgetC);

    MultiLinkControlScreen_LabelWidget2 = leLabelWidget_New();
    MultiLinkControlScreen_LabelWidget2->fn->setPosition(MultiLinkControlScreen_LabelWidget2, -2, -1);
    MultiLinkControlScreen_LabelWidget2->fn->setSize(MultiLinkControlScreen_LabelWidget2, 25, 25);
    MultiLinkControlScreen_LabelWidget2->fn->setEnabled(MultiLinkControlScreen_LabelWidget2, LE_FALSE);
    MultiLinkControlScreen_LabelWidget2->fn->setScheme(MultiLinkControlScreen_LabelWidget2, &TextScheme);
    MultiLinkControlScreen_LabelWidget2->fn->setBackgroundType(MultiLinkControlScreen_LabelWidget2, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_LabelWidget2->fn->setHAlignment(MultiLinkControlScreen_LabelWidget2, LE_HALIGN_CENTER);
    MultiLinkControlScreen_LabelWidget2->fn->setString(MultiLinkControlScreen_LabelWidget2, (leString*)&string_DeviceC);
    MultiLinkControlScreen_DeviceCButton->fn->addChild(MultiLinkControlScreen_DeviceCButton, (leWidget*)MultiLinkControlScreen_LabelWidget2);

    MultiLinkControlScreen_TempLabelC = leLabelWidget_New();
    MultiLinkControlScreen_TempLabelC->fn->setPosition(MultiLinkControlScreen_TempLabelC, 5, 18);
    MultiLinkControlScreen_TempLabelC->fn->setSize(MultiLinkControlScreen_TempLabelC, 55, 30);
    MultiLinkControlScreen_TempLabelC->fn->setScheme(MultiLinkControlScreen_TempLabelC, &TextScheme);
    MultiLinkControlScreen_TempLabelC->fn->setBackgroundType(MultiLinkControlScreen_TempLabelC, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_TempLabelC->fn->setHAlignment(MultiLinkControlScreen_TempLabelC, LE_HALIGN_CENTER);
    MultiLinkControlScreen_TempLabelC->fn->setString(MultiLinkControlScreen_TempLabelC, (leString*)&string_DefaultTemp);
    MultiLinkControlScreen_DeviceCButton->fn->addChild(MultiLinkControlScreen_DeviceCButton, (leWidget*)MultiLinkControlScreen_TempLabelC);

    MultiLinkControlScreen_DeviceBButton = leButtonWidget_New();
    MultiLinkControlScreen_DeviceBButton->fn->setPosition(MultiLinkControlScreen_DeviceBButton, 370, 240);
    MultiLinkControlScreen_DeviceBButton->fn->setSize(MultiLinkControlScreen_DeviceBButton, 65, 65);
    MultiLinkControlScreen_DeviceBButton->fn->setBackgroundType(MultiLinkControlScreen_DeviceBButton, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_DeviceBButton->fn->setBorderType(MultiLinkControlScreen_DeviceBButton, LE_WIDGET_BORDER_NONE);
    MultiLinkControlScreen_DeviceBButton->fn->setPressedOffset(MultiLinkControlScreen_DeviceBButton, 0);
    MultiLinkControlScreen_DeviceBButton->fn->setPressedEventCallback(MultiLinkControlScreen_DeviceBButton, event_MultiLinkControlScreen_DeviceBButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_DeviceBButton);

    MultiLinkControlScreen_ImageSequenceWidgetB = leImageSequenceWidget_New();
    MultiLinkControlScreen_ImageSequenceWidgetB->fn->setPosition(MultiLinkControlScreen_ImageSequenceWidgetB, 0, 0);
    MultiLinkControlScreen_ImageSequenceWidgetB->fn->setSize(MultiLinkControlScreen_ImageSequenceWidgetB, 65, 65);
    MultiLinkControlScreen_ImageSequenceWidgetB->fn->setEnabled(MultiLinkControlScreen_ImageSequenceWidgetB, LE_FALSE);
    MultiLinkControlScreen_ImageSequenceWidgetB->fn->setBackgroundType(MultiLinkControlScreen_ImageSequenceWidgetB, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_ImageSequenceWidgetB->fn->setImageCount(MultiLinkControlScreen_ImageSequenceWidgetB, 2);
    MultiLinkControlScreen_ImageSequenceWidgetB->fn->setImage(MultiLinkControlScreen_ImageSequenceWidgetB, 0, &DeviceSelect60);
    MultiLinkControlScreen_ImageSequenceWidgetB->fn->setImageDelay(MultiLinkControlScreen_ImageSequenceWidgetB, 0, 1000);
    MultiLinkControlScreen_ImageSequenceWidgetB->fn->setImage(MultiLinkControlScreen_ImageSequenceWidgetB, 1, &DeviceNoSelect60);
    MultiLinkControlScreen_ImageSequenceWidgetB->fn->setImageDelay(MultiLinkControlScreen_ImageSequenceWidgetB, 1, 1000);
    MultiLinkControlScreen_DeviceBButton->fn->addChild(MultiLinkControlScreen_DeviceBButton, (leWidget*)MultiLinkControlScreen_ImageSequenceWidgetB);

    MultiLinkControlScreen_LabelWidget1 = leLabelWidget_New();
    MultiLinkControlScreen_LabelWidget1->fn->setPosition(MultiLinkControlScreen_LabelWidget1, -1, -2);
    MultiLinkControlScreen_LabelWidget1->fn->setSize(MultiLinkControlScreen_LabelWidget1, 25, 25);
    MultiLinkControlScreen_LabelWidget1->fn->setEnabled(MultiLinkControlScreen_LabelWidget1, LE_FALSE);
    MultiLinkControlScreen_LabelWidget1->fn->setScheme(MultiLinkControlScreen_LabelWidget1, &TextScheme);
    MultiLinkControlScreen_LabelWidget1->fn->setBackgroundType(MultiLinkControlScreen_LabelWidget1, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_LabelWidget1->fn->setHAlignment(MultiLinkControlScreen_LabelWidget1, LE_HALIGN_CENTER);
    MultiLinkControlScreen_LabelWidget1->fn->setString(MultiLinkControlScreen_LabelWidget1, (leString*)&string_DeviceB);
    MultiLinkControlScreen_DeviceBButton->fn->addChild(MultiLinkControlScreen_DeviceBButton, (leWidget*)MultiLinkControlScreen_LabelWidget1);

    MultiLinkControlScreen_TempLabelB = leLabelWidget_New();
    MultiLinkControlScreen_TempLabelB->fn->setPosition(MultiLinkControlScreen_TempLabelB, 5, 18);
    MultiLinkControlScreen_TempLabelB->fn->setSize(MultiLinkControlScreen_TempLabelB, 55, 30);
    MultiLinkControlScreen_TempLabelB->fn->setScheme(MultiLinkControlScreen_TempLabelB, &TextScheme);
    MultiLinkControlScreen_TempLabelB->fn->setBackgroundType(MultiLinkControlScreen_TempLabelB, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_TempLabelB->fn->setHAlignment(MultiLinkControlScreen_TempLabelB, LE_HALIGN_CENTER);
    MultiLinkControlScreen_TempLabelB->fn->setString(MultiLinkControlScreen_TempLabelB, (leString*)&string_DefaultTemp);
    MultiLinkControlScreen_DeviceBButton->fn->addChild(MultiLinkControlScreen_DeviceBButton, (leWidget*)MultiLinkControlScreen_TempLabelB);

    MultiLinkControlScreen_DeviceAButton = leButtonWidget_New();
    MultiLinkControlScreen_DeviceAButton->fn->setPosition(MultiLinkControlScreen_DeviceAButton, 440, 120);
    MultiLinkControlScreen_DeviceAButton->fn->setSize(MultiLinkControlScreen_DeviceAButton, 65, 65);
    MultiLinkControlScreen_DeviceAButton->fn->setBackgroundType(MultiLinkControlScreen_DeviceAButton, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_DeviceAButton->fn->setBorderType(MultiLinkControlScreen_DeviceAButton, LE_WIDGET_BORDER_NONE);
    MultiLinkControlScreen_DeviceAButton->fn->setPressedOffset(MultiLinkControlScreen_DeviceAButton, 0);
    MultiLinkControlScreen_DeviceAButton->fn->setPressedEventCallback(MultiLinkControlScreen_DeviceAButton, event_MultiLinkControlScreen_DeviceAButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_DeviceAButton);

    MultiLinkControlScreen_ImageSequenceWidgetA = leImageSequenceWidget_New();
    MultiLinkControlScreen_ImageSequenceWidgetA->fn->setPosition(MultiLinkControlScreen_ImageSequenceWidgetA, 0, 0);
    MultiLinkControlScreen_ImageSequenceWidgetA->fn->setSize(MultiLinkControlScreen_ImageSequenceWidgetA, 65, 65);
    MultiLinkControlScreen_ImageSequenceWidgetA->fn->setEnabled(MultiLinkControlScreen_ImageSequenceWidgetA, LE_FALSE);
    MultiLinkControlScreen_ImageSequenceWidgetA->fn->setBackgroundType(MultiLinkControlScreen_ImageSequenceWidgetA, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_ImageSequenceWidgetA->fn->setImageCount(MultiLinkControlScreen_ImageSequenceWidgetA, 2);
    MultiLinkControlScreen_ImageSequenceWidgetA->fn->setImage(MultiLinkControlScreen_ImageSequenceWidgetA, 0, &DeviceSelect60);
    MultiLinkControlScreen_ImageSequenceWidgetA->fn->setImageDelay(MultiLinkControlScreen_ImageSequenceWidgetA, 0, 1000);
    MultiLinkControlScreen_ImageSequenceWidgetA->fn->setImage(MultiLinkControlScreen_ImageSequenceWidgetA, 1, &DeviceNoSelect60);
    MultiLinkControlScreen_ImageSequenceWidgetA->fn->setImageDelay(MultiLinkControlScreen_ImageSequenceWidgetA, 1, 1000);
    MultiLinkControlScreen_DeviceAButton->fn->addChild(MultiLinkControlScreen_DeviceAButton, (leWidget*)MultiLinkControlScreen_ImageSequenceWidgetA);

    MultiLinkControlScreen_LabelWidget0 = leLabelWidget_New();
    MultiLinkControlScreen_LabelWidget0->fn->setPosition(MultiLinkControlScreen_LabelWidget0, -1, -2);
    MultiLinkControlScreen_LabelWidget0->fn->setSize(MultiLinkControlScreen_LabelWidget0, 25, 25);
    MultiLinkControlScreen_LabelWidget0->fn->setEnabled(MultiLinkControlScreen_LabelWidget0, LE_FALSE);
    MultiLinkControlScreen_LabelWidget0->fn->setScheme(MultiLinkControlScreen_LabelWidget0, &TextScheme);
    MultiLinkControlScreen_LabelWidget0->fn->setBackgroundType(MultiLinkControlScreen_LabelWidget0, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_LabelWidget0->fn->setHAlignment(MultiLinkControlScreen_LabelWidget0, LE_HALIGN_CENTER);
    MultiLinkControlScreen_LabelWidget0->fn->setString(MultiLinkControlScreen_LabelWidget0, (leString*)&string_DeviceA);
    MultiLinkControlScreen_DeviceAButton->fn->addChild(MultiLinkControlScreen_DeviceAButton, (leWidget*)MultiLinkControlScreen_LabelWidget0);

    MultiLinkControlScreen_TempLabelA = leLabelWidget_New();
    MultiLinkControlScreen_TempLabelA->fn->setPosition(MultiLinkControlScreen_TempLabelA, 5, 18);
    MultiLinkControlScreen_TempLabelA->fn->setSize(MultiLinkControlScreen_TempLabelA, 55, 30);
    MultiLinkControlScreen_TempLabelA->fn->setScheme(MultiLinkControlScreen_TempLabelA, &WhiteScheme);
    MultiLinkControlScreen_TempLabelA->fn->setBackgroundType(MultiLinkControlScreen_TempLabelA, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_TempLabelA->fn->setHAlignment(MultiLinkControlScreen_TempLabelA, LE_HALIGN_CENTER);
    MultiLinkControlScreen_TempLabelA->fn->setString(MultiLinkControlScreen_TempLabelA, (leString*)&string_DefaultTemp);
    MultiLinkControlScreen_DeviceAButton->fn->addChild(MultiLinkControlScreen_DeviceAButton, (leWidget*)MultiLinkControlScreen_TempLabelA);

    MultiLinkControlScreen_SliderImageWidget = leImageWidget_New();
    MultiLinkControlScreen_SliderImageWidget->fn->setPosition(MultiLinkControlScreen_SliderImageWidget, 730, 150);
    MultiLinkControlScreen_SliderImageWidget->fn->setSize(MultiLinkControlScreen_SliderImageWidget, 60, 250);
    MultiLinkControlScreen_SliderImageWidget->fn->setBackgroundType(MultiLinkControlScreen_SliderImageWidget, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_SliderImageWidget->fn->setBorderType(MultiLinkControlScreen_SliderImageWidget, LE_WIDGET_BORDER_NONE);
    MultiLinkControlScreen_SliderImageWidget->fn->setImage(MultiLinkControlScreen_SliderImageWidget, (leImage*)&Slider50);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_SliderImageWidget);

    MultiLinkControlScreen_SliderControlPanel = leWidget_New();
    MultiLinkControlScreen_SliderControlPanel->fn->setPosition(MultiLinkControlScreen_SliderControlPanel, 726, 205);
    MultiLinkControlScreen_SliderControlPanel->fn->setSize(MultiLinkControlScreen_SliderControlPanel, 67, 147);
    MultiLinkControlScreen_SliderControlPanel->fn->setBackgroundType(MultiLinkControlScreen_SliderControlPanel, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_SliderControlPanel);

    MultiLinkControlScreen_ScrollKnobImageWidget = leImageWidget_New();
    MultiLinkControlScreen_ScrollKnobImageWidget->fn->setPosition(MultiLinkControlScreen_ScrollKnobImageWidget, 745, 261);
    MultiLinkControlScreen_ScrollKnobImageWidget->fn->setSize(MultiLinkControlScreen_ScrollKnobImageWidget, 30, 30);
    MultiLinkControlScreen_ScrollKnobImageWidget->fn->setEnabled(MultiLinkControlScreen_ScrollKnobImageWidget, LE_FALSE);
    MultiLinkControlScreen_ScrollKnobImageWidget->fn->setBackgroundType(MultiLinkControlScreen_ScrollKnobImageWidget, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_ScrollKnobImageWidget->fn->setBorderType(MultiLinkControlScreen_ScrollKnobImageWidget, LE_WIDGET_BORDER_NONE);
    MultiLinkControlScreen_ScrollKnobImageWidget->fn->setImage(MultiLinkControlScreen_ScrollKnobImageWidget, (leImage*)&Knob30);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_ScrollKnobImageWidget);

    MultiLinkControlScreen_SelectedColorPanelA = leWidget_New();
    MultiLinkControlScreen_SelectedColorPanelA->fn->setPosition(MultiLinkControlScreen_SelectedColorPanelA, 510, 144);
    MultiLinkControlScreen_SelectedColorPanelA->fn->setSize(MultiLinkControlScreen_SelectedColorPanelA, 20, 20);
    MultiLinkControlScreen_SelectedColorPanelA->fn->setScheme(MultiLinkControlScreen_SelectedColorPanelA, &BlueScheme);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_SelectedColorPanelA);

    MultiLinkControlScreen_AllDevicesButton = leButtonWidget_New();
    MultiLinkControlScreen_AllDevicesButton->fn->setPosition(MultiLinkControlScreen_AllDevicesButton, 585, 391);
    MultiLinkControlScreen_AllDevicesButton->fn->setSize(MultiLinkControlScreen_AllDevicesButton, 60, 60);
    MultiLinkControlScreen_AllDevicesButton->fn->setScheme(MultiLinkControlScreen_AllDevicesButton, &TextScheme);
    MultiLinkControlScreen_AllDevicesButton->fn->setBorderType(MultiLinkControlScreen_AllDevicesButton, LE_WIDGET_BORDER_NONE);
    MultiLinkControlScreen_AllDevicesButton->fn->setToggleable(MultiLinkControlScreen_AllDevicesButton, LE_TRUE);
    MultiLinkControlScreen_AllDevicesButton->fn->setString(MultiLinkControlScreen_AllDevicesButton, (leString*)&string_AllString);
    MultiLinkControlScreen_AllDevicesButton->fn->setPressedImage(MultiLinkControlScreen_AllDevicesButton, (leImage*)&DeviceNoSelect40);
    MultiLinkControlScreen_AllDevicesButton->fn->setReleasedImage(MultiLinkControlScreen_AllDevicesButton, (leImage*)&DeviceSelect40Bulb);
    MultiLinkControlScreen_AllDevicesButton->fn->setImagePosition(MultiLinkControlScreen_AllDevicesButton, LE_RELATIVE_POSITION_BEHIND);
    MultiLinkControlScreen_AllDevicesButton->fn->setPressedOffset(MultiLinkControlScreen_AllDevicesButton, 0);
    MultiLinkControlScreen_AllDevicesButton->fn->setPressedEventCallback(MultiLinkControlScreen_AllDevicesButton, event_MultiLinkControlScreen_AllDevicesButton_OnPressed);
    MultiLinkControlScreen_AllDevicesButton->fn->setReleasedEventCallback(MultiLinkControlScreen_AllDevicesButton, event_MultiLinkControlScreen_AllDevicesButton_OnReleased);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_AllDevicesButton);

    MultiLinkControlScreen_LabelWidget_0 = leLabelWidget_New();
    MultiLinkControlScreen_LabelWidget_0->fn->setPosition(MultiLinkControlScreen_LabelWidget_0, 410, 2);
    MultiLinkControlScreen_LabelWidget_0->fn->setSize(MultiLinkControlScreen_LabelWidget_0, 380, 25);
    MultiLinkControlScreen_LabelWidget_0->fn->setScheme(MultiLinkControlScreen_LabelWidget_0, &TextScheme);
    MultiLinkControlScreen_LabelWidget_0->fn->setHAlignment(MultiLinkControlScreen_LabelWidget_0, LE_HALIGN_CENTER);
    MultiLinkControlScreen_LabelWidget_0->fn->setString(MultiLinkControlScreen_LabelWidget_0, (leString*)&string_DemoName);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_LabelWidget_0);

    MultiLinkControlScreen_SelectedColorPanelB = leWidget_New();
    MultiLinkControlScreen_SelectedColorPanelB->fn->setPosition(MultiLinkControlScreen_SelectedColorPanelB, 439, 264);
    MultiLinkControlScreen_SelectedColorPanelB->fn->setSize(MultiLinkControlScreen_SelectedColorPanelB, 20, 20);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_SelectedColorPanelB);

    MultiLinkControlScreen_SelectedColorPanelC = leWidget_New();
    MultiLinkControlScreen_SelectedColorPanelC->fn->setPosition(MultiLinkControlScreen_SelectedColorPanelC, 511, 388);
    MultiLinkControlScreen_SelectedColorPanelC->fn->setSize(MultiLinkControlScreen_SelectedColorPanelC, 20, 20);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_SelectedColorPanelC);

    MultiLinkControlScreen_DeviceDataPanelA = leWidget_New();
    MultiLinkControlScreen_DeviceDataPanelA->fn->setPosition(MultiLinkControlScreen_DeviceDataPanelA, 37, 114);
    MultiLinkControlScreen_DeviceDataPanelA->fn->setSize(MultiLinkControlScreen_DeviceDataPanelA, 300, 340);
    MultiLinkControlScreen_DeviceDataPanelA->fn->setScheme(MultiLinkControlScreen_DeviceDataPanelA, &WhiteScheme);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_DeviceDataPanelA);

    MultiLinkControlScreen_ColorGraphLabel = leLabelWidget_New();
    MultiLinkControlScreen_ColorGraphLabel->fn->setPosition(MultiLinkControlScreen_ColorGraphLabel, 90, 49);
    MultiLinkControlScreen_ColorGraphLabel->fn->setSize(MultiLinkControlScreen_ColorGraphLabel, 123, 19);
    MultiLinkControlScreen_ColorGraphLabel->fn->setScheme(MultiLinkControlScreen_ColorGraphLabel, &BackScheme);
    MultiLinkControlScreen_ColorGraphLabel->fn->setBackgroundType(MultiLinkControlScreen_ColorGraphLabel, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_ColorGraphLabel->fn->setHAlignment(MultiLinkControlScreen_ColorGraphLabel, LE_HALIGN_CENTER);
    MultiLinkControlScreen_ColorGraphLabel->fn->setString(MultiLinkControlScreen_ColorGraphLabel, (leString*)&string_ColorChannels);
    MultiLinkControlScreen_DeviceDataPanelA->fn->addChild(MultiLinkControlScreen_DeviceDataPanelA, (leWidget*)MultiLinkControlScreen_ColorGraphLabel);

    MultiLinkControlScreen_TempSensorGraphLabel = leLabelWidget_New();
    MultiLinkControlScreen_TempSensorGraphLabel->fn->setPosition(MultiLinkControlScreen_TempSensorGraphLabel, 71, 181);
    MultiLinkControlScreen_TempSensorGraphLabel->fn->setSize(MultiLinkControlScreen_TempSensorGraphLabel, 170, 25);
    MultiLinkControlScreen_TempSensorGraphLabel->fn->setScheme(MultiLinkControlScreen_TempSensorGraphLabel, &BackScheme);
    MultiLinkControlScreen_TempSensorGraphLabel->fn->setBackgroundType(MultiLinkControlScreen_TempSensorGraphLabel, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_TempSensorGraphLabel->fn->setHAlignment(MultiLinkControlScreen_TempSensorGraphLabel, LE_HALIGN_CENTER);
    MultiLinkControlScreen_TempSensorGraphLabel->fn->setString(MultiLinkControlScreen_TempSensorGraphLabel, (leString*)&string_TempSensor);
    MultiLinkControlScreen_DeviceDataPanelA->fn->addChild(MultiLinkControlScreen_DeviceDataPanelA, (leWidget*)MultiLinkControlScreen_TempSensorGraphLabel);

    MultiLinkControlScreen_LineGraphLabelA = leLabelWidget_New();
    MultiLinkControlScreen_LineGraphLabelA->fn->setPosition(MultiLinkControlScreen_LineGraphLabelA, 66, 314);
    MultiLinkControlScreen_LineGraphLabelA->fn->setSize(MultiLinkControlScreen_LineGraphLabelA, 40, 25);
    MultiLinkControlScreen_LineGraphLabelA->fn->setBackgroundType(MultiLinkControlScreen_LineGraphLabelA, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_LineGraphLabelA->fn->setHAlignment(MultiLinkControlScreen_LineGraphLabelA, LE_HALIGN_RIGHT);
    MultiLinkControlScreen_LineGraphLabelA->fn->setString(MultiLinkControlScreen_LineGraphLabelA, (leString*)&string_DeviceA);
    MultiLinkControlScreen_DeviceDataPanelA->fn->addChild(MultiLinkControlScreen_DeviceDataPanelA, (leWidget*)MultiLinkControlScreen_LineGraphLabelA);

    MultiLinkControlScreen_PanelWidget_0 = leWidget_New();
    MultiLinkControlScreen_PanelWidget_0->fn->setPosition(MultiLinkControlScreen_PanelWidget_0, 10, 8);
    MultiLinkControlScreen_PanelWidget_0->fn->setSize(MultiLinkControlScreen_PanelWidget_0, 10, 10);
    MultiLinkControlScreen_PanelWidget_0->fn->setScheme(MultiLinkControlScreen_PanelWidget_0, &RedScheme);
    MultiLinkControlScreen_LineGraphLabelA->fn->addChild(MultiLinkControlScreen_LineGraphLabelA, (leWidget*)MultiLinkControlScreen_PanelWidget_0);

    MultiLinkControlScreen_LineGraphLabelB = leLabelWidget_New();
    MultiLinkControlScreen_LineGraphLabelB->fn->setPosition(MultiLinkControlScreen_LineGraphLabelB, 129, 314);
    MultiLinkControlScreen_LineGraphLabelB->fn->setSize(MultiLinkControlScreen_LineGraphLabelB, 40, 25);
    MultiLinkControlScreen_LineGraphLabelB->fn->setBackgroundType(MultiLinkControlScreen_LineGraphLabelB, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_LineGraphLabelB->fn->setHAlignment(MultiLinkControlScreen_LineGraphLabelB, LE_HALIGN_RIGHT);
    MultiLinkControlScreen_LineGraphLabelB->fn->setString(MultiLinkControlScreen_LineGraphLabelB, (leString*)&string_DeviceB);
    MultiLinkControlScreen_DeviceDataPanelA->fn->addChild(MultiLinkControlScreen_DeviceDataPanelA, (leWidget*)MultiLinkControlScreen_LineGraphLabelB);

    MultiLinkControlScreen_PanelWidget_1 = leWidget_New();
    MultiLinkControlScreen_PanelWidget_1->fn->setPosition(MultiLinkControlScreen_PanelWidget_1, 9, 8);
    MultiLinkControlScreen_PanelWidget_1->fn->setSize(MultiLinkControlScreen_PanelWidget_1, 10, 10);
    MultiLinkControlScreen_PanelWidget_1->fn->setScheme(MultiLinkControlScreen_PanelWidget_1, &GreenScheme);
    MultiLinkControlScreen_LineGraphLabelB->fn->addChild(MultiLinkControlScreen_LineGraphLabelB, (leWidget*)MultiLinkControlScreen_PanelWidget_1);

    MultiLinkControlScreen_LineGraphLabelC = leLabelWidget_New();
    MultiLinkControlScreen_LineGraphLabelC->fn->setPosition(MultiLinkControlScreen_LineGraphLabelC, 192, 314);
    MultiLinkControlScreen_LineGraphLabelC->fn->setSize(MultiLinkControlScreen_LineGraphLabelC, 40, 25);
    MultiLinkControlScreen_LineGraphLabelC->fn->setBackgroundType(MultiLinkControlScreen_LineGraphLabelC, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_LineGraphLabelC->fn->setHAlignment(MultiLinkControlScreen_LineGraphLabelC, LE_HALIGN_RIGHT);
    MultiLinkControlScreen_LineGraphLabelC->fn->setString(MultiLinkControlScreen_LineGraphLabelC, (leString*)&string_DeviceC);
    MultiLinkControlScreen_DeviceDataPanelA->fn->addChild(MultiLinkControlScreen_DeviceDataPanelA, (leWidget*)MultiLinkControlScreen_LineGraphLabelC);

    MultiLinkControlScreen_PanelWidget_2 = leWidget_New();
    MultiLinkControlScreen_PanelWidget_2->fn->setPosition(MultiLinkControlScreen_PanelWidget_2, 9, 8);
    MultiLinkControlScreen_PanelWidget_2->fn->setSize(MultiLinkControlScreen_PanelWidget_2, 10, 10);
    MultiLinkControlScreen_PanelWidget_2->fn->setScheme(MultiLinkControlScreen_PanelWidget_2, &BlueScheme);
    MultiLinkControlScreen_LineGraphLabelC->fn->addChild(MultiLinkControlScreen_LineGraphLabelC, (leWidget*)MultiLinkControlScreen_PanelWidget_2);

    MultiLinkControlScreen_DeviceInfoLabel = leLabelWidget_New();
    MultiLinkControlScreen_DeviceInfoLabel->fn->setPosition(MultiLinkControlScreen_DeviceInfoLabel, 4, 4);
    MultiLinkControlScreen_DeviceInfoLabel->fn->setSize(MultiLinkControlScreen_DeviceInfoLabel, 294, 25);
    MultiLinkControlScreen_DeviceInfoLabel->fn->setScheme(MultiLinkControlScreen_DeviceInfoLabel, &BackScheme);
    MultiLinkControlScreen_DeviceInfoLabel->fn->setBackgroundType(MultiLinkControlScreen_DeviceInfoLabel, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_DeviceInfoLabel->fn->setHAlignment(MultiLinkControlScreen_DeviceInfoLabel, LE_HALIGN_CENTER);
    MultiLinkControlScreen_DeviceInfoLabel->fn->setString(MultiLinkControlScreen_DeviceInfoLabel, (leString*)&string_WiFiDeviceInfo);
    MultiLinkControlScreen_DeviceDataPanelA->fn->addChild(MultiLinkControlScreen_DeviceDataPanelA, (leWidget*)MultiLinkControlScreen_DeviceInfoLabel);

    MultiLinkControlScreen_BLEDeviceAName = leLabelWidget_New();
    MultiLinkControlScreen_BLEDeviceAName->fn->setPosition(MultiLinkControlScreen_BLEDeviceAName, 48, 56);
    MultiLinkControlScreen_BLEDeviceAName->fn->setSize(MultiLinkControlScreen_BLEDeviceAName, 200, 30);
    MultiLinkControlScreen_BLEDeviceAName->fn->setScheme(MultiLinkControlScreen_BLEDeviceAName, &BLEPanelScheme);
    MultiLinkControlScreen_BLEDeviceAName->fn->setBackgroundType(MultiLinkControlScreen_BLEDeviceAName, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_BLEDeviceAName->fn->setString(MultiLinkControlScreen_BLEDeviceAName, (leString*)&string_BLEDeviceInfo);
    MultiLinkControlScreen_DeviceDataPanelA->fn->addChild(MultiLinkControlScreen_DeviceDataPanelA, (leWidget*)MultiLinkControlScreen_BLEDeviceAName);

    MultiLinkControlScreen_BLEDeviceBName = leLabelWidget_New();
    MultiLinkControlScreen_BLEDeviceBName->fn->setPosition(MultiLinkControlScreen_BLEDeviceBName, 48, 96);
    MultiLinkControlScreen_BLEDeviceBName->fn->setSize(MultiLinkControlScreen_BLEDeviceBName, 200, 30);
    MultiLinkControlScreen_BLEDeviceBName->fn->setScheme(MultiLinkControlScreen_BLEDeviceBName, &BLEPanelScheme);
    MultiLinkControlScreen_BLEDeviceBName->fn->setBackgroundType(MultiLinkControlScreen_BLEDeviceBName, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_BLEDeviceBName->fn->setString(MultiLinkControlScreen_BLEDeviceBName, (leString*)&string_BLEDeviceInfo);
    MultiLinkControlScreen_DeviceDataPanelA->fn->addChild(MultiLinkControlScreen_DeviceDataPanelA, (leWidget*)MultiLinkControlScreen_BLEDeviceBName);

    MultiLinkControlScreen_BLEDeviceCName = leLabelWidget_New();
    MultiLinkControlScreen_BLEDeviceCName->fn->setPosition(MultiLinkControlScreen_BLEDeviceCName, 48, 136);
    MultiLinkControlScreen_BLEDeviceCName->fn->setSize(MultiLinkControlScreen_BLEDeviceCName, 200, 30);
    MultiLinkControlScreen_BLEDeviceCName->fn->setBackgroundType(MultiLinkControlScreen_BLEDeviceCName, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_BLEDeviceCName->fn->setString(MultiLinkControlScreen_BLEDeviceCName, (leString*)&string_BLEDeviceInfo);
    MultiLinkControlScreen_DeviceDataPanelA->fn->addChild(MultiLinkControlScreen_DeviceDataPanelA, (leWidget*)MultiLinkControlScreen_BLEDeviceCName);

    MultiLinkControlScreen_BLEDeviceAOK = leImageWidget_New();
    MultiLinkControlScreen_BLEDeviceAOK->fn->setPosition(MultiLinkControlScreen_BLEDeviceAOK, 12, 63);
    MultiLinkControlScreen_BLEDeviceAOK->fn->setSize(MultiLinkControlScreen_BLEDeviceAOK, 35, 25);
    MultiLinkControlScreen_BLEDeviceAOK->fn->setBackgroundType(MultiLinkControlScreen_BLEDeviceAOK, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_BLEDeviceAOK->fn->setBorderType(MultiLinkControlScreen_BLEDeviceAOK, LE_WIDGET_BORDER_NONE);
    MultiLinkControlScreen_BLEDeviceAOK->fn->setImage(MultiLinkControlScreen_BLEDeviceAOK, (leImage*)&Check30);
    MultiLinkControlScreen_DeviceDataPanelA->fn->addChild(MultiLinkControlScreen_DeviceDataPanelA, (leWidget*)MultiLinkControlScreen_BLEDeviceAOK);

    MultiLinkControlScreen_BLEDeviceBOK = leImageWidget_New();
    MultiLinkControlScreen_BLEDeviceBOK->fn->setPosition(MultiLinkControlScreen_BLEDeviceBOK, 12, 101);
    MultiLinkControlScreen_BLEDeviceBOK->fn->setSize(MultiLinkControlScreen_BLEDeviceBOK, 35, 25);
    MultiLinkControlScreen_BLEDeviceBOK->fn->setBackgroundType(MultiLinkControlScreen_BLEDeviceBOK, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_BLEDeviceBOK->fn->setBorderType(MultiLinkControlScreen_BLEDeviceBOK, LE_WIDGET_BORDER_NONE);
    MultiLinkControlScreen_BLEDeviceBOK->fn->setImage(MultiLinkControlScreen_BLEDeviceBOK, (leImage*)&Check30);
    MultiLinkControlScreen_DeviceDataPanelA->fn->addChild(MultiLinkControlScreen_DeviceDataPanelA, (leWidget*)MultiLinkControlScreen_BLEDeviceBOK);

    MultiLinkControlScreen_BLEDeviceCOK = leImageWidget_New();
    MultiLinkControlScreen_BLEDeviceCOK->fn->setPosition(MultiLinkControlScreen_BLEDeviceCOK, 12, 141);
    MultiLinkControlScreen_BLEDeviceCOK->fn->setSize(MultiLinkControlScreen_BLEDeviceCOK, 35, 25);
    MultiLinkControlScreen_BLEDeviceCOK->fn->setBackgroundType(MultiLinkControlScreen_BLEDeviceCOK, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_BLEDeviceCOK->fn->setBorderType(MultiLinkControlScreen_BLEDeviceCOK, LE_WIDGET_BORDER_NONE);
    MultiLinkControlScreen_BLEDeviceCOK->fn->setImage(MultiLinkControlScreen_BLEDeviceCOK, (leImage*)&Check30);
    MultiLinkControlScreen_DeviceDataPanelA->fn->addChild(MultiLinkControlScreen_DeviceDataPanelA, (leWidget*)MultiLinkControlScreen_BLEDeviceCOK);

    MultiLinkControlScreen_NetInfoPanel = leWidget_New();
    MultiLinkControlScreen_NetInfoPanel->fn->setPosition(MultiLinkControlScreen_NetInfoPanel, 9, 32);
    MultiLinkControlScreen_NetInfoPanel->fn->setSize(MultiLinkControlScreen_NetInfoPanel, 285, 303);
    MultiLinkControlScreen_NetInfoPanel->fn->setBackgroundType(MultiLinkControlScreen_NetInfoPanel, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_DeviceDataPanelA->fn->addChild(MultiLinkControlScreen_DeviceDataPanelA, (leWidget*)MultiLinkControlScreen_NetInfoPanel);

    MultiLinkControlScreen_NetInfString = leLabelWidget_New();
    MultiLinkControlScreen_NetInfString->fn->setPosition(MultiLinkControlScreen_NetInfString, 4, 6);
    MultiLinkControlScreen_NetInfString->fn->setSize(MultiLinkControlScreen_NetInfString, 80, 25);
    MultiLinkControlScreen_NetInfString->fn->setBackgroundType(MultiLinkControlScreen_NetInfString, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_NetInfString->fn->setString(MultiLinkControlScreen_NetInfString, (leString*)&string_InterfaceStr);
    MultiLinkControlScreen_NetInfoPanel->fn->addChild(MultiLinkControlScreen_NetInfoPanel, (leWidget*)MultiLinkControlScreen_NetInfString);

    MultiLinkControlScreen_NetSSIDString = leLabelWidget_New();
    MultiLinkControlScreen_NetSSIDString->fn->setPosition(MultiLinkControlScreen_NetSSIDString, 4, 33);
    MultiLinkControlScreen_NetSSIDString->fn->setSize(MultiLinkControlScreen_NetSSIDString, 73, 25);
    MultiLinkControlScreen_NetSSIDString->fn->setBackgroundType(MultiLinkControlScreen_NetSSIDString, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_NetSSIDString->fn->setString(MultiLinkControlScreen_NetSSIDString, (leString*)&string_SSIDStr);
    MultiLinkControlScreen_NetInfoPanel->fn->addChild(MultiLinkControlScreen_NetInfoPanel, (leWidget*)MultiLinkControlScreen_NetSSIDString);

    MultiLinkControlScreen_NetIPString = leLabelWidget_New();
    MultiLinkControlScreen_NetIPString->fn->setPosition(MultiLinkControlScreen_NetIPString, 4, 59);
    MultiLinkControlScreen_NetIPString->fn->setSize(MultiLinkControlScreen_NetIPString, 86, 25);
    MultiLinkControlScreen_NetIPString->fn->setBackgroundType(MultiLinkControlScreen_NetIPString, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_NetIPString->fn->setString(MultiLinkControlScreen_NetIPString, (leString*)&string_IPAddrStr);
    MultiLinkControlScreen_NetInfoPanel->fn->addChild(MultiLinkControlScreen_NetInfoPanel, (leWidget*)MultiLinkControlScreen_NetIPString);

    MultiLinkControlScreen_NetConnString = leLabelWidget_New();
    MultiLinkControlScreen_NetConnString->fn->setPosition(MultiLinkControlScreen_NetConnString, 4, 86);
    MultiLinkControlScreen_NetConnString->fn->setSize(MultiLinkControlScreen_NetConnString, 96, 25);
    MultiLinkControlScreen_NetConnString->fn->setBackgroundType(MultiLinkControlScreen_NetConnString, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_NetConnString->fn->setString(MultiLinkControlScreen_NetConnString, (leString*)&string_Connections);
    MultiLinkControlScreen_NetInfoPanel->fn->addChild(MultiLinkControlScreen_NetInfoPanel, (leWidget*)MultiLinkControlScreen_NetConnString);

    MultiLinkControlScreen_NetURLString = leLabelWidget_New();
    MultiLinkControlScreen_NetURLString->fn->setPosition(MultiLinkControlScreen_NetURLString, 4, 112);
    MultiLinkControlScreen_NetURLString->fn->setSize(MultiLinkControlScreen_NetURLString, 79, 25);
    MultiLinkControlScreen_NetURLString->fn->setBackgroundType(MultiLinkControlScreen_NetURLString, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_NetURLString->fn->setString(MultiLinkControlScreen_NetURLString, (leString*)&string_NetWebURLStr);
    MultiLinkControlScreen_NetInfoPanel->fn->addChild(MultiLinkControlScreen_NetInfoPanel, (leWidget*)MultiLinkControlScreen_NetURLString);

    MultiLinkControlScreen_NetWebURLQR = leImageWidget_New();
    MultiLinkControlScreen_NetWebURLQR->fn->setPosition(MultiLinkControlScreen_NetWebURLQR, 63, 146);
    MultiLinkControlScreen_NetWebURLQR->fn->setSize(MultiLinkControlScreen_NetWebURLQR, 160, 160);
    MultiLinkControlScreen_NetWebURLQR->fn->setBackgroundType(MultiLinkControlScreen_NetWebURLQR, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_NetWebURLQR->fn->setBorderType(MultiLinkControlScreen_NetWebURLQR, LE_WIDGET_BORDER_NONE);
    MultiLinkControlScreen_NetWebURLQR->fn->setImage(MultiLinkControlScreen_NetWebURLQR, (leImage*)&QRCode2);
    MultiLinkControlScreen_NetInfoPanel->fn->addChild(MultiLinkControlScreen_NetInfoPanel, (leWidget*)MultiLinkControlScreen_NetWebURLQR);

    MultiLinkControlScreen_NetInterfaceInfo = leLabelWidget_New();
    MultiLinkControlScreen_NetInterfaceInfo->fn->setPosition(MultiLinkControlScreen_NetInterfaceInfo, 114, 6);
    MultiLinkControlScreen_NetInterfaceInfo->fn->setSize(MultiLinkControlScreen_NetInterfaceInfo, 170, 25);
    MultiLinkControlScreen_NetInterfaceInfo->fn->setScheme(MultiLinkControlScreen_NetInterfaceInfo, &BlueScheme);
    MultiLinkControlScreen_NetInterfaceInfo->fn->setBackgroundType(MultiLinkControlScreen_NetInterfaceInfo, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_NetInterfaceInfo->fn->setHAlignment(MultiLinkControlScreen_NetInterfaceInfo, LE_HALIGN_CENTER);
    MultiLinkControlScreen_NetInterfaceInfo->fn->setString(MultiLinkControlScreen_NetInterfaceInfo, (leString*)&string_IntfValueStr);
    MultiLinkControlScreen_NetInfoPanel->fn->addChild(MultiLinkControlScreen_NetInfoPanel, (leWidget*)MultiLinkControlScreen_NetInterfaceInfo);

    MultiLinkControlScreen_NetSSIDInfo = leLabelWidget_New();
    MultiLinkControlScreen_NetSSIDInfo->fn->setPosition(MultiLinkControlScreen_NetSSIDInfo, 114, 33);
    MultiLinkControlScreen_NetSSIDInfo->fn->setSize(MultiLinkControlScreen_NetSSIDInfo, 170, 25);
    MultiLinkControlScreen_NetSSIDInfo->fn->setScheme(MultiLinkControlScreen_NetSSIDInfo, &BlueScheme);
    MultiLinkControlScreen_NetSSIDInfo->fn->setBackgroundType(MultiLinkControlScreen_NetSSIDInfo, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_NetSSIDInfo->fn->setHAlignment(MultiLinkControlScreen_NetSSIDInfo, LE_HALIGN_CENTER);
    MultiLinkControlScreen_NetSSIDInfo->fn->setString(MultiLinkControlScreen_NetSSIDInfo, (leString*)&string_SSIDValueStr);
    MultiLinkControlScreen_NetInfoPanel->fn->addChild(MultiLinkControlScreen_NetInfoPanel, (leWidget*)MultiLinkControlScreen_NetSSIDInfo);

    MultiLinkControlScreen_NetIPInfo = leLabelWidget_New();
    MultiLinkControlScreen_NetIPInfo->fn->setPosition(MultiLinkControlScreen_NetIPInfo, 114, 59);
    MultiLinkControlScreen_NetIPInfo->fn->setSize(MultiLinkControlScreen_NetIPInfo, 170, 25);
    MultiLinkControlScreen_NetIPInfo->fn->setScheme(MultiLinkControlScreen_NetIPInfo, &BlueScheme);
    MultiLinkControlScreen_NetIPInfo->fn->setBackgroundType(MultiLinkControlScreen_NetIPInfo, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_NetIPInfo->fn->setHAlignment(MultiLinkControlScreen_NetIPInfo, LE_HALIGN_CENTER);
    MultiLinkControlScreen_NetIPInfo->fn->setString(MultiLinkControlScreen_NetIPInfo, (leString*)&string_IPAddrValueStr);
    MultiLinkControlScreen_NetInfoPanel->fn->addChild(MultiLinkControlScreen_NetInfoPanel, (leWidget*)MultiLinkControlScreen_NetIPInfo);

    MultiLinkControlScreen_NetConnInfo = leLabelWidget_New();
    MultiLinkControlScreen_NetConnInfo->fn->setPosition(MultiLinkControlScreen_NetConnInfo, 114, 86);
    MultiLinkControlScreen_NetConnInfo->fn->setSize(MultiLinkControlScreen_NetConnInfo, 170, 25);
    MultiLinkControlScreen_NetConnInfo->fn->setScheme(MultiLinkControlScreen_NetConnInfo, &BlueScheme);
    MultiLinkControlScreen_NetConnInfo->fn->setBackgroundType(MultiLinkControlScreen_NetConnInfo, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_NetConnInfo->fn->setHAlignment(MultiLinkControlScreen_NetConnInfo, LE_HALIGN_CENTER);
    MultiLinkControlScreen_NetConnInfo->fn->setString(MultiLinkControlScreen_NetConnInfo, (leString*)&string_ZeroValueStr);
    MultiLinkControlScreen_NetInfoPanel->fn->addChild(MultiLinkControlScreen_NetInfoPanel, (leWidget*)MultiLinkControlScreen_NetConnInfo);

    MultiLinkControlScreen_NetURLInfo = leLabelWidget_New();
    MultiLinkControlScreen_NetURLInfo->fn->setPosition(MultiLinkControlScreen_NetURLInfo, 114, 111);
    MultiLinkControlScreen_NetURLInfo->fn->setSize(MultiLinkControlScreen_NetURLInfo, 170, 25);
    MultiLinkControlScreen_NetURLInfo->fn->setScheme(MultiLinkControlScreen_NetURLInfo, &BlueScheme);
    MultiLinkControlScreen_NetURLInfo->fn->setBackgroundType(MultiLinkControlScreen_NetURLInfo, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_NetURLInfo->fn->setHAlignment(MultiLinkControlScreen_NetURLInfo, LE_HALIGN_CENTER);
    MultiLinkControlScreen_NetURLInfo->fn->setString(MultiLinkControlScreen_NetURLInfo, (leString*)&string_NetWebURLValue);
    MultiLinkControlScreen_NetInfoPanel->fn->addChild(MultiLinkControlScreen_NetInfoPanel, (leWidget*)MultiLinkControlScreen_NetURLInfo);

    MultiLinkControlScreen_LineGraphWidget_0 = leLineGraphWidget_New();
    MultiLinkControlScreen_LineGraphWidget_0->fn->setPosition(MultiLinkControlScreen_LineGraphWidget_0, 60, 306);
    MultiLinkControlScreen_LineGraphWidget_0->fn->setSize(MultiLinkControlScreen_LineGraphWidget_0, 260, 122);
    MultiLinkControlScreen_LineGraphWidget_0->fn->setScheme(MultiLinkControlScreen_LineGraphWidget_0, &GraphScheme);
    MultiLinkControlScreen_LineGraphWidget_0->fn->setFillGraphArea(MultiLinkControlScreen_LineGraphWidget_0, LE_FALSE);
    MultiLinkControlScreen_LineGraphWidget_0->fn->setMinValue(MultiLinkControlScreen_LineGraphWidget_0, LINE_GRAPH_AXIS_0, 10);
    MultiLinkControlScreen_LineGraphWidget_0->fn->setMaxValue(MultiLinkControlScreen_LineGraphWidget_0, LINE_GRAPH_AXIS_0, 60);
    MultiLinkControlScreen_LineGraphWidget_0->fn->setTicksLabelFont(MultiLinkControlScreen_LineGraphWidget_0, (leFont*)&Tiny);
    MultiLinkControlScreen_LineGraphWidget_0->fn->setCategoryAxisLabelsVisible(MultiLinkControlScreen_LineGraphWidget_0, LE_FALSE);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_LineGraphWidget_0);

    MultiLinkControlScreen_BarGraphWidget_0 = leBarGraphWidget_New();
    MultiLinkControlScreen_BarGraphWidget_0->fn->setPosition(MultiLinkControlScreen_BarGraphWidget_0, 58, 169);
    MultiLinkControlScreen_BarGraphWidget_0->fn->setSize(MultiLinkControlScreen_BarGraphWidget_0, 258, 123);
    MultiLinkControlScreen_BarGraphWidget_0->fn->setMaxValue(MultiLinkControlScreen_BarGraphWidget_0, BAR_GRAPH_AXIS_0, 255);
    MultiLinkControlScreen_BarGraphWidget_0->fn->setValueAxisTicksInterval(MultiLinkControlScreen_BarGraphWidget_0, BAR_GRAPH_AXIS_0, 100);
    MultiLinkControlScreen_BarGraphWidget_0->fn->setValueAxisTicksVisible(MultiLinkControlScreen_BarGraphWidget_0, BAR_GRAPH_AXIS_0, LE_FALSE);
    MultiLinkControlScreen_BarGraphWidget_0->fn->setValueAxisSubticksInterval(MultiLinkControlScreen_BarGraphWidget_0, BAR_GRAPH_AXIS_0, BAR_GRAPH_TICK_IN);
    MultiLinkControlScreen_BarGraphWidget_0->fn->setTicksLabelFont(MultiLinkControlScreen_BarGraphWidget_0, (leFont*)&Tiny);
    MultiLinkControlScreen_BarGraphWidget_0->fn->addCategory(MultiLinkControlScreen_BarGraphWidget_0, NULL);    MultiLinkControlScreen_BarGraphWidget_0->fn->setCategoryString(MultiLinkControlScreen_BarGraphWidget_0, 0, (leString*)&string_DeviceA);
    MultiLinkControlScreen_BarGraphWidget_0->fn->addCategory(MultiLinkControlScreen_BarGraphWidget_0, NULL);    MultiLinkControlScreen_BarGraphWidget_0->fn->setCategoryString(MultiLinkControlScreen_BarGraphWidget_0, 1, (leString*)&string_DeviceB);
    MultiLinkControlScreen_BarGraphWidget_0->fn->addCategory(MultiLinkControlScreen_BarGraphWidget_0, NULL);    MultiLinkControlScreen_BarGraphWidget_0->fn->setCategoryString(MultiLinkControlScreen_BarGraphWidget_0, 2, (leString*)&string_DeviceC);
    MultiLinkControlScreen_BarGraphWidget_0->fn->addSeries(MultiLinkControlScreen_BarGraphWidget_0, NULL);
    MultiLinkControlScreen_BarGraphWidget_0->fn->setSeriesScheme(MultiLinkControlScreen_BarGraphWidget_0, 0, &RedScheme);
    MultiLinkControlScreen_BarGraphWidget_0->fn->addDataToSeries(MultiLinkControlScreen_BarGraphWidget_0, 0, 10, NULL);
    MultiLinkControlScreen_BarGraphWidget_0->fn->addDataToSeries(MultiLinkControlScreen_BarGraphWidget_0, 0, 10, NULL);
    MultiLinkControlScreen_BarGraphWidget_0->fn->addDataToSeries(MultiLinkControlScreen_BarGraphWidget_0, 0, 10, NULL);
    MultiLinkControlScreen_BarGraphWidget_0->fn->addSeries(MultiLinkControlScreen_BarGraphWidget_0, NULL);
    MultiLinkControlScreen_BarGraphWidget_0->fn->setSeriesScheme(MultiLinkControlScreen_BarGraphWidget_0, 1, &GreenScheme);
    MultiLinkControlScreen_BarGraphWidget_0->fn->addDataToSeries(MultiLinkControlScreen_BarGraphWidget_0, 1, 10, NULL);
    MultiLinkControlScreen_BarGraphWidget_0->fn->addDataToSeries(MultiLinkControlScreen_BarGraphWidget_0, 1, 10, NULL);
    MultiLinkControlScreen_BarGraphWidget_0->fn->addDataToSeries(MultiLinkControlScreen_BarGraphWidget_0, 1, 10, NULL);
    MultiLinkControlScreen_BarGraphWidget_0->fn->addSeries(MultiLinkControlScreen_BarGraphWidget_0, NULL);
    MultiLinkControlScreen_BarGraphWidget_0->fn->setSeriesScheme(MultiLinkControlScreen_BarGraphWidget_0, 2, &BlueScheme);
    MultiLinkControlScreen_BarGraphWidget_0->fn->addDataToSeries(MultiLinkControlScreen_BarGraphWidget_0, 2, 10, NULL);
    MultiLinkControlScreen_BarGraphWidget_0->fn->addDataToSeries(MultiLinkControlScreen_BarGraphWidget_0, 2, 10, NULL);
    MultiLinkControlScreen_BarGraphWidget_0->fn->addDataToSeries(MultiLinkControlScreen_BarGraphWidget_0, 2, 10, NULL);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_BarGraphWidget_0);

    MultiLinkControlScreen_DeviceInfoButton = leButtonWidget_New();
    MultiLinkControlScreen_DeviceInfoButton->fn->setPosition(MultiLinkControlScreen_DeviceInfoButton, 69, 54);
    MultiLinkControlScreen_DeviceInfoButton->fn->setSize(MultiLinkControlScreen_DeviceInfoButton, 80, 60);
    MultiLinkControlScreen_DeviceInfoButton->fn->setBackgroundType(MultiLinkControlScreen_DeviceInfoButton, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_DeviceInfoButton->fn->setBorderType(MultiLinkControlScreen_DeviceInfoButton, LE_WIDGET_BORDER_NONE);
    MultiLinkControlScreen_DeviceInfoButton->fn->setVAlignment(MultiLinkControlScreen_DeviceInfoButton, LE_VALIGN_TOP);
    MultiLinkControlScreen_DeviceInfoButton->fn->setPressedImage(MultiLinkControlScreen_DeviceInfoButton, (leImage*)&GraphTabA60);
    MultiLinkControlScreen_DeviceInfoButton->fn->setReleasedImage(MultiLinkControlScreen_DeviceInfoButton, (leImage*)&graphtab60);
    MultiLinkControlScreen_DeviceInfoButton->fn->setPressedOffset(MultiLinkControlScreen_DeviceInfoButton, 0);
    MultiLinkControlScreen_DeviceInfoButton->fn->setPressedEventCallback(MultiLinkControlScreen_DeviceInfoButton, event_MultiLinkControlScreen_DeviceInfoButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_DeviceInfoButton);

    MultiLinkControlScreen_BLEInfoButton = leButtonWidget_New();
    MultiLinkControlScreen_BLEInfoButton->fn->setPosition(MultiLinkControlScreen_BLEInfoButton, 146, 49);
    MultiLinkControlScreen_BLEInfoButton->fn->setSize(MultiLinkControlScreen_BLEInfoButton, 80, 66);
    MultiLinkControlScreen_BLEInfoButton->fn->setBackgroundType(MultiLinkControlScreen_BLEInfoButton, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_BLEInfoButton->fn->setBorderType(MultiLinkControlScreen_BLEInfoButton, LE_WIDGET_BORDER_NONE);
    MultiLinkControlScreen_BLEInfoButton->fn->setVAlignment(MultiLinkControlScreen_BLEInfoButton, LE_VALIGN_TOP);
    MultiLinkControlScreen_BLEInfoButton->fn->setPressedImage(MultiLinkControlScreen_BLEInfoButton, (leImage*)&bleTabA60);
    MultiLinkControlScreen_BLEInfoButton->fn->setReleasedImage(MultiLinkControlScreen_BLEInfoButton, (leImage*)&bleTab60);
    MultiLinkControlScreen_BLEInfoButton->fn->setPressedOffset(MultiLinkControlScreen_BLEInfoButton, 0);
    MultiLinkControlScreen_BLEInfoButton->fn->setPressedEventCallback(MultiLinkControlScreen_BLEInfoButton, event_MultiLinkControlScreen_BLEInfoButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_BLEInfoButton);

    MultiLinkControlScreen_WiFiInfoButton = leButtonWidget_New();
    MultiLinkControlScreen_WiFiInfoButton->fn->setPosition(MultiLinkControlScreen_WiFiInfoButton, 224, 54);
    MultiLinkControlScreen_WiFiInfoButton->fn->setSize(MultiLinkControlScreen_WiFiInfoButton, 80, 60);
    MultiLinkControlScreen_WiFiInfoButton->fn->setBackgroundType(MultiLinkControlScreen_WiFiInfoButton, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_WiFiInfoButton->fn->setBorderType(MultiLinkControlScreen_WiFiInfoButton, LE_WIDGET_BORDER_NONE);
    MultiLinkControlScreen_WiFiInfoButton->fn->setVAlignment(MultiLinkControlScreen_WiFiInfoButton, LE_VALIGN_TOP);
    MultiLinkControlScreen_WiFiInfoButton->fn->setPressedImage(MultiLinkControlScreen_WiFiInfoButton, (leImage*)&WifiTabA60);
    MultiLinkControlScreen_WiFiInfoButton->fn->setReleasedImage(MultiLinkControlScreen_WiFiInfoButton, (leImage*)&WifiTab60);
    MultiLinkControlScreen_WiFiInfoButton->fn->setPressedOffset(MultiLinkControlScreen_WiFiInfoButton, 0);
    MultiLinkControlScreen_WiFiInfoButton->fn->setPressedEventCallback(MultiLinkControlScreen_WiFiInfoButton, event_MultiLinkControlScreen_WiFiInfoButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_WiFiInfoButton);

    MultiLinkControlScreen_ColorWheelSelectColor = leWidget_New();
    MultiLinkControlScreen_ColorWheelSelectColor->fn->setPosition(MultiLinkControlScreen_ColorWheelSelectColor, 567, 102);
    MultiLinkControlScreen_ColorWheelSelectColor->fn->setSize(MultiLinkControlScreen_ColorWheelSelectColor, 86, 25);
    MultiLinkControlScreen_ColorWheelSelectColor->fn->setScheme(MultiLinkControlScreen_ColorWheelSelectColor, &WhiteScheme);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_ColorWheelSelectColor);

    MultiLinkControlScreen_AnimImageWidget = leImageSequenceWidget_New();
    MultiLinkControlScreen_AnimImageWidget->fn->setPosition(MultiLinkControlScreen_AnimImageWidget, 48, 138);
    MultiLinkControlScreen_AnimImageWidget->fn->setSize(MultiLinkControlScreen_AnimImageWidget, 280, 280);
    MultiLinkControlScreen_AnimImageWidget->fn->setBackgroundType(MultiLinkControlScreen_AnimImageWidget, LE_WIDGET_BACKGROUND_NONE);
    MultiLinkControlScreen_AnimImageWidget->fn->setImageCount(MultiLinkControlScreen_AnimImageWidget, 1);
    MultiLinkControlScreen_AnimImageWidget->fn->setImage(MultiLinkControlScreen_AnimImageWidget, 0, &InfoGraphic);
    MultiLinkControlScreen_AnimImageWidget->fn->setImageDelay(MultiLinkControlScreen_AnimImageWidget, 0, 1000);
    root0->fn->addChild(root0, (leWidget*)MultiLinkControlScreen_AnimImageWidget);

    MultiLinkControlScreen_MfgBlock = leWidget_New();
    MultiLinkControlScreen_MfgBlock->fn->setPosition(MultiLinkControlScreen_MfgBlock, 83, 33);
    MultiLinkControlScreen_MfgBlock->fn->setSize(MultiLinkControlScreen_MfgBlock, 49, 46);
    MultiLinkControlScreen_MfgBlock->fn->setScheme(MultiLinkControlScreen_MfgBlock, &InfoGraphicBackScheme);
    MultiLinkControlScreen_AnimImageWidget->fn->addChild(MultiLinkControlScreen_AnimImageWidget, (leWidget*)MultiLinkControlScreen_MfgBlock);

    MultiLinkControlScreen_BldgBlock = leWidget_New();
    MultiLinkControlScreen_BldgBlock->fn->setPosition(MultiLinkControlScreen_BldgBlock, 149, 30);
    MultiLinkControlScreen_BldgBlock->fn->setSize(MultiLinkControlScreen_BldgBlock, 50, 47);
    MultiLinkControlScreen_BldgBlock->fn->setScheme(MultiLinkControlScreen_BldgBlock, &InfoGraphicBackScheme);
    MultiLinkControlScreen_AnimImageWidget->fn->addChild(MultiLinkControlScreen_AnimImageWidget, (leWidget*)MultiLinkControlScreen_BldgBlock);

    MultiLinkControlScreen_EnergyBlock = leWidget_New();
    MultiLinkControlScreen_EnergyBlock->fn->setPosition(MultiLinkControlScreen_EnergyBlock, 214, 74);
    MultiLinkControlScreen_EnergyBlock->fn->setSize(MultiLinkControlScreen_EnergyBlock, 31, 56);
    MultiLinkControlScreen_EnergyBlock->fn->setScheme(MultiLinkControlScreen_EnergyBlock, &InfoGraphicBackScheme);
    MultiLinkControlScreen_AnimImageWidget->fn->addChild(MultiLinkControlScreen_AnimImageWidget, (leWidget*)MultiLinkControlScreen_EnergyBlock);

    MultiLinkControlScreen_EnvBlock = leWidget_New();
    MultiLinkControlScreen_EnvBlock->fn->setPosition(MultiLinkControlScreen_EnvBlock, 205, 146);
    MultiLinkControlScreen_EnvBlock->fn->setSize(MultiLinkControlScreen_EnvBlock, 51, 47);
    MultiLinkControlScreen_EnvBlock->fn->setScheme(MultiLinkControlScreen_EnvBlock, &InfoGraphicBackScheme);
    MultiLinkControlScreen_AnimImageWidget->fn->addChild(MultiLinkControlScreen_AnimImageWidget, (leWidget*)MultiLinkControlScreen_EnvBlock);

    MultiLinkControlScreen_AgriBlock = leWidget_New();
    MultiLinkControlScreen_AgriBlock->fn->setPosition(MultiLinkControlScreen_AgriBlock, 149, 199);
    MultiLinkControlScreen_AgriBlock->fn->setSize(MultiLinkControlScreen_AgriBlock, 44, 53);
    MultiLinkControlScreen_AgriBlock->fn->setScheme(MultiLinkControlScreen_AgriBlock, &InfoGraphicBackScheme);
    MultiLinkControlScreen_AnimImageWidget->fn->addChild(MultiLinkControlScreen_AnimImageWidget, (leWidget*)MultiLinkControlScreen_AgriBlock);

    MultiLinkControlScreen_LogiBlock = leWidget_New();
    MultiLinkControlScreen_LogiBlock->fn->setPosition(MultiLinkControlScreen_LogiBlock, 77, 211);
    MultiLinkControlScreen_LogiBlock->fn->setSize(MultiLinkControlScreen_LogiBlock, 51, 41);
    MultiLinkControlScreen_LogiBlock->fn->setScheme(MultiLinkControlScreen_LogiBlock, &InfoGraphicBackScheme);
    MultiLinkControlScreen_AnimImageWidget->fn->addChild(MultiLinkControlScreen_AnimImageWidget, (leWidget*)MultiLinkControlScreen_LogiBlock);

    MultiLinkControlScreen_HomeAutoBlock = leWidget_New();
    MultiLinkControlScreen_HomeAutoBlock->fn->setPosition(MultiLinkControlScreen_HomeAutoBlock, 26, 148);
    MultiLinkControlScreen_HomeAutoBlock->fn->setSize(MultiLinkControlScreen_HomeAutoBlock, 61, 43);
    MultiLinkControlScreen_HomeAutoBlock->fn->setScheme(MultiLinkControlScreen_HomeAutoBlock, &InfoGraphicBackScheme);
    MultiLinkControlScreen_AnimImageWidget->fn->addChild(MultiLinkControlScreen_AnimImageWidget, (leWidget*)MultiLinkControlScreen_HomeAutoBlock);

    MultiLinkControlScreen_SmartCityBlock = leWidget_New();
    MultiLinkControlScreen_SmartCityBlock->fn->setPosition(MultiLinkControlScreen_SmartCityBlock, 32, 79);
    MultiLinkControlScreen_SmartCityBlock->fn->setSize(MultiLinkControlScreen_SmartCityBlock, 41, 48);
    MultiLinkControlScreen_SmartCityBlock->fn->setScheme(MultiLinkControlScreen_SmartCityBlock, &InfoGraphicBackScheme);
    MultiLinkControlScreen_AnimImageWidget->fn->addChild(MultiLinkControlScreen_AnimImageWidget, (leWidget*)MultiLinkControlScreen_SmartCityBlock);

    MultiLinkControlScreen_SmartConSecLogoBlock = leWidget_New();
    MultiLinkControlScreen_SmartConSecLogoBlock->fn->setPosition(MultiLinkControlScreen_SmartConSecLogoBlock, 102, 89);
    MultiLinkControlScreen_SmartConSecLogoBlock->fn->setSize(MultiLinkControlScreen_SmartConSecLogoBlock, 75, 75);
    MultiLinkControlScreen_SmartConSecLogoBlock->fn->setScheme(MultiLinkControlScreen_SmartConSecLogoBlock, &InfoGraphicBackScheme);
    MultiLinkControlScreen_AnimImageWidget->fn->addChild(MultiLinkControlScreen_AnimImageWidget, (leWidget*)MultiLinkControlScreen_SmartConSecLogoBlock);

    MultiLinkControlScreen_SmartBlock = leWidget_New();
    MultiLinkControlScreen_SmartBlock->fn->setPosition(MultiLinkControlScreen_SmartBlock, 88, 163);
    MultiLinkControlScreen_SmartBlock->fn->setSize(MultiLinkControlScreen_SmartBlock, 28, 17);
    MultiLinkControlScreen_SmartBlock->fn->setScheme(MultiLinkControlScreen_SmartBlock, &InfoGraphicBackScheme);
    MultiLinkControlScreen_AnimImageWidget->fn->addChild(MultiLinkControlScreen_AnimImageWidget, (leWidget*)MultiLinkControlScreen_SmartBlock);

    MultiLinkControlScreen_ConnectedBlock = leWidget_New();
    MultiLinkControlScreen_ConnectedBlock->fn->setPosition(MultiLinkControlScreen_ConnectedBlock, 121, 164);
    MultiLinkControlScreen_ConnectedBlock->fn->setSize(MultiLinkControlScreen_ConnectedBlock, 37, 16);
    MultiLinkControlScreen_ConnectedBlock->fn->setScheme(MultiLinkControlScreen_ConnectedBlock, &InfoGraphicBackScheme);
    MultiLinkControlScreen_AnimImageWidget->fn->addChild(MultiLinkControlScreen_AnimImageWidget, (leWidget*)MultiLinkControlScreen_ConnectedBlock);

    MultiLinkControlScreen_SecureBlock = leWidget_New();
    MultiLinkControlScreen_SecureBlock->fn->setPosition(MultiLinkControlScreen_SecureBlock, 163, 164);
    MultiLinkControlScreen_SecureBlock->fn->setSize(MultiLinkControlScreen_SecureBlock, 28, 20);
    MultiLinkControlScreen_SecureBlock->fn->setScheme(MultiLinkControlScreen_SecureBlock, &InfoGraphicBackScheme);
    MultiLinkControlScreen_AnimImageWidget->fn->addChild(MultiLinkControlScreen_AnimImageWidget, (leWidget*)MultiLinkControlScreen_SecureBlock);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    MultiLinkControlScreen_OnShow(); // raise event

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_MultiLinkControlScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);

    MultiLinkControlScreen_OnUpdate(); // raise event
}

void screenHide_MultiLinkControlScreen(void)
{
    MultiLinkControlScreen_OnHide(); // raise event


    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    MultiLinkControlScreen_PanelWidget0 = NULL;
    MultiLinkControlScreen_LineWidget0 = NULL;
    MultiLinkControlScreen_ImageWidget0 = NULL;
    MultiLinkControlScreen_DisconnectButton = NULL;
    MultiLinkControlScreen_ColorPickerImage = NULL;
    MultiLinkControlScreen_DeviceCButton = NULL;
    MultiLinkControlScreen_DeviceBButton = NULL;
    MultiLinkControlScreen_DeviceAButton = NULL;
    MultiLinkControlScreen_SliderImageWidget = NULL;
    MultiLinkControlScreen_SliderControlPanel = NULL;
    MultiLinkControlScreen_ScrollKnobImageWidget = NULL;
    MultiLinkControlScreen_SelectedColorPanelA = NULL;
    MultiLinkControlScreen_AllDevicesButton = NULL;
    MultiLinkControlScreen_LabelWidget_0 = NULL;
    MultiLinkControlScreen_SelectedColorPanelB = NULL;
    MultiLinkControlScreen_SelectedColorPanelC = NULL;
    MultiLinkControlScreen_DeviceDataPanelA = NULL;
    MultiLinkControlScreen_LineGraphWidget_0 = NULL;
    MultiLinkControlScreen_BarGraphWidget_0 = NULL;
    MultiLinkControlScreen_DeviceInfoButton = NULL;
    MultiLinkControlScreen_BLEInfoButton = NULL;
    MultiLinkControlScreen_WiFiInfoButton = NULL;
    MultiLinkControlScreen_ColorWheelSelectColor = NULL;
    MultiLinkControlScreen_AnimImageWidget = NULL;
    MultiLinkControlScreen_ImageSequenceWidgetC = NULL;
    MultiLinkControlScreen_LabelWidget2 = NULL;
    MultiLinkControlScreen_TempLabelC = NULL;
    MultiLinkControlScreen_ImageSequenceWidgetB = NULL;
    MultiLinkControlScreen_LabelWidget1 = NULL;
    MultiLinkControlScreen_TempLabelB = NULL;
    MultiLinkControlScreen_ImageSequenceWidgetA = NULL;
    MultiLinkControlScreen_LabelWidget0 = NULL;
    MultiLinkControlScreen_TempLabelA = NULL;
    MultiLinkControlScreen_ColorGraphLabel = NULL;
    MultiLinkControlScreen_TempSensorGraphLabel = NULL;
    MultiLinkControlScreen_LineGraphLabelA = NULL;
    MultiLinkControlScreen_LineGraphLabelB = NULL;
    MultiLinkControlScreen_LineGraphLabelC = NULL;
    MultiLinkControlScreen_DeviceInfoLabel = NULL;
    MultiLinkControlScreen_BLEDeviceAName = NULL;
    MultiLinkControlScreen_BLEDeviceBName = NULL;
    MultiLinkControlScreen_BLEDeviceCName = NULL;
    MultiLinkControlScreen_BLEDeviceAOK = NULL;
    MultiLinkControlScreen_BLEDeviceBOK = NULL;
    MultiLinkControlScreen_BLEDeviceCOK = NULL;
    MultiLinkControlScreen_NetInfoPanel = NULL;
    MultiLinkControlScreen_PanelWidget_0 = NULL;
    MultiLinkControlScreen_PanelWidget_1 = NULL;
    MultiLinkControlScreen_PanelWidget_2 = NULL;
    MultiLinkControlScreen_NetInfString = NULL;
    MultiLinkControlScreen_NetSSIDString = NULL;
    MultiLinkControlScreen_NetIPString = NULL;
    MultiLinkControlScreen_NetConnString = NULL;
    MultiLinkControlScreen_NetURLString = NULL;
    MultiLinkControlScreen_NetWebURLQR = NULL;
    MultiLinkControlScreen_NetInterfaceInfo = NULL;
    MultiLinkControlScreen_NetSSIDInfo = NULL;
    MultiLinkControlScreen_NetIPInfo = NULL;
    MultiLinkControlScreen_NetConnInfo = NULL;
    MultiLinkControlScreen_NetURLInfo = NULL;
    MultiLinkControlScreen_MfgBlock = NULL;
    MultiLinkControlScreen_BldgBlock = NULL;
    MultiLinkControlScreen_EnergyBlock = NULL;
    MultiLinkControlScreen_EnvBlock = NULL;
    MultiLinkControlScreen_AgriBlock = NULL;
    MultiLinkControlScreen_LogiBlock = NULL;
    MultiLinkControlScreen_HomeAutoBlock = NULL;
    MultiLinkControlScreen_SmartCityBlock = NULL;
    MultiLinkControlScreen_SmartConSecLogoBlock = NULL;
    MultiLinkControlScreen_SmartBlock = NULL;
    MultiLinkControlScreen_ConnectedBlock = NULL;
    MultiLinkControlScreen_SecureBlock = NULL;


    showing = LE_FALSE;
}

void screenDestroy_MultiLinkControlScreen(void)
{
    if(initialized == LE_FALSE)
        return;

    initialized = LE_FALSE;
}

leWidget* screenGetRoot_MultiLinkControlScreen(uint32_t lyrIdx)
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

