#include "philo_three.h"

void	phil_print(t_all_philos *phil, char *str, unsigned long time, int index)
{
	sem_wait(phil->printing);
	printf("%lu %d %s", time, index, str);
	sem_post(phil->printing);
}

int	phil_fork(t_all_philos *phil)
{
	sem_wait(phil->time_control);
	sem_wait(phil->forks);
	if (!phil->thread_works)
	{
		sem_post(phil->time_control);
		sem_post(phil->forks);
		return (0);
	}
	phil_print(phil, "has taken a fork\n",
		get_time() - phil->start_time, phil->index);
	sem_wait(phil->forks);
	if (!phil->thread_works)
	{
		sem_post(phil->time_control);
		sem_post(phil->forks);
		sem_post(phil->forks);
		return (0);
	}
	phil_print(phil, "has taken a fork\n",
		get_time() - phil->start_time, phil->index);
	sem_post(phil->time_control);
	return (1);
}

void	phil_eat(t_all_philos *phil, int *eatings)
{
	unsigned long	time;

	if (!phil_fork(phil))
		return ;
	time = get_time();
	phil->limit = time + phil->time_to_die;
	(*eatings)++;
	if (!phil->thread_works)
	{
		sem_post(phil->forks);
		sem_post(phil->forks);
		return ;
	}
	phil_print(phil, "is eating\n", get_time() - phil->start_time, phil->index);
	while (time + phil->time_to_eat > get_time())
		usleep(100);
	sem_post(phil->forks);
	sem_post(phil->forks);
}

void	phil_sleep(t_all_philos *phil)
{
	unsigned long	time;

	time = get_time();
	if (!phil->thread_works)
		return ;
	phil_print(phil, "is sleeping\n",
		get_time() - phil->start_time, phil->index);
	while (time + phil->time_to_sleep > get_time())
		usleep(100);
}
