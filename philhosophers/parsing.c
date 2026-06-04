/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marilins <marilins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 16:49:57 by marilins          #+#    #+#             */
/*   Updated: 2026/06/04 02:30:35 by marilins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include "philosophers.h"

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	safe_atol(char *str, long *result)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	if (!is_number(str))
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (nb > (LONG_MAX - (str[i] - '0')) / 10)
			return (0);
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	*result = nb;
	return (1);
}

static int	parse_required(char **argv, t_table *table)
{
	long	tmp;

	if (!safe_atol(argv[1], &tmp) || tmp < 1 || tmp > INT_MAX)
		return (0);
	table->n_philo = (int)tmp;
	if (!safe_atol(argv[2], &tmp) || tmp < 1)
		return (0);
	table->time_to_die = tmp;
	if (!safe_atol(argv[3], &tmp) || tmp < 1)
		return (0);
	table->time_to_eat = tmp;
	if (!safe_atol(argv[4], &tmp) || tmp < 1)
		return (0);
	table->time_to_sleep = tmp;
	return (1);
}

int	parse_args(int argc, char **argv, t_table *table)
{
	long	tmp;

	if (argc != 5 && argc != 6)
		return (0);
	table->has_optional = 0; // por padrao não ha arg opcional
	table->must_eat = -1; //como não há opcional não há numero min. de ref.
	table->stop_now = 0; // por padrao nao para imediatamente
	table->philo = NULL; //free NULL é seguro
	table->forks = NULL;
	table->forks_ready = 0;
	table->philos_ready = 0;
	table->print_ready = 0;
	table->stop_ready = 0;
	if (!parse_required(argv, table))
		return (0);
	if (argc == 6)
	{
		if (!safe_atol(argv[5], &tmp) || tmp > INT_MAX)
			return (0);
		table->has_optional = 1;
		table->must_eat = (int)tmp;
		if (table->must_eat == 0)
			table->stop_now = 1;
	}
	return (1);
}

