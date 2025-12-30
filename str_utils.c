/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 12:58:48 by lartes-s          #+#    #+#             */
/*   Updated: 2025/12/30 19:29:46 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long	ft_atoi(char *str)
{
	long	res;
	int		i;

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

void	error_message(char *text)
{
	if (text)
		write(2, text, ft_strlen(text) + 1);
}

void	print_message(char *str, char *color, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->mutexes.write_lock);
	if (!dead_loop(philo) || str[0] == 'd')
	{
		time = get_time() - philo->times.born_time;
		printf("%s%zu: %d %s%s\n", color, time, philo->id, str, RESET);
	}
	pthread_mutex_unlock(philo->mutexes.write_lock);
}
