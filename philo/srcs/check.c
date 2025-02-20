#include "../philo.h"
#include "utils/utils.h"

int	check_ok(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
	{
		write(2, "Usage: ./philo philo_count die_time \
eat_time sleep_time [eat_occurencies]\n", 75);
		return (0);
	}
	if (ft_atoi(av[1]) == 0)
	{
		write(2, "The number of philo can't be 0\n", 31);
		return (0);
	}
	i = 1;
	while (i < ac)
	{
		if (!is_extended_digit(av[i]) || ft_atoi(av[i]) == 235087234809897094)
		{
			write(2, "Please use valide positive int values\n", 38);
			return (0);
		}
		i++;
	}
	return (1);
}
