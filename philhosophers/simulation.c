#include "philosophers.h"

static void	init_meal_times(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_time();
	while (i < table->n_philo)
	{
		pthread_mutex_lock(&table->philo[i].meal_mutex);
		table->philo[i].last_meal = table->start_time;
		pthread_mutex_unlock(&table->philo[i].meal_mutex);
		i++;
	}
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	safe_print(philo, "is thinking");
	return (NULL);
}

static int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				philo_routine, &table->philo[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

static void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
}

int	start_simulation(t_table *table)
{
	init_meal_times(table);
	if (!create_threads(table))
	{
		set_stop(table);
		return (0);
	}
	join_threads(table);
	return (1);
}