#include "utils.h"

static int	is_digit(int n)
{
	if (n < 48 || n > 57)
		return (0);
	else
		return (1);
}

int	is_extended_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			i++;
		if (!is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
