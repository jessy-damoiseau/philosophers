#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>


typedef struct	s_philo
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
	int				*forks;
	t_philo			*philo;
	time_t			stime_ref;
	suseconds_t		utime_ref;
	struct timeval	time;
	int				id;
}				t_parse;

size_t	len(char *str);
int		print_fd(char *str, int fd, int ret);
int		ft_atoi(char *str);
void	init_struct(t_parse *parse);
int		clear_struct(t_parse *parse, int ret);
long long int	get_time(t_parse *parse);
void	*action_philo(void *struct_parse);
#endif