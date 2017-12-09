# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhuylebr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/28 12:59:02 by vhuylebr          #+#    #+#              #
#    Updated: 2017/11/25 16:25:48 by vhuylebr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =       ft_malloc.so

CC      =       gcc

SRCS    =		src/main.c 


RM      =       rm -f

OBJS    =       $(SRCS:.c=.o)

CFLAGS	=		-Wall -Werror -Wextra -I include

all: $(NAME)

$(NAME):	$(OBJS)
					$(CC) -o $(NAME) -fpic $(OBJS) 

#					ar rc $(NAME) $(OBJ)
#					ranlib $(NAME)

clean :
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clear fclean re
