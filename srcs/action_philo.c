/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdamoise <jdamoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:17:14 by jessy             #+#    #+#             */
/*   Updated: 2022/02/09 19:39:42 by jdamoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_parse *parse, int id, t_philo *philo)
{
	pthread_mutex_lock(&parse->access);
	if (parse->stop)
	{
		pthread_mutex_unlock(&parse->access);
		return ;
	}
	pthread_mutex_unlock(&parse->access);
	
	pthread_mutex_lock(&parse->lock_fork[id]);
	pthread_mutex_lock(&parse->mtext);
	print_activity(philo[id].id_philo, parse, "has taken a fork");
	pthread_mutex_unlock(&parse->mtext);
	
	
	
	pthread_mutex_lock(&parse->access);
	if (parse->stop)
	{
		pthread_mutex_unlock(&parse->lock_fork[id]);
		pthread_mutex_unlock(&parse->access);
		return ;
	}
	pthread_mutex_unlock(&parse->access);
	
	pthread_mutex_lock(&parse->lock_fork[philo[id].id_philo % parse->nbphilo]);
	pthread_mutex_lock(&parse->mtext);
	print_activity(philo[id].id_philo, parse, "has taken a fork");
	print_activity(philo[id].id_philo, parse, "is eating");
	pthread_mutex_unlock(&parse->mtext);

	
	ft_usleep(parse->teat, parse);
	pthread_mutex_unlock(&parse->lock_fork[id]);
	pthread_mutex_unlock(&parse->lock_fork[philo[id].id_philo
		% parse->nbphilo]);
	pthread_mutex_lock(&parse->philo[id].access_eat);
	philo[id].teat = get_time(parse);
	pthread_mutex_unlock(&parse->philo[id].access_eat);
}

void	philo_sleep(t_parse *parse, int id, t_philo *philo)
{
	pthread_mutex_lock(&parse->access);
	if (parse->stop)
	{
		pthread_mutex_unlock(&parse->access);
		return ;
	}
	pthread_mutex_unlock(&parse->access);
	
	pthread_mutex_lock(&parse->mtext);
	print_activity(philo[id].id_philo, parse, "is sleeping");
	pthread_mutex_unlock(&parse->mtext);
	
	ft_usleep(parse->tsleep, parse);
	
	pthread_mutex_lock(&parse->access);
	if (parse->stop)
	{
		pthread_mutex_unlock(&parse->access);
		return ;
	}
	pthread_mutex_unlock(&parse->access);
	
	pthread_mutex_lock(&parse->mtext);
	print_activity(philo[id].id_philo, parse, "is thinking");
	pthread_mutex_unlock(&parse->mtext);
}

void	unlock_mutex(t_parse *parse, int id)
{
	pthread_mutex_unlock(&parse->mtext);
	pthread_mutex_unlock(&parse->access);
	pthread_mutex_unlock(&parse->philo[id].access_eat);
	pthread_mutex_unlock(&parse->lock_fork[id]);
	pthread_mutex_unlock(&parse->lock_fork[parse->philo[id].id_philo
		% parse->nbphilo]);
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
	while (!parse->stop)
	{
		take_forks(parse, id, parse->philo);
		
		pthread_mutex_lock(&parse->access);
		if (parse->stop)
		{
			pthread_mutex_unlock(&parse->access);
			break ;
		}
		pthread_mutex_unlock(&parse->access);
		
		philo_sleep(parse, id, parse->philo);
		
		pthread_mutex_lock(&parse->access);
		if (parse->stop)
		{
			pthread_mutex_unlock(&parse->access);
			break ;
		}
		pthread_mutex_unlock(&parse->access);
		if (parse->philo[id].nbeat > 0){
			parse->philo[id].nbeat--;
		}
			
	}
	unlock_mutex(parse, id);
	pthread_detach(death);
	return (0);
}
