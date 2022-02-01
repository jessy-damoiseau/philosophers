#include "../header/philosophers.h"

int		len_nb(long long int nb)
{
	int i;

	i = 1;
	while (nb / 10)
	{
		i++;
		nb /= 10;
	}
	return (i);
}


char	*lltoa(long long int nb)
{
	int len;
	char	*ret;

	len = len_nb(nb);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	ret[len] = 0;
	len--;
	while (len >= 0)
	{
		ret[len--] = nb % 10 + '0';
		nb /= 10;
	}
	return (ret);
}

char	*itoa(int nb)
{
	int len;
	char	*ret;

	len = len_nb((long long int)nb);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	ret[len] = 0;
	len--;
	while (len >= 0)
	{
		ret[len--] = nb % 10 + '0';
		nb /= 10;
	}
	return (ret);
}

void	ft_putstr(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

void	print_activity(int id_philo, t_parse *parse, char *act)
{
	ft_putstr(lltoa(get_time(parse)));
	ft_putstr(" ms philosopher number ");
	ft_putstr(itoa(id_philo));
	ft_putstr(" -> ");
	ft_putstr(act);
	ft_putstr("\n");
}
