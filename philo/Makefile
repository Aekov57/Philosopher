# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: misimon <misimon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 16:07:27 by misimon           #+#    #+#              #
#    Updated: 2022/11/28 21:07:14 by misimon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	NAME :
NAME	:= 	philo
#	FILE :
SRC_DIR	:= 	src

SRCS	:=	main.c					\
			utils/ft_atoi.c			\
			utils/error.c			\
			init/init_philo.c		\
			init/create_philo.c		\

SRCS := 	$(SRCS:%=$(SRC_DIR)/%)

#	COMPILATION:
CC := 		@gcc
CFLAGS := 	-Wall -Werror -Wextra
DANGER := -fsanitize=address

#	STATIC LIB CREATION:
AR :=		@ar
ARFLAG :=	-rcs

#	BUILD:
OBJS_DIR := .build
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

#	TOOLS:

RM	:= @rm -rf
DUP_DIR = @mkdir -p $(@D)
CREATE_DIR = [ ! -d $(OBJS_DIR) ] && mkdir $(OBJS_DIR)
ALLOBJS = $(OBJS_DIR)/%.o

#	COMMAND:

all : $(NAME)

.create.build :
	$(CREATE_DIR)
	$(CLONE_LIB)

$(OBJS_DIR)/%.o : $(SRC_DIR)/%.c
	$(DUP_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo "\033[1A\033[0J\033[32;1m\rPhilosopher compilation >>\033[0m\033[30;1m $@\033[0m"

$(NAME) : $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(DANGER) -g

clean :
	$(RM) $(OBJS_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all