//*****************************************************************************
//	CLI Interface
//*****************************************************************************

#include "cli.h"

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <stdbool.h>
#include <stdint.h>
#include "utils.h"
#include "cmdline.h"
#include "eeprom_conf.h"
#include "board.h"
#include "usb-printf.h"


int
Cmd_help(int argc, char *argv[])
{
    CmdLineObject *p_entry;

    //
    // Print some header text.
    //
    PRINTF("\nAvailable commands\r\n");
    PRINTF("------------------\r\n");

    //
    // Point at the beginning of the command table.
    //
    p_entry = &cmd_table[0];

    //
    // Enter a loop to read each entry from the command table.  The
    // end of the table has been reached when the command name is NULL.
    //
    while(p_entry->p_cmd_str)
    {
        //
        // Print the command name and the brief description.
        //
        PRINTF("%s%s\r\n", p_entry->p_cmd_str, p_entry->p_help_str);

        //
        // Advance to the next entry in the table.
        //
        p_entry++;
    }

    //
    // Return success.
    //
    return(0);
}


void PrintValues(const char* lable, const uint8_t *data,int size)
{
	int i;
	PRINTF("\n\r%s",lable);

	for(i = 0; i < size ; i++)
	{
		PRINTF("%02X ", data[i]);
	}

}


void PrintValueReverse(const char* lable, const uint8_t *data,int size)
{
	int i;
	PRINTF("\n\r%s",lable);

	for(i = size -1 ; i >=0 ; i--)
	{
		PRINTF("%02X ", data[i]);
	}

}

//extern void PrintLoRaSettings();

int Cmd_show(int argc, char *argv[])
{
	uint8_t val[16];

	if(GetActivationMethod() == ACTIVATION_METHOD_ABP)
	{
		PRINTF("\r\nActivation Method : ABP" );
	}
	else
	{
			PRINTF("\r\nActivation Method : OTAA" );
	}

	if(GetActivationMethod() == ACTIVATION_METHOD_OTAA)
	{
		BoardGetUniqueId( val );
		PrintValues("Device EUI: ",val,DEVICE_EUI_SIZE);

		eeprom_read(EEPROM_APPLICATION_EUI_ADDR, val, APPLICATION_EUI_SIZE);
		PrintValues("Application EUI: ", val, APPLICATION_EUI_SIZE);

		eeprom_read(EEPROM_APPLICATION_KEY_ADDR, val, APPLICATION_KEY_SIZE);
		PrintValues("Application Key: ", val, APPLICATION_KEY_SIZE);
	}
	else
	{

		BoardGetUniqueId( val );
		PrintValues("Device EUI: ",val,DEVICE_EUI_SIZE);

		eeprom_read(EEPROM_APPLICATION_EUI_ADDR, val, APPLICATION_EUI_SIZE);
		PrintValues("Application EUI: ", val, APPLICATION_EUI_SIZE);

		eeprom_read(EEPROM_DEV_ADDR, val, DEV_ADDR_SIZE);
		PrintValueReverse("Device Address: ",val ,DEV_ADDR_SIZE);

		eeprom_read(EEPROM_NWKSKEY, val, NWKSKEY_SIZE);
		PrintValues("Network Session Key: ",val ,NWKSKEY_SIZE);

		eeprom_read(EEPROM_APPSKEY, val, APPSKEY_SIZE);
		PrintValues("App Session Key: ",val ,APPSKEY_SIZE);
	}

return 0;
}

void CLI_PrintError()
{
	PRINTF("Bad arguments\n");
}

void CLI_SetPrintHelp()
{
    PRINTF("\n\r");
	PRINTF("set activation otaa|abp\r\n");
	PRINTF("set appeui Application EUI\r\n");
	PRINTF("set appkey App Key\r\n");
	if(GetActivationMethod() == ACTIVATION_METHOD_ABP)
	{
		PRINTF("set devaddr Device Address\r\n");
		PRINTF("set netskey Network Session Key\r\n");
		PRINTF("set appskey App Session Key\r\n");
	}
}


