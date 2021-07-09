#ifndef PHILO_TWO_H
# define PHILO_TWO_H

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
	sem_t			*forks;
	sem_t			*printing;
	sem_t			*time_control;
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
void			*life_cycle(void *args);
int				join_threads(t_all_philos *our_philos);
void			killer(t_all_philos *our_philos);
void			init_curr_phil(t_all_philos *our_philos);
int				init_philos(t_all_philos *our_philos, char **argv);
void			init_current_fork(t_all_philos *our_philos, sem_t *forks,
					sem_t *print_control, sem_t *one_per_time);
int				init_forks(t_all_philos *our_philos, sem_t *forks,
					sem_t *print_control, sem_t *one_per_time);
int				init_threads(t_all_philos *our_philos);
unsigned long	get_time(void);
int				quit_with_msg(char *message, int exit_code);
int				ft_strlen(char *str);
void			phil_print(t_current_philo *phil,
					char *str, unsigned long time, int index);
int				phil_forks(t_current_philo *phil);
void			phil_eat(t_current_philo *phil, int *eatings);
void			phil_sleep(t_current_philo *phil);

#endif