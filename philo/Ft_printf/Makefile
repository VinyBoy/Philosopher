# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 15:17:23 by marvin            #+#    #+#              #
#    Updated: 2023/01/28 15:17:23 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		libftprintf.a
CC =		cc
CFLAGS = 	-Wall -Wextra -Werror
AR = 		ar rcs
RM = 		rm -rf
SRC = 		ft_printf.c \
		ft_print_nbr.c \
		ft_print_unsigned.c \
		ft_print_print.c \
		ft_print_hexa.c \
		ft_print_ptr.c \

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
		$(AR) $(NAME) $(OBJ)

all : $(NAME)

clean : 
		$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re