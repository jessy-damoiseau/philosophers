/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:17:14 by jessy             #+#    #+#             */
/*   Updated: 2021/12/16 17:42:20 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_parse *parse, int id, t_philo *philo)
{
	pthread_mutex_lock(&parse->lock_fork[id]);
	pthread_mutex_lock(&parse->mtext);
	printf("%lld ms philosopher number %d -> has taken a fork\n",
		get_time(parse), philo[id].id_philo);
	pthread_mutex_unlock(&parse->mtext);
	pthread_mutex_lock(&parse->lock_fork[philo[id].id_philo % parse->nbphilo]);
	pthread_mutex_lock(&parse->mtext);
	printf("%lld ms philosopher number %d -> has taken a fork\n",
		get_time(parse), philo[id].id_philo);
	pthread_mutex_unlock(&parse->mtext);
}

void	philo_eat(t_parse *parse, int id, t_philo *philo)
{
	pthread_mutex_lock(&parse->mtext);
	printf("%lld ms philosopher number %d -> is eating\n",
		get_time(parse), philo[id].id_philo);
	pthread_mutex_unlock(&parse->mtext);
	usleep(parse->teat * 1000);
	philo[id].teat = get_time(parse);
	pthread_mutex_unlock(&parse->lock_fork[id]);
	pthread_mutex_unlock(&parse->lock_fork[philo[id].id_philo
		% parse->nbphilo]);
}

void	philo_sleep(t_parse *parse, int id, t_philo *philo)
{
	pthread_mutex_lock(&parse->mtext);
	printf("%lld ms philosopher number %d -> is sleeping\n",
		get_time(parse), philo[id].id_philo);
	pthread_mutex_unlock(&parse->mtext);
	usleep(parse->tsleep * 1000);
}

void	philo_think(t_parse *parse, int id, t_philo *philo)
{
	pthread_mutex_lock(&parse->mtext);
	printf("%lld ms philosopher number %d -> is thinking\n",
		get_time(parse), philo[id].id_philo);
	pthread_mutex_unlock(&parse->mtext);
}

void	*action_philo(void *struct_parse)
{
	t_parse	*parse;
	int		id;

	parse = struct_parse;
	id = parse->id;
	while (!parse->stop)
	{
		take_forks(parse, id, parse->philo);
		philo_eat(parse, id, parse->philo);
		philo_sleep(parse, id, parse->philo);
		philo_think(parse, id, parse->philo);
		if (parse->philo[id].nbeat > 0)
			parse->philo[id].nbeat--;
	}
	return (0);
}
