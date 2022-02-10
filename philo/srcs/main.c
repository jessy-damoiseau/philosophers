/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdamoise <jdamoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:40:21 by jessy             #+#    #+#             */
/*   Updated: 2022/02/10 14:33:40 by jdamoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	init_mutex3(t_parse *parse)
{
	int	i;

	i = pthread_mutex_init(&parse->access, 0);
	if (i)
		return (clear_struct(parse,
				print_fd("mutex init failed\n", 2, 1)));
	return (0);
}

int	init_mutex2(t_parse *parse, int *tab)
{
	int	i;

	i = 0;
	while (i < parse->nbforks)
		tab[i++] = 0;
	i = 0;
	while (i < parse->nbforks)
	{
		tab[i] = pthread_mutex_init(&parse->lock_fork[i], 0);
		if (tab[i] != 0)
		{
			pthread_mutex_destroy(&parse->mtext);
			while (i >= 0)
				pthread_mutex_destroy(&parse->lock_fork[i--]);
			free(tab);
			clear_struct(parse, 1);
			return (print_fd("mutex init failed\n", 2, 1));
		}
		i++;
	}
	free(tab);
	return (init_mutex3(parse));
}

int	init_mutex(t_parse *parse)
{
	int	*tab;
	int	i;

	i = pthread_mutex_init(&parse->mtext, 0);
	if (i)
		return (print_fd("mutex init failed\n", 2, 1));
	parse->lock_fork = malloc(sizeof(pthread_mutex_t) * parse->nbforks);
	if (!parse->lock_fork)
	{
		pthread_mutex_destroy(&parse->mtext);
		return (print_fd("malloc failed\n", 2, 1));
	}
	tab = malloc(sizeof(int) * (parse->nbforks));
	if (!tab)
	{
		free(parse->lock_fork);
		pthread_mutex_destroy(&parse->mtext);
		return (print_fd("malloc failed\n", 2, 1));
	}
	return (init_mutex2(parse, tab));
}

int	init_thread(t_parse *parse)
{
	parse->id = 0;
	while (parse->id < parse->nbphilo)
	{
		if (pthread_create(&parse->tab_thread[parse->id],
				0, &action_philo, parse))
			return (clear_struct(parse,
					print_fd("fail to create thread\n", 2, 1)));
		usleep(350);
		pthread_mutex_lock(&parse->access);
		parse->id++;
		pthread_mutex_unlock(&parse->access);
	}
	check_end(parse);
	return (0);
}

int	main(int ac, char **av)
{
	t_parse		parse;

	init_struct(&parse);
	if (parsing(&parse, av, ac))
		return (1);
	if (init_mutex(&parse))
		return (1);
	parse.tab_thread = malloc(sizeof(pthread_t) * parse.nbphilo);
	if (!parse.tab_thread)
		return (clear_struct(&parse, 1));
	gettimeofday(&parse.time, 0);
	parse.stime_ref = parse.time.tv_sec;
	parse.utime_ref = parse.time.tv_usec;
	if (parse.nbphilo == 1)
	{
		print_activity(1, &parse, "has taken a fork");
		ft_usleep(parse.tdie, &parse);
		printf("%lld ms philosopher died\n",
			get_time(&parse));
		return (clear_struct(&parse, 0));
	}
	return (init_thread(&parse));
}
