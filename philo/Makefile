# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mriant <mriant@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/14 12:43:14 by mriant            #+#    #+#              #
#    Updated: 2022/04/15 17:27:59 by mriant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = ${addprefix srcs/, \
	atoi_philo.c \
	main.c \
	utils.c}

OBJS = ${SRCS:srcs/%.c=build/%.o}

DEPS = ${SRCS:srcs/%.c=build/%.d}

CC = cc

CFLAGS = -Wall -Wextra -Werror

IFLAGS = -I./includes -MMD

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o $@

build/%.o: srcs/%.c
	mkdir -p build
	${CC} ${CFLAGS} -c $< -o $@ ${IFLAGS}

.PHONY: all
all: ${NAME}

.PHONY: clean
clean:
	rm -rf ${OBJS}
	rm -rf ${DEPS}
	rm -rf build

.PHONY: fclean
fclean: clean
	rm -rf ${NAME}

.PHONY: re
re: fclean
	make all

-include ${DEPS}