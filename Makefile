# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 10:50:18 by rcabezas          #+#    #+#              #
#    Updated: 2022/05/25 14:31:23 by rcabezas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_containers

INC= -I utils

CXX = clang++

CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -g3 #-fsanitize=address

SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
