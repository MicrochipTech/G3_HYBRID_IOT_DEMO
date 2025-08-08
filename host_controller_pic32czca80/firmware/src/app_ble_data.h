/* 
 * File:   app_ble_data.h
 * Author: C18797
 *
 * Created on July 20, 2022, 2:51 PM
 */

#ifndef APP_BLE_DATA_H
#define	APP_BLE_DATA_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MIN_NOTIF_PACKET_SIZE 22    
#define NUM_DEMO_DEVICES 2
#define DEVICE_ADDR_SIZE 12
#define DEVICE_NAME_SIZE 31
#define MAX_DEVICE_LIST 31
#define DEFAULT_DEVICE_TEMP_VALUE_C 40
#define DEFAULT_DEVICE_TEMP_VALUE_F 104
    
typedef enum
{
    APP_BLE_DEVICE_A,
    APP_BLE_DEVICE_B,
    APP_BLE_DEVICE_C,
    APP_BLE_DEVICE_ALL,
    APP_BLE_DEVICE_MAX = APP_BLE_DEVICE_ALL,
} APP_BLE_DEVICE_ID;
    
typedef enum
{
    CELS,
    FAHR,
} APP_BLE_DEVICE_TEMP_UNIT;

typedef enum
{
    NOTIF_LED,
    NOTIF_TEMP,
    NOTIF_INVALID,
} APP_BLE_NOTIF_TYPE;

typedef struct
{
    uint32_t idx;
    bool valid;
    char deviceAddress[DEVICE_ADDR_SIZE + 1];
    char deviceName[DEVICE_NAME_SIZE + 1];
    
    bool active;
    bool connected;
    char connHandleStr[5];
    char ctrlHandleStr[5];
    uint32_t tempSensorValue;
    uint32_t rgb888;
    struct
    {
        uint8_t r;
        uint8_t s;
        uint8_t v;
        uint8_t onoff;
    } led;
} APP_BLE_DEVICE;

void APP_BLE_InitData(void);
void APP_ResetData(void);

APP_RESULT APP_BLE_SetDeviceAddr(uint32_t index,
                                 char * deviceAddr);

void APP_BLED_SetActiveDevice(APP_BLE_DEVICE * device);

APP_BLE_DEVICE * APP_BLED_GetActiveDevice(void);
void APP_BLED_SetActiveDevice(APP_BLE_DEVICE * device);
APP_BLE_DEVICE * APP_BLED_GetActiveDevice(void);
void APP_BLED_SetDeviceColor(uint32_t index, uint32_t rgb888);
APP_RESULT APP_BLED_GetDeviceColor(uint32_t index, uint32_t * rgb888);

APP_BLE_DEVICE * APP_BLED_GetMultiLinkDemoDevice(uint32_t index);
APP_BLE_DEVICE * APP_BLED_GetDeviceByShortAddr(APP_BLE_DEVICE * list,
                                               uint32_t listSize,
                                               char * addr2Byte);
APP_BLE_NOTIF_TYPE APP_BLED_ParseNotification(char * notifStr,
                                      uint32_t size,
                                      char * outAddr2Byte,
                                      uint32_t * outValue);
APP_RESULT APP_BLED_GetDeviceTemp(APP_BLE_DEVICE * device,
                                  APP_BLE_DEVICE_TEMP_UNIT unit,
                                  uint32_t * outValue);

extern APP_BLE_DEVICE availableDevices[];
extern APP_BLE_DEVICE connectedDevices[];
extern APP_BLE_DEVICE demoDevices[];
extern APP_BLE_DEVICE multiLinkDemoDevices[];


#ifdef	__cplusplus
}
#endif

#endif	/* APP_BLE_DATA_H */

