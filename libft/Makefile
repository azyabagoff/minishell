# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 18:33:46 by sesnowbi          #+#    #+#              #
#    Updated: 2021/07/06 14:09:03 by sesnowbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
SRCS	= ft_memset.c \
		  ft_bzero.c \
		  ft_memcpy.c \
		  ft_memccpy.c \
		  ft_memmove.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_strlen.c \
		  ft_strlcpy.c \
		  ft_strlcat.c \
		  ft_strchr.c \
		  ft_strrchr.c \
		  ft_strnstr.c \
		  ft_strncmp.c \
		  ft_strcmp.c \
		  ft_atoi.c \
		  ft_atoll.c \
		  ft_isalpha.c \
		  ft_isdigit.c \
		  ft_isalnum.c \
		  ft_isascii.c \
		  ft_isprint.c \
		  ft_toupper.c \
		  ft_tolower.c \
		  ft_calloc.c \
		  ft_strdup.c \
		  ft_substr.c \
		  ft_strjoin.c \
		  ft_strjoin1.c \
		  ft_strtrim.c \
		  ft_split.c \
		  ft_itoa.c \
		  ft_lltoa.c \
		  ft_strmapi.c \
		  ft_putchar_fd.c \
		  ft_putstr_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  ft_ternar.c
INC		= libft.h
OBJS	= $(SRCS:.c=.o)

BONUS	= ft_lstnew.c \
		  ft_lstadd_front.c \
		  ft_lstsize.c \
		  ft_lstlast.c \
		  ft_lstadd_back.c \
		  ft_lstdelone.c \
		  ft_lstclear.c \
		  ft_lstiter.c \
		  ft_lstmap.c
B_OBJS	= $(BONUS:.c=.o)


CC		= gcc
RM		= /bin/rm -f
CFLAGS	= -Wall -Wextra -Werror

%.o:%.c $(INC)
	$(CC) $(CFLAGS) -c $< -include $(INC) -o $(<:.c=.o)

$(NAME):		$(OBJS) $(B_OBJS)
					ar rc $(NAME) $(OBJS) $(B_OBJS)

all:			$(INC) $(NAME)

clean:
				$(RM) $(OBJS) $(B_OBJS)

fclean:			clean
					$(RM) $(NAME)

re:				fclean all

bonus:			$(NAME) $(B_OBJS)
					ar rc $(NAME) $(OBJS) $(B_OBJS)

.PHONY:			all clean fclean re bonus
