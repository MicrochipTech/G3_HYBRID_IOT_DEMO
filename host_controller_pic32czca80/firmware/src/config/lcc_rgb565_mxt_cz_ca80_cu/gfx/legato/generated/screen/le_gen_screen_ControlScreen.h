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
extern leWidget* ControlScreen_Panel_0;
extern leWidget* ControlScreen_ColorWheelSelectColor;
extern leButtonWidget* ControlScreen_WiFiInfoButton;
extern leButtonWidget* ControlScreen_BLEInfoButton;
extern leButtonWidget* ControlScreen_DeviceInfoButton;
extern leWidget* ControlScreen_SelectedColorPanelC;
extern leWidget* ControlScreen_SelectedColorPanelB;
extern leLabelWidget* ControlScreen_LabelWidget_0;
extern leButtonWidget* ControlScreen_AllDevicesButton;
extern leWidget* ControlScreen_SelectedColorPanelA;
extern leImageWidget* ControlScreen_ScrollKnobImageWidget;
extern leWidget* ControlScreen_SliderControlPanel;
extern leImageWidget* ControlScreen_SliderImageWidget;
extern leLabelWidget* ControlScreen_TempLabelA;
extern leLabelWidget* ControlScreen_LabelWidget0;
extern leButtonWidget* ControlScreen_DeviceAButton;
extern leLabelWidget* ControlScreen_TempLabelB;
extern leLabelWidget* ControlScreen_LabelWidget1;
extern leButtonWidget* ControlScreen_DeviceBButton;
extern leLabelWidget* ControlScreen_TempLabelC;
extern leLabelWidget* ControlScreen_LabelWidget2;
extern leButtonWidget* ControlScreen_DeviceCButton;
extern leImageWidget* ControlScreen_ColorPickerImage;
extern leButtonWidget* ControlScreen_DisconnectButton;
extern leImageWidget* ControlScreen_ImageWidget0;
extern leLineWidget* ControlScreen_LineWidget0;
extern leWidget* ControlScreen_PanelWidget0;
extern leLabelWidget* ControlScreen_LabelWidget_0_0;
extern leLineWidget* ControlScreen_LineWidget0_0;
extern leImageWidget* ControlScreen_ImageWidget0_0;
extern leButtonWidget* ControlScreen_WiFiInfoButton_0;
extern leButtonWidget* ControlScreen_BLEInfoButton_0;
extern leButtonWidget* ControlScreen_DeviceInfoButton_0;
extern leImageSequenceWidget* ControlScreen_AnimImageWidget;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_ControlScreen_WiFiInfoButton_OnPressed(leButtonWidget* btn);
void event_ControlScreen_BLEInfoButton_OnPressed(leButtonWidget* btn);
void event_ControlScreen_DeviceInfoButton_OnPressed(leButtonWidget* btn);
void event_ControlScreen_AllDevicesButton_OnPressed(leButtonWidget* btn);
void event_ControlScreen_AllDevicesButton_OnReleased(leButtonWidget* btn);
void event_ControlScreen_DeviceAButton_OnPressed(leButtonWidget* btn);
void event_ControlScreen_DeviceBButton_OnPressed(leButtonWidget* btn);
void event_ControlScreen_DeviceCButton_OnPressed(leButtonWidget* btn);
void event_ControlScreen_DisconnectButton_OnPressed(leButtonWidget* btn);
void event_ControlScreen_WiFiInfoButton_OnPressed(leButtonWidget* btn);
void event_ControlScreen_BLEInfoButton_OnPressed(leButtonWidget* btn);
void event_ControlScreen_DeviceInfoButton_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_ControlScreen(void); // called when Legato is initialized
leResult screenShow_ControlScreen(void); // called when screen is shown
void screenHide_ControlScreen(void); // called when screen is hidden
void screenDestroy_ControlScreen(void); // called when Legato is destroyed
void screenUpdate_ControlScreen(void); // called when Legato is updating

leWidget* screenGetRoot_ControlScreen(uint32_t lyrIdx); // gets a root widget for this screen

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_CONTROLSCREEN_H
