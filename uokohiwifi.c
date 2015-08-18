#include "uokohiwifi.h"


static uint         select_option;
static uint         update_uoko_ad;
static char        *usignal;


static int get_options(int argc, char *const *argv);


int main(int argc, char *const *argv)
{
	if(get_options(argc, argv) != OK)
	{
	   return 1;		
	}

	if(update_uoko_ad)
	{
		printf("update ad \n");		
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

                printf("%d\n", uoko_strcmp(usignal, "update"));
                if (uoko_strcmp(usignal, "update") == 1)
                {
                	update_uoko_ad = 1;
                    goto next;
                }

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
