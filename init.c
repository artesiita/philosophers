/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 12:58:15 by lartes-s          #+#    #+#             */
/*   Updated: 2025/12/29 18:45:06 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
void    print_engine(t_engine *engine, int i, int right_fork)
{
    printf("--------------\n");
    printf("ENGINE->PHILOS[%d]\n", i);
    printf("--------------\n");
    printf("Philo id: %d\n", engine->philos[i].id);
    printf("Philo count: %d\n", engine->philo_count);
    printf("Time to die: %zu\n", engine->philos[i].times.die);
    printf("Time to eat: %zu\n", engine->philos[i].times.eat);
    printf("Time to sleep: %zu\n", engine->philos[i].times.sleep);
    printf("Must eat: %d\n", engine->philos[i].must_eat);
    printf("Left fork: %d\n", i);
    printf("Right fork: %d\n", right_fork);
    printf("--------------\n");
    printf("\n");
}*/
    

void    init_mutexes(t_engine *engine)
{
    int i;

    i = 0;
    while (i < engine->philo_count)
    {
        pthread_mutex_init(&engine->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&engine->meal_lock, NULL);
    pthread_mutex_init(&engine->write_lock, NULL);
    pthread_mutex_init(&engine->dead_lock, NULL);
}

void init_philos(t_engine *engine, int ac, char **av)
{
    int i;
    int right_fork;

    i = 0;
    while (i < engine->philo_count)
    {
        engine->philos[i].id = i + 1;
        engine->philos[i].times.die = engine->times.die;
        engine->philos[i].times.eat = engine->times.eat;
        engine->philos[i].times.sleep = engine->times.sleep;
        engine->philos[i].philo_count = engine->philo_count;
        if (ac == 6)
            engine->philos[i].must_eat = (int)ft_atoi(av[5]);
        else
            engine->philos[i].must_eat = -1;
        engine->philos[i].mutexes.left_fork = &engine->forks[i];
        right_fork = (i + 1) % engine->philo_count;
        engine->philos[i].mutexes.right_fork = &engine->forks[right_fork];
        engine->philos[i].mutexes.write_lock = &engine->write_lock;
        engine->philos[i].mutexes.meal_lock = &engine->meal_lock;
        engine->philos[i].mutexes.dead_lock = &engine->dead_lock;
        engine->philos[i].times.born_time = engine->start_time;
        //print_engine(engine, i, right_fork);
        i++;
    }
}

int init_threads(t_engine *engine)
{
    int i;

    i = 0;
    while (i < engine->philo_count)
    {
        engine->philos[i].times.last_meal = engine->start_time;
        if (pthread_create(&engine->philos[i].thread_id, NULL, &philo_routine, &engine->philos[i]) != 0)
        {
            printf("Error creating thread\n");
            return (0);
        }
        i++;
    }
    return (1);
}

int init_engine(t_engine *engine, int ac, char **av)
{
    engine->philo_count = (int)ft_atoi(av[1]);
    engine->times.die = ft_atoi(av[2]);
    engine->times.eat = ft_atoi(av[3]);
    engine->times.sleep = ft_atoi(av[4]);
    engine->start_time = get_time();
    engine->philos = malloc(sizeof(t_philo) * engine->philo_count);
    if (!engine->philos)
        return (0);
    engine->forks = malloc(sizeof(t_mutex) * engine->philo_count);
    if (!engine->forks)
    {
        free(engine->philos);
        return (0);
    }
    init_mutexes(engine);
    init_philos(engine, ac, av);
    return (1);
}

//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
