/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:47:53 by jessy             #+#    #+#             */
/*   Updated: 2021/12/16 18:19:19 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	i;

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
	return (0);
}

int	check_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j++]))
				return (1);
		}
	}
	return (0);
}

int	parsing(t_parse *parse, char **args, int ac)
{
	int	i;
	int	fill;

	i = 0;
	if (ac < 5)
		return (print_fd("not enought args\n", 2, 1));
	if (ac > 6)
		return (print_fd("to many args\n", 2, 1));
	if (check_args(args))
		return (print_fd("one of the arguments is not a number\n", 2, 1));
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
