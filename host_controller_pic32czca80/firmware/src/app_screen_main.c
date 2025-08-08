/*******************************************************************************
* Copyright (C) 2023 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#include "definitions.h"
#include "app_config.h"
#include "app_ui.h"

#define ANIM_BUTTON_HIDE_Y 480
#define ANIM_BUTTON_SHOW_Y 194
#define ANIM_BUTTON_COEFF 4

#define ANIM_TITLE_HIDE_X 480
#define ANIM_TITLE_SHOW_X 50

typedef enum
{
    APP_SCREEN_MAIN_INIT,
    APP_SCREEN_MAIN_ANIM1,
    APP_SCREEN_MAIN_ANIM2,
    APP_SCREEN_MAIN_ANIM3,
    APP_SCREEN_MAIN_ANIM4,
    APP_SCREEN_MAIN_PROCESS,
    APP_SCREEN_MAIN_EXIT_ANIM1,
    APP_SCREEN_MAIN_EXIT_ANIM2,
    APP_SCREEN_MAIN_EXIT_ANIM3,
} APP_SCREEN_MAIN_STATE;

APP_SCREEN_MAIN_STATE mainScreenState = APP_SCREEN_MAIN_INIT;
static SYS_TIME_HANDLE mainAnimTimer = SYS_TIME_HANDLE_INVALID;
static volatile uint32_t mainAnimTickCount = 0;
static uint32_t mainAnimTickPrev = 0;


static void MainTimer_Callback (uintptr_t context)
{
    mainAnimTickCount++;
}


void event_MainMenu_ConnectButton_OnPressed(leButtonWidget* btn)
{
    
}

void event_MainMenu_ConnectButton_OnReleased(leButtonWidget* btn)
{
    if (mainScreenState == APP_SCREEN_MAIN_PROCESS)
    {
        mainScreenState = APP_SCREEN_MAIN_EXIT_ANIM1;
    }
}

void event_MainMenu_ControlButton_OnReleased(leButtonWidget* btn)
{
    
}

void event_MainMenu_ConfigButton_OnPressed(leButtonWidget* btn)
{
    
}

void event_MainMenu_ConfigButton_OnReleased(leButtonWidget* btn)
{
    
}

void MainMenu_OnShow(void)
{
    mainScreenState = APP_SCREEN_MAIN_INIT;
    
    mainAnimTickCount = 0;
    mainAnimTimer = SYS_TIME_CallbackRegisterMS(MainTimer_Callback, 1, ANIM_TIMER_TICK_PERIOD_MS, SYS_TIME_PERIODIC);   
    SYS_TIME_TimerStop(mainAnimTimer);
    
    MainMenu_LabelWidget0->fn->setVisible(MainMenu_LabelWidget0, LE_FALSE);
    
    MainMenu_LabelWidget1->fn->setVisible(MainMenu_LabelWidget1, LE_FALSE);
    MainMenu_ControlLabel->fn->setVisible(MainMenu_ControlLabel, LE_FALSE);
    MainMenu_ConfigButton->fn->setVisible(MainMenu_ConfigButton, LE_FALSE);
    
    MainMenu_ConnectButton->fn->setY(MainMenu_ConnectButton, ANIM_BUTTON_HIDE_Y);
    MainMenu_ConnectButton->fn->setY(MainMenu_ConnectButton, ANIM_BUTTON_HIDE_Y);
    
}

void MainMenu_OnHide(void)
{
    SYS_TIME_TimerDestroy(mainAnimTimer);
}

void MainMenu_OnUpdate(void)
{
    switch(mainScreenState)
    {
        case APP_SCREEN_MAIN_INIT:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;
            
            SYS_TIME_TimerStart(mainAnimTimer);
                
            mainScreenState = APP_SCREEN_MAIN_ANIM1;
            
            break;
        }
        case APP_SCREEN_MAIN_ANIM1:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;
            
            MainMenu_LabelWidget0->fn->setVisible(MainMenu_LabelWidget0, LE_TRUE);
            mainScreenState = APP_SCREEN_MAIN_ANIM2;
            
            break;
        }
        case APP_SCREEN_MAIN_ANIM2:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;
            
            if (mainAnimTickPrev != mainAnimTickCount)
            {
                int y = MainMenu_ConnectButton->fn->getY(MainMenu_ConnectButton);
                int deltaY = (y - ANIM_BUTTON_SHOW_Y) / ANIM_BUTTON_COEFF;

                if (deltaY > 0)
                {
                    MainMenu_ConnectButton->fn->setY(MainMenu_ConnectButton, y - deltaY);
                }
                else
                {
                    MainMenu_ConnectButton->fn->setY(MainMenu_ConnectButton, ANIM_BUTTON_SHOW_Y);

                    mainScreenState = APP_SCREEN_MAIN_ANIM4;
                }
            }
          

            break;
        }
        case APP_SCREEN_MAIN_ANIM4:
        {
            SYS_TIME_TimerStop(mainAnimTimer);

            mainScreenState = APP_SCREEN_MAIN_PROCESS;
            
            //FIXME ADD DELAY
//            vTaskDelay(4000 / portTICK_PERIOD_MS);;
            
            MainMenu_LabelWidget1->fn->setVisible(MainMenu_LabelWidget1, LE_TRUE);                    

            break;
        }
        case APP_SCREEN_MAIN_PROCESS:
        {
            break;
        }
        case APP_SCREEN_MAIN_EXIT_ANIM1:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;
            
            MainMenu_LabelWidget1->fn->setVisible(MainMenu_LabelWidget1, LE_FALSE);   
            SYS_TIME_TimerStart(mainAnimTimer);
            
            mainScreenState = APP_SCREEN_MAIN_EXIT_ANIM2;
                     
            break;
        }        
        case APP_SCREEN_MAIN_EXIT_ANIM2:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;
            
            if (mainAnimTickPrev != mainAnimTickCount)
            {
                int y = MainMenu_ConnectButton->fn->getY(MainMenu_ConnectButton);
                int deltaY = (ANIM_BUTTON_HIDE_Y - y) / ANIM_BUTTON_COEFF;

                if (deltaY > 0)
                {
                    MainMenu_ConnectButton->fn->setY(MainMenu_ConnectButton, y + deltaY);
                }
                else
                {
//                    MainMenu_LabelWidget0->fn->setVisible(MainMenu_LabelWidget0, LE_FALSE);                    
                    MainMenu_ConnectButton->fn->setY(MainMenu_ConnectButton, ANIM_BUTTON_HIDE_Y);
                    
                    SYS_TIME_TimerStop(mainAnimTimer);
                    
                    mainScreenState = APP_SCREEN_MAIN_EXIT_ANIM3;
                }
                
                mainAnimTickPrev = mainAnimTickCount;
            }
                    
            break;
        }        
        case APP_SCREEN_MAIN_EXIT_ANIM3:
        {
            if(leRenderer_IsIdle() != LE_TRUE)
                break;            
            
            legato_showScreen(screenID_MultiLinkConnectScreen);
            
            mainScreenState = APP_SCREEN_MAIN_INIT;
                     
            break;
        }
        default:
        {
            break;
        }
    }
}
