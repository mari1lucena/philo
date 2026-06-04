/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marilins <marilins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 01:08:06 by marilins          #+#    #+#             */
/*   Updated: 2026/06/04 02:17:14 by marilins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	alloc_table(t_table *table)
{
	table->philo = malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philo)
		return (0);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->forks)
	{
		free(table->philo);
		table->philo = NULL;
		return (0);
	}
	return (1);
}

static int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (0);
		table->forks_ready++;
		i++;
	}
	return (1);
}

static int	init_global_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (0);
	table->print_ready = 1;
	if (pthread_mutex_init(&table->stop_mutex, NULL) != 0)
		return (0);
	table->stop_ready = 1;
	return (1);
}

static int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].left_fork = i;
		table->philo[i].right_fork = (i + 1) % table->n_philo;
		table->philo[i].meals_eaten = 0;
		table->philo[i].last_meal = 0;
		table->philo[i].table = table;
		if (pthread_mutex_init(&table->philo[i].meal_mutex, NULL) != 0)
			return (0);
		table->philos_ready++;
		i++;
	}
	return (1);
}

int	init_table(t_table *table)
{
	if (!alloc_table(table))
		return (0);
	if (!init_forks(table) || !init_global_mutexes(table)
		|| !init_philos(table))
	{
		clean_table(table);
		return (0);
	}
	return (1);
}