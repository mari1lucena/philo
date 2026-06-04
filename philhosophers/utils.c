/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marilins <marilins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 02:35:47 by marilins          #+#    #+#             */
/*   Updated: 2026/06/04 13:18:08 by marilins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	is_stopped(t_table *table)
{
	int	stop;

	pthread_mutex_lock(&table->stop_mutex);
	stop = table->stop_now;
	pthread_mutex_unlock(&table->stop_mutex);
	return (stop);
}

void	set_stop(t_table *table)
{
	pthread_mutex_lock(&table->stop_mutex);
	table->stop_now = 1;
	pthread_mutex_unlock(&table->stop_mutex);
}

void	safe_print(t_philo *philo, char *msg)
{
	t_table	*table;
	int		stop;

	table = philo->table;
	pthread_mutex_lock(&table->print_mutex);
	pthread_mutex_lock(&table->stop_mutex);
	stop = table->stop_now;
	if (!stop || msg[0] == 'd')
		printf("%ld %d %s\n", get_time() - table->start_time,
			philo->id, msg);
	pthread_mutex_unlock(&table->stop_mutex);
	pthread_mutex_unlock(&table->print_mutex);
}

/*void	safe_print(t_philo *philo, char *msg)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->print_mutex);
	if (!is_stopped(table) || msg[0] == 'd')
		printf("%ld %d %s\n", get_time() - table->start_time,
			philo->id, msg);
	pthread_mutex_unlock(&table->print_mutex);
}*/

void	smart_sleep(t_table *table, long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (is_stopped(table))
			break ;
		usleep(1000);
	}
}

/*void	smart_sleep(t_table *table, long time)
{
	long	start;

	start = get_time();
	while (!is_stopped(table) && get_time() - start < time)
		usleep(500);
}*/

//Nunca fazer lock em stop_mutex e depois tentar pegar print_mutex.