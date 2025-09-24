NAME = push_swap
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = push_swap.c stack_operations.c stack_ops_extra.c operations_swap.c operations_push.c operations_rotate.c operations_reverse.c utils_atoi.c utils_put.c utils_check.c utils_error.c sort.c sort_utils.c sort_small.c sort_five.c sort_large.c index_assign.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
