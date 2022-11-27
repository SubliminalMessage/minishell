NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
HEADER = libft.h

# COLORS
BLUE = '\033[1;34m'
PURPLE = '\033[1;35m'
RED = '\033[1;31m'
GREEN = '\033[1;32m'
YELLOW = '\033[1;33m'
WHITE = '\033[1;37m'

SRC_FILES = 	ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strdup.c \
				ft_calloc.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_atoi.c \
				ft_memmove.c \
				ft_memcpy.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_lstnew.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstadd_front.c \
				ft_lstadd_back.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstiter.c \
				ft_lstmap.c

SRC_OBJS = $(SRC_FILES:%.c=bin/%.o)

all: $(NAME)

$(NAME): $(SRC_OBJS)
	@echo $(PURPLE)"[Creating $(NAME) ]"$(WHITE)
	@ar -rcs $(NAME) $(SRC_OBJS)

bin/%.o: %.c
	@echo $(BLUE)"[Compilation]"$(WHITE)": $< "
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -I ./ -o $@

clean:
	@echo $(RED)"[Deleting Object Files]"$(WHITE)": "
	@rm -rf bin

fclean: clean
	@echo $(RED)"[Deleting $(NAME)]"$(WHITE)": "
	@rm -f $(NAME)

re: fclean all
