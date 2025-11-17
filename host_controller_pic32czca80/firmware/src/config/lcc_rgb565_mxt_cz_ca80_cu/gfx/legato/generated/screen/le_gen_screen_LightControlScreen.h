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
extern leWidget* LightControlScreen_Panel_0;
extern leLabelWidget* LightControlScreen_LabelWidget_0;
extern leImageWidget* LightControlScreen_ImageWidget0;
extern leLineWidget* LightControlScreen_LineWidget0;
extern leWidget* LightControlScreen_PanelWidget0;
extern leLabelWidget* LightControlScreen_LabelSmartLighting;
extern leLineWidget* LightControlScreen_LineWidget0_0;
extern leImageWidget* LightControlScreen_ImageMicrochipWidget;
extern leLabelWidget* LightControlScreen_LightingIndoorStatusLabel;
extern leLabelWidget* LightControlScreen_LightingOutdoorStatusLabel;
extern leButtonWidget* LightControlScreen_LightingIndoorRefreshButtonWidget;
extern leButtonWidget* LightControlScreen_LightingOutdoorRefreshButtonWidget;
extern leButtonWidget* LightControlScreen_LightingOutdoorOnOffButtonWidget;
extern leLabelWidget* LightControlScreen_LightingOutdoorOnStatusLabel;
extern leLabelWidget* LightControlScreen_LightingOutdoorOffStatusLabel;
extern leLabelWidget* LightControlScreen_LightingIndoorOffStatusLabel;
extern leLabelWidget* LightControlScreen_LightingIndoorOnStatusLabel;
extern leButtonWidget* LightControlScreen_NextLightingButtonWidget;
extern leLabelWidget* LightControlScreen_NextLightingStatusLabel;
extern leButtonWidget* LightControlScreen_LightingIndoorOnOffButtonWidget;
extern leImageWidget* LightControlScreen_LightingIndoorConnIcon;
extern leImageWidget* LightControlScreen_LightingOutdoorConnIcon;
extern leImageWidget* LightControlScreen_CloudWidget;
extern leImageWidget* LightControlScreen_WifiWidget;
extern leImageWidget* LightControlScreen_G3Widget;
extern leImageWidget* LightControlScreen_AlarmWidget;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_LightControlScreen_LightingIndoorRefreshButtonWidget_OnPressed(leButtonWidget* btn);
void event_LightControlScreen_LightingOutdoorRefreshButtonWidget_OnPressed(leButtonWidget* btn);
void event_LightControlScreen_LightingOutdoorOnOffButtonWidget_OnPressed(leButtonWidget* btn);
void event_LightControlScreen_LightingOutdoorOnOffButtonWidget_OnReleased(leButtonWidget* btn);
void event_LightControlScreen_NextLightingButtonWidget_OnPressed(leButtonWidget* btn);
void event_LightControlScreen_LightingIndoorOnOffButtonWidget_OnPressed(leButtonWidget* btn);
void event_LightControlScreen_LightingIndoorOnOffButtonWidget_OnReleased(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_LightControlScreen(void); // called when Legato is initialized
leResult screenShow_LightControlScreen(void); // called when screen is shown
void screenHide_LightControlScreen(void); // called when screen is hidden
void screenDestroy_LightControlScreen(void); // called when Legato is destroyed
void screenUpdate_LightControlScreen(void); // called when Legato is updating

leWidget* screenGetRoot_LightControlScreen(uint32_t lyrIdx); // gets a root widget for this screen

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_LIGHTCONTROLSCREEN_H
