#include "legato.h"
#include "interfaces.h"

#include "libmodbus/modbus.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**************************************************************************************************************/
int validate_number(char *str) {
	while (*str) {
		if(!isdigit(*str)){ //if the character is not a number, return false
			return 0;
		}
		str++; //point to next character
	}
	return 1;
}

int validate_ip(const char *ipRef) { //check whether the IP is valid or not
	int num, dots = 0;
	char *ptr;
	char ip[20];
	sprintf(ip, "%s", ipRef);
	
	if (ip == NULL)
		return 0;
		
	ptr = strtok(ip, "."); //cut the string using dor delimiter
	if (ptr == NULL)
		return 0;
	
	while (ptr) {
		if (!validate_number(ptr)) //check whether the sub string is holding only number or not
			return 0;
        num = atoi(ptr); //convert substring to number
		if (num >= 0 && num <= 255) {
            ptr = strtok(NULL, "."); //cut the next part of the string
            if (ptr != NULL)
				dots++; //increase the dot count
		} 
		else
			return 0;
    }
	
    if (dots != 3) //if the number of dots are not 3, return false
		return 0;
		
	return 1;
}
/**************************************************************************************************************/

modbus_t * 			ctx = NULL;

int					Debug = 0;					// 0: disable, 1: enable

char				Protocol[5] = {0};			// rtu / tcp
uint8_t				Slave = 1;					// slave ID

uint32_t			Timeout = 1;				// response timeout
char				Com[50] = {0};				// COM Port
uint32_t			BitRate = 9600;				// 4800 / 9600 / 14400 / 19200 / 38400 / 56000 / 57600 / 115200
uint8_t 			DataBit = 8;				// 8 / 7
char 				Parity = 'N';				// 'O' / 'E' / 'N'
uint8_t 			StopBit = 1;				// 1 / 2

char				Ip[16] = {0};				// 000.000.000.000 - max 15 char
uint16_t			Port = 502;					

int8_t modbus_SetParameter (const char* name, const char* value)
{
	if (strcmp (name, "Protocol") == 0 && strlen(value) > 2)
	{
		sprintf(Protocol, "%s", value);
	}
	else if (strcmp (name, "Timeout") == 0)
	{
		Timeout = (uint32_t)atoi(value);
	}
	else if (strcmp (name, "Com") == 0)
	{
		sprintf(Com, "%s", value);
	}
	else if (strcmp (name, "BitRate") == 0)
	{
		BitRate = (uint32_t)atoi(value);
	}
	else if (strcmp (name, "DataBit") == 0)
	{
		DataBit = (uint8_t)atoi(value);
	}
	else if (strcmp (name, "Parity") == 0 && strlen(value) > 0)
	{
		Parity = value[0];
	}
	else if (strcmp (name, "StopBit") == 0)
	{
		StopBit = (uint8_t)atoi(value);
	}
	else if (strcmp (name, "Ip") == 0)
	{
		sprintf(Ip, "%s", value);
	}
	else if (strcmp (name, "Port") == 0)
	{
		Port = (uint16_t)atoi(value);
	}
	else if (strcmp (name, "Debug") == 0)
	{
		Debug = atoi(value);
		if (ctx != NULL)
		{
			modbus_set_debug (ctx, Debug);
		}
	}
	else if (strcmp (name, "Slave") == 0)
	{
		Slave = (uint8_t)atoi(value);
		if (ctx != NULL)
		{
			modbus_set_slave(ctx, Slave);
		}
	}
	else
	{
		return -1;
	}
	
	return 0;
}

int8_t modbus_GetParameter (const char* name, char* value, size_t valueSize)
{
	if (strcmp (name, "Protocol") == 0)
	{
		sprintf(value, "%s", Protocol);
	}
	else if (strcmp (name, "Timeout") == 0)
	{
		sprintf(value, "%d", Timeout);
	}
	else if (strcmp (name, "Com") == 0)
	{
		sprintf(value, "%s", Com);
	}
	else if (strcmp (name, "BitRate") == 0)
	{
		sprintf(value, "%d", BitRate);
	}
	else if (strcmp (name, "DataBit") == 0)
	{
		sprintf(value, "%d", DataBit);
	}
	else if (strcmp (name, "Parity") == 0)
	{
		sprintf(value, "%c", Parity);
	}
	else if (strcmp (name, "StopBit") == 0)
	{
		sprintf(value, "%d", StopBit);
	}
	else if (strcmp (name, "Ip") == 0)
	{
		sprintf(value, "%s", Ip);
	}
	else if (strcmp (name, "Port") == 0)
	{
		sprintf(value, "%d", Port);
	}
	else if (strcmp (name, "Debug") == 0)
	{
		sprintf(value, "%d", Debug);
	}
	else if (strcmp (name, "Slave") == 0)
	{
		sprintf(value, "%d", Slave);
	}
	else
	{
		return -1;
	}
	
	return 0;
}

