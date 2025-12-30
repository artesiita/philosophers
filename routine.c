/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:13:05 by lartes-s          #+#    #+#             */
/*   Updated: 2025/12/30 14:32:10 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    eat_routine(t_philo *philo)
{
    pthread_mutex_lock(philo->mutexes.left_fork);
    print_message("has taken a fork", philo);
    pthread_mutex_lock(philo->mutexes.right_fork);
    print_message("has taken a fork", philo);
    print_message("is eating", philo);
    pthread_mutex_lock(philo->mutexes.meal_lock);
    philo->times.last_meal = get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->mutexes.meal_lock);
    ft_usleep(philo->times.eat);
    pthread_mutex_unlock(philo->mutexes.right_fork);
    pthread_mutex_unlock(philo->mutexes.left_fork);
}

void    *philo_routine(void *pointer) 
{
    t_philo *philo;
    
    philo = (t_philo *)pointer;
    if (philo->philo_count == 1)
    {
        pthread_mutex_lock(philo->mutexes.left_fork);
        print_message("has taken a fork", philo);
        ft_usleep(philo->times.die);
        pthread_mutex_unlock(philo->mutexes.left_fork);
        return (NULL);
    }
    if (philo->id % 2 == 0)
        ft_usleep(1);
    while(1)
    {
        eat_routine(philo);
        print_message("is sleeping", philo);
        ft_usleep(philo->times.sleep);
        print_message("is thinking", philo);
    }
    return (NULL);
}

int    launcher(t_engine *engine)
{
    int i;

    if (!init_threads(engine))
    {
        error_message("error init_threads\n");
        return (0);
    }
    i = 0;
    while (i < engine->philo_count)
    {
        pthread_join(engine->philos[i].thread_id, NULL);
        i++;
    }
    return (1);
}

//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]