#ifndef LE_GEN_SCREEN_SWALLCONTROLSCREEN_H
#define LE_GEN_SCREEN_SWALLCONTROLSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* SWallControlScreen_Panel_0;
extern leWidget* SWallControlScreen_PanelWidget0;
extern leLineWidget* SWallControlScreen_LineWidget0;
extern leImageWidget* SWallControlScreen_ImageWidget0;
extern leLabelWidget* SWallControlScreen_LabelWidget_0;
extern leButtonWidget* SWallControlScreen_DeviceAButton;
extern leLabelWidget* SWallControlScreen_SolarInverterStatusLabel;
extern leLabelWidget* SWallControlScreen_SolarInverterStatusLabel_0;
extern leLabelWidget* SWallControlScreen_BatteryChargerStatusLabel;
extern leLabelWidget* SWallControlScreen_LeakDetectorStatusLabel;
extern leLabelWidget* SWallControlScreen_EnergyStorageStatusLabel;
extern leLabelWidget* SWallControlScreen_HeatPumpStatusLabel;
extern leLabelWidget* SWallControlScreen_EVChargerStatusLabel;
extern leProgressBarWidget* SWallControlScreen_EVChargerProgressBarWidget;
extern leProgressBarWidget* SWallControlScreen_StorageProgressBarWidget;
extern leProgressBarWidget* SWallControlScreen_BatteryProgressBarWidget;
extern leButtonWidget* SWallControlScreen_BatteryChargerRefreshButtonWidget;
extern leButtonWidget* SWallControlScreen_EnergyStorageRefreshButtonWidget;
extern leButtonWidget* SWallControlScreen_EVChargerRefreshButtonWidget;
extern leButtonWidget* SWallControlScreen_SolarInverterRefreshButtonWidget;
extern leButtonWidget* SWallControlScreen_LeakDetectorRefreshButtonWidget;
extern leButtonWidget* SWallControlScreen_HeatPumpRefreshButtonWidget;
extern leTextFieldWidget* SWallControlScreen_SolarInverterTextFieldWidget;
extern leTextFieldWidget* SWallControlScreen_LeakDetectorTextFieldWidget;
extern leTextFieldWidget* SWallControlScreen_HeatPumpTextFieldWidget;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_SWallControlScreen_DeviceAButton_OnPressed(leButtonWidget* btn);
void event_SWallControlScreen_BatteryChargerRefreshButtonWidget_OnPressed(leButtonWidget* btn);
void event_SWallControlScreen_EnergyStorageRefreshButtonWidget_OnPressed(leButtonWidget* btn);
void event_SWallControlScreen_EVChargerRefreshButtonWidget_OnPressed(leButtonWidget* btn);
void event_SWallControlScreen_SolarInverterRefreshButtonWidget_OnPressed(leButtonWidget* btn);
void event_SWallControlScreen_LeakDetectorRefreshButtonWidget_OnPressed(leButtonWidget* btn);
void event_SWallControlScreen_HeatPumpRefreshButtonWidget_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_SWallControlScreen(void); // called when Legato is initialized
leResult screenShow_SWallControlScreen(void); // called when screen is shown
void screenHide_SWallControlScreen(void); // called when screen is hidden
void screenDestroy_SWallControlScreen(void); // called when Legato is destroyed
void screenUpdate_SWallControlScreen(void); // called when Legato is updating

leWidget* screenGetRoot_SWallControlScreen(uint32_t lyrIdx); // gets a root widget for this screen

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_SWALLCONTROLSCREEN_H
