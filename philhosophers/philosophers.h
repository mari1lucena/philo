#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	t_table			*table;
};

struct s_table
{
	int				n_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				has_optional;
	int				must_eat;
	int				stop_now;
	long			start_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	int				forks_ready;
	int				philos_ready;
	int				print_ready;
	int				stop_ready;
};



//parsing.c
int	parse_args(int argc, char **argv, t_table *table);

//initi.c
int		init_table(t_table *table);

//clean.c
void	clean_table(t_table *table);

// utils.c
long	get_time(void);
int		is_stopped(t_table *table);
void	set_stop(t_table *table);
void	safe_print(t_philo *philo, char *msg);
void	smart_sleep(t_table *table, long time);

/* simulation.c */
int		start_simulation(t_table *table);

/* routine.c */
void	*philo_routine(void *arg);

#endif