int Cmd_set(int argc, char *argv[])
{
	uint8_t var[16];
	uint8_t addr[4];
	if(argc < 3)
	{
		if(argc == 2 && (strcmp(argv[1],"?")==0))
		{
			CLI_SetPrintHelp();
		}
		else
		{
			CLI_PrintError();
		}

		return 0;
	}

	if(strcmp(argv[1],"activation")==0)
	{
		if(strcmp(argv[2],"otaa") ==0 )
		{
				SetActivationMethod(ACTIVATION_METHOD_OTAA);
				PRINTF("\r\nDone\r\n");
		}else if(strcmp(argv[2],"abp") ==0)
		{
				SetActivationMethod(ACTIVATION_METHOD_ABP);
				PRINTF("\r\nDone\r\n");
		}else
		{
				CLI_PrintError();
				return 0;

		}

	}else if(strcmp(argv[1],"appeui")==0)
	{

		if(check_str_size(argv[2],APPLICATION_EUI_SIZE) && check_hex_str_format(argv[2]))
		{
			if(convert_hex_to_array(var, APPLICATION_EUI_SIZE, argv[2]))
			{
				eeprom_write(EEPROM_APPLICATION_EUI_ADDR, var, APPLICATION_EUI_SIZE);
				PRINTF("\r\nDone\r\n");
				return 0;
			}
		}

	}else if(strcmp(argv[1],"appkey")==0)
	{
		if(check_str_size(argv[2],APPLICATION_KEY_SIZE) && check_hex_str_format(argv[2]))
		{
			if(convert_hex_to_array(var, APPLICATION_KEY_SIZE, argv[2]))
			{
				eeprom_write(EEPROM_APPLICATION_KEY_ADDR, var, APPLICATION_KEY_SIZE);
				PRINTF("\r\nDone\r\n");
				return 0;
			}
		}


	}else if(strcmp(argv[1],"netskey")==0)
	{
		if(check_str_size(argv[2],NWKSKEY_SIZE) && check_hex_str_format(argv[2]))
		{
			if(convert_hex_to_array(var,NWKSKEY_SIZE, argv[2]))
			{
				eeprom_write(EEPROM_NWKSKEY, var, NWKSKEY_SIZE);
				PRINTF("\r\nDone\r\n");
				return 0;
			}
		}

	}else if(strcmp(argv[1],"appskey")==0)
	{
		if(check_str_size(argv[2],APPSKEY_SIZE) && check_hex_str_format(argv[2]))
		{
			if(convert_hex_to_array(var ,APPSKEY_SIZE, argv[2]))
			{
				eeprom_write(EEPROM_APPSKEY, var, APPSKEY_SIZE);
				PRINTF("\r\nDone\r\n");
				return 0;
			}
		}
	}else if(strcmp(argv[1],"devaddr")==0)
	{
		if(check_str_size(argv[2],DEV_ADDR_SIZE) && check_hex_str_format(argv[2]))
		{
			if(convert_hex_to_array(var,DEV_ADDR_SIZE, argv[2]))
			{
				addr[0]= var[3];	addr[1]= var[2];addr[2]= var[1];addr[3]= var[0];
				eeprom_write(EEPROM_DEV_ADDR, addr, DEV_ADDR_SIZE);
				PRINTF("\r\nDone\r\n");
				return 0;
			}
		}
	}
	else
	{
		CLI_PrintError();
		return 0;
	}

	return 1;

}

extern void reset_device(void);

int Cmd_reload(int argc, char *argv[])
{
	reset_device();
	return 0;
}

//*****************************************************************************
//
// This is the table that holds the command names, implementing functions,
// and brief description.
//
//*****************************************************************************
CmdLineObject cmd_table[] =
{
    { "help",Cmd_help,"    : Display list of commands" },
    { "h",Cmd_help,"       : alias for help" },
    { "?",Cmd_help,"       : alias for help" },
    { "sh",Cmd_show,"      : Show configuration" },
    { "set",Cmd_set,"     : Set Device setting" },
	{ "reload",Cmd_reload,"  : Reload Device setting" },
    { 0, 0, 0 }
};


void cli_init()
{
	ClearClmLineBuffer();
  PRINTF("\r\n> ");
}

void cli_process(void)
{
        int status;

		if(!USB_get_cmd_line()) return;

        status = cmd_line_process(cmd_line_buf);

        if(status == CLI_BAD_CMD)
        {
            PRINTF("Bad command!\n");
        }

        else if(status == CLI_TOO_MANY_ARGS)
        {
            PRINTF("Too many arguments for command processor!\n");
        }

		ClearClmLineBuffer();
		PRINTF("\r\n> ");

}

