/*
** EPITECH PROJECT, 2023
** hehe
** File description:
** hehe
*/

#include "../headers/my.h"

//put a character
int my_putchar(char c)
{
    write(1, &c, 1);
    return 0;
}

//put a string
int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        write(1, str + i, 1);
        i++;
    }
    return (0);
}

//use ASCII to print lowercase
char *my_low(char *str)
{
    for (int i = 0 ; str[i] != '\0' ; i++) {
        if (str[i] >= 65 && str[i] <= 90)
            str[i] = str[i] + 32;
    }
    return (str);
}

//print a nbr
int my_put_nbr(int nb)
{
    long div = 1;
    long num = nb;
    int n = 0;

    while (num % div != num) {
        n++;
        div = div * 10;
    }
    if (num < 0) {
        write(1, "-", 1);
        div = -div;
    }
    if (n == 0)
        write(1, "0", 1);
    for (int i = 0 ; i < n ; i++) {
        my_putchar(48 + ((num % div) / (div / 10)));
        div = div / 10;
    }
    return (0);
}
