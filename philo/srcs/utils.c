/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdamoise <jdamoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:40:18 by jessy             #+#    #+#             */
/*   Updated: 2022/02/09 19:13:49 by jdamoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

size_t	len(char *str)
{
	size_t	ret;

	ret = 0;
	while (str[ret])
		ret++;
	return (ret);
}

int	print_fd(char *str, int fd, int ret)
{
	write(fd, str, len(str));
	return (ret);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i++] - '0';
	return (result * sign);
}

void	init_struct(t_parse *parse)
{
	parse->nbphilo = 0;
	parse->nbeat = -1;
	parse->tdie = 0;
	parse->tsleep = 0;
	parse->nbforks = 0;
	parse->teat = 0;
	parse->philo = 0;
	parse->id = 0;
	parse->tab_thread = 0;
	parse->stop = 0;
}

int	clear_struct(t_parse *parse, int ret)
{
	int	i;

	i = 0;
	while (i < parse->nbphilo)
	{
		pthread_mutex_destroy(&parse->philo[i].access_death);
		pthread_mutex_destroy(&parse->philo[i++].access_eat);
	}
	free(parse->philo);
	pthread_mutex_destroy(&parse->mtext);
	pthread_mutex_destroy(&parse->access);
	i = 0;
	while (i < parse->nbforks)
		pthread_mutex_destroy(&parse->lock_fork[i++]);
	free(parse->tab_thread);
	free(parse->lock_fork);
	return (ret);
}
