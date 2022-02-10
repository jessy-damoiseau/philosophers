/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdamoise <jdamoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:17:14 by jessy             #+#    #+#             */
/*   Updated: 2022/02/10 14:29:00 by jdamoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	fork1(t_parse *parse, int id, t_philo *philo)
{
	pthread_mutex_lock(&parse->lock_fork[id]);
	pthread_mutex_lock(&parse->mtext);
	if (check_status(parse))
		return (1);
	print_activity(philo[id].id_philo, parse, "has taken a fork");
	pthread_mutex_unlock(&parse->mtext);
	return (0);
}

int	fork2(t_parse *parse, int id, t_philo *philo)
{
	pthread_mutex_lock(&parse->lock_fork[philo[id].id_philo % parse->nbphilo]);
	pthread_mutex_lock(&parse->mtext);
	if (check_status(parse))
		return (1);
	print_activity(philo[id].id_philo, parse, "has taken a fork");
	print_activity(philo[id].id_philo, parse, "is eating");
	pthread_mutex_unlock(&parse->mtext);
	if (check_status(parse))
		return (1);
	ft_usleep(parse->teat, parse);
	pthread_mutex_unlock(&parse->lock_fork[id]);
	pthread_mutex_unlock(&parse->lock_fork[philo[id].id_philo
		% parse->nbphilo]);
	pthread_mutex_lock(&parse->philo[id].access_eat);
	philo[id].teat = get_time(parse);
	pthread_mutex_unlock(&parse->philo[id].access_eat);
	return (0);
}

int	sleeping(t_parse *parse, int id, t_philo *philo)
{
	pthread_mutex_lock(&parse->mtext);
	if (check_status(parse))
		return (1);
	print_activity(philo[id].id_philo, parse, "is sleeping");
	pthread_mutex_unlock(&parse->mtext);
	ft_usleep(parse->tsleep, parse);
	pthread_mutex_lock(&parse->mtext);
	if (check_status(parse))
		return (1);
	print_activity(philo[id].id_philo, parse, "is thinking");
	pthread_mutex_unlock(&parse->mtext);
	return (0);
}

void	go_action(t_parse *parse, int id)
{
	while (!check_status(parse))
	{
		if (!fork1(parse, id, parse->philo))
			if (!fork2(parse, id, parse->philo))
				if (!sleeping(parse, id, parse->philo))
					if (parse->philo[id].nbeat > 0)
						parse->philo[id].nbeat--;
	}
}

void	*action_philo(void *struct_parse)
{
	t_parse		*parse;
	int			id;
	pthread_t	death;

	parse = struct_parse;
	pthread_mutex_lock(&parse->access);
	id = parse->id;
	pthread_mutex_unlock(&parse->access);
	pthread_mutex_lock(&parse->philo[id].access_eat);
	parse->philo[id].teat = get_time(parse);
	pthread_mutex_unlock(&parse->philo[id].access_eat);
	if (pthread_create(&death, 0, &check_death, parse))
	{
		clear_struct(parse, print_fd("fail to create thread\n", 2, 1));
		return (0);
	}
	go_action(parse, id);
	pthread_join(death, 0);
	unlock_mutex(parse, id);
	return (0);
}
