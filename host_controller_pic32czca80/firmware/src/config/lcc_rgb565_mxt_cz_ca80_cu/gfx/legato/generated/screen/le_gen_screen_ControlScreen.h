#ifndef LE_GEN_SCREEN_CONTROLSCREEN_H
#define LE_GEN_SCREEN_CONTROLSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* ControlScreen_PanelWidget0;
extern leLineWidget* ControlScreen_LineWidget0;
extern leImageWidget* ControlScreen_ImageWidget0;
extern leButtonWidget* ControlScreen_DisconnectButton;
extern leImageWidget* ControlScreen_ColorPickerImage;
extern leButtonWidget* ControlScreen_DeviceCButton;
extern leButtonWidget* ControlScreen_DeviceBButton;
extern leButtonWidget* ControlScreen_DeviceAButton;
extern leImageWidget* ControlScreen_SliderImageWidget;
extern leWidget* ControlScreen_SliderControlPanel;
extern leImageWidget* ControlScreen_ScrollKnobImageWidget;
extern leWidget* ControlScreen_SelectedColorPanelA;
extern leButtonWidget* ControlScreen_AllDevicesButton;
extern leLabelWidget* ControlScreen_LabelWidget_0;
extern leWidget* ControlScreen_SelectedColorPanelB;
extern leWidget* ControlScreen_SelectedColorPanelC;
extern leWidget* ControlScreen_DeviceDataPanelA;
extern leLineGraphWidget* ControlScreen_LineGraphWidget_0;
extern leBarGraphWidget* ControlScreen_BarGraphWidget_0;
extern leButtonWidget* ControlScreen_DeviceInfoButton;
extern leButtonWidget* ControlScreen_BLEInfoButton;
extern leButtonWidget* ControlScreen_WiFiInfoButton;
extern leWidget* ControlScreen_ColorWheelSelectColor;
extern leImageSequenceWidget* ControlScreen_AnimImageWidget;
extern leImageSequenceWidget* ControlScreen_ImageSequenceWidgetC;
extern leLabelWidget* ControlScreen_LabelWidget2;
extern leLabelWidget* ControlScreen_TempLabelC;
extern leImageSequenceWidget* ControlScreen_ImageSequenceWidgetB;
extern leLabelWidget* ControlScreen_LabelWidget1;
extern leLabelWidget* ControlScreen_TempLabelB;
extern leImageSequenceWidget* ControlScreen_ImageSequenceWidgetA;
extern leLabelWidget* ControlScreen_LabelWidget0;
extern leLabelWidget* ControlScreen_TempLabelA;
extern leLabelWidget* ControlScreen_ColorGraphLabel;
extern leLabelWidget* ControlScreen_TempSensorGraphLabel;
extern leLabelWidget* ControlScreen_LineGraphLabelA;
extern leLabelWidget* ControlScreen_LineGraphLabelB;
extern leLabelWidget* ControlScreen_LineGraphLabelC;
extern leLabelWidget* ControlScreen_DeviceInfoLabel;
extern leLabelWidget* ControlScreen_BLEDeviceAName;
extern leLabelWidget* ControlScreen_BLEDeviceBName;
extern leLabelWidget* ControlScreen_BLEDeviceCName;
extern leImageWidget* ControlScreen_BLEDeviceAOK;
extern leImageWidget* ControlScreen_BLEDeviceBOK;
extern leImageWidget* ControlScreen_BLEDeviceCOK;
extern leWidget* ControlScreen_NetInfoPanel;
extern leWidget* ControlScreen_PanelWidget_0;
extern leWidget* ControlScreen_PanelWidget_1;
extern leWidget* ControlScreen_PanelWidget_2;
extern leLabelWidget* ControlScreen_NetInfString;
extern leLabelWidget* ControlScreen_NetSSIDString;
extern leLabelWidget* ControlScreen_NetIPString;
extern leLabelWidget* ControlScreen_NetConnString;
extern leLabelWidget* ControlScreen_NetURLString;
extern leImageWidget* ControlScreen_NetWebURLQR;
extern leLabelWidget* ControlScreen_NetInterfaceInfo;
extern leLabelWidget* ControlScreen_NetSSIDInfo;
extern leLabelWidget* ControlScreen_NetIPInfo;
extern leLabelWidget* ControlScreen_NetConnInfo;
extern leLabelWidget* ControlScreen_NetURLInfo;
extern leWidget* ControlScreen_MfgBlock;
extern leWidget* ControlScreen_BldgBlock;
extern leWidget* ControlScreen_EnergyBlock;
extern leWidget* ControlScreen_EnvBlock;
extern leWidget* ControlScreen_AgriBlock;
extern leWidget* ControlScreen_LogiBlock;
extern leWidget* ControlScreen_HomeAutoBlock;
extern leWidget* ControlScreen_SmartCityBlock;
extern leWidget* ControlScreen_SmartConSecLogoBlock;
extern leWidget* ControlScreen_SmartBlock;
extern leWidget* ControlScreen_ConnectedBlock;
extern leWidget* ControlScreen_SecureBlock;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_ControlScreen_DisconnectButton_OnPressed(leButtonWidget* btn);
void event_ControlScreen_DeviceCButton_OnPressed(leButtonWidget* btn);
void event_ControlScreen_DeviceBButton_OnPressed(leButtonWidget* btn);
void event_ControlScreen_DeviceAButton_OnPressed(leButtonWidget* btn);
void event_ControlScreen_AllDevicesButton_OnPressed(leButtonWidget* btn);
void event_ControlScreen_AllDevicesButton_OnReleased(leButtonWidget* btn);
void event_ControlScreen_DeviceInfoButton_OnPressed(leButtonWidget* btn);
void event_ControlScreen_BLEInfoButton_OnPressed(leButtonWidget* btn);
void event_ControlScreen_WiFiInfoButton_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_ControlScreen(void); // called when Legato is initialized
leResult screenShow_ControlScreen(void); // called when screen is shown
void screenHide_ControlScreen(void); // called when screen is hidden
void screenDestroy_ControlScreen(void); // called when Legato is destroyed
void screenUpdate_ControlScreen(void); // called when Legato is updating

leWidget* screenGetRoot_ControlScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void ControlScreen_OnShow(void); // called when this screen is shown
void ControlScreen_OnHide(void); // called when this screen is hidden
void ControlScreen_OnUpdate(void); // called when this screen is updated

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_CONTROLSCREEN_H
