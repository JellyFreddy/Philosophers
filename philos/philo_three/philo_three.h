#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>

typedef struct s_all_philos
{
	char			thread_works;
	char			finished;
	int				index;
	int				finished_philos;
	int				nbr_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				nbr_of_etngs;
	unsigned long	start_time;
	unsigned long	limit;
	sem_t			*forks;
	sem_t			*printing;
	sem_t			*time_control;
	pthread_t		thread;
	int				*pids;
}				t_all_philos;

int				ft_atoi(const char *str);
int				ft_strlen(char *str);
void			init_threads(t_all_philos *our_philos);
int				init_forks(t_all_philos *our_philos, sem_t *forks,
					sem_t *print_control, sem_t *one_per_time);
int				init_philos(t_all_philos *our_philos, char **argv);
void			check_death(t_all_philos *our_philos);
void			phil_print(t_all_philos *phil,
					char *str, unsigned long time, int index);
int				phil_fork(t_all_philos *phil);
void			phil_eat(t_all_philos *phil, int *eatings);
void			phil_sleep(t_all_philos *phil);
int				quit_with_msg(char *message, int exit_code);
unsigned long	get_time(void);
void			kill_them_all(t_all_philos *our_phil);
void			*life_cycle(void *args);

#endif