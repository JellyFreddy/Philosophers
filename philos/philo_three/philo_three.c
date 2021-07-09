#include "philo_three.h"

void	*life_cycle(void *args)
{
	t_all_philos	*phil;
	int				had_eatings;

	had_eatings = 0;
	phil = (t_all_philos *)args;
	while (phil->thread_works && (phil->nbr_of_etngs == 0
			|| had_eatings < phil->nbr_of_etngs))
	{
		phil_eat(phil, &had_eatings);
		phil_sleep(phil);
		if (!phil->thread_works)
			break ;
		phil_print(phil, "is thinking\n",
			get_time() - phil->start_time, phil->index);
	}
	if (had_eatings == phil->nbr_of_etngs)
		phil->finished = 1;
	return (0);
}

void	kill_them_all(t_all_philos *our_phil)
{
	int	i;

	i = -1;
	while (++i < our_phil->nbr_philos)
		kill(our_phil->pids[i], SIGKILL);
}

int	main(int argc, char **argv)
{
	t_all_philos	our_philos;
	sem_t			forks;
	sem_t			print_control;
	sem_t			one_per_time;

	our_philos.start_time = get_time();
	our_philos.finished_philos = 0;
	if (argc != 5 && argc != 6)
		quit_with_msg("wrong number of arguments\n\0", 1);
	if (!init_philos(&our_philos, argv))
		quit_with_msg("wrong value of argumnets\n\0", 2);
	if (init_forks(&our_philos, &forks, &print_control, &one_per_time))
		quit_with_msg("failed to initialise semaphores\n\0", 3);
	init_threads(&our_philos);
	waitpid(-1, NULL, 0);
	kill_them_all(&our_philos);
	free(our_philos.pids);
	if (sem_close(our_philos.forks) || sem_close(our_philos.time_control)
		|| sem_close(our_philos.printing))
		quit_with_msg("failed to destroy forks\n\0", 6);
	return (0);
}
