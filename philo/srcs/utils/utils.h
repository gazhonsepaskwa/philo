#ifndef UTILS_H
# define UTILS_H

#include <unistd.h>

int			is_extended_digit(char *str);
int			check_ok(int ac, char **av);
long		ft_atoi(const char *str);
long long	get_passed_ms(void);
void		msleep(int ms);

#endif
