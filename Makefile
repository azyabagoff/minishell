# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 18:33:46 by sesnowbi          #+#    #+#              #
#    Updated: 2021/07/01 16:14:01 by sesnowbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
LIBFT_D	= ./libft
LIBFT_A	= libft.a
LIBFT_H = libft.h
LIBFT	= libft/libft.a

SRCS	= test_main.c GNL/get_next_line.c GNL/get_next_line_utils.c \
			srcs/other_utils/utils_2dim_arr.c srcs/other_utils/exit_errors.c srcs/other_utils/realloc_2dim_arr.c srcs/other_utils/free_mini_strct.c \
			srcs/other_utils/funcs_mini_strct.c srcs/other_utils/find_put_status.c srcs/other_utils/pipe_utils.c srcs/other_utils/change_shlvl.c \
			srcs/env_handlers/get_env.c srcs/env_handlers/set_env.c srcs/env_handlers/check_env_has_val.c srcs/env_handlers/check_env_exists.c \
			srcs/env_handlers/del_env_by_name.c srcs/env_handlers/del_uninit_envs.c \
			srcs/builtins/echo.c srcs/builtins/cd.c srcs/builtins/pwd.c srcs/builtins/export.c srcs/builtins/unset.c srcs/builtins/env.c srcs/builtins/exit.c \
			srcs/execution/exec_bin.c srcs/execution/exec_bin_pipe.c srcs/execution/exec_pipe.c srcs/execution/execution.c srcs/execution/exec_redir.c

INC		= includes/minishell.h
DEPS	= $(INC) $(LIBFT_D)/$(LIBFT_H)
OBJS	= $(SRCS:.c=.o)

CC		= gcc
RM		= /bin/rm -f
CFLAGS	= -g -Wall -Werror -Wextra# -fsanitize=address
FLAGS	= -g -lreadline -Llibft -lft -Wall -Werror -Wextra# -fsanitize=address

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -include $(INC) -o $(<:.c=.o)

$(NAME):		$(OBJS) $(LIBFT)
					$(CC) $(FLAGS) $(OBJS) -o $(NAME)

all:			$(NAME)

$(LIBFT) :	NONE
				$(MAKE) -C $(LIBFT_D)

clean:
				$(RM) $(OBJS)
				$(MAKE) clean -C $(LIBFT_D)

fclean:			clean
					$(RM) $(NAME)
					$(MAKE) fclean -C $(LIBFT_D)

re:				fclean all

.PHONY:			all clean fclean re NONE
