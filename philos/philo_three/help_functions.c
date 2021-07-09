#include "philo_three.h"

unsigned long	get_time(void)
{
	struct timeval	te;
	unsigned long	milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000 + te.tv_usec / 1000;
	return (milliseconds);
}

int	quit_with_msg(char *message, int exit_code)
{
	write(2, message, ft_strlen(message));
	exit (exit_code);
}
