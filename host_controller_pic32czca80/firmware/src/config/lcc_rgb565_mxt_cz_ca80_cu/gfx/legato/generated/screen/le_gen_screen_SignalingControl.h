#ifndef LE_GEN_SCREEN_SIGNALINGCONTROL_H
#define LE_GEN_SCREEN_SIGNALINGCONTROL_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* SignalingControl_Panel_0;
extern leWidget* SignalingControl_PanelWidget0;
extern leLineWidget* SignalingControl_LineWidget0_0;
extern leImageWidget* SignalingControl_ImageMicrochipWidget;
extern leImageWidget* SignalingControl_CloudWidget;
extern leImageWidget* SignalingControl_WifiWidget;
extern leLabelWidget* SignalingControl_PanelLedStatusLabel;
extern leLabelWidget* SignalingControl_EmergencyButtonStatusLabel;
extern leButtonWidget* SignalingControl_PanelLedRefreshButtonWidget;
extern leButtonWidget* SignalingControl_EmergencyButtonRefreshButtonWidget;
extern leButtonWidget* SignalingControl_NextSignalingButtonWidget;
extern leImageWidget* SignalingControl_PanelLedConnIcon;
extern leImageWidget* SignalingControl_EmergencyButtonConnIcon;
extern leButtonWidget* SignalingControl_SignalingAlarmOnOffButtonWidget;
extern leLabelWidget* SignalingControl_LightingOutdoorOffStatusLabel;
extern leLabelWidget* SignalingControl_LightingOutdoorOnStatusLabel;
extern leImageWidget* SignalingControl_G3Widget;
extern leImageWidget* SignalingControl_AlarmWidget;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_SignalingControl_PanelLedRefreshButtonWidget_OnPressed(leButtonWidget* btn);
void event_SignalingControl_EmergencyButtonRefreshButtonWidget_OnPressed(leButtonWidget* btn);
void event_SignalingControl_NextSignalingButtonWidget_OnPressed(leButtonWidget* btn);
void event_SignalingControl_SignalingAlarmOnOffButtonWidget_OnPressed(leButtonWidget* btn);
void event_SignalingControl_SignalingAlarmOnOffButtonWidget_OnReleased(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_SignalingControl(void); // called when Legato is initialized
leResult screenShow_SignalingControl(void); // called when screen is shown
void screenHide_SignalingControl(void); // called when screen is hidden
void screenDestroy_SignalingControl(void); // called when Legato is destroyed
void screenUpdate_SignalingControl(void); // called when Legato is updating

leWidget* screenGetRoot_SignalingControl(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void SignalingControl_OnShow(void); // called when this screen is shown
void SignalingControl_OnHide(void); // called when this screen is hidden
void SignalingControl_OnUpdate(void); // called when this screen is updated

#define SignalingControl_OnShow() APP_SCREEN_SIGNALING_OnShow()
#define SignalingControl_OnUpdate() APP_SCREEN_SIGNALING_OnUpdate()
#define SignalingControl_OnHide() APP_SCREEN_SIGNALING_OnHide()

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_SIGNALINGCONTROL_H
