/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marilins <marilins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 01:08:56 by marilins          #+#    #+#             */
/*   Updated: 2026/06/04 02:27:52 by marilins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	destroy_philo_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_ready)
	{
		pthread_mutex_destroy(&table->philo[i].meal_mutex);
		i++;
	}
	table->philos_ready = 0;
}

static void	destroy_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->forks_ready)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	table->forks_ready = 0;
}

void	clean_table(t_table *table)
{
	if (!table)
		return ;
	if (table->philo)
		destroy_philo_mutexes(table);
	if (table->forks)
		destroy_forks(table);
	if (table->print_ready)
	{
		pthread_mutex_destroy(&table->print_mutex);
		table->print_ready = 0;
	}
	if (table->stop_ready)
	{
		pthread_mutex_destroy(&table->stop_mutex);
		table->stop_ready = 0;
	}
	free(table->philo);
	free(table->forks);
	table->philo = NULL;
	table->forks = NULL;
}
