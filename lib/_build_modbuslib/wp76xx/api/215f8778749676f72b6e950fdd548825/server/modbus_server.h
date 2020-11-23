

/*
 * ====================== WARNING ======================
 *
 * THE CONTENTS OF THIS FILE HAVE BEEN AUTO-GENERATED.
 * DO NOT MODIFY IN ANY WAY.
 *
 * ====================== WARNING ======================
 */


#ifndef MODBUS_INTERFACE_H_INCLUDE_GUARD
#define MODBUS_INTERFACE_H_INCLUDE_GUARD


#include "legato.h"


//--------------------------------------------------------------------------------------------------
/**
 * Get the server service reference
 */
//--------------------------------------------------------------------------------------------------
le_msg_ServiceRef_t modbus_GetServiceRef
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * Get the client session reference for the current message
 */
//--------------------------------------------------------------------------------------------------
le_msg_SessionRef_t modbus_GetClientSessionRef
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * Initialize the server and advertise the service.
 */
//--------------------------------------------------------------------------------------------------
void modbus_AdvertiseService
(
    void
);



//--------------------------------------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------------------------------------
int8_t modbus_SetParameter
(
    const char* LE_NONNULL name,
        ///< [IN] parameter name
    const char* LE_NONNULL value
        ///< [IN] parameter value
);



//--------------------------------------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------------------------------------
int8_t modbus_GetParameter
(
    const char* LE_NONNULL name,
        ///< [IN] parameter name
    char* value,
        ///< [OUT] parameter value
    size_t valueSize
        ///< [IN]
);



//--------------------------------------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------------------------------------
int8_t modbus_Connect
(
    void
);



//--------------------------------------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------------------------------------
int8_t modbus_Disconnect
(
    void
);



//--------------------------------------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------------------------------------
int8_t modbus_Read_Bit
(
    uint16_t address,
        ///< [IN] Readable/Writable bit address
    uint8_t* destPtr,
        ///< [OUT] value place after read
    size_t* destSizePtr
        ///< [INOUT]
);



//--------------------------------------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------------------------------------
int8_t modbus_Read_InputBit
(
    uint16_t address,
        ///< [IN] Read only bit address
    uint8_t* destPtr,
        ///< [OUT] value place after read
    size_t* destSizePtr
        ///< [INOUT]
);



//--------------------------------------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------------------------------------
int8_t modbus_Read_Word
(
    uint16_t address,
        ///< [IN] Readable/Writable word address
    uint16_t* destPtr,
        ///< [OUT] value place after read
    size_t* destSizePtr
        ///< [INOUT]
);



//--------------------------------------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------------------------------------
int8_t modbus_Read_InputWord
(
    uint16_t address,
        ///< [IN] Read only word address
    uint16_t* destPtr,
        ///< [OUT] value place after read
    size_t* destSizePtr
        ///< [INOUT]
);



//--------------------------------------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------------------------------------
int8_t modbus_Write_Bit
(
    uint16_t address,
        ///< [IN] Readable/Writable bit address
    const uint8_t* destPtr,
        ///< [IN] value place after read
    size_t destSize
        ///< [IN]
);



//--------------------------------------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------------------------------------
int8_t modbus_Write_Word
(
    uint16_t address,
        ///< [IN] Readable/Writable word address
    const uint16_t* destPtr,
        ///< [IN] value place after read
    size_t destSize
        ///< [IN]
);


#endif // MODBUS_INTERFACE_H_INCLUDE_GUARD