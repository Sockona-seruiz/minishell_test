.PHONY: re, clean, fclean, all, bonus

NAME= minishell

SRC_FILE=	./get_next_line/get_next_line.c\
			./get_next_line/get_next_line_utils.c\
			./main.c

OBJ=${SRC_FILE:.c=.o}

INCLUDES=./get_next_line/get_next_line.h\
		./libft/libft.h\
		./minishell.h

all: $(NAME)

all bonus : $(NAME)

$(NAME): ${OBJ}
	@gcc libft/libft.a -o minishell ${OBJ}

%.o: %.c
	@gcc -c -Wall -Wextra -c $< -o $@

clean:
	@rm -f $(OBJ)
fclean: clean
	@rm -f $(NAME) $(BONUS)

re: fclean all