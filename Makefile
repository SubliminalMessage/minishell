### ---   ---   ---         ---   ---   --- ###
#             PROJECT COMPILATION             #
### ---   ---   ---         ---   ---   --- ###

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra #-g3 -fsanitize=address
READLINE_FLAGS = -lreadline

### ---   ---   ---         ---   ---   --- ###
#               PROJECT PATHS                 #
### ---   ---   ---         ---   ---   --- ###

INCLUDE				= -I include -I libft/include -I src/debug/ # TODO remove debug
SRCS_PATH			= src/
LIBFT_PATH			= libft/
LIBFT				= $(LIBFT_PATH)libft.a
LIBFT_REPO			= $(LIBFT_PATH)Makefile

### ---   ---   ---         ---   ---   --- ###
#               PROJECT FILES                 #
### ---   ---   ---         ---   ---   --- ###

NAME		= minishell

SRC_FILES	= 	main.c \
				parsing/prompt.c \
				parsing/commands.c \
				parsing/environ.c \
				parsing/expansion.c \
				utils/handle_str.c \
				utils/split_quote_conscious.c \
				utils/debug/print_debug.c # TODO This file is not meant to reach the final version of the Minishell

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
NC		= '\033[0m'

### ---   ---   ---         ---   ---   --- ###
#                     RULES                   #
### ---   ---   ---         ---   ---   --- ###

.PHONY: all re clean fclean norm todo TODO execute

all: $(NAME)

$(NAME): $(LIBFT) $(SRC_OBJS)
	@echo $(BLUE)[Compilation]$(WHITE): $(NAME)$(NC)
	$(CC) $(CFLAGS) $(INCLUDE) $(READLINE_FLAGS) $(SRC_OBJS) $(LIBFT) -o $(NAME)

$(LIBFT): $(LIBFT_REPO)
	@make -C $(LIBFT_PATH)

$(LIBFT_REPO):
	@# TODO Remove in intra version
	git submodule update --init --recursive

bin/%.o: src/%.c
	@echo $(BLUE)"[Compilation]"$(WHITE)": $< "$(NC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean: $(LIBFT_REPO)
	@echo $(RED)"[Deleting Object Files]"$(NC)
	@rm -rf bin
	@make -C $(LIBFT_PATH) fclean
	@#make fclean -C $(LIBFT_PATH)

fclean: clean
	@echo $(RED)"[Deleting $(NAME)]"$(NC)
	@rm -f $(NAME)
	@rm -f $(DEBUG)

re: fclean all

norm:
	@norminette $(SRC_FILES:%=$(SRCS_PATH)%) $(INCLUDE_FILES:%=$(INCLUDE_PATH)%) | sed "s/src/\\`echo '\n\r'`/g"

todo:
	@cat $(SRC_FILES:%=$(SRCS_PATH)%) | grep '//\stodo:.*' -ioh --color=never

TODO:
	@echo "*****************************************"
	@grep "TODO" -nr -i --exclude-dir=".git" .
	@echo "*****************************************"

execute: all
	@clear && ./minishell --debug


### ---   ---   ---         ---   ---   --- ###
#                    DEBUG                    #
### ---   ---   ---         ---   ---   --- ###

DEBUG		=	debug

DEBUG_FILES	=	utils/clean_cmd.c \
				utils/copy_all.c \
				debug/exe_cmd.c \
				debug/file.c \
				utils/get.c \
				debug/join_input.c \
				debug/main.c \
				debug/run.c \
				debug/wait_result.c

DEBUG_OBJS	=	$(DEBUG_FILES:%.c=bin/%.o)

$(DEBUG): $(DEBUG_OBJS) $(LIBFT)
	@echo $(BLUE)[Compilation]$(WHITE): $@$(NC)
	$(CC) $(CFLAGS) $(INCLUDE) $(DEBUG_OBJS) $(LIBFT) -o $@

exec_dev: $(DEBUG)
	valgrind --leak-check=full --show-leak-kinds=all --undef-value-errors=no --trace-children=yes --track-fds=yes ./$(DEBUG)
