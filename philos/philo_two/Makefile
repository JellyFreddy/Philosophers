NAME_TWO	:= philo_two
objs_two	:= ./eat_sleep_print.o ./ft_atoi.o ./ft_strlen.o ./help_functions.o ./init.o ./philo_two.o
CC			:= gcc
CFLAGS		:= -Wall -Werror -Wextra

all: $(NAME_TWO)

deps_two := $(patsubst %.o, %.d, $(objs_two))
-include $(deps_two)
DEPFLAGS = -MMD -MF $(@:.o=.d)

$(NAME_TWO): $(objs_two)
	$(CC) $(CFLAGS) $(objs_two) -o $(NAME_TWO)

%.o: %.c Makefile
	$(CC) -c $< $(DEPFLAGS)

clean:
	rm -f $(objs_two) $(deps_two)

fclean: clean
	rm -f $(NAME_TWO)

re: fclean all

.PHONY: clean all fclean re                                