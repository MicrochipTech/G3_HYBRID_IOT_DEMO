#ifndef _APP_TASKS__H    /* Guard against multiple inclusion */
#define _APP_TASKS__H




/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    typedef enum
    {
        APP_TASK_BLE,
        APP_TASK_UI,
        APP_TASK_WIFI,
        APP_TASK_HTTP,
        APP_TASK_MAX,
    } APP_TASKS;
    
    
    typedef struct
    {
        uint32_t msg;
    } APP_TASKS_CONFIG;



    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _APP_TASKS__H */

/* *****************************************************************************
 End of File
 */
