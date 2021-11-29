/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:17:14 by jessy             #+#    #+#             */
/*   Updated: 2021/11/29 17:54:14 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_parse *parse, int id, t_philo *philo)
{
	pthread_mutex_lock(&parse->lock_fork[id]);
	parse->forks[id] = 0;
	pthread_mutex_lock(&parse->mtext);
	printf("%lld ms philosopher number %d -> has taken a fork\n",
		get_time(parse), philo[id].id_philo);
	pthread_mutex_unlock(&parse->mtext);
	
	pthread_mutex_lock(&parse->lock_fork[philo[id].id_philo % parse->nbphilo]);
	parse->forks[philo[id].id_philo % parse->nbphilo] = 0;
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
		parse->forks[id] = 1;
		parse->forks[philo[id].id_philo % parse->nbphilo] = 1;
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

int		check_death(t_parse *parse, int id, t_philo *philo)
{
	long long int time;
	
	time = 0;
	time = get_time(parse) - philo[id].teat;
	if (time < 0)
		time *= -1;
	pthread_mutex_lock(&parse->mtext);
	printf("id: %d -> time : %lld, tdie : %d\n",id, time, parse->tdie);
	pthread_mutex_unlock(&parse->mtext);
	if (time > parse->tdie)
	{
		philo[id].death = 1;
		return (1);
	}
	return (0);
}


void	*action_philo(void *struct_parse)
{
	t_parse	*parse;
	int		id;
	int		act;

	parse = struct_parse;
	id = parse->id;
	act = -1;
	while (++act < 3)
	{
		if (check_death(parse, id, parse->philo))
			return (0);
		if (act == 0)
			take_forks(parse, id, parse->philo);
		else if (act == 1)
			philo_eat(parse, id, parse->philo);
		else if(act == 2)
			philo_sleep(parse, id, parse->philo);
		if (check_death(parse, id, parse->philo))
			return (0);
	}
	philo_think(parse, id, parse->philo);
	if (parse->philo[id].nbeat > 0)
		parse->philo[id].nbeat--;
	return (0);
}