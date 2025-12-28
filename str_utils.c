
#include "philo.h"

int ft_strlen(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
        i++;
    return (i);
}

int ft_atoi(char *str)
{
    int long    res;
    int         sign;
    int         i;

    i = 0;
    res = 0;
    sign = 1;
    while (((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13)) && str[i] != '\0')
        i++;
    while ((str[i] == '-' || str[i] == '+') && str[i] != '\0')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
    {
        res = (res * 10) + (str[i] - '0');
        i++;
    }
    return (res * sign);
}