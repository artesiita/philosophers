/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 12:58:24 by lartes-s          #+#    #+#             */
/*   Updated: 2025/12/30 15:35:49 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_valid_num(char *str)
{
    int i;

    i = 0;
    if (str[i] == '+')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
            i++;
        else
            return (0);
    }
    return (1);
}

int check_args(int ac, char **av)
{
    int     i;
    long    num;

	i = 0;
	if (ac < 5 || ac > 6)
        return ((printf("Argument ERROR\n")), 0);
	while (++i < ac)
	{
        if (!is_valid_num(av[i]))
            return ((printf("Argument ERROR\n")), 0);
		num = ft_atoi(av[i]);
		if (i == 1 && (num < 1 || num > PHILO_MAX_COUNT))
            return ((printf("Argument ERROR\n")), 0);
		else if (i == 5 && (num < 0 || num > INT_MAX))
            return ((printf("Argument ERROR\n")), 0);
		else if (i != 1 && i != 5 && (num < 1 || num > INT_MAX))
            return ((printf("Argument ERROR\n")), 0);
	}
    return (1);
}


int main(int ac, char **av)
{
    t_engine engine;
    int i;
    
    if (!check_args(ac, av))
        return (0);
    if(!init_engine(&engine, ac, av))
        return ((printf("error init_engine\n")), 0);
    if (!init_threads(&engine))
        return ((printf("error init_threads\n")), 0);
    monitor(engine.philos);
    i = 0;
    while (i < engine.philo_count)
    {
        pthread_join(engine.philos[i].thread_id, NULL);
        i++;
    }
    return (0);
}

//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
