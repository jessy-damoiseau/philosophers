/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdamoise <jdamoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:59:28 by jessy             #+#    #+#             */
/*   Updated: 2022/02/10 15:29:20 by jdamoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	go_death(t_parse *parse, int id)
{
	pthread_mutex_lock(&parse->philo[id].access_death);
	parse->philo[id].death = 1;
	pthread_mutex_unlock(&parse->philo[id].access_death);
	pthread_mutex_lock(&parse->access);
	parse->stop = 1;
	pthread_mutex_unlock(&parse->access);
	pthread_mutex_unlock(&parse->philo[id].access_eat);
	pthread_mutex_lock(&parse->mtext);
	print_activity(parse->philo[id].id_philo, parse, "died");
	pthread_mutex_unlock(&parse->mtext);
}

void	*check_death(void *struct_parse)
{
	t_parse			*parse;
	int				id;

	parse = struct_parse;
	pthread_mutex_lock(&parse->access);
	id = parse->id;
	while (!parse->stop)
	{
		pthread_mutex_unlock(&parse->access);
		usleep(parse->tdie + 1000);
		pthread_mutex_lock(&parse->philo[id].access_eat);
		if (!check_status(parse) && (get_time(parse)
				- parse->philo[id].teat > parse->tdie))
			go_death(parse, id);
		pthread_mutex_unlock(&parse->philo[id].access_eat);
		pthread_mutex_lock(&parse->access);
	}
	pthread_mutex_unlock(&parse->access);
	return (0);
}

void	check_end(t_parse *parse)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (!loop(parse, &status))
		usleep(100);
	while (i < parse->nbphilo)
		pthread_join(parse->tab_thread[i++], 0);
	if (status == 2)
	{
		print_fd("All philosophers have finised eating\n", 1, 0);
	}
	clear_struct(parse, 0);
}

int	loop(t_parse *parse, int *status)
{
	int	i;

	i = 0;
	while (i < parse->nbphilo)
	{
		pthread_mutex_lock(&parse->philo[i].access_death);
		if (parse->philo[i].death)
		{
			pthread_mutex_unlock(&parse->philo[i].access_death);
			*status = 1;
			return (1);
		}
		pthread_mutex_unlock(&parse->philo[i].access_death);
		i++;
	}
	i = 0;
	while (i < parse->nbphilo)
	{
		if (parse->philo[i++].nbeat)
			return (0);
	}
	parse->stop = 1;
	*status = 2;
	return (1);
}
