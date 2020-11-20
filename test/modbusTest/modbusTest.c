#include "legato.h"
#include "interfaces.h"

char ret[101];
uint8_t bits[128];
uint16_t words[128];
size_t size;

void reset()
{
	int i;
	for (i = 0; i < 200; i++)
	{
		bits[i] = 0;
		words[i] = 0;
	}
}

char* get(int bit, size_t s)
{
	int i;
	static char ret[1024] = {0};
	LE_INFO("size : %d", s);
	ret[0] = '\0';
	if (bit == 0)
	{
		for (i = 0; i < s; i++)
		{
			sprintf(ret, "%s%d,", ret, bits[i]);
		}
	}
	else
	{
		for (i = 0; i < s; i++)
		{
			sprintf(ret, "%s%d,", ret, words[i]);
		}
	}
	return ret;
}

COMPONENT_INIT
{
	LE_INFO("SetParameter: %d", modbus_SetParameter("Protocol","hehehaha"));
	LE_INFO("GetParameter: %d[%s]", modbus_GetParameter("totoco", ret, 100), ret);
	LE_INFO("Connect: %d", modbus_Connect());
	LE_INFO("Disconnect: %d", modbus_Disconnect());
	
	LE_INFO("--------------------------------");
	size = 5;
	reset();
	LE_INFO("Read Bit: %d [%d] [%s]", modbus_Read_Bit(123, bits, &size), size, get(0, size));
	
	LE_INFO("--------------------------------");
	size = 10;
	reset();
	LE_INFO("Read InputBit: %d [%d] [%s]", modbus_Read_InputBit(456, bits, &size), size, get(0, size));
	
	LE_INFO("--------------------------------");
	size = 7;
	reset();
	LE_INFO("Read Word: %d [%d] [%s]", modbus_Read_Word(321, words, &size), size, get(1, size));
	
	LE_INFO("--------------------------------");
	size = 2;
	reset();
	LE_INFO("Read InputWord: %d [%d] [%s]", modbus_Read_InputWord(654, words, &size), size, get(1, size));
	
	LE_INFO("--------------------------------");
	size = 3;
	bits[0] = 1; bits[1] = 5; bits[2] = 2;
	reset();
	LE_INFO("Write Bit: %d", modbus_Write_Bit(789, bits, size));
	
	LE_INFO("--------------------------------");
	size = 4;
	words[0] = 3; words[1] = 111; words[2] = 3212; words[3] = 1020;
	LE_INFO("Write Word: %d", modbus_Write_Word(987, words, size));
	
	exit(EXIT_SUCCESS);
}