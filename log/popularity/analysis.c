#!/usr/local/bin/tcc -run
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* time group sender */

int main(void)
{
        FILE *f;
        char time[128], group[128], sender[128];
        char ptime[128];

        f = fopen("stat.sorted", "r");
        setenv("TZ", "Asia/Hong_Kong", 1);
        while (3 == fscanf(f, "%s%s%s",
                                time, group, sender))
        {
                struct tm tm;
                strptime(time, "%s", &tm);
                strftime(ptime, sizeof ptime,
                                "%c %Z", &tm);

                printf("%s %s %s\n", ptime,
                        group, sender);
        }

        fclose(f);
        return 0;
}
