SRC = main.c\
	stack.c\
	stack.h\
NAME = push_swap
CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJC = $(SRCS:.c=.o)
RM = rm -f
AR = ar -rc

all: $(NAME)

$(NAME): $(OBJC)
	$(AR) $(NAME) $(OBJC)

clea:
	$(RM) $(OBJC)

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
