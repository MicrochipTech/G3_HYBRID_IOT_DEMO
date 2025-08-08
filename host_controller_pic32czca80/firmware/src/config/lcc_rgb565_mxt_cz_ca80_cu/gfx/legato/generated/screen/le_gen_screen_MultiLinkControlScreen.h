#ifndef LE_GEN_SCREEN_MULTILINKCONTROLSCREEN_H
#define LE_GEN_SCREEN_MULTILINKCONTROLSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* MultiLinkControlScreen_PanelWidget0;
extern leLineWidget* MultiLinkControlScreen_LineWidget0;
extern leImageWidget* MultiLinkControlScreen_ImageWidget0;
extern leButtonWidget* MultiLinkControlScreen_DisconnectButton;
extern leImageWidget* MultiLinkControlScreen_ColorPickerImage;
extern leButtonWidget* MultiLinkControlScreen_DeviceCButton;
extern leButtonWidget* MultiLinkControlScreen_DeviceBButton;
extern leButtonWidget* MultiLinkControlScreen_DeviceAButton;
extern leImageWidget* MultiLinkControlScreen_SliderImageWidget;
extern leWidget* MultiLinkControlScreen_SliderControlPanel;
extern leImageWidget* MultiLinkControlScreen_ScrollKnobImageWidget;
extern leWidget* MultiLinkControlScreen_SelectedColorPanelA;
extern leButtonWidget* MultiLinkControlScreen_AllDevicesButton;
extern leLabelWidget* MultiLinkControlScreen_LabelWidget_0;
extern leWidget* MultiLinkControlScreen_SelectedColorPanelB;
extern leWidget* MultiLinkControlScreen_SelectedColorPanelC;
extern leWidget* MultiLinkControlScreen_DeviceDataPanelA;
extern leLineGraphWidget* MultiLinkControlScreen_LineGraphWidget_0;
extern leBarGraphWidget* MultiLinkControlScreen_BarGraphWidget_0;
extern leButtonWidget* MultiLinkControlScreen_DeviceInfoButton;
extern leButtonWidget* MultiLinkControlScreen_BLEInfoButton;
extern leButtonWidget* MultiLinkControlScreen_WiFiInfoButton;
extern leWidget* MultiLinkControlScreen_ColorWheelSelectColor;
extern leImageSequenceWidget* MultiLinkControlScreen_AnimImageWidget;
extern leImageSequenceWidget* MultiLinkControlScreen_ImageSequenceWidgetC;
extern leLabelWidget* MultiLinkControlScreen_LabelWidget2;
extern leLabelWidget* MultiLinkControlScreen_TempLabelC;
extern leImageSequenceWidget* MultiLinkControlScreen_ImageSequenceWidgetB;
extern leLabelWidget* MultiLinkControlScreen_LabelWidget1;
extern leLabelWidget* MultiLinkControlScreen_TempLabelB;
extern leImageSequenceWidget* MultiLinkControlScreen_ImageSequenceWidgetA;
extern leLabelWidget* MultiLinkControlScreen_LabelWidget0;
extern leLabelWidget* MultiLinkControlScreen_TempLabelA;
extern leLabelWidget* MultiLinkControlScreen_ColorGraphLabel;
extern leLabelWidget* MultiLinkControlScreen_TempSensorGraphLabel;
extern leLabelWidget* MultiLinkControlScreen_LineGraphLabelA;
extern leLabelWidget* MultiLinkControlScreen_LineGraphLabelB;
extern leLabelWidget* MultiLinkControlScreen_LineGraphLabelC;
extern leLabelWidget* MultiLinkControlScreen_DeviceInfoLabel;
extern leLabelWidget* MultiLinkControlScreen_BLEDeviceAName;
extern leLabelWidget* MultiLinkControlScreen_BLEDeviceBName;
extern leLabelWidget* MultiLinkControlScreen_BLEDeviceCName;
extern leImageWidget* MultiLinkControlScreen_BLEDeviceAOK;
extern leImageWidget* MultiLinkControlScreen_BLEDeviceBOK;
extern leImageWidget* MultiLinkControlScreen_BLEDeviceCOK;
extern leWidget* MultiLinkControlScreen_NetInfoPanel;
extern leWidget* MultiLinkControlScreen_PanelWidget_0;
extern leWidget* MultiLinkControlScreen_PanelWidget_1;
extern leWidget* MultiLinkControlScreen_PanelWidget_2;
extern leLabelWidget* MultiLinkControlScreen_NetInfString;
extern leLabelWidget* MultiLinkControlScreen_NetSSIDString;
extern leLabelWidget* MultiLinkControlScreen_NetIPString;
extern leLabelWidget* MultiLinkControlScreen_NetConnString;
extern leLabelWidget* MultiLinkControlScreen_NetURLString;
extern leImageWidget* MultiLinkControlScreen_NetWebURLQR;
extern leLabelWidget* MultiLinkControlScreen_NetInterfaceInfo;
extern leLabelWidget* MultiLinkControlScreen_NetSSIDInfo;
extern leLabelWidget* MultiLinkControlScreen_NetIPInfo;
extern leLabelWidget* MultiLinkControlScreen_NetConnInfo;
extern leLabelWidget* MultiLinkControlScreen_NetURLInfo;
extern leWidget* MultiLinkControlScreen_MfgBlock;
extern leWidget* MultiLinkControlScreen_BldgBlock;
extern leWidget* MultiLinkControlScreen_EnergyBlock;
extern leWidget* MultiLinkControlScreen_EnvBlock;
extern leWidget* MultiLinkControlScreen_AgriBlock;
extern leWidget* MultiLinkControlScreen_LogiBlock;
extern leWidget* MultiLinkControlScreen_HomeAutoBlock;
extern leWidget* MultiLinkControlScreen_SmartCityBlock;
extern leWidget* MultiLinkControlScreen_SmartConSecLogoBlock;
extern leWidget* MultiLinkControlScreen_SmartBlock;
extern leWidget* MultiLinkControlScreen_ConnectedBlock;
extern leWidget* MultiLinkControlScreen_SecureBlock;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_MultiLinkControlScreen_DisconnectButton_OnPressed(leButtonWidget* btn);
void event_MultiLinkControlScreen_DeviceCButton_OnPressed(leButtonWidget* btn);
void event_MultiLinkControlScreen_DeviceBButton_OnPressed(leButtonWidget* btn);
void event_MultiLinkControlScreen_DeviceAButton_OnPressed(leButtonWidget* btn);
void event_MultiLinkControlScreen_AllDevicesButton_OnPressed(leButtonWidget* btn);
void event_MultiLinkControlScreen_AllDevicesButton_OnReleased(leButtonWidget* btn);
void event_MultiLinkControlScreen_DeviceInfoButton_OnPressed(leButtonWidget* btn);
void event_MultiLinkControlScreen_BLEInfoButton_OnPressed(leButtonWidget* btn);
void event_MultiLinkControlScreen_WiFiInfoButton_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_MultiLinkControlScreen(void); // called when Legato is initialized
leResult screenShow_MultiLinkControlScreen(void); // called when screen is shown
void screenHide_MultiLinkControlScreen(void); // called when screen is hidden
void screenDestroy_MultiLinkControlScreen(void); // called when Legato is destroyed
void screenUpdate_MultiLinkControlScreen(void); // called when Legato is updating

leWidget* screenGetRoot_MultiLinkControlScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void MultiLinkControlScreen_OnShow(void); // called when this screen is shown
void MultiLinkControlScreen_OnHide(void); // called when this screen is hidden
void MultiLinkControlScreen_OnUpdate(void); // called when this screen is updated

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_MULTILINKCONTROLSCREEN_H
