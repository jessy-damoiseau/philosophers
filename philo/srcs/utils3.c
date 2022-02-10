/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdamoise <jdamoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:34:12 by jdamoise          #+#    #+#             */
/*   Updated: 2022/02/10 14:34:13 by jdamoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

long long int	get_time(t_parse *parse)
{
	long long int	sec;
	long long int	usec;

	gettimeofday(&parse->time, 0);
	sec = parse->time.tv_sec - parse->stime_ref;
	usec = parse->time.tv_usec - parse->utime_ref;
	return (sec * 1000 + (usec / 1000));
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_status(t_parse *parse)
{
	pthread_mutex_lock(&parse->access);
	if (parse->stop)
	{
		pthread_mutex_unlock(&parse->access);
		return (1);
	}
	pthread_mutex_unlock(&parse->access);
	return (0);
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
