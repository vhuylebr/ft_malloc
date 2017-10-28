# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhuylebr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/28 12:59:02 by vhuylebr          #+#    #+#              #
#    Updated: 2017/10/28 12:59:06 by vhuylebr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =       ft_malloc

CC      =       gcc

SRCS    =		src/main.c


RM      =       rm -f

OBJS    =       $(SRCS:.c=.o)

CFLAGS	=		-Wall -Werror -Wextra -I include

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean :
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clear fclean re
