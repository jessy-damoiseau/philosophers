#include <philosophers.h>

size_t	len(char *str)
{
	size_t ret;

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
	int i;
	int sign;
	int result;

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
}

int	clear_struct(t_parse *parse, int ret)
{
	int i;

	i = 0;
	free(parse->forks);
	free(parse->philo);
	pthread_mutex_destroy(&parse->mtext);
	while (i < parse->nbforks)
		pthread_mutex_destroy(&parse->lock_fork[i++]);
	free(parse->lock_fork);
	return (ret);
}

long long int	get_time(t_parse *parse)
{
	long long int sec;
	long long int usec;

	gettimeofday(&parse->time, 0);
	sec = parse->time.tv_sec - parse->stime_ref;
	usec = parse->time.tv_usec - parse->utime_ref;
	return (sec * 1000 + (usec / 1000));
}
