/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marilins <marilins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 14:20:47 by marilins          #+#    #+#             */
/*   Updated: 2026/06/07 14:20:48 by marilins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				philo_routine, &table->philo[i]) != 0)
			return (0);
		table->threads_ready++;
		i++;
	}
	if (table->n_philo > 1)
	{
		if (pthread_create(&table->monitor, NULL,
				monitor_routine, table) != 0)
			return (0);
		table->monitor_ready = 1;
	}
	return (1);
}

static void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->threads_ready)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
	if (table->monitor_ready)
		pthread_join(table->monitor, NULL);
}

int	start_simulation(t_table *table)
{
	init_meal_times(table);
	if (!create_threads(table))
	{
		set_stop(table);
		join_threads(table);
		return (0);
	}
	join_threads(table);
	return (1);
}
