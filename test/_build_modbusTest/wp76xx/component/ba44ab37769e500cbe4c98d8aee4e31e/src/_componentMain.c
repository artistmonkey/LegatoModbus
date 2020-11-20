/*
 * AUTO-GENERATED _componentMain.c for the modbusTest component.

 * Don't bother hand-editing this file.
 */

#include "legato.h"
#include "../liblegato/eventLoop.h"
#include "../liblegato/log.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const char* _modbusTest_modbus_ServiceInstanceName;
const char** modbus_ServiceInstanceNamePtr = &_modbusTest_modbus_ServiceInstanceName;
void modbus_ConnectService(void);
// Component log session variables.
le_log_SessionRef_t modbusTest_LogSession;
le_log_Level_t* modbusTest_LogLevelFilterPtr;

// Component initialization function (COMPONENT_INIT).
void _modbusTest_COMPONENT_INIT(void);

// Library initialization function.
// Will be called by the dynamic linker loader when the library is loaded.
__attribute__((constructor)) void _modbusTest_Init(void)
{
    LE_DEBUG("Initializing modbusTest component library.");

    // Connect client-side IPC interfaces.
    modbus_ConnectService();

    // Register the component with the Log Daemon.
    modbusTest_LogSession = log_RegComponent("modbusTest", &modbusTest_LogLevelFilterPtr);

    //Queue the COMPONENT_INIT function to be called by the event loop
    event_QueueComponentInit(_modbusTest_COMPONENT_INIT);
}


#ifdef __cplusplus
}
#endif
