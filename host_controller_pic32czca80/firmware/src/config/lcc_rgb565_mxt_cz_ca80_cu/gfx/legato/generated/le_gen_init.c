#include "gfx/legato/generated/le_gen_init.h"

static int32_t currentScreen;
static int32_t changingToScreen;

void legato_initializeScreenState(void)
{
    leSetStringTable(&stringTable);

    initializeStrings();

    screenInit_LightControlScreen();
    screenInit_MainMenu();
    screenInit_MultiLinkConnectScreen();
    screenInit_SWallControlScreen();
    screenInit_ControlScreen();

    currentScreen = -1;
    changingToScreen = -1;

    legato_showScreen(screenID_MainMenu);
}

uint32_t legato_getCurrentScreen(void)
{
    return currentScreen;
}

static void legato_hideCurrentScreen(void)
{
    switch(currentScreen)
    {
        case screenID_LightControlScreen:
        {
            screenHide_LightControlScreen();
            currentScreen = 0;
            break;
        }
        case screenID_MainMenu:
        {
            screenHide_MainMenu();
            currentScreen = 0;
            break;
        }
        case screenID_MultiLinkConnectScreen:
        {
            screenHide_MultiLinkConnectScreen();
            currentScreen = 0;
            break;
        }
        case screenID_SWallControlScreen:
        {
            screenHide_SWallControlScreen();
            currentScreen = 0;
            break;
        }
        case screenID_ControlScreen:
        {
            screenHide_ControlScreen();
            currentScreen = 0;
            break;
        }
    }
}

void legato_showScreen(uint32_t id)
{
    if(changingToScreen >= 0)
        return;

    changingToScreen = id;
}

void legato_updateScreenState(void)
{
    if(leIsDrawing() == LE_TRUE)
        return;

    if(changingToScreen >= 0)
    {
        legato_hideCurrentScreen();

        switch(changingToScreen)
        {
            case screenID_LightControlScreen:
            {
                screenShow_LightControlScreen();
                break;
            }
            case screenID_MainMenu:
            {
                screenShow_MainMenu();
                break;
            }
            case screenID_MultiLinkConnectScreen:
            {
                screenShow_MultiLinkConnectScreen();
                break;
            }
            case screenID_SWallControlScreen:
            {
                screenShow_SWallControlScreen();
                break;
            }
            case screenID_ControlScreen:
            {
                screenShow_ControlScreen();
                break;
            }
        }

        currentScreen = changingToScreen;
        changingToScreen = -1;
    }

    switch(currentScreen)
    {
        case screenID_LightControlScreen:
        {
            screenUpdate_LightControlScreen();
            break;
        }
        case screenID_MainMenu:
        {
            screenUpdate_MainMenu();
            break;
        }
        case screenID_MultiLinkConnectScreen:
        {
            screenUpdate_MultiLinkConnectScreen();
            break;
        }
        case screenID_SWallControlScreen:
        {
            screenUpdate_SWallControlScreen();
            break;
        }
        case screenID_ControlScreen:
        {
            screenUpdate_ControlScreen();
            break;
        }
    }
}

leBool legato_isChangingScreens(void)
{
    return changingToScreen != -1;
}

