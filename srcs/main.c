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

int	fill_philo(t_parse *parse, t_philo **philo)
{
	int i;

	i = 0;
	(*philo) = malloc(sizeof(t_philo) * parse->nbphilo);
	if (!(*philo))
		return (print_fd("error malloc\n", 2, 1));
	while (i < parse->nbphilo)
	{
		(*philo)[i].nbeat = parse->nbeat;
		(*philo)[i].id_philo = i + 1;
		i++;
	}
	parse->forks = malloc(sizeof(int) * parse->nbforks);
	if (!parse->forks)
		return (print_fd("error malloc\n", 2, 1));
	i = 0;
	while (i < parse->nbforks)
		parse->forks[i++] = 1;
	return (0);
}

int	parsing(t_parse *parse, char **args, int ac, t_philo **philo)
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
	return (fill_philo(parse, philo));
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

void	action_philo(t_parse *parse, t_philo *philo, int id)
{
	if (!parse->forks[id]){}
		//mutex_lock1
	parse->forks[id] = 0;
	//mutex_lock3
	printf("%ld ms philosopher number %d -> has taken a fork\n", get_time(parse), philo[id].id_philo);
	//mutex_unlock3
	if (!parse->forks[philo[id].id_philo % parse->nbphilo]){}
		//mutex_lock2
	parse->forks[philo[id].id_philo % parse->nbphilo] = 0;
	//mutex_lock3
	printf("%ld ms philosopher number %d -> has taken a fork\n", get_time(parse), philo[id].id_philo);
	printf("%ld ms philosopher number %d -> is eating\n", get_time(parse), philo[id].id_philo);
	//mutex_unlock3
	usleep(parse->teat * 100);
	parse->forks[id] = 1;
	parse->forks[philo[id].id_philo % parse->nbphilo] = 1;
	//mutex_unlock1
	//mutex_unlock2;
	//mutex_lock3
	printf("%ld ms philosopher number %d -> is sleeping\n", get_time(parse), philo[id].id_philo);
	//mutex_unlock3
	usleep(parse->tsleep * 100);
	//mutex_lock3
	printf("%ld ms philosopher number %d -> is thinking\n", get_time(parse), philo[id].id_philo);
	//mutex_unlock3
}

int	main(int ac, char **av)
{
	t_parse parse;
	t_philo	*philo;
	int i;

	philo = 0;
	init_struct(&parse);
	parsing(&parse, av, ac, &philo);
	gettimeofday(&parse.time, 0);
	parse.stime_ref = parse.time.tv_sec;
	parse.utime_ref = parse.time.tv_usec;
	while (1)
	{
		i = 0;
		while (i < parse.nbphilo)
		{
			action_philo(&parse, philo, i++);
			//break ;
		}
		while (1);
	}
	return (0);
}