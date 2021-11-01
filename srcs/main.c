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
		printf("fill : |%d|\n", fill);
		if (fill < 0)
		{
			print_fd(args[i], 2, 0);
			return (print_fd(": invalid args\n", 2, 1));
		}
		fill_struct(parse, fill, i);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_parse parse;

	init_struct(&parse);
	parsing(&parse, av, ac);
	return (0);
}