# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 18:33:46 by sesnowbi          #+#    #+#              #
#    Updated: 2021/06/11 21:36:24 by sesnowbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
LIBFT_D	= ./libft
LIBFT_A	= libft.a
LIBFT_H = libft.h
LIBFT	= libft/libft.a

SRCS	= srcs/main.c GNL/get_next_line.c GNL/get_next_line_utils.c
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
					$(RM) $(LIBFT_A)
					$(MAKE) fclean -C $(LIBFT_D)

re:				fclean all

.PHONY:			all clean fclean re NONE
