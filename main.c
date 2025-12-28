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
		error_message("[Argument Count ERROR]\n", 1);
	while (++i < ac)
	{
        if (!is_valid_num(av[i]))
        {
            error_message("[Argument ERROR]\n", 1);
            return (0);
        }
		num = ft_atoi(av[i]);
		if (i == 1 && (num < 1 || num > PHILO_MAX_COUNT))
        {
            error_message("[Argument ERROR]\n", 1);
            return (0);
        }
		else if (i == 5 && (num < 0 || num > INT_MAX))
        {
			error_message("[Argument ERROR]\n", 1);
            return (0);
        }
		else if (i != 1 && i != 5 && (num < 1 || num > INT_MAX))
        {
            error_message("[Argument ERROR]\n", 1);
            return (0);
        }

	}
    return (1);
}


int main(int ac, char **av)
{
    if (!check_args(ac, av))
        return (0);
    printf("args OK\n");
    return (0);
}



//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]