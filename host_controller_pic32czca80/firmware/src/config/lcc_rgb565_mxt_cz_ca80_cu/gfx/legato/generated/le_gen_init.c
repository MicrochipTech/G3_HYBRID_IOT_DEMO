#include "gfx/legato/generated/le_gen_init.h"

static int32_t currentScreen;
static int32_t changingToScreen;

void legato_initializeScreenState(void)
{
    leSetStringTable(&stringTable);

    initializeStrings();

    screenInit_MainMenu();
    screenInit_MultiLinkControlScreen();
    screenInit_MultiLinkConnectScreen();

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
        case screenID_MainMenu:
        {
            screenHide_MainMenu();
            currentScreen = 0;
            break;
        }
        case screenID_MultiLinkControlScreen:
        {
            screenHide_MultiLinkControlScreen();
            currentScreen = 0;
            break;
        }
        case screenID_MultiLinkConnectScreen:
        {
            screenHide_MultiLinkConnectScreen();
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
    if(changingToScreen >= 0)
    {
        legato_hideCurrentScreen();

        switch(changingToScreen)
        {
            case screenID_MainMenu:
            {
                screenShow_MainMenu();
                break;
            }
            case screenID_MultiLinkControlScreen:
            {
                screenShow_MultiLinkControlScreen();
                break;
            }
            case screenID_MultiLinkConnectScreen:
            {
                screenShow_MultiLinkConnectScreen();
                break;
            }
        }

        currentScreen = changingToScreen;
        changingToScreen = -1;
    }

    switch(currentScreen)
    {
        case screenID_MainMenu:
        {
            screenUpdate_MainMenu();
            break;
        }
        case screenID_MultiLinkControlScreen:
        {
            screenUpdate_MultiLinkControlScreen();
            break;
        }
        case screenID_MultiLinkConnectScreen:
        {
            screenUpdate_MultiLinkConnectScreen();
            break;
        }
    }
}

leBool legato_isChangingScreens(void)
{
    return changingToScreen != -1;
}

