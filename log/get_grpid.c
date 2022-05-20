#include <ctype.h>
#include <stdio.h>
#include <string.h>

void proc(char *fn)
{
        FILE *f;
        char buf[100 * 1024], *s, *s1;

        f = fopen(fn, "r");
        fread(buf, 1, sizeof buf, f);
        fclose(f);

        s = strstr(buf, "\"sender\"");
        if (!s) goto proc_err;
        s = strstr(s, "\"group\"");
        if (!s) goto proc_err;
        s = strstr(s, "\"id\"");
        if (!s) goto proc_err;
        s = strchr(s, ':');
        if (!s) goto proc_err;

        while (!isdigit(*s)) ++s;
        s1 = s;
        while (isdigit(*s1)) ++s1;
        *s1 = '\0';

        puts(s);
        return;

proc_err:
        return;
}

int main(int argc, char *argv[])
{
        if (argc != 2)
                return 1;

        proc(argv[1]);

        return 0;
}
