#include "philo_two.h"

void	init_curr_phil(t_all_philos *our_philos)
{
	int	i;

	i = -1;
	while (++i < our_philos->nbr_philos)
	{
		our_philos->philos[i].time_to_sleep = our_philos->time_to_sleep;
		our_philos->philos[i].time_to_eat = our_philos->time_to_eat;
		our_philos->philos[i].time_to_die = our_philos->time_to_die;
		our_philos->philos[i].nbr_of_etngs = our_philos->nbr_of_etngs;
	}
}

int	init_philos(t_all_philos *our_philos, char **argv)
{
	our_philos->nbr_philos = ft_atoi(argv[1]);
	our_philos->time_to_die = ft_atoi(argv[2]);
	our_philos->time_to_eat = ft_atoi(argv[3]);
	our_philos->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		our_philos->nbr_of_etngs = ft_atoi(argv[5]);
	else
		our_philos->nbr_of_etngs = 0;
	if (our_philos->nbr_philos < 2 || our_philos->time_to_die < 0
		|| our_philos->time_to_eat < 0 || our_philos->time_to_sleep < 0
		|| our_philos->nbr_of_etngs < 0)
		return (0);
	our_philos->philos
		= malloc(sizeof(t_current_philo) * our_philos->nbr_philos);
	if (!our_philos->philos)
		return (0);
	init_curr_phil(our_philos);
	return (1);
}

void	init_current_fork(t_all_philos *our_philos, sem_t *forks,
						  sem_t *print_control, sem_t *one_per_time)
{
	int	i;

	i = -1;
	while (++i < our_philos->nbr_philos)
	{
		our_philos->philos[i].time_control = one_per_time;
		our_philos->philos[i].forks = forks;
		our_philos->philos[i].printing = print_control;
	}
}

int	init_forks(t_all_philos *our_philos, sem_t *forks,
				  sem_t *print_control, sem_t *one_per_time)
{
	sem_unlink("forks\0");
	sem_unlink("print_control\0");
	sem_unlink("one_per_time\0");
	forks = sem_open("forks\0", O_CREAT, 0666, our_philos->nbr_philos);
	if (forks == SEM_FAILED)
	{
		write(2, "failed to create forks\n", 23);
		return (1);
	}
	print_control = sem_open("print_control\0", O_CREAT, 0666, 1);
	if (print_control == SEM_FAILED)
	{
		write(2, "failed to create forks\n", 23);
		return (1);
	}
	one_per_time = sem_open("one_per_time\0", O_CREAT, 0666, 1);
	if (one_per_time == SEM_FAILED)
	{
		write(2, "failed to create forks\n", 23);
		return (1);
	}
	init_current_fork(our_philos, forks, print_control, one_per_time);
	return (0);
}

int	init_threads(t_all_philos *our_philos)
{
	int	i;

	i = -1;
	while (++i < our_philos->nbr_philos)
	{
		our_philos->philos[i].finished = 0;
		our_philos->philos[i].index = i;
		if (pthread_create(&our_philos->philos[i].thread,
				NULL, life_cycle, &our_philos->philos[i]) != 0)
			return (0);
		our_philos->philos[i].limit = get_time() + our_philos->time_to_die;
		usleep(50);
	}
	return (1);
}
