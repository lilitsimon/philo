NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SOURCES = main.c

OBJECTS = $(SOURCES:.c=.o)

NO_COLOR = \033[0;39m
GREEN = \033[1;32m
MAGENTA = \033[0;96m

all: $(NAME)

$(NAME): $(OBJECTS)
		$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
		@echo "$(GREEN)philo compiled$(NO_COLOR)"

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:	
		rm -f $(OBJECTS)
		@echo "$(MAGENTA)philo object files cleaned$(NO_COLOR)"

fclean: clean
		rm -f $(NAME)
		@echo "$(MAGENTA)philo cleaned$(NO_COLOR)"

re: fclean all

.PHONY: all clean fclean re
