### ---   ---   ---         ---   ---   --- ###
#             PROJECT COMPILATION             #
### ---   ---   ---         ---   ---   --- ###

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -g3 -fsanitize=address
READLINE_FLAGS = -lreadline

### ---   ---   ---         ---   ---   --- ###
#               PROJECT PATHS                 #
### ---   ---   ---         ---   ---   --- ###

INCS_PATH			= include/
SRCS_PATH			= src/
LIBFT_PATH			= libft/
LIBFT				= $(LIBFT_PATH)/libft.a

### ---   ---   ---         ---   ---   --- ###
#               PROJECT FILES                 #
### ---   ---   ---         ---   ---   --- ###

NAME		= minishell

SRC_FILES	= 	main.c \
				prompt.c

SRC_OBJS 	= $(SRC_FILES:%.c=bin/%.o)

### ---   ---   ---         ---   ---   --- ###
#              COLORS & EXTRAS :)             #
### ---   ---   ---         ---   ---   --- ###

RED		= '\033[1;31m'
GREEN	= '\033[1;32m'
PURPLE	= '\033[1;35m'
YELLOW	= '\033[1;33m'
WHITE	= '\033[1;37m'
BLUE	= '\033[1;34m'

### ---   ---   ---         ---   ---   --- ###
#                  GAME RULES                 #
### ---   ---   ---         ---   ---   --- ###

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(LIBFT) $(SRC_OBJS)
	$(CC) $(CFLAGS) $(READLINE_FLAGS) $(SRC_OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

bin/%.o: src/%.c
	@echo $(BLUE)"[Compilation]"$(WHITE)": $< "
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCS_PATH) -I $(LIBFT_PATH) -c $< -o $@

clean:
	@echo $(RED)"[Deleting Object Files]"$(WHITE)
	@rm -rf bin
	@rm -f	$(INCS_PATH)/minitalk.h.gch
	@make clean -C $(LIBFT_PATH)

fclean: clean 
	@echo $(RED)"[Deleting $(NAME)]"$(WHITE)
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all