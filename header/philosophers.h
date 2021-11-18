#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct	s_philo
{
				int id_philo;
				int	nbeat;
				int nb_fork;
}				t_philo;

typedef struct s_parse
{
	int	nbphilo;
	int	tdie;
	int	teat;
	int	tsleep;
	int	nbeat;
	int	nbforks;
	int	*forks;
	time_t stime_ref;
	suseconds_t utime_ref;
	struct timeval time;
}				t_parse;

size_t	len(char *str);
int		print_fd(char *str, int fd, int ret);
int		ft_atoi(char *str);
void	init_struct(t_parse *parse);
#endif