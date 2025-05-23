/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:14:02 by norabino          #+#    #+#             */
/*   Updated: 2025/04/20 22:08:12 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_init_table(t_table *table, char **av)
{
	table->nb_philo = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		table->how_many_meals = ft_atol(av[5]);
	else
		table->how_many_meals = -1;
	table->simulation_ended = 0;
	table->start_simulation = ft_get_current_timestamp();
	pthread_create(&table->monitor, NULL, ft_monitor, table);
	pthread_mutex_init(&table->info, NULL);
	pthread_mutex_init(&table->write, NULL);
	//pthread_mutex_init(&(*table)->replete, NULL);
	table->philos = malloc(table->nb_philo * sizeof(t_philo));
	table->forks = malloc(table->nb_philo * sizeof(t_fork));
}

int	ft_init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->forks[i].id = i + 1;
		pthread_mutex_init(&table->forks[i].fork, NULL);
		i++;
	}
	return (1);
}

int	ft_init_philos(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->nb_philo)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->left_fork = &table->forks[i];
		if (i == table->nb_philo - 1)
			philo->right_fork = &table->forks[0];
		else
			philo->right_fork = &table->forks[i + 1];
		philo->table = table;
		philo->last_meal = 0;
		pthread_create(&philo->id_thread, NULL, ft_routine, philo);
		i++;
	}
	return (1);
}

t_table	*ft_init(char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (table);
	ft_init_table(table, av);
	if (!ft_init_forks(table) || !ft_init_philos(table))
		return (printf("error malloc philo ou fork"), NULL);
	printf("nbphilo = %d\ntime to die = %d\ntime to eat = %d\ntime to sleep = %d\nhowmanyeat = %d\n\n\n", table->nb_philo, table->time_to_die, table->time_to_eat, table->time_to_sleep, table->how_many_meals);
	//int	i = 0;
	//while (i < table->nb_philo)
	//{
	//	printf("Philo %d\n", table->philos[i].id);
	//	printf("adjacent Forks %d and %d\n\n", table->philos[i].left_fork->id, table->philos[i].right_fork->id);
	//	i++;
	//}
	return (table);
}
