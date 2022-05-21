#!/usr/local/bin/tcc -run
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

typedef int bool;

#define ZERO_IF(cond) if (cond) return 0
bool is_check_cmd(char *buf)
{
        char *s, *s1;

        s = strstr(buf, "\"Plain\"");
        ZERO_IF (!s);
        s = strstr(s, "\"text\"");
        ZERO_IF (!s);
        s = strchr(s, ':');
        ZERO_IF (!s);
        s = strchr(s, '"');
        ZERO_IF (!s);
        ++s;

        return s[0] == 'c' && s == strstr(s, "check");
}

#define RET_IF(cond) if (cond) return

void print_time(char *buf)
{
        char *s, *s1, ch;

        s = strstr(buf, "\"time\"");
        RET_IF (!s);
        s = strchr(s, ':');
        RET_IF (!s);

        while (!isdigit(*s)) ++s;
        s1 = s;
        while (isdigit(*s1)) ++s1; /* s1 -> end */
        ch = *s1;
        *s1 = '\0';
        printf("%s", s);
        *s1 = ch;
}

void print_group(char *buf)
{
        char *s, *s1, ch;

        s = strstr(buf, "\"sender\"");
        RET_IF (!s);
        s = strstr(buf, "\"group\"");
        RET_IF (!s);
        s = strstr(s, "\"id\"");
        RET_IF (!s);
        s = strchr(s, ':');
        RET_IF (!s);

        while (!isdigit(*s)) ++s;
        s1 = s;
        while (isdigit(*s1)) ++s1; /* s1 -> end */
        ch = *s1;
        *s1 = '\0';
        printf("%s", s);
        *s1 = ch;
}

void print_sender(char *buf)
{
        char *s, *s1, ch;

        s = strstr(buf, "\"sender\"");
        RET_IF (!s);
        s = strstr(s, "\"id\"");
        RET_IF (!s);
        s = strchr(s, ':');
        RET_IF (!s);

        while (!isdigit(*s)) ++s;
        s1 = s;
        while (isdigit(*s1)) ++s1; /* s1 -> end */
        ch = *s1;
        *s1 = '\0';
        printf("%s", s);
        *s1 = ch;
}


/* check popularity of `check` command */
void proc_file(char *fn)
{
        FILE *f;
        char buf[1024 * 1024];

        f = fopen(fn, "r");
        if (!f)
        {
                fprintf(stderr, "cannot open %s\n", fn);
                return;
        }
        fread(buf, 1, sizeof buf, f);
        fclose(f);

        if (!is_check_cmd(buf))
                return;
        print_time(buf); putchar(' ');
        print_group(buf); putchar(' ');
        print_sender(buf); putchar('\n');
}

void proc(char *dir)
{
        int c;
        DIR *d;
        struct dirent *e;

        chdir(dir);
        d = opendir(".");

        c = 0;
        while ((e = readdir(d)))
        {
                if (e->d_name[0] == '.')
                        continue;
                proc_file(e->d_name);
                
                ++c;
                if (c % 100 == 0)
                        fprintf(stderr, "%d ", c);
        }

        fprintf(stderr, "\n");
        closedir(d);
}

/* a.out ~/lognana/groupmsg/1234566/ ~/lognana/groupmsg/23455/ ... */
int main(int argc, char *argv[])
{
        int i;

        for (i = 1; i < argc; ++i)
        {
                fprintf(stderr, "folder %d of %d (%s)\n", i, argc, argv[i]);
                proc(argv[i]);
        }

        return 0;
}
