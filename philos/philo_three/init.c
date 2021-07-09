#include "philo_three.h"

void	check_death(t_all_philos *our_philos)
{
	unsigned long	time;

	if (our_philos->finished)
		exit (1);
	time = get_time();
	if (our_philos->limit < time)
	{
		sem_wait(our_philos->printing);
		our_philos->thread_works = 0;
		printf("%lu %d %s", time - our_philos->start_time,
			   our_philos->index, "is dead\n");
		exit(2);
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
	our_philos->pids = malloc(sizeof(int) * our_philos->nbr_of_etngs);
	if (!our_philos->pids)
		return (0);
	return (1);
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
	our_philos->time_control = one_per_time;
	our_philos->forks = forks;
	our_philos->printing = print_control;
	return (0);
}

void	init_threads(t_all_philos *our_philos)
{
	int	i;
	int	pid;

	i = -1;
	while (++i < our_philos->nbr_philos)
	{
		pid = fork();
		our_philos->pids[i] = pid;
		if (pid == 0)
		{
			our_philos->thread_works = 1;
			our_philos->index = i + 1;
			our_philos->finished = 0;
			pthread_create(&our_philos->thread, NULL, life_cycle, our_philos);
			our_philos->limit = get_time() + our_philos->time_to_die;
			pthread_detach(our_philos->thread);
			while (our_philos->thread_works)
				check_death(our_philos);
		}
		usleep(50);
	}
}