int8_t modbus_Disconnect ()
{
	if (ctx != NULL)
	{
		modbus_close(ctx);
		modbus_free(ctx);
		ctx = NULL;
	}
	return 0;
}

int8_t modbus_Connect ()
{
	modbus_Disconnect();
	
	int ret = 0;
	if (
		strcmp(Protocol, "rtu") == 0
	) 
	{		
		// Check Bit Rate
		if (
			BitRate != 4800 &&
			BitRate != 9600 &&
			BitRate != 19200 &&
			BitRate != 38400 &&
			BitRate != 56000 &&
			BitRate != 57600 &&
			BitRate != 115200
		)
		{
			ret = -4;								// Invalid Bit Rate
		}
		
		// Check Data Bit
		if (
			DataBit != 8 &&
			DataBit != 7
		)
		{
			ret = -5;									// Invalid Data Bit
		}
		
		// Check Parity
		if (
			Parity != 'O' &&
			Parity != 'E' &&
			Parity != 'N'
		)
		{
			ret = -6;								// Invalid Parity
		}
		
		// Check Stop Bit
		if (
			StopBit != 1 &&
			StopBit != 2
		)
		{
			ret = -7;								// Invalid Stop Bit
		}
		
		// Check COM
		if (
			strlen(Com) < 3
		)
		{
			ret = -8;								// Invalid COM string
		}
		
		// enough parameter
		if (
			ret == 0
		)
		{
			ctx = modbus_new_rtu (Com, BitRate, Parity, DataBit, StopBit);
		}
		else
		{
			ctx = NULL;
		}
	}
	else if (
		strcmp(Protocol, "tcp") == 0
	)
	{
		// Check ip is valid
		if (
			validate_ip(Ip) == 0
		)
		{
			ret = -2; 								// Invalid IP address
		}
		
		// Check port range
		if (
			Port < 1 && Port > 65535
		)
		{
			ret = -3;								// Port out of range
		}
		
		// enough parameter
		if (
			ret == 0
		)
		{
			ctx = modbus_new_tcp (Ip, Port);		// Create tcp object
		}
		else
		{
			ctx = NULL;
		}
	}
	else
	{
		ret = -1;									// Empty Protocol
	}
	
	if (ctx != NULL)
	{
		modbus_set_debug (ctx, Debug);
		modbus_set_response_timeout (ctx, Timeout, 0);
		modbus_set_slave(ctx, Slave);
		
		if (
			modbus_connect (ctx) == -1
		)
		{
			ret = -99;
			modbus_Disconnect();
		}
	}
	return ret;
}

int8_t modbus_Read_Bit (uint16_t address, uint8_t* dest, size_t* destSize)
{
	int8_t ret = -9;
	if (ctx != NULL)
	{
		ret = modbus_read_bits (ctx, address, *destSize, dest);
	}
	return ret;
}

int8_t modbus_Read_InputBit (uint16_t address, uint8_t* dest, size_t* destSize)
{
	int8_t ret = -9;
	if (ctx != NULL)
	{
		ret = modbus_read_input_bits (ctx, address, *destSize, dest);
	}
	return ret;
}

int8_t modbus_Read_Word (uint16_t address, uint16_t* dest, size_t* destSize)
{
	int8_t ret = -9;
	if (ctx != NULL)
	{
		ret = modbus_read_registers (ctx, address, *destSize, dest);
	}
	return ret;
}

int8_t modbus_Read_InputWord (uint16_t address, uint16_t* dest, size_t* destSize)
{
	int8_t ret = -9;
	if (ctx != NULL)
	{
		ret = modbus_read_input_registers (ctx, address, *destSize, dest);
	}
	return ret;
}

int8_t modbus_Write_Bit (uint16_t address, const uint8_t* dest, size_t destSize)
{
	int8_t ret = -9;
	int cnt = 0;
	if (ctx != NULL)
	{
		for (cnt = 0; cnt < destSize; cnt++)
		{
			if (dest[cnt] == 0)
			{
				ret = modbus_write_bit (ctx, address, FALSE);
			}
			else
			{
				ret = modbus_write_bit (ctx, address, TRUE);
			}
		}		
	}
	return ret;
}

int8_t modbus_Write_Word (uint16_t address, const uint16_t* dest, size_t destSize)
{
	int8_t ret = -9;
	if (ctx != NULL)
	{
		ret = modbus_write_registers (ctx, address, destSize, &dest[0]);
	}
	return ret;
}

COMPONENT_INIT
{
	
}