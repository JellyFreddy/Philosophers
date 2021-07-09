#include "philo_one.h"

void	init_current_philos(t_all_philos *our_philos)
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
	init_current_philos(our_philos);
	return (1);
}

pthread_mutex_t	*init_forks(t_all_philos *our_philos,
		pthread_mutex_t *forks, pthread_mutex_t *mutex_for_prntng)
{
	int	i;

	i = -1;
	forks = malloc(sizeof(pthread_mutex_t) * our_philos->nbr_philos);
	if (!forks)
		return (0);
	while (++i < our_philos->nbr_philos)
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (0);
	if (pthread_mutex_init(mutex_for_prntng, NULL) != 0)
		return (0);
	i = -1;
	while (++i < our_philos->nbr_philos)
	{
		our_philos->philos[i].printing_mutex = mutex_for_prntng;
		our_philos->philos[i].left_fork = &forks[i];
		our_philos->philos[i].right_fork
			= &forks[(i + 1) % our_philos->nbr_philos];
	}
	return (forks);
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

int	init_argument(int argc, char **argv, t_all_philos *our_philos)
{
	if (argc != 5 && argc != 6)
	{
		write(2, "wrong number of arguments\n", 26);
		return (1);
	}
	if (!init_philos(our_philos, argv))
	{
		write(2, "wrong value of argumnets\n", 25);
		return (1);
	}
	return (0);
}
