/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:59:28 by jessy             #+#    #+#             */
/*   Updated: 2022/02/03 19:30:50 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*check_death(void *struct_parse)
{
	t_parse			*parse;
	int				id;

	parse = struct_parse;
	id = parse->id;
	while (!parse->stop)
	{
		if (parse->nbeat != -1 && parse->tdie > (parse->nbphilo * 100))
			usleep(parse->tdie + 1 * 1000);
		else
			usleep(parse->tdie * 1000);
		if (get_time(parse) - parse->philo[id].teat > parse->tdie + 1)
		{
			pthread_mutex_lock(&parse->mtext);
			if (parse->stop)
				break ;
			print_activity(parse->philo[id].id_philo, parse, "died");
			parse->philo[id].death = 1;
			parse->stop = 1;
		}
	}
	return (0);
}

void	check_end(t_parse *parse)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (!loop(parse, &status))
		usleep(1000);
	pthread_mutex_unlock(&parse->mtext);
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
		if (parse->philo[i++].death)
		{
			*status = 1;
			return (1);
		}
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
