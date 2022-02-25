# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 10:50:18 by rcabezas          #+#    #+#              #
#    Updated: 2022/02/24 09:47:02 by rcabezas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_containers

INC= -I utils

CXX = clang++

CXXFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3 #-std=c++98

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
