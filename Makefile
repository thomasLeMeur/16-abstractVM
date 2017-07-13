# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tle-meur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/14 15:29:40 by tle-meur          #+#    #+#              #
#    Updated: 2016/06/01 14:32:24 by tle-meur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	avm

CC		=	g++

FLAGS	=	-Wall -Wextra -Werror -std=c++14

SRCS	=	main.cpp OperandFactory.cpp Lexer.cpp Parser.cpp Logger.cpp StackProcess.cpp Vm.cpp

OBJS	=	$(SRCS:.cpp=.o)

INCS	=	.

LIBS	=


all		:	$(NAME)

%.o		:	%.cpp
			@$(CC) $(FLAGS) -o $@ -c $< -I $(INCS)

$(NAME)	:	$(OBJS)
			@$(CC) $(FLAGS) -o $@ $^ -I $(INCS) $(LIBS)
			@echo "$(NAME) created"

clean	:
			@rm -f $(OBJS)
			@echo "objects deleted"

fclean	:	clean
			@rm -f $(NAME)
			@echo "$(NAME) deleted"

re		:	fclean $(NAME)

simple	:	re
			@rm -f $(OBJS)
			@echo "objects deleted"

.PHONY	:	all clean fclean re simple
