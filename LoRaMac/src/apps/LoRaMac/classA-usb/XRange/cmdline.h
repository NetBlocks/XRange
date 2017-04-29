#ifndef __CMDLINE_H__
#define __CMDLINE_H__

#define CLI_BAD_CMD         (-1)
#define CLI_TOO_MANY_ARGS   (-2)

typedef int (*pfuncCmdLine)(int argc, char *argv[]);

typedef struct
{
    const char *p_cmd_str;
    pfuncCmdLine pfuncCmd;
    const char *p_help_str;
}
CmdLineObject;

extern CmdLineObject cmd_table[];

extern int cmd_line_process(char *cmd_line);


#endif 
