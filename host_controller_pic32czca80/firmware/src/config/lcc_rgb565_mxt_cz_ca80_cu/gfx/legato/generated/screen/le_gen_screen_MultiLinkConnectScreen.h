#ifndef LE_GEN_SCREEN_MULTILINKCONNECTSCREEN_H
#define LE_GEN_SCREEN_MULTILINKCONNECTSCREEN_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* MultiLinkConnectScreen_PanelWidget0;
extern leLineWidget* MultiLinkConnectScreen_LineWidget0;
extern leImageWidget* MultiLinkConnectScreen_ImageWidget0;
extern leImageSequenceWidget* MultiLinkConnectScreen_ImageSequenceWidgetC;
extern leImageSequenceWidget* MultiLinkConnectScreen_ImageSequenceWidgetB;
extern leImageSequenceWidget* MultiLinkConnectScreen_ImageSequenceWidgetA;
extern leImageSequenceWidget* MultiLinkConnectScreen_ProgressAnimSequence;
extern leLabelWidget* MultiLinkConnectScreen_ConnectionStatusLabel;
extern leButtonWidget* MultiLinkConnectScreen_HomeButton;
extern leButtonWidget* MultiLinkConnectScreen_ControlButton;
extern leLabelWidget* MultiLinkConnectScreen_LabelWidget_0;
extern leLabelWidget* MultiLinkConnectScreen_SWallConnectionStatusLabel;
extern leLabelWidget* MultiLinkConnectScreen_LightingWallConnectionStatusLabel;
extern leLabelWidget* MultiLinkConnectScreen_SignalingWallConnectionStatusLabel;
extern leLabelWidget* MultiLinkConnectScreen_LabelWidgetC;
extern leImageWidget* MultiLinkConnectScreen_CheckImageC;
extern leLabelWidget* MultiLinkConnectScreen_LabelWidgetB;
extern leImageWidget* MultiLinkConnectScreen_CheckImageB;
extern leLabelWidget* MultiLinkConnectScreen_LabelWidgetA;
extern leImageWidget* MultiLinkConnectScreen_CheckImageA;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_MultiLinkConnectScreen_HomeButton_OnPressed(leButtonWidget* btn);
void event_MultiLinkConnectScreen_ControlButton_OnPressed(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_MultiLinkConnectScreen(void); // called when Legato is initialized
leResult screenShow_MultiLinkConnectScreen(void); // called when screen is shown
void screenHide_MultiLinkConnectScreen(void); // called when screen is hidden
void screenDestroy_MultiLinkConnectScreen(void); // called when Legato is destroyed
void screenUpdate_MultiLinkConnectScreen(void); // called when Legato is updating

leWidget* screenGetRoot_MultiLinkConnectScreen(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void MultiLinkConnectScreen_OnShow(void); // called when this screen is shown
void MultiLinkConnectScreen_OnHide(void); // called when this screen is hidden
void MultiLinkConnectScreen_OnUpdate(void); // called when this screen is updated

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_MULTILINKCONNECTSCREEN_H
