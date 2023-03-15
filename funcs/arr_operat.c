/*
** EPITECH PROJECT, 2023
** hehehe
** File description:
** hehe
*/

#include "../headers/my.h"

//split une string en array
//puis renvoie adresse de l'array
char **str_to_array(char **dest, char *src)
{
    char *ptr = src;
    int i = 1;
    int j = 0;

    for (; *ptr; i += (*ptr == ' '), ptr++);
    ptr = src;
    dest = malloc(i * sizeof(char *) + 1);
    for (; *src; j++) {
        for (; *ptr != ' '; ptr++);
        if (*ptr)
            *ptr++ = 0;
        dest[j] = my_strdup(src);
        src = ptr;
    }
    dest[j] = 0;
    return (dest);
}

//sort array src en fonction des flags
//puis renvoie array src sorted
char **sort_array(char **src, flags_t *flags, char *path, char *tmp)
{
    int sorted = 0;
    struct stat buf1;
    struct stat buf2;
    while (!sorted) {
        sorted = 1;
        for (int i = 1; src[i]; i++) {
            stat(my_strcat(path, src[i - 1], 1), &buf1);
            stat(my_strcat(path, src[i], 1), &buf2);
            flags->t ?
                buf1.st_mtime < buf2.st_mtime ?
                    (tmp = src[i - 1], src[i - 1] = src[i], src[i] =
                    tmp, sorted = 0) : 0 :
                my_strcmp(my_low(my_strdup(src[i - 1])),
                my_low(my_strdup(src[i]))) == 1 - 2 * flags->r ?
                    (tmp = src[i - 1], src[i - 1] = src[i], src[i] =
                    tmp, sorted = 0) :
                    0;
        }
    }
    return (src);
}

//strdup recursif sur le directory precise par path
void my_recursive(char * const *tab, flags_t *flags, char **av, char *path)
{
    struct stat buf;
    char *npath = NULL;

    flags->total = 0;
    for (int i = 0 ; tab[i] ; i++) {
        if (tab[i][0] != '.' || flags->a) {
            npath = my_strcat(my_strdup(path), tab[i], 1);
            stat(npath, &buf);
            S_ISDIR(buf.st_mode) && my_strcmp(tab[i], "..") &&
            my_strcmp(tab[i], ".") ?
                (write(1, "\n", 1), my_ls(av, npath)) :
                0;
        }
    }
}

//affiche contenu du directory precisé par path
int my_show_word_array(char * const *tab, flags_t *flags, char **av, char *path)
{
    struct stat buf;

    lstat(path, &buf);
    if ((flags->_r || flags->d) && S_ISDIR(buf.st_mode)){
        my_putstr(path);
        write(1, (flags->d) ? ((path[my_strlen(path) - 1] != '/') ? "/\n" : "")
                : ":\n", 2);
    }
    (flags->l && S_ISDIR(buf.st_mode)) ? my_putstr("total "),
        my_put_nbr(flags->total), write(1, "\n", 1) : 1;
    for (int i = 0 ; tab[i] && !flags->d; i++) {
        if (tab[i][0] != '.' || flags->a){
            (flags->l) ? l_prefix(tab[i], path) : 1;
            my_putstr(tab[i]);
            write(1, "\n", 1);
        }
    }
    if (flags->_r)
        my_recursive(tab, flags, av, path);
    return (0);
}

//affiche tout ce qu'il faut pour le flag -l
void l_prefix(char *file, char *path)
{
    struct stat buf;

    lstat(my_strcat(my_strdup(path), file, 1), &buf);
    (S_ISDIR(buf.st_mode)) ? my_putchar('d') : 1;
    (S_ISREG(buf.st_mode)) ? my_putchar('-') : 1;
    (S_ISLNK(buf.st_mode)) ? my_putchar('l') : 1;
    my_putchar((buf.st_mode & S_IRUSR) ? 'r' : '-');
    my_putchar((buf.st_mode & S_IWUSR) ? 'w' : '-');
    my_putchar((buf.st_mode & S_IXUSR) ? 'x' : '-');
    my_putchar((buf.st_mode & S_IRGRP) ? 'r' : '-');
    my_putchar((buf.st_mode & S_IWGRP) ? 'w' : '-');
    my_putchar((buf.st_mode & S_IXGRP) ? 'x' : '-');
    my_putchar((buf.st_mode & S_IROTH) ? 'r' : '-');
    my_putchar((buf.st_mode & S_IWOTH) ? 'w' : '-');
    my_putchar((buf.st_mode & S_IXOTH) ? 'x' : '-');
    my_putchar(' ');
    l_prefix2(buf);
}
