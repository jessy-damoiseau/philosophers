# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdamoise <jdamoise@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/09 14:45:20 by bmaudet           #+#    #+#              #
#    Updated: 2022/02/10 14:29:10 by jdamoise         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = philo

################################################################################

SRCS1 =	main.c action_philo.c parsing.c utils.c utils2.c utils3.c activity.c

################################################################################

HEADERS_DIR	=	header
SRCS_DIR	=	srcs
OBJS_DIR	=	objs

################################################################################

CC =		@gcc
RM =		@rm -rf
CFLAGS =	-Wall -Wextra -Werror -g3 -I$(HEADERS_DIR) #-fsanitize=thread
################################################################################

_RED		=	\033[31m
_GREEN		=	\033[32m
_YELLOW		=	\033[33m
_CYAN		=	\033[96m

################################################################################

OBJS1 = $(addprefix $(OBJS_DIR)/, $(SRCS1:.c=.o))

OBJS2 = $(addprefix $(OBJS_DIR)/, $(SRCS2:.c=.o))

################################################################################

all:	init_dir init_name1 $(NAME1)

################################################################################

init_dir:
		@ $(shell mkdir -p $(OBJS_DIR))

init_name1:
		if test -f $(NAME1);\
		then echo "$(_CYAN)[$(NAME1) program already created]";\
		else echo "$(_YELLOW)[Initialize program]";\
		fi

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
				@ echo "\t$(_YELLOW) compiling... $*.c"
				$(CC) $(CFLAGS) -c $< -o $@

################################################################################

$(NAME1):	$(OBJS1)
			echo "\t$(_YELLOW)[Creating $(NAME1) program]"
					$(CC) $(OBJS1) -o $(NAME1) $(CFLAGS)
					echo "$(_GREEN)[$(NAME1) program created & ready]"

################################################################################

clean:
		echo "$(_RED)[cleaning up .out & objects files]"
		$(RM) $(OBJS1) $(OBJS2) $(OBJS_DIR)

fclean:		clean
			echo "$(_RED)[cleaning up .out, objects & library files]"
			$(RM) $(NAME1) $(NAME2)

re:		fclean all

################################################################################


.SILENT:
		all

.PHONY: clean all fclean re
