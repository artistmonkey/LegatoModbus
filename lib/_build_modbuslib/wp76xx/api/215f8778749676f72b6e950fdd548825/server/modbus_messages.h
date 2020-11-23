
/*
 * ====================== WARNING ======================
 *
 * THE CONTENTS OF THIS FILE HAVE BEEN AUTO-GENERATED.
 * DO NOT MODIFY IN ANY WAY.
 *
 * ====================== WARNING ======================
 */


#ifndef MODBUS_MESSAGES_H_INCLUDE_GUARD
#define MODBUS_MESSAGES_H_INCLUDE_GUARD


#include "legato.h"

#define PROTOCOL_ID_STR "98291297fff67f6b55fa1c5496a93200"

#ifdef MK_TOOLS_BUILD
    extern const char** modbus_ServiceInstanceNamePtr;
    #define SERVICE_INSTANCE_NAME (*modbus_ServiceInstanceNamePtr)
#else
    #define SERVICE_INSTANCE_NAME "modbus"
#endif


#define _MAX_MSG_SIZE 271

// Define the message type for communicating between client and server
typedef struct __attribute__((packed))
{
    uint32_t id;
    uint8_t buffer[_MAX_MSG_SIZE];
}
_Message_t;

#define _MSGID_modbus_SetParameter 0
#define _MSGID_modbus_GetParameter 1
#define _MSGID_modbus_Connect 2
#define _MSGID_modbus_Disconnect 3
#define _MSGID_modbus_Read_Bit 4
#define _MSGID_modbus_Read_InputBit 5
#define _MSGID_modbus_Read_Word 6
#define _MSGID_modbus_Read_InputWord 7
#define _MSGID_modbus_Write_Bit 8
#define _MSGID_modbus_Write_Word 9


#endif // MODBUS_MESSAGES_H_INCLUDE_GUARD