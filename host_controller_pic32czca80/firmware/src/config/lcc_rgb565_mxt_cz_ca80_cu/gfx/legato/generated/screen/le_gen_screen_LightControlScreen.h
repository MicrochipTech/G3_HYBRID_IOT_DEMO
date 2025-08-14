#ifndef LE_GEN_SCREEN_LIGHTCONTROLSCREEN_H
#define LE_GEN_SCREEN_LIGHTCONTROLSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* LightControlScreen_PanelWidget0;
extern leLineWidget* LightControlScreen_LineWidget0;
extern leImageWidget* LightControlScreen_ImageWidget0;
extern leButtonWidget* LightControlScreen_DisconnectButton;
extern leImageWidget* LightControlScreen_ColorPickerImage;
extern leButtonWidget* LightControlScreen_DeviceCButton;
extern leButtonWidget* LightControlScreen_DeviceBButton;
extern leButtonWidget* LightControlScreen_DeviceAButton;
extern leImageWidget* LightControlScreen_SliderImageWidget;
extern leWidget* LightControlScreen_SliderControlPanel;
extern leImageWidget* LightControlScreen_ScrollKnobImageWidget;
extern leWidget* LightControlScreen_SelectedColorPanelA;
extern leButtonWidget* LightControlScreen_AllDevicesButton;
extern leLabelWidget* LightControlScreen_LabelWidget_0;
extern leWidget* LightControlScreen_SelectedColorPanelB;
extern leWidget* LightControlScreen_SelectedColorPanelC;
extern leWidget* LightControlScreen_DeviceDataPanelA;
extern leLineGraphWidget* LightControlScreen_LineGraphWidget_0;
extern leBarGraphWidget* LightControlScreen_BarGraphWidget_0;
extern leButtonWidget* LightControlScreen_DeviceInfoButton;
extern leButtonWidget* LightControlScreen_BLEInfoButton;
extern leButtonWidget* LightControlScreen_WiFiInfoButton;
extern leWidget* LightControlScreen_ColorWheelSelectColor;
extern leImageSequenceWidget* LightControlScreen_AnimImageWidget;
extern leImageSequenceWidget* LightControlScreen_ImageSequenceWidgetC;
extern leLabelWidget* LightControlScreen_LabelWidget2;
extern leLabelWidget* LightControlScreen_TempLabelC;
extern leImageSequenceWidget* LightControlScreen_ImageSequenceWidgetB;
extern leLabelWidget* LightControlScreen_LabelWidget1;
extern leLabelWidget* LightControlScreen_TempLabelB;
extern leImageSequenceWidget* LightControlScreen_ImageSequenceWidgetA;
extern leLabelWidget* LightControlScreen_LabelWidget0;
extern leLabelWidget* LightControlScreen_TempLabelA;
extern leLabelWidget* LightControlScreen_ColorGraphLabel;
extern leLabelWidget* LightControlScreen_TempSensorGraphLabel;
extern leLabelWidget* LightControlScreen_LineGraphLabelA;
extern leLabelWidget* LightControlScreen_LineGraphLabelB;
extern leLabelWidget* LightControlScreen_LineGraphLabelC;
extern leLabelWidget* LightControlScreen_DeviceInfoLabel;
extern leLabelWidget* LightControlScreen_BLEDeviceAName;
extern leLabelWidget* LightControlScreen_BLEDeviceBName;
extern leLabelWidget* LightControlScreen_BLEDeviceCName;
extern leImageWidget* LightControlScreen_BLEDeviceAOK;
extern leImageWidget* LightControlScreen_BLEDeviceBOK;
extern leImageWidget* LightControlScreen_BLEDeviceCOK;
extern leWidget* LightControlScreen_NetInfoPanel;
extern leWidget* LightControlScreen_PanelWidget_0;
extern leWidget* LightControlScreen_PanelWidget_1;
extern leWidget* LightControlScreen_PanelWidget_2;
extern leLabelWidget* LightControlScreen_NetInfString;
extern leLabelWidget* LightControlScreen_NetSSIDString;
extern leLabelWidget* LightControlScreen_NetIPString;
extern leLabelWidget* LightControlScreen_NetConnString;
extern leLabelWidget* LightControlScreen_NetURLString;
extern leImageWidget* LightControlScreen_NetWebURLQR;
extern leLabelWidget* LightControlScreen_NetInterfaceInfo;
extern leLabelWidget* LightControlScreen_NetSSIDInfo;
extern leLabelWidget* LightControlScreen_NetIPInfo;
extern leLabelWidget* LightControlScreen_NetConnInfo;
extern leLabelWidget* LightControlScreen_NetURLInfo;
extern leWidget* LightControlScreen_MfgBlock;
extern leWidget* LightControlScreen_BldgBlock;
extern leWidget* LightControlScreen_EnergyBlock;
extern leWidget* LightControlScreen_EnvBlock;
extern leWidget* LightControlScreen_AgriBlock;
extern leWidget* LightControlScreen_LogiBlock;
extern leWidget* LightControlScreen_HomeAutoBlock;
extern leWidget* LightControlScreen_SmartCityBlock;
extern leWidget* LightControlScreen_SmartConSecLogoBlock;
extern leWidget* LightControlScreen_SmartBlock;
extern leWidget* LightControlScreen_ConnectedBlock;
extern leWidget* LightControlScreen_SecureBlock;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_LightControlScreen_DisconnectButton_OnPressed(leButtonWidget* btn);
void event_LightControlScreen_DeviceCButton_OnPressed(leButtonWidget* btn);
void event_LightControlScreen_DeviceBButton_OnPressed(leButtonWidget* btn);
void event_LightControlScreen_DeviceAButton_OnPressed(leButtonWidget* btn);
void event_LightControlScreen_AllDevicesButton_OnPressed(leButtonWidget* btn);
void event_LightControlScreen_AllDevicesButton_OnReleased(leButtonWidget* btn);
void event_LightControlScreen_DeviceInfoButton_OnPressed(leButtonWidget* btn);
void event_LightControlScreen_BLEInfoButton_OnPressed(leButtonWidget* btn);
void event_LightControlScreen_WiFiInfoButton_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_LightControlScreen(void); // called when Legato is initialized
leResult screenShow_LightControlScreen(void); // called when screen is shown
void screenHide_LightControlScreen(void); // called when screen is hidden
void screenDestroy_LightControlScreen(void); // called when Legato is destroyed
void screenUpdate_LightControlScreen(void); // called when Legato is updating

leWidget* screenGetRoot_LightControlScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void LightControlScreen_OnShow(void); // called when this screen is shown
void LightControlScreen_OnHide(void); // called when this screen is hidden
void LightControlScreen_OnUpdate(void); // called when this screen is updated

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_LIGHTCONTROLSCREEN_H
