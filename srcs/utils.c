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
	parse->nbeat = 0;
	parse->tdie = 0;
	parse->tsleep = 0;
	parse->nbforks = 0;
	parse->teat = 0;
}