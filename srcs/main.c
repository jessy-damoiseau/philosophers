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

size_t	get_time(t_parse *parse)
{
	size_t sec;
	size_t usec;

	gettimeofday(&parse->time, 0);
	sec = parse->time.tv_sec - parse->stime_ref;
	usec = parse->time.tv_usec - parse->utime_ref;
	return (sec * 1000 + (usec / 100));
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

void	*action_philo(void *struct_parse)
{
	t_parse *parse;
	t_philo *philo;
	int id;

	parse = struct_parse;
	philo = parse->philo;
	id = parse->id;
	pthread_mutex_lock(&parse->lock_fork[id]);
	parse->forks[id] = 0;
	pthread_mutex_lock(&parse->mtext);
	printf("%ld ms philosopher number %d -> has taken a fork\n", get_time(parse), philo[id].id_philo);
	pthread_mutex_unlock(&parse->mtext);
	pthread_mutex_lock(&parse->lock_fork[philo[id].id_philo % parse->nbphilo]);
	parse->forks[philo[id].id_philo % parse->nbphilo] = 0;
	pthread_mutex_lock(&parse->mtext);
	printf("%ld ms philosopher number %d -> has taken a fork\n", get_time(parse), philo[id].id_philo);
	printf("%ld ms philosopher number %d -> is eating\n", get_time(parse), philo[id].id_philo);
	pthread_mutex_unlock(&parse->mtext);
	usleep(parse->teat * 100);
	parse->forks[id] = 1;
	parse->forks[philo[id].id_philo % parse->nbphilo] = 1;
	pthread_mutex_unlock(&parse->lock_fork[id]);
	pthread_mutex_unlock(&parse->lock_fork[philo[id].id_philo % parse->nbphilo]);
	pthread_mutex_lock(&parse->mtext);
	printf("%ld ms philosopher number %d -> is sleeping\n", get_time(parse), philo[id].id_philo);
	pthread_mutex_unlock(&parse->mtext);
	usleep(parse->tsleep * 100);
	pthread_mutex_lock(&parse->mtext);
	printf("%ld ms philosopher number %d -> is thinking\n", get_time(parse), philo[id].id_philo);
	pthread_mutex_unlock(&parse->mtext);
	if (parse->philo[id].nbeat > 0)
		parse->philo[id].nbeat--;
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
			parse.id++;
		}
		parse.id = 0;
		while (parse.id < parse.nbphilo)
		{
			pthread_join(parse.tab_thread[parse.id], NULL);
			parse.id++;
		}
		parse.id = 0;
		finish_philo = 0;
		while (parse.id < parse.nbphilo)
		{
			if (!parse.philo[parse.id].nbeat)
				finish_philo++;
			parse.id++;
		}
		if (finish_philo == parse.nbphilo)
			break ;
	}
	return (clear_struct(&parse, 0));
}