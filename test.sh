#!/bin/bash

#Comment DEFINE on main
clang++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=ft main.cpp -o ft_containers;
./ft_containers > a;
clang++ -Wall -Wextra -Werror -std=c++98 -D NAMESPACE=std main.cpp -o ft_containers;
./ft_containers > b;
diff -y a b > difference.txt;
rm a b ft_containers
cat difference.txt | grep '|'
