# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rthomas <rthomas@student.42nice.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 12:49:39 by rthomas           #+#    #+#              #
#    Updated: 2022/06/01 15:21:37 by rthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SOURCES =	pipex.c \
			utils.c

OBJECTS = ${SOURCES:.c=.o}

all: libft ${NAME}

${NAME}: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} ./libft/libft.a -o ${NAME}

libft:
	make -C ./libft

clean:
	rm -f ${OBJECTS}
	make clean -C ./libft

fclean: clean
	rm -f ${NAME}
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean libft re