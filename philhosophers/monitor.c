/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marilins <marilins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 17:02:38 by marilins          #+#    #+#             */
/*   Updated: 2026/06/07 15:48:17 by marilins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_philo(t_table *table, int i, int *full)
{
	long	last_meal;
	int		meals;

	pthread_mutex_lock(&table->philo[i].meal_mutex);
	last_meal = table->philo[i].last_meal;
	meals = table->philo[i].meals_eaten;
	pthread_mutex_unlock(&table->philo[i].meal_mutex);
	if (get_time() - last_meal >= table->time_to_die)
	{
		set_stop(table);
		safe_print(&table->philo[i], "died");
		return (1);
	}
	if (table->has_optional && meals >= table->must_eat)
		(*full)++;
	return (0);
}

static int	check_simulation(t_table *table)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while (i < table->n_philo)
	{
		if (check_philo(table, i, &full))
			return (1);
		i++;
	}
	if (table->has_optional && full == table->n_philo)
	{
		set_stop(table);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (!is_stopped(table))
	{
		if (check_simulation(table))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
