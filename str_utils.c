/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 12:58:48 by lartes-s          #+#    #+#             */
/*   Updated: 2025/12/29 12:58:53 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_strlen(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
        i++;
    return (i);
}

long ft_atoi(char *str)
{
    long    res;
    int     i;

    i = 0;
    res = 0;
    if (str[i] == '+')
        i++;
    while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
    {
        res = (res * 10) + (str[i] - '0');
        i++;
    }
    return (res);
}
