# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mriant <mriant@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/14 12:43:14 by mriant            #+#    #+#              #
#    Updated: 2022/05/17 17:19:40 by mriant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS = ${addprefix srcs/, \
	actions_bonus.c \
	atoi_philo_bonus.c \
	clean_bonus.c \
	lists_bonus.c \
	main_bonus.c \
	parsing_bonus.c \
	utils_bonus.c}

OBJS = ${SRCS:srcs/%.c=build/%.o}

DEPS = ${SRCS:srcs/%.c=build/%.d}

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -pthread #-fsanitize=thread

IFLAGS = -I./includes -MMD -pthread

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o $@

build/%.o: srcs/%.c
	mkdir -p build
	${CC} ${CFLAGS} -c $< -o $@ ${IFLAGS}

.PHONY: all
all: ${NAME}

.PHONY: bonus
bonus: all

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