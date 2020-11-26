#include "legato.h"
#include "interfaces.h"
#include <pthread.h>

void modbusTestFunc ()
{
	LE_INFO("************************************");
    char param[100] = {0};
    modbus_GetParameter("Com", param, 99);
    LE_INFO("%s", param);
    if (strcmp(param, "/dev/ttyUSB0") != 0)
    {
        LE_INFO("Protocol : %d", modbus_SetParameter("Protocol", "tcp"));


        LE_INFO("Ip : %d", modbus_SetParameter("Ip", "192.168.13.101"));
        LE_INFO("Port : %d", modbus_SetParameter("Port", "502"));

        /*
        LE_INFO("Com : %d", modbus_SetParameter("Com", "/dev/ttyUSB0"));
        LE_INFO("BitRate : %d", modbus_SetParameter("BitRate", "9600"));
        LE_INFO("DataBit : %d", modbus_SetParameter("DataBit", "8"));
        LE_INFO("Parity : %d", modbus_SetParameter("Parity", "N"));
        LE_INFO("StopBit : %d", modbus_SetParameter("StopBit", "1"));
        LE_INFO("Debug : %d", modbus_SetParameter("Debug", "1"));
        LE_INFO("Slave : %d", modbus_SetParameter("Slave", "3"));
        */
        LE_INFO("Connect : %d", modbus_Connect());
    }
    else
    {
        LE_INFO("Already connected");
    }
    
    char disp[100] = {0};
    uint16_t ret[32];
    int8_t resp = -1;
    size_t range = 5;
    
    for (int i = 0; i < 5; i++)
    {
        resp = modbus_Read_Word(5409, ret, &range);
        if (resp < 0)
        {
            LE_INFO("Fail reading...");
        }
        else
        {
            disp[0] = '\0';
            for (int i = 0; i < range; i++)
            {
                sprintf(disp, "%s[%d]", disp, ret[i]);
            }
            LE_INFO("Index[%d]%s", i, disp);
        }      
        LE_INFO("Write : %d", modbus_Write_Word(4197, ret, range));
        sleep(1);
    }
    modbus_GetParameter("Com", param, 99);
    if (strcmp(param, "/dev/ttyUSB0") != 0)
    {
        LE_INFO("Disconnect : %d", modbus_Disconnect());
    }
}

le_thread_Ref_t t;
int ThreadWait;

void* threadFunc(void* context)
{
	LE_INFO("In Thread..........");
	modbusTestFunc ();
	ThreadWait = 0;
	pthread_exit(NULL);
}

COMPONENT_INIT
{
	modbusTestFunc ();
	
	LE_INFO("Thread.................");
	
	ThreadWait = 1;
	t = le_thread_Create("threading", threadFunc, NULL);
	le_thread_Start(t);
	
	while (ThreadWait > 0) 
	{
		usleep(50 * 1000);
	}
    exit(EXIT_SUCCESS);
}