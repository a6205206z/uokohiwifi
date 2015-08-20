#include "remotecmd.h"


static uint         select_option;
static char         *usignal;
static const char   *uoko_command_server = "http://www.baidu.com/";

static int get_options(int argc, char *const *argv);
static int pull_command();


int main(int argc, char *const *argv)
{
	if(get_options(argc, argv) != OK)
	{
	   return 1;		
	}
}


static int pull_command()
{
    return OK;
}



static int
get_options(int argc, char *const *argv)
{
    u_char     *p;
    uint   		i;

    for (i = 1; i < argc; i++) 
    {

        p = (u_char *) argv[i];

        if (*p++ != '-') 
        {
            printf("invalid option: \"%s\"\n", argv[i]);
            return ERROR;
        }

        while (*p) 
        {

            switch (*p++) 
            {
            case 's':
                if (*p) 
                {
                    usignal = (char *) p;
                }
                else if (argv[++i]) 
                {
                    usignal = argv[i];
                } 
                else 
                {
                    printf(0, "option \"-s\" requires parameter\n");
                    return ERROR;
                }


                if (uoko_strcmp(usignal, "--pull-command") == 0)
                {
                    pull_command();
                    goto next;
                }

                printf(0, "invalid option: \"-s %s\"", usignal);
                return ERROR;
                break;

            default:
                printf(0, "invalid option: \"%c\"\n", *(p - 1));
                return ERROR;
            }
        }

    next:

        continue;
    }

    return OK;
}
