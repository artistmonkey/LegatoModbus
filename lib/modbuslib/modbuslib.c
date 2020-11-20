#include "legato.h"
#include "interfaces.h"

uint8_t modbus_SetParameter (const char* name, const char* value)
{
	LE_INFO("Set Parameter { name : %s, value : %s }", name, value);
	return 0;
}

uint8_t modbus_GetParameter (const char* name, char* value, size_t valueSize)
{
	LE_INFO("Get Parameter { name : %s }", name);
	sprintf(value, "%s", name);
	return 1;
}

uint8_t modbus_Connect ()
{
	LE_INFO("Connect");
	return 2;
}

uint8_t modbus_Disconnect ()
{
	LE_INFO("Disconnect");
	return 3;
}

uint8_t modbus_Read_Bit (uint16_t address, uint8_t* dest, size_t* destSize)
{
	LE_INFO("Read Bit : { address : %d, length : %d }", address, *destSize);
	int i = 0;
	for (i = 0; i < *destSize; i++)
	{
		LE_INFO("%d", dest[i]);
		dest[i] = i;
	}
	*destSize = i;
	return 4;
}

uint8_t modbus_Read_InputBit (uint16_t address, uint8_t* dest, size_t* destSize)
{
	LE_INFO("Read InputBit : { address : %d, length : %d }", address, *destSize);
	int i = 0;
	for (i = 0; i < *destSize; i++)
	{
		LE_INFO("%d", dest[i]);
		dest[i] = i;
	}
	*destSize = i;
	return 5;
}

uint8_t modbus_Read_Word (uint16_t address, uint16_t* dest, size_t* destSize)
{
	LE_INFO("Read Word : { address : %d, length : %d }", address, *destSize);
	int i = 0;
	for (i = 0; i < *destSize; i++)
	{
		LE_INFO("%d", dest[i]);
		dest[i] = i;
	}
	*destSize = i;
	return 6;
}

uint8_t modbus_Read_InputWord (uint16_t address, uint16_t* dest, size_t* destSize)
{
	LE_INFO("Read InputWord : { address : %d, length : %d }", address, *destSize);
	int i = 0;
	for (i = 0; i < *destSize; i++)
	{
		LE_INFO("%d", dest[i]);
		dest[i] = i;
	}
	*destSize = i;
	return 7;
}

uint8_t modbus_Write_Bit (uint16_t address, const uint8_t* dest, size_t destSize)
{
	LE_INFO("Write Bit : { address : %d }", address);
	int i = 0;
	for (i = 0; i < destSize; i++)
	{
		LE_INFO("%d", dest[i]);
	}
	return 8;
}

uint8_t modbus_Write_Word (uint16_t address, const uint16_t* dest, size_t destSize)
{
	LE_INFO("Write Bit : { address : %d }", address);
	int i = 0;
	for (i = 0; i < destSize; i++)
	{
		LE_INFO("%d", dest[i]);
	}
	return 9;
}

COMPONENT_INIT
{
	
}