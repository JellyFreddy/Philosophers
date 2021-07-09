#include "philo_two.h"

void	phil_print(t_current_philo *phil,
				   char *str, unsigned long time, int index)
{
	sem_wait(phil->printing);
	printf("%lu %d %s", time, index + 1, str);
	sem_post(phil->printing);
}

int	phil_forks(t_current_philo *phil)
{
	sem_wait(phil->time_control);
	sem_wait(phil->forks);
	if (!g_simulation_works)
	{
		sem_post(phil->time_control);
		sem_post(phil->forks);
		return (0);
	}
	phil_print(phil, "has taken a fork\n",
		get_time() - g_start_time, phil->index);
	sem_wait(phil->forks);
	if (!g_simulation_works)
	{
		sem_post(phil->time_control);
		sem_post(phil->forks);
		sem_post(phil->forks);
		return (0);
	}
	phil_print(phil, "has taken a fork\n",
		get_time() - g_start_time, phil->index);
	sem_post(phil->time_control);
	return (1);
}

void	phil_eat(t_current_philo *phil, int *eatings)
{
	unsigned long	time;

	if (!phil_forks(phil))
		return ;
	time = get_time();
	phil->limit = time + phil->time_to_die;
	(*eatings)++;
	if (!g_simulation_works)
	{
		sem_post(phil->forks);
		sem_post(phil->forks);
		return ;
	}
	phil_print(phil, "is eating\n", get_time() - g_start_time, phil->index);
	while (time + phil->time_to_eat > get_time())
		usleep(100);
	sem_post(phil->forks);
	sem_post(phil->forks);
}

void	phil_sleep(t_current_philo *phil)
{
	unsigned long	time;

	time = get_time();
	if (!g_simulation_works)
		return ;
	phil_print(phil, "is sleeping\n", get_time() - g_start_time, phil->index);
	while (time + phil->time_to_sleep > get_time())
		usleep(100);
}
