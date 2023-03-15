/*
** EPITECH PROJECT, 2023
** hehe
** File description:
** hehe
*/

#include "../headers/my.h"

//init les flags à 0
flags_t *init_flags(void)
{
    flags_t *flags = malloc(sizeof(flags_t));

    flags->l = 0;
    flags->r = 0;
    flags->d = 0;
    flags->t = 0;
    flags->_r = 0;
    flags->a = 0;
    flags->total = 0;
    return flags;
}

//definition flags
flags_t *set_flags(char **av)
{
    flags_t *flags = init_flags();
    int valid = 0;

for (int i = 1; i < my_ac(0); i++) {
    for (int j = 1; av[i][0] == '-' && av[i][j]; j++, valid = 0) {
        av[i][j] == 'l' ? flags->l = 1, valid = 1 : (void)1;
        av[i][j] == 'd' ? flags->d = 1, valid = 1 : (void)1;
        av[i][j] == 'r' ? flags->r = 1, valid = 1 : (void)1;
        av[i][j] == 'R' ? flags->_r = 1, valid = 1 : (void)1;
        av[i][j] == 't' ? flags->t = 1, valid = 1 : (void)1;
        av[i][j] == 'a' ? flags->a = 1, valid = 1 : (void)1;
        valid ? (void)1 : (write(2, "ERROR: Invalid flag\n", 21), exit(84));
        }
    }
    return flags;
}

//number len
int my_nlen(int n)
{
    int i = 0;

    for (; n; n /= 10, i++);
    return i;
}

//afficher information temps fichier
void my_puttime(char *time)
{
    time += 4;
    for (int colon = 0; *time != ':' || !colon; time++){
        (*time == ':') ? colon = 1 : 1;
        my_putchar(*time);
    }
}

//afficher informations fichiers
void l_prefix2(struct stat buf)
{
    struct passwd *pwd = getpwuid(buf.st_uid);
    struct group *gp = getgrgid(buf.st_gid);

    my_put_nbr((int)buf.st_nlink);
    my_putchar(' ');
    my_putstr(pwd->pw_name);
    my_putchar(' ');
    my_putstr(gp->gr_name);
    my_putchar(' ');
    for (int i = 0; i > my_nlen(buf.st_size) - 5; my_putchar(' '), i--);
    my_put_nbr(buf.st_size);
    my_putchar(' ');
    my_puttime(ctime(&buf.st_mtime));
    my_putchar(' ');
}
