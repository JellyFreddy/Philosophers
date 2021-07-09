#include "philo_one.h"

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

int	destroy_forks(int nbr_philos,
			pthread_mutex_t *forks, pthread_mutex_t *mutex_for_prntng)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(mutex_for_prntng))
		return (0);
	while (i < nbr_philos)
	{
		if (pthread_mutex_destroy(&forks[i]))
			return (0);
		i++;
	}
	return (1);
}
