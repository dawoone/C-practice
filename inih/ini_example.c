/* Example: parse a simple configuration file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"

int module_cnt;

typedef struct
{
    int index;	
    char name[32];
    char email[32];
} configuration;

static int handler(void* user, const char* section, const char* name,
                   const char* value)
{
    int* cnt = (int*)user;

    #define MATCH2(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH2("protocol", "modules")) {
	    *cnt = atoi(value);
	    return 0;
    }
}

static int module_handler(void* user, const char* section, const char* name,
		          const char* value) {
    configuration** pconfig = (configuration**)user;
    
    #define MATCH(n) strcmp(name, n) == 0
    int idx = atoi(section);
    if (MATCH("name")) {
	    memcpy((*pconfig)[idx].name, value, 32);
    } else if (MATCH("email")) {
	    memcpy((*pconfig)[idx].email, value, 32);
    } else {
	    return 0;
    }
    (*pconfig)[idx].index = idx;
    return 1;
}

int main(int argc, char* argv[])
{
    if (ini_parse("test.ini", handler, &module_cnt) < 0) {
        printf("Can't load 'test.ini'\n");
        return 1;
    }
    printf("cnt=%d\n", module_cnt);

    configuration* config = (configuration*)malloc(sizeof(configuration)*module_cnt);
    if (ini_parse("test.ini", module_handler, &config) < 0) {
        printf("Can't load 'test.ini'\n");
        return 1;
    }

    for (int i = 0; i < module_cnt; i++) {
    	printf("index=%d, name=%s, email=%s\n", config[i].index, config[i].name, config[i].email);
    }

    free(config);

    return 0;
}
