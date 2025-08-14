#include "gfx/legato/generated/screen/le_gen_screen_ControlScreen.h"

// screen member widget declarations
static leWidget* root0;

leWidget* ControlScreen_Panel_0;
leWidget* ControlScreen_ColorWheelSelectColor;
leButtonWidget* ControlScreen_WiFiInfoButton;
leButtonWidget* ControlScreen_BLEInfoButton;
leButtonWidget* ControlScreen_DeviceInfoButton;
leWidget* ControlScreen_SelectedColorPanelC;
leWidget* ControlScreen_SelectedColorPanelB;
leLabelWidget* ControlScreen_LabelWidget_0;
leButtonWidget* ControlScreen_AllDevicesButton;
leWidget* ControlScreen_SelectedColorPanelA;
leImageWidget* ControlScreen_ScrollKnobImageWidget;
leWidget* ControlScreen_SliderControlPanel;
leImageWidget* ControlScreen_SliderImageWidget;
leLabelWidget* ControlScreen_TempLabelA;
leLabelWidget* ControlScreen_LabelWidget0;
leButtonWidget* ControlScreen_DeviceAButton;
leLabelWidget* ControlScreen_TempLabelB;
leLabelWidget* ControlScreen_LabelWidget1;
leButtonWidget* ControlScreen_DeviceBButton;
leLabelWidget* ControlScreen_TempLabelC;
leLabelWidget* ControlScreen_LabelWidget2;
leButtonWidget* ControlScreen_DeviceCButton;
leImageWidget* ControlScreen_ColorPickerImage;
leButtonWidget* ControlScreen_DisconnectButton;
leImageWidget* ControlScreen_ImageWidget0;
leLineWidget* ControlScreen_LineWidget0;
leWidget* ControlScreen_PanelWidget0;
leLabelWidget* ControlScreen_LabelWidget_0_0;
leLineWidget* ControlScreen_LineWidget0_0;
leImageWidget* ControlScreen_ImageWidget0_0;
leButtonWidget* ControlScreen_WiFiInfoButton_0;
leButtonWidget* ControlScreen_BLEInfoButton_0;
leButtonWidget* ControlScreen_DeviceInfoButton_0;
leImageSequenceWidget* ControlScreen_AnimImageWidget;

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

    ControlScreen_Panel_0 = leWidget_New();
    ControlScreen_Panel_0->fn->setPosition(ControlScreen_Panel_0, 0, 0);
    ControlScreen_Panel_0->fn->setSize(ControlScreen_Panel_0, 800, 480);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_Panel_0);

    ControlScreen_ColorWheelSelectColor = leWidget_New();
    ControlScreen_ColorWheelSelectColor->fn->setPosition(ControlScreen_ColorWheelSelectColor, 567, 102);
    ControlScreen_ColorWheelSelectColor->fn->setSize(ControlScreen_ColorWheelSelectColor, 86, 25);
    ControlScreen_ColorWheelSelectColor->fn->setScheme(ControlScreen_ColorWheelSelectColor, &WhiteScheme);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_ColorWheelSelectColor);

    ControlScreen_WiFiInfoButton = leButtonWidget_New();
    ControlScreen_WiFiInfoButton->fn->setPosition(ControlScreen_WiFiInfoButton, 224, 54);
    ControlScreen_WiFiInfoButton->fn->setSize(ControlScreen_WiFiInfoButton, 80, 60);
    ControlScreen_WiFiInfoButton->fn->setBackgroundType(ControlScreen_WiFiInfoButton, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_WiFiInfoButton->fn->setBorderType(ControlScreen_WiFiInfoButton, LE_WIDGET_BORDER_NONE);
    ControlScreen_WiFiInfoButton->fn->setVAlignment(ControlScreen_WiFiInfoButton, LE_VALIGN_TOP);
    ControlScreen_WiFiInfoButton->fn->setPressedImage(ControlScreen_WiFiInfoButton, (leImage*)&WifiTabA60);
    ControlScreen_WiFiInfoButton->fn->setReleasedImage(ControlScreen_WiFiInfoButton, (leImage*)&WifiTab60);
    ControlScreen_WiFiInfoButton->fn->setPressedOffset(ControlScreen_WiFiInfoButton, 0);
    ControlScreen_WiFiInfoButton->fn->setPressedEventCallback(ControlScreen_WiFiInfoButton, event_ControlScreen_WiFiInfoButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_WiFiInfoButton);

    ControlScreen_BLEInfoButton = leButtonWidget_New();
    ControlScreen_BLEInfoButton->fn->setPosition(ControlScreen_BLEInfoButton, 146, 49);
    ControlScreen_BLEInfoButton->fn->setSize(ControlScreen_BLEInfoButton, 80, 66);
    ControlScreen_BLEInfoButton->fn->setBackgroundType(ControlScreen_BLEInfoButton, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_BLEInfoButton->fn->setBorderType(ControlScreen_BLEInfoButton, LE_WIDGET_BORDER_NONE);
    ControlScreen_BLEInfoButton->fn->setVAlignment(ControlScreen_BLEInfoButton, LE_VALIGN_TOP);
    ControlScreen_BLEInfoButton->fn->setPressedImage(ControlScreen_BLEInfoButton, (leImage*)&bleTabA60);
    ControlScreen_BLEInfoButton->fn->setReleasedImage(ControlScreen_BLEInfoButton, (leImage*)&bleTab60);
    ControlScreen_BLEInfoButton->fn->setPressedOffset(ControlScreen_BLEInfoButton, 0);
    ControlScreen_BLEInfoButton->fn->setPressedEventCallback(ControlScreen_BLEInfoButton, event_ControlScreen_BLEInfoButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_BLEInfoButton);

    ControlScreen_DeviceInfoButton = leButtonWidget_New();
    ControlScreen_DeviceInfoButton->fn->setPosition(ControlScreen_DeviceInfoButton, 69, 54);
    ControlScreen_DeviceInfoButton->fn->setSize(ControlScreen_DeviceInfoButton, 80, 60);
    ControlScreen_DeviceInfoButton->fn->setBackgroundType(ControlScreen_DeviceInfoButton, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_DeviceInfoButton->fn->setBorderType(ControlScreen_DeviceInfoButton, LE_WIDGET_BORDER_NONE);
    ControlScreen_DeviceInfoButton->fn->setVAlignment(ControlScreen_DeviceInfoButton, LE_VALIGN_TOP);
    ControlScreen_DeviceInfoButton->fn->setPressedImage(ControlScreen_DeviceInfoButton, (leImage*)&GraphTabA60);
    ControlScreen_DeviceInfoButton->fn->setReleasedImage(ControlScreen_DeviceInfoButton, (leImage*)&graphtab60);
    ControlScreen_DeviceInfoButton->fn->setPressedOffset(ControlScreen_DeviceInfoButton, 0);
    ControlScreen_DeviceInfoButton->fn->setPressedEventCallback(ControlScreen_DeviceInfoButton, event_ControlScreen_DeviceInfoButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_DeviceInfoButton);

    ControlScreen_SelectedColorPanelC = leWidget_New();
    ControlScreen_SelectedColorPanelC->fn->setPosition(ControlScreen_SelectedColorPanelC, 511, 388);
    ControlScreen_SelectedColorPanelC->fn->setSize(ControlScreen_SelectedColorPanelC, 20, 20);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_SelectedColorPanelC);

    ControlScreen_SelectedColorPanelB = leWidget_New();
    ControlScreen_SelectedColorPanelB->fn->setPosition(ControlScreen_SelectedColorPanelB, 439, 264);
    ControlScreen_SelectedColorPanelB->fn->setSize(ControlScreen_SelectedColorPanelB, 20, 20);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_SelectedColorPanelB);

    ControlScreen_LabelWidget_0 = leLabelWidget_New();
    ControlScreen_LabelWidget_0->fn->setPosition(ControlScreen_LabelWidget_0, 410, 2);
    ControlScreen_LabelWidget_0->fn->setSize(ControlScreen_LabelWidget_0, 380, 25);
    ControlScreen_LabelWidget_0->fn->setScheme(ControlScreen_LabelWidget_0, &TextScheme);
    ControlScreen_LabelWidget_0->fn->setHAlignment(ControlScreen_LabelWidget_0, LE_HALIGN_CENTER);
    ControlScreen_LabelWidget_0->fn->setString(ControlScreen_LabelWidget_0, (leString*)&string_DemoName);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_LabelWidget_0);

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

    ControlScreen_SelectedColorPanelA = leWidget_New();
    ControlScreen_SelectedColorPanelA->fn->setPosition(ControlScreen_SelectedColorPanelA, 510, 144);
    ControlScreen_SelectedColorPanelA->fn->setSize(ControlScreen_SelectedColorPanelA, 20, 20);
    ControlScreen_SelectedColorPanelA->fn->setScheme(ControlScreen_SelectedColorPanelA, &BlueScheme);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_SelectedColorPanelA);

    ControlScreen_ScrollKnobImageWidget = leImageWidget_New();
    ControlScreen_ScrollKnobImageWidget->fn->setPosition(ControlScreen_ScrollKnobImageWidget, 745, 261);
    ControlScreen_ScrollKnobImageWidget->fn->setSize(ControlScreen_ScrollKnobImageWidget, 30, 30);
    ControlScreen_ScrollKnobImageWidget->fn->setEnabled(ControlScreen_ScrollKnobImageWidget, LE_FALSE);
    ControlScreen_ScrollKnobImageWidget->fn->setBackgroundType(ControlScreen_ScrollKnobImageWidget, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_ScrollKnobImageWidget->fn->setBorderType(ControlScreen_ScrollKnobImageWidget, LE_WIDGET_BORDER_NONE);
    ControlScreen_ScrollKnobImageWidget->fn->setImage(ControlScreen_ScrollKnobImageWidget, (leImage*)&Knob30);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_ScrollKnobImageWidget);

    ControlScreen_SliderControlPanel = leWidget_New();
    ControlScreen_SliderControlPanel->fn->setPosition(ControlScreen_SliderControlPanel, 726, 205);
    ControlScreen_SliderControlPanel->fn->setSize(ControlScreen_SliderControlPanel, 67, 147);
    ControlScreen_SliderControlPanel->fn->setBackgroundType(ControlScreen_SliderControlPanel, LE_WIDGET_BACKGROUND_NONE);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_SliderControlPanel);

    ControlScreen_SliderImageWidget = leImageWidget_New();
    ControlScreen_SliderImageWidget->fn->setPosition(ControlScreen_SliderImageWidget, 730, 150);
    ControlScreen_SliderImageWidget->fn->setSize(ControlScreen_SliderImageWidget, 60, 250);
    ControlScreen_SliderImageWidget->fn->setBackgroundType(ControlScreen_SliderImageWidget, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_SliderImageWidget->fn->setBorderType(ControlScreen_SliderImageWidget, LE_WIDGET_BORDER_NONE);
    ControlScreen_SliderImageWidget->fn->setImage(ControlScreen_SliderImageWidget, (leImage*)&Slider50);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_SliderImageWidget);

    ControlScreen_TempLabelA = leLabelWidget_New();
    ControlScreen_TempLabelA->fn->setPosition(ControlScreen_TempLabelA, 5, 18);
    ControlScreen_TempLabelA->fn->setSize(ControlScreen_TempLabelA, 55, 30);
    ControlScreen_TempLabelA->fn->setScheme(ControlScreen_TempLabelA, &WhiteScheme);
    ControlScreen_TempLabelA->fn->setBackgroundType(ControlScreen_TempLabelA, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_TempLabelA->fn->setHAlignment(ControlScreen_TempLabelA, LE_HALIGN_CENTER);
    ControlScreen_TempLabelA->fn->setString(ControlScreen_TempLabelA, (leString*)&string_DefaultTemp);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_TempLabelA);

    ControlScreen_LabelWidget0 = leLabelWidget_New();
    ControlScreen_LabelWidget0->fn->setPosition(ControlScreen_LabelWidget0, 0, -1);
    ControlScreen_LabelWidget0->fn->setSize(ControlScreen_LabelWidget0, 25, 25);
    ControlScreen_LabelWidget0->fn->setEnabled(ControlScreen_LabelWidget0, LE_FALSE);
    ControlScreen_LabelWidget0->fn->setScheme(ControlScreen_LabelWidget0, &TextScheme);
    ControlScreen_LabelWidget0->fn->setBackgroundType(ControlScreen_LabelWidget0, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_LabelWidget0->fn->setHAlignment(ControlScreen_LabelWidget0, LE_HALIGN_CENTER);
    ControlScreen_LabelWidget0->fn->setString(ControlScreen_LabelWidget0, (leString*)&string_DeviceA);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_LabelWidget0);

    ControlScreen_DeviceAButton = leButtonWidget_New();
    ControlScreen_DeviceAButton->fn->setPosition(ControlScreen_DeviceAButton, 440, 120);
    ControlScreen_DeviceAButton->fn->setSize(ControlScreen_DeviceAButton, 65, 65);
    ControlScreen_DeviceAButton->fn->setBackgroundType(ControlScreen_DeviceAButton, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_DeviceAButton->fn->setBorderType(ControlScreen_DeviceAButton, LE_WIDGET_BORDER_NONE);
    ControlScreen_DeviceAButton->fn->setPressedOffset(ControlScreen_DeviceAButton, 0);
    ControlScreen_DeviceAButton->fn->setPressedEventCallback(ControlScreen_DeviceAButton, NULL /* event_LightControlScreen_DeviceAButton_OnPressed*/);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_DeviceAButton);

    ControlScreen_TempLabelB = leLabelWidget_New();
    ControlScreen_TempLabelB->fn->setPosition(ControlScreen_TempLabelB, 5, 18);
    ControlScreen_TempLabelB->fn->setSize(ControlScreen_TempLabelB, 55, 30);
    ControlScreen_TempLabelB->fn->setScheme(ControlScreen_TempLabelB, &TextScheme);
    ControlScreen_TempLabelB->fn->setBackgroundType(ControlScreen_TempLabelB, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_TempLabelB->fn->setHAlignment(ControlScreen_TempLabelB, LE_HALIGN_CENTER);
    ControlScreen_TempLabelB->fn->setString(ControlScreen_TempLabelB, (leString*)&string_DefaultTemp);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_TempLabelB);

    ControlScreen_LabelWidget1 = leLabelWidget_New();
    ControlScreen_LabelWidget1->fn->setPosition(ControlScreen_LabelWidget1, -1, -2);
    ControlScreen_LabelWidget1->fn->setSize(ControlScreen_LabelWidget1, 25, 25);
    ControlScreen_LabelWidget1->fn->setEnabled(ControlScreen_LabelWidget1, LE_FALSE);
    ControlScreen_LabelWidget1->fn->setScheme(ControlScreen_LabelWidget1, &TextScheme);
    ControlScreen_LabelWidget1->fn->setBackgroundType(ControlScreen_LabelWidget1, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_LabelWidget1->fn->setHAlignment(ControlScreen_LabelWidget1, LE_HALIGN_CENTER);
    ControlScreen_LabelWidget1->fn->setString(ControlScreen_LabelWidget1, (leString*)&string_DeviceB);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_LabelWidget1);

    ControlScreen_DeviceBButton = leButtonWidget_New();
    ControlScreen_DeviceBButton->fn->setPosition(ControlScreen_DeviceBButton, 370, 240);
    ControlScreen_DeviceBButton->fn->setSize(ControlScreen_DeviceBButton, 65, 65);
    ControlScreen_DeviceBButton->fn->setBackgroundType(ControlScreen_DeviceBButton, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_DeviceBButton->fn->setBorderType(ControlScreen_DeviceBButton, LE_WIDGET_BORDER_NONE);
    ControlScreen_DeviceBButton->fn->setPressedOffset(ControlScreen_DeviceBButton, 0);
    ControlScreen_DeviceBButton->fn->setPressedEventCallback(ControlScreen_DeviceBButton, NULL /*event_LightControlScreen_DeviceBButton_OnPressed*/);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_DeviceBButton);

    ControlScreen_TempLabelC = leLabelWidget_New();
    ControlScreen_TempLabelC->fn->setPosition(ControlScreen_TempLabelC, 5, 18);
    ControlScreen_TempLabelC->fn->setSize(ControlScreen_TempLabelC, 55, 30);
    ControlScreen_TempLabelC->fn->setScheme(ControlScreen_TempLabelC, &TextScheme);
    ControlScreen_TempLabelC->fn->setBackgroundType(ControlScreen_TempLabelC, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_TempLabelC->fn->setHAlignment(ControlScreen_TempLabelC, LE_HALIGN_CENTER);
    ControlScreen_TempLabelC->fn->setString(ControlScreen_TempLabelC, (leString*)&string_DefaultTemp);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_TempLabelC);

    ControlScreen_LabelWidget2 = leLabelWidget_New();
    ControlScreen_LabelWidget2->fn->setPosition(ControlScreen_LabelWidget2, -2, -1);
    ControlScreen_LabelWidget2->fn->setSize(ControlScreen_LabelWidget2, 25, 25);
    ControlScreen_LabelWidget2->fn->setEnabled(ControlScreen_LabelWidget2, LE_FALSE);
    ControlScreen_LabelWidget2->fn->setScheme(ControlScreen_LabelWidget2, &TextScheme);
    ControlScreen_LabelWidget2->fn->setBackgroundType(ControlScreen_LabelWidget2, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_LabelWidget2->fn->setHAlignment(ControlScreen_LabelWidget2, LE_HALIGN_CENTER);
    ControlScreen_LabelWidget2->fn->setString(ControlScreen_LabelWidget2, (leString*)&string_DeviceC);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_LabelWidget2);

    ControlScreen_DeviceCButton = leButtonWidget_New();
    ControlScreen_DeviceCButton->fn->setPosition(ControlScreen_DeviceCButton, 440, 360);
    ControlScreen_DeviceCButton->fn->setSize(ControlScreen_DeviceCButton, 65, 65);
    ControlScreen_DeviceCButton->fn->setBackgroundType(ControlScreen_DeviceCButton, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_DeviceCButton->fn->setBorderType(ControlScreen_DeviceCButton, LE_WIDGET_BORDER_NONE);
    ControlScreen_DeviceCButton->fn->setPressedOffset(ControlScreen_DeviceCButton, 0);
    ControlScreen_DeviceCButton->fn->setPressedEventCallback(ControlScreen_DeviceCButton, NULL /*event_LightControlScreen_DeviceCButton_OnPressed*/);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_DeviceCButton);

    ControlScreen_ColorPickerImage = leImageWidget_New();
    ControlScreen_ColorPickerImage->fn->setPosition(ControlScreen_ColorPickerImage, 514, 173);
    ControlScreen_ColorPickerImage->fn->setSize(ControlScreen_ColorPickerImage, 200, 200);
    ControlScreen_ColorPickerImage->fn->setBackgroundType(ControlScreen_ColorPickerImage, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_ColorPickerImage->fn->setBorderType(ControlScreen_ColorPickerImage, LE_WIDGET_BORDER_NONE);
    ControlScreen_ColorPickerImage->fn->setMargins(ControlScreen_ColorPickerImage, 0, 0, 0, 0);
    ControlScreen_ColorPickerImage->fn->setImage(ControlScreen_ColorPickerImage, (leImage*)&ColorPickerBlueBack200_565);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_ColorPickerImage);

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
    ControlScreen_DisconnectButton->fn->setPressedEventCallback(ControlScreen_DisconnectButton, NULL /* event_LightControlScreen_DisconnectButton_OnPressed */);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_DisconnectButton);

    ControlScreen_ImageWidget0 = leImageWidget_New();
    ControlScreen_ImageWidget0->fn->setPosition(ControlScreen_ImageWidget0, 10, 10);
    ControlScreen_ImageWidget0->fn->setSize(ControlScreen_ImageWidget0, 100, 40);
    ControlScreen_ImageWidget0->fn->setBackgroundType(ControlScreen_ImageWidget0, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_ImageWidget0->fn->setBorderType(ControlScreen_ImageWidget0, LE_WIDGET_BORDER_NONE);
    ControlScreen_ImageWidget0->fn->setImage(ControlScreen_ImageWidget0, (leImage*)&MchpLogo_100);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_ImageWidget0);

    ControlScreen_LineWidget0 = leLineWidget_New();
    ControlScreen_LineWidget0->fn->setPosition(ControlScreen_LineWidget0, 97, 25);
    ControlScreen_LineWidget0->fn->setSize(ControlScreen_LineWidget0, 700, 15);
    ControlScreen_LineWidget0->fn->setScheme(ControlScreen_LineWidget0, &WhiteScheme);
    ControlScreen_LineWidget0->fn->setBackgroundType(ControlScreen_LineWidget0, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_LineWidget0->fn->setStartPoint(ControlScreen_LineWidget0, 0, 5);
    ControlScreen_LineWidget0->fn->setEndPoint(ControlScreen_LineWidget0, 700, 5);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_LineWidget0);

    ControlScreen_PanelWidget0 = leWidget_New();
    ControlScreen_PanelWidget0->fn->setPosition(ControlScreen_PanelWidget0, 0, 4);
    ControlScreen_PanelWidget0->fn->setSize(ControlScreen_PanelWidget0, 800, 480);
    ControlScreen_PanelWidget0->fn->setScheme(ControlScreen_PanelWidget0, &BackScheme);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_PanelWidget0);

    ControlScreen_LabelWidget_0_0 = leLabelWidget_New();
    ControlScreen_LabelWidget_0_0->fn->setPosition(ControlScreen_LabelWidget_0_0, 410, 2);
    ControlScreen_LabelWidget_0_0->fn->setSize(ControlScreen_LabelWidget_0_0, 380, 25);
    ControlScreen_LabelWidget_0_0->fn->setScheme(ControlScreen_LabelWidget_0_0, &TextScheme);
    ControlScreen_LabelWidget_0_0->fn->setHAlignment(ControlScreen_LabelWidget_0_0, LE_HALIGN_CENTER);
    ControlScreen_LabelWidget_0_0->fn->setString(ControlScreen_LabelWidget_0_0, (leString*)&string_DemoName);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_LabelWidget_0_0);

    ControlScreen_LineWidget0_0 = leLineWidget_New();
    ControlScreen_LineWidget0_0->fn->setPosition(ControlScreen_LineWidget0_0, 97, 25);
    ControlScreen_LineWidget0_0->fn->setSize(ControlScreen_LineWidget0_0, 700, 15);
    ControlScreen_LineWidget0_0->fn->setScheme(ControlScreen_LineWidget0_0, &WhiteScheme);
    ControlScreen_LineWidget0_0->fn->setBackgroundType(ControlScreen_LineWidget0_0, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_LineWidget0_0->fn->setStartPoint(ControlScreen_LineWidget0_0, 0, 5);
    ControlScreen_LineWidget0_0->fn->setEndPoint(ControlScreen_LineWidget0_0, 700, 5);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_LineWidget0_0);

    ControlScreen_ImageWidget0_0 = leImageWidget_New();
    ControlScreen_ImageWidget0_0->fn->setPosition(ControlScreen_ImageWidget0_0, 10, 10);
    ControlScreen_ImageWidget0_0->fn->setSize(ControlScreen_ImageWidget0_0, 100, 40);
    ControlScreen_ImageWidget0_0->fn->setBackgroundType(ControlScreen_ImageWidget0_0, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_ImageWidget0_0->fn->setBorderType(ControlScreen_ImageWidget0_0, LE_WIDGET_BORDER_NONE);
    ControlScreen_ImageWidget0_0->fn->setImage(ControlScreen_ImageWidget0_0, (leImage*)&MchpLogo_100);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_ImageWidget0_0);

    ControlScreen_WiFiInfoButton_0 = leButtonWidget_New();
    ControlScreen_WiFiInfoButton_0->fn->setPosition(ControlScreen_WiFiInfoButton_0, 228, 72);
    ControlScreen_WiFiInfoButton_0->fn->setSize(ControlScreen_WiFiInfoButton_0, 80, 60);
    ControlScreen_WiFiInfoButton_0->fn->setBackgroundType(ControlScreen_WiFiInfoButton_0, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_WiFiInfoButton_0->fn->setBorderType(ControlScreen_WiFiInfoButton_0, LE_WIDGET_BORDER_NONE);
    ControlScreen_WiFiInfoButton_0->fn->setVAlignment(ControlScreen_WiFiInfoButton_0, LE_VALIGN_TOP);
    ControlScreen_WiFiInfoButton_0->fn->setPressedImage(ControlScreen_WiFiInfoButton_0, (leImage*)&WifiTabA60);
    ControlScreen_WiFiInfoButton_0->fn->setReleasedImage(ControlScreen_WiFiInfoButton_0, (leImage*)&WifiTab60);
    ControlScreen_WiFiInfoButton_0->fn->setPressedOffset(ControlScreen_WiFiInfoButton_0, 0);
    ControlScreen_WiFiInfoButton_0->fn->setPressedEventCallback(ControlScreen_WiFiInfoButton_0, event_ControlScreen_WiFiInfoButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_WiFiInfoButton_0);

    ControlScreen_BLEInfoButton_0 = leButtonWidget_New();
    ControlScreen_BLEInfoButton_0->fn->setPosition(ControlScreen_BLEInfoButton_0, 150, 68);
    ControlScreen_BLEInfoButton_0->fn->setSize(ControlScreen_BLEInfoButton_0, 80, 65);
    ControlScreen_BLEInfoButton_0->fn->setBackgroundType(ControlScreen_BLEInfoButton_0, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_BLEInfoButton_0->fn->setBorderType(ControlScreen_BLEInfoButton_0, LE_WIDGET_BORDER_NONE);
    ControlScreen_BLEInfoButton_0->fn->setVAlignment(ControlScreen_BLEInfoButton_0, LE_VALIGN_TOP);
    ControlScreen_BLEInfoButton_0->fn->setPressedImage(ControlScreen_BLEInfoButton_0, (leImage*)&bleTabA60);
    ControlScreen_BLEInfoButton_0->fn->setReleasedImage(ControlScreen_BLEInfoButton_0, (leImage*)&bleTab60);
    ControlScreen_BLEInfoButton_0->fn->setPressedOffset(ControlScreen_BLEInfoButton_0, 0);
    ControlScreen_BLEInfoButton_0->fn->setPressedEventCallback(ControlScreen_BLEInfoButton_0, event_ControlScreen_BLEInfoButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_BLEInfoButton_0);

    ControlScreen_DeviceInfoButton_0 = leButtonWidget_New();
    ControlScreen_DeviceInfoButton_0->fn->setPosition(ControlScreen_DeviceInfoButton_0, 73, 72);
    ControlScreen_DeviceInfoButton_0->fn->setSize(ControlScreen_DeviceInfoButton_0, 80, 60);
    ControlScreen_DeviceInfoButton_0->fn->setBackgroundType(ControlScreen_DeviceInfoButton_0, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_DeviceInfoButton_0->fn->setBorderType(ControlScreen_DeviceInfoButton_0, LE_WIDGET_BORDER_NONE);
    ControlScreen_DeviceInfoButton_0->fn->setVAlignment(ControlScreen_DeviceInfoButton_0, LE_VALIGN_TOP);
    ControlScreen_DeviceInfoButton_0->fn->setPressedImage(ControlScreen_DeviceInfoButton_0, (leImage*)&GraphTabA60);
    ControlScreen_DeviceInfoButton_0->fn->setReleasedImage(ControlScreen_DeviceInfoButton_0, (leImage*)&graphtab60);
    ControlScreen_DeviceInfoButton_0->fn->setPressedOffset(ControlScreen_DeviceInfoButton_0, 0);
    ControlScreen_DeviceInfoButton_0->fn->setPressedEventCallback(ControlScreen_DeviceInfoButton_0, event_ControlScreen_DeviceInfoButton_OnPressed);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_DeviceInfoButton_0);

    ControlScreen_AnimImageWidget = leImageSequenceWidget_New();
    ControlScreen_AnimImageWidget->fn->setPosition(ControlScreen_AnimImageWidget, 50, 163);
    ControlScreen_AnimImageWidget->fn->setSize(ControlScreen_AnimImageWidget, 280, 280);
    ControlScreen_AnimImageWidget->fn->setBackgroundType(ControlScreen_AnimImageWidget, LE_WIDGET_BACKGROUND_NONE);
    ControlScreen_AnimImageWidget->fn->setImageCount(ControlScreen_AnimImageWidget, 1);
    ControlScreen_AnimImageWidget->fn->setImage(ControlScreen_AnimImageWidget, 0, &InfoGraphic);
    ControlScreen_AnimImageWidget->fn->setImageDelay(ControlScreen_AnimImageWidget, 0, 1000);
    root0->fn->addChild(root0, (leWidget*)ControlScreen_AnimImageWidget);

    leAddRootWidget(root0, 0);
    leSetLayerColorMode(0, LE_COLOR_MODE_RGB_565);

    showing = LE_TRUE;

    return LE_SUCCESS;
}

void screenUpdate_ControlScreen(void)
{
    root0->fn->setSize(root0, root0->rect.width, root0->rect.height);
}

void screenHide_ControlScreen(void)
{

    leRemoveRootWidget(root0, 0);
    leWidget_Delete(root0);
    root0 = NULL;

    ControlScreen_Panel_0 = NULL;
    ControlScreen_ColorWheelSelectColor = NULL;
    ControlScreen_WiFiInfoButton = NULL;
    ControlScreen_BLEInfoButton = NULL;
    ControlScreen_DeviceInfoButton = NULL;
    ControlScreen_SelectedColorPanelC = NULL;
    ControlScreen_SelectedColorPanelB = NULL;
    ControlScreen_LabelWidget_0 = NULL;
    ControlScreen_AllDevicesButton = NULL;
    ControlScreen_SelectedColorPanelA = NULL;
    ControlScreen_ScrollKnobImageWidget = NULL;
    ControlScreen_SliderControlPanel = NULL;
    ControlScreen_SliderImageWidget = NULL;
    ControlScreen_TempLabelA = NULL;
    ControlScreen_LabelWidget0 = NULL;
    ControlScreen_DeviceAButton = NULL;
    ControlScreen_TempLabelB = NULL;
    ControlScreen_LabelWidget1 = NULL;
    ControlScreen_DeviceBButton = NULL;
    ControlScreen_TempLabelC = NULL;
    ControlScreen_LabelWidget2 = NULL;
    ControlScreen_DeviceCButton = NULL;
    ControlScreen_ColorPickerImage = NULL;
    ControlScreen_DisconnectButton = NULL;
    ControlScreen_ImageWidget0 = NULL;
    ControlScreen_LineWidget0 = NULL;
    ControlScreen_PanelWidget0 = NULL;
    ControlScreen_LabelWidget_0_0 = NULL;
    ControlScreen_LineWidget0_0 = NULL;
    ControlScreen_ImageWidget0_0 = NULL;
    ControlScreen_WiFiInfoButton_0 = NULL;
    ControlScreen_BLEInfoButton_0 = NULL;
    ControlScreen_DeviceInfoButton_0 = NULL;
    ControlScreen_AnimImageWidget = NULL;


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

