/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:59:28 by jessy             #+#    #+#             */
/*   Updated: 2021/12/16 18:19:09 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*check_death(void *struct_parse)
{
	t_parse			*parse;
	int				id;
	long long int	time;
	long long int	diff;

	parse = struct_parse;
	while (!parse->stop)
	{
		id = 0;
		time = get_time(parse);
		while (id < parse->nbphilo && !parse->stop)
		{
			diff = parse->philo[id].teat - time;
			if (diff < 0)
				diff *= -1;
			if (diff > parse->tdie)
			{
				parse->philo[id].death = 1;
				parse->stop = 1;
			}
			id++;
		}
		usleep(1000);
	}
	return (0);
}

void	check_end(t_parse *parse)
{
	int	status;

	status = 0;
	while (!loop(parse, &status))
		usleep(1000);
	if (status == 1)
		print_fd("A philosopher died\n", 1, 0);
	if (status == 2)
		print_fd("All philosophers have finised eating\n", 1, 0);
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
