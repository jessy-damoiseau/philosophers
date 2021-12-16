/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jessy <jessy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:40:24 by jessy             #+#    #+#             */
/*   Updated: 2021/12/16 18:13:28 by jessy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id_philo;
	int				nbeat;
	int				nb_fork;
	long long int	teat;
	int				death;
}				t_philo;

typedef struct s_parse
{
	pthread_mutex_t	mtext;
	pthread_mutex_t	*lock_fork;
	pthread_t		*tab_thread;
	int				nbphilo;
	int				tdie;
	int				teat;
	int				tsleep;
	int				nbeat;
	int				nbforks;
	t_philo			*philo;
	time_t			stime_ref;
	suseconds_t		utime_ref;
	struct timeval	time;
	int				id;
	int				stop;
}				t_parse;

void			take_forks(t_parse *parse, int id, t_philo *philo);
void			philo_eat(t_parse *parse, int id, t_philo *philo);
void			philo_sleep(t_parse *parse, int id, t_philo *philo);
void			philo_think(t_parse *parse, int id, t_philo *philo);
void			*action_philo(void *struct_parse);
int				init_mutex2(t_parse *parse, int *tab);
int				init_mutex(t_parse *parse);
int				init_thread(t_parse *parse);
int				main(int ac, char **av);
void			fill_struct(t_parse *parse, int fill, int i);
int				fill_philo(t_parse *parse);
int				parsing(t_parse *parse, char **args, int ac);
size_t			len(char *str);
int				print_fd(char *str, int fd, int ret);
int				ft_atoi(char *str);
void			init_struct(t_parse *parse);
int				clear_struct(t_parse *parse, int ret);
void			*check_death(void *struct_parse);
void			check_end(t_parse *parse);
int				loop(t_parse *parse, int *status);
long long int	get_time(t_parse *parse);
int				ft_isdigit(int c);
#endif
