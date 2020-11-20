/*
 * AUTO-GENERATED _componentMain.c for the modbuslib component.

 * Don't bother hand-editing this file.
 */

#include "legato.h"
#include "../liblegato/eventLoop.h"
#include "../liblegato/log.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const char* _modbuslib_modbus_ServiceInstanceName;
const char** modbus_ServiceInstanceNamePtr = &_modbuslib_modbus_ServiceInstanceName;
void modbus_AdvertiseService(void);
// Component log session variables.
le_log_SessionRef_t modbuslib_LogSession;
le_log_Level_t* modbuslib_LogLevelFilterPtr;

// Component initialization function (COMPONENT_INIT).
void _modbuslib_COMPONENT_INIT(void);

// Library initialization function.
// Will be called by the dynamic linker loader when the library is loaded.
__attribute__((constructor)) void _modbuslib_Init(void)
{
    LE_DEBUG("Initializing modbuslib component library.");

    // Advertise server-side IPC interfaces.
    modbus_AdvertiseService();

    // Register the component with the Log Daemon.
    modbuslib_LogSession = log_RegComponent("modbuslib", &modbuslib_LogLevelFilterPtr);

    //Queue the COMPONENT_INIT function to be called by the event loop
    event_QueueComponentInit(_modbuslib_COMPONENT_INIT);
}


#ifdef __cplusplus
}
#endif
