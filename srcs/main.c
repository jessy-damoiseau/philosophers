#include <philosophers.h>

void	fill_struct(t_parse *parse, int fill, int i)
{
	if (i == 1)
	{
		parse->nbphilo = fill;
		parse->nbforks = fill;
	}
	else if (i == 2)
		parse->tdie = fill;
	else if (i == 3)
		parse->teat = fill;
	else if (i == 4)
		parse->tsleep = fill;
	else if (i == 5)
		parse->nbeat = fill;
}

int	fill_philo(t_parse *parse)
{
	int i;

	i = 0;
	parse->philo = malloc(sizeof(t_philo) * parse->nbphilo);
	if (!parse->philo)
		return (print_fd("error malloc\n", 2, 1));
	while (i < parse->nbphilo)
	{
		parse->philo[i].nbeat = parse->nbeat;
		parse->philo[i].id_philo = i + 1;
		parse->philo[i].teat = 0;
		parse->philo[i].death = 0;
		i++;
	}
	parse->forks = malloc(sizeof(int) * parse->nbforks);
	if (!parse->forks)
	{
		free(parse->philo);
		return (print_fd("error malloc\n", 2, 1));
	}
	i = 0;
	while (i < parse->nbforks)
		parse->forks[i++] = 1;
	return (0);
}

int	parsing(t_parse *parse, char **args, int ac)
{
	int	i;
	int fill;

	i = 0;
	if (ac < 5)
		return (print_fd("not enought args\n", 2, 1));
	if (ac > 6)
		return (print_fd("to many args\n", 2, 1));
	while (args[++i])
	{
		fill = ft_atoi(args[i]);
		if (fill < 0)
		{
			print_fd(args[i], 2, 0);
			return (print_fd(": invalid args\n", 2, 1));
		}
		fill_struct(parse, fill, i);
	}
	return (fill_philo(parse));
}

int init_mutex(t_parse *parse)
{
	int tab[parse->nbforks];
	int i;

	i = pthread_mutex_init(&parse->mtext, 0);
	if (i)
		return (print_fd("mutex init failed\n", 2, 1));
	parse->lock_fork = malloc(sizeof(pthread_mutex_t) * parse->nbforks);
	if (!parse->lock_fork)
	{
		pthread_mutex_destroy(&parse->mtext);
		return (print_fd("malloc failed\n", 2, 1));
	}
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
			clear_struct(parse, 1);
			return (print_fd("mutex init failed\n", 2, 1));
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_parse	parse;
	int		finish_philo;

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
	while (1)
	{
		parse.id = 0;
		while (parse.id < parse.nbphilo)
		{
			pthread_create(&parse.tab_thread[parse.id], 0, &action_philo, &parse);
			usleep(10);
			parse.id++;
		}
		parse.id = 0;
		finish_philo = 0;
		while (parse.id < parse.nbphilo)
		{
			if (parse.philo[parse.id].death)
			{
				printf("philosopher is dead\n");
				return (clear_struct(&parse, 0));
			}
			if (!parse.philo[parse.id].nbeat)
				finish_philo++;
			parse.id++;
		}
		if (finish_philo == parse.nbphilo)
			break ;

	}
	return (clear_struct(&parse, 0));
}