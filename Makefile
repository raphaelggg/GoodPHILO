# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/20 15:15:18 by ragolden          #+#    #+#              #
#    Updated: 2026/06/12 21:58:04 by ragolden         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        =   philo

CC          =   cc
CFLAGS      =   -Wall -Wextra -Werror -pthread

INC_DIR     =   inc
SRC_DIR     =   srcs
OBJ_DIR     =   objs

SRC_FILES   =   main.c parsing.c utils.c init.c time_gestion.c threads_routine.c monitor.c
SRCS        =   $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS        =   $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compilation terminée avec succès ! (./philo)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Objets nettoyés."

fclean: clean
	@rm -f $(NAME)
	@echo "Exécutable supprimé."

re: fclean all

.PHONY: all clean fclean re