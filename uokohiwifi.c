#include "uokohiwifi.h"


static uint         select_option;
static uint         update_uoko_ad;
static char         *usignal;
static const char   *uoko_add_host = "http://www.baidu.com/";

static int  get_options(int argc, char *const *argv);
static int download_ad();


int main(int argc, char *const *argv)
{
	if(get_options(argc, argv) != OK)
	{
	   return 1;		
	}

	if(update_uoko_ad)
	{
		download_ad();	
	}
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


                if (uoko_strcmp(usignal, "updatead") == 0)
                {
                	update_uoko_ad = 1;
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


static int
download_ad()
{
    char cmd[300] = "wget ";
    strcat(cmd ,uoko_add_host);
    system(cmd);
}