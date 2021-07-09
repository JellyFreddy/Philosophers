#include "philo_two.h"

void	*life_cycle(void *args)
{
	t_current_philo	*phil;
	int				had_eatings;

	had_eatings = 0;
	phil = (t_current_philo *)args;
	while (g_simulation_works == 1 && (phil->nbr_of_etngs == 0
			|| had_eatings < phil->nbr_of_etngs))
	{
		phil_eat(phil, &had_eatings);
		phil_sleep(phil);
		if (!g_simulation_works)
			return (0);
		phil_print(phil, "is thinking\n",
			get_time() - g_start_time, phil->index);
	}
	if (had_eatings == phil->nbr_of_etngs)
	{
		g_finished_philos++;
		phil->finished = 1;
	}
	return (0);
}

int	join_threads(t_all_philos *our_philos)
{
	int	i;

	i = 0;
	while (i < our_philos->nbr_philos)
	{
		if (pthread_join(our_philos->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	killer(t_all_philos *our_philos)
{
	unsigned long	time;
	int				i;

	while (g_simulation_works && g_finished_philos
		< our_philos->nbr_philos)
	{
		i = -1;
		while (++i < our_philos->nbr_philos)
		{
			time = get_time();
			if (our_philos->philos[i].finished == 0
				&& our_philos->philos[i].limit < time)
			{
				g_simulation_works = 0;
				phil_print(&our_philos->philos[i], "is dead\n",
					time - g_start_time, our_philos->philos[i].index);
				break ;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_all_philos	our_philos;
	sem_t			forks;
	sem_t			print_control;
	sem_t			one_per_time;

	g_simulation_works = 1;
	g_start_time = get_time();
	g_finished_philos = 0;
	if (argc != 5 && argc != 6)
		quit_with_msg("wrong number of arguments\n\0", 1);
	if (!init_philos(&our_philos, argv))
		quit_with_msg("wrong value of argumnets\n\0", 2);
	if (init_forks(&our_philos, &forks, &print_control, &one_per_time))
		quit_with_msg("failed to initialise semaphores\n\0", 3);
	if (!(init_threads(&our_philos)))
		quit_with_msg("failed to initialise threads\n\0", 4);
	killer(&our_philos);
	if (!(join_threads(&our_philos)))
		quit_with_msg("failed to join threads\n\0", 5);
	if (sem_close(our_philos.philos[0].forks)
		|| sem_close(our_philos.philos[0].printing)
		|| sem_close(our_philos.philos[0].time_control))
		quit_with_msg("failed to destroy forks\n\0", 6);
	free(our_philos.philos);
	return (0);
}
