#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>

#include "keys.h"
/*
    Get event
    read file /dev/input/[event]
    print keys on the screen, using array from keys.h
*/

char* GetEvent();

int main(void)
{

    char dir_event[20] = "/dev/input/";
    strcat(dir_event,GetEvent());

    struct input_event event;    
    int fd = open(dir_event, O_RDONLY);

    if (!fd)
        exit(2);
    
    while (read(fd, &event, sizeof(event)) > 0)
    {
        if (event.type == EV_KEY && event.value == 1 && event.code < 128)
            printf("%s", keys[event.code]);
        fflush(stdout);
    }
    return 0;
}

char* GetEvent()
{
    char* pattern = 
    "grep -E 'Handlers|EV' /proc/bus/input/devices |"
    "grep -B1 120013 |"
    "grep -E -o event[0-9]{2}";

    FILE* pipe = popen(pattern, "r");
    if (!pipe)
        exit(1);

    static char event[9];
    fgets(event, 9, pipe);
    event[strlen(event) - 1] = '\0';

    return event;
}