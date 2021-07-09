#include "philo_one.h"

void	phil_print(t_current_philo *phil,
				   char *str, unsigned long time, int index)
{
	pthread_mutex_lock(phil->printing_mutex);
	printf("%lu %d %s", time, index + 1, str);
	pthread_mutex_unlock(phil->printing_mutex);
}

int	phil_forks(t_current_philo *phil)
{
	pthread_mutex_lock(phil->left_fork);
	if (!g_simulation_works)
	{
		pthread_mutex_unlock(phil->left_fork);
		return (0);
	}
	phil_print(phil, "has taken a fork\n",
		get_time() - g_start_time, phil->index);
	pthread_mutex_lock(phil->right_fork);
	if (!g_simulation_works)
	{
		pthread_mutex_unlock(phil->left_fork);
		pthread_mutex_unlock(phil->right_fork);
		return (0);
	}
	phil_print(phil, "has taken a fork\n",
		get_time() - g_start_time, phil->index);
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
		pthread_mutex_unlock(phil->left_fork);
		pthread_mutex_unlock(phil->right_fork);
		return ;
	}
	phil_print(phil, "is eating\n", get_time() - g_start_time, phil->index);
	while (time + phil->time_to_eat > get_time())
		usleep(100);
	pthread_mutex_unlock(phil->left_fork);
	pthread_mutex_unlock(phil->right_fork);
}

void	phil_sleep(t_current_philo	*phil)
{
	unsigned long	time;

	time = get_time();
	if (!g_simulation_works)
		return ;
	phil_print(phil, "is sleeping\n", get_time() - g_start_time, phil->index);
	while (time + phil->time_to_sleep > get_time())
		usleep(100);
}
