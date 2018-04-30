# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mploux <mploux@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/06 18:10:48 by mploux            #+#    #+#              #
#    Updated: 2018/04/24 16:21:34 by mploux           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm
CC = gcc
CXX = g++
FILES =\
Factory.cpp\
main.cpp\
Stack.cpp\
Error.cpp\
Action.cpp\
utils.cpp

SRC = src/
DIRS = bin

SYSTEM = $(shell uname -s)

WHITE = \033[7;49;39m
BLUE = \033[7;49;34m
GREEN = \033[0;49;32m
GREEN_BG = \033[1;49;32m
GRAY = \033[7;49;90m
NO_COLOR = \033[m

OBJS = $(addprefix bin/,$(FILES:.cpp=.o))
HDRS = $(OBJS:.o=.d)

INCLUDES = -I srcs/

CFLAGS = -std=c++11 -std=gnu++11 -Wall -Wextra -pedantic -g
FLAGS = $(CFLAGS) $(INCLUDES)

MKDIR = mkdir -p
RMDIR = rm -rf
RM = rm -rf

all: $(NAME)

$(NAME): $(DIRS) $(OBJS)
	@printf "\r$(GREEN)Compiling sources: DONE !                      $(NO_COLOR)\n";
	@printf "Building objects...\r"
	@$(CXX) -o $(NAME) $(OBJS) $(CFLAGS) $(INCLUDES) $(DEPS) $(DEPSFLAGS)
	@printf "\r$(GREEN)Building objects: DONE !$(NO_COLOR)\n";
	@printf "\n$(GREEN)Building done: $(GREEN_BG)$(NAME)$(NO_COLOR)\n"

$(DIRS):
	@$(MKDIR) $(dir $(OBJS))

bin/%.o: src/%.cpp
	@printf "\rCompiling sources: $<                          \r";
	@$(CXX) $(CFLAGS) -MMD -c $< -o $@ $(INCLUDES)

clean:
	@printf "Cleaning objects..."
	@$(RM) $(OBJS)
	@$(RM) $(HDRS)
	@$(RMDIR) bin
	@printf "\r$(GREEN)Cleaning objects: DONE !$(NO_COLOR)\n";

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(HDRS)
