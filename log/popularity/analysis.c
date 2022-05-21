#!/usr/local/bin/tcc -run
#include <stdio.h>

/* time group sender */

int main(void)
{
        FILE *f;
        char time[128], group[128], sender[128];

        f = fopen("stat", "r");
        while (3 == fscanf(f, "%s%s%s",
                                time, group, sender))
        {
                printf("%s %s %s\n", time, group,
                                sender);
        }

        fclose(f);
        return 0;
}
