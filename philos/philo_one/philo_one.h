#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>

char			g_finished_philos;
char			g_simulation_works;
unsigned long	g_start_time;

typedef struct s_current_philo
{
	char			finished;
	int				index;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				nbr_of_etngs;
	unsigned long	limit;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*printing_mutex;
	pthread_t		thread;
}				t_current_philo;

typedef struct s_all_philos
{
	int				nbr_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				nbr_of_etngs;
	t_current_philo	*philos;
}				t_all_philos;

int				ft_atoi(const char *str);
int				ft_strlen(char *str);
void			*life_cycle(void *args);
void			killer(t_all_philos *our_philos);
void			phil_print(t_current_philo *phil,
					char *str, unsigned long time, int index);
int				phil_forks(t_current_philo *phil);
void			phil_eat(t_current_philo *phil, int *eatings);
void			phil_sleep(t_current_philo	*phil);
int				join_threads(t_all_philos *our_philos);
int				destroy_forks(int nbr_philos,
					pthread_mutex_t *forks, pthread_mutex_t *mutex_for_prntng);
unsigned long	get_time(void);
int				quit_with_msg(char *message, int exit_code);
void			init_current_philos(t_all_philos *our_philos);
int				init_philos(t_all_philos *our_philos, char **argv);
pthread_mutex_t	*init_forks(t_all_philos *our_philos,
					pthread_mutex_t *forks, pthread_mutex_t *mutex_for_prntng);
int				init_threads(t_all_philos *our_philos);
int				init_argument(int argc, char **argv, t_all_philos *our_philos);

#endif