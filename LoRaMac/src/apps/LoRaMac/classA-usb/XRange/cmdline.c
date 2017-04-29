#include <string.h>
#include "cmdline.h"
#ifndef CMDLINE_MAX_ARGS
#define CMDLINE_MAX_ARGS        8
#endif

int cmd_line_process(char *cmd_line)
{
    static char *argv[CMDLINE_MAX_ARGS + 1];
    char *pch;
    int argc;
    int find_arg = 1;
    CmdLineObject *cmd_object;
		argc = 0;
    pch = cmd_line;

    while(*pch)
    {
        if(*pch == ' ')
        {
            *pch = 0;
            find_arg = 1;
        }
        else
        {
            if(find_arg)
            {
                if(argc < CMDLINE_MAX_ARGS)
                {
                    argv[argc] = pch;
                    argc++;
                    find_arg = 0;
                }
                else
                {
                    return(CLI_TOO_MANY_ARGS);
                }
            }
        }
        pch++;
    }

    if(argc)
    {
        cmd_object = &cmd_table[0];
        while(cmd_object->p_cmd_str)
        {
            if(!strcmp(argv[0], cmd_object->p_cmd_str))
            {
                return(cmd_object->pfuncCmd(argc, argv));
            }
            cmd_object++;
        }
    }
    return(CLI_BAD_CMD);
}

