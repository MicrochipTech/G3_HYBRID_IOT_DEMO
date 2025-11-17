#ifndef LE_GEN_SCREEN_MAINMENU_H
#define LE_GEN_SCREEN_MAINMENU_H

#include "gfx/legato/legato.h"

#include "gfx/legato/generated/le_gen_scheme.h"
#include "gfx/legato/generated/le_gen_assets.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
// DOM-IGNORE-END

// screen member widget declarations
extern leWidget* MainMenu_BackPanel;
extern leLabelWidget* MainMenu_LabelWidget0;
extern leLineWidget* MainMenu_LineWidget0;
extern leImageWidget* MainMenu_ImageWidget0;
extern leButtonWidget* MainMenu_ConnectButton;
extern leButtonWidget* MainMenu_ControlButton;
extern leButtonWidget* MainMenu_ConfigButton;
extern leImageWidget* MainMenu_ImageWidget_0;
extern leLabelWidget* MainMenu_LabelWidget1;
extern leLabelWidget* MainMenu_ControlLabel;

// event handlers
// !!THESE MUST BE IMPLEMENTED IN THE APPLICATION CODE!!
void event_MainMenu_ConnectButton_OnPressed(leButtonWidget* btn);
void event_MainMenu_ConnectButton_OnReleased(leButtonWidget* btn);
void event_MainMenu_ControlButton_OnReleased(leButtonWidget* btn);
void event_MainMenu_ConfigButton_OnReleased(leButtonWidget* btn);

// screen lifecycle functions
// DO NOT CALL THESE DIRECTLY
leResult screenInit_MainMenu(void); // called when Legato is initialized
leResult screenShow_MainMenu(void); // called when screen is shown
void screenHide_MainMenu(void); // called when screen is hidden
void screenDestroy_MainMenu(void); // called when Legato is destroyed
void screenUpdate_MainMenu(void); // called when Legato is updating

leWidget* screenGetRoot_MainMenu(uint32_t lyrIdx); // gets a root widget for this screen

// Screen Events:
void MainMenu_OnShow(void); // called when this screen is shown
void MainMenu_OnHide(void); // called when this screen is hidden
void MainMenu_OnUpdate(void); // called when this screen is updated

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // LE_GEN_SCREEN_MAINMENU_H
