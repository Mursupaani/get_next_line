# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 13:18:29 by anpollan          #+#    #+#              #
#    Updated: 2025/04/28 19:09:29 by anpollan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= a.out
SRCS		= get_next_line.c get_next_line_utils.c main.c
OBJS		= $(SRCS:%.c=%.o)
CC			= cc
C_FLAGS		= -Wall -Wextra -Werror

all: $(NAME) clean

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(C_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(BONUS_OBJS)
	
fclean:	clean
	rm -rf $(NAME) compile_commands.json

re: fclean all

.PHONY: all clean fclean re
