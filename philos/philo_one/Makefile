NAME_ONE	:= philo_one
objs_one	:= ./eat_sleep_print.o ./finish.o ./ft_atoi.o ./ft_strlen.o ./help_functions.o ./init.o ./philo_one.o
CC		:= gcc
CFLAGS	:= -Wall -Werror -Wextra

all: $(NAME_ONE)

deps_one := $(patsubst %.o, %.d, $(objs_one))
-include $(deps_one)
DEPFLAGS = -MMD -MF $(@:.o=.d)

$(NAME_ONE): $(objs_one)
	$(CC) $(CFLAGS) $(objs_one) -o $(NAME_ONE)

%.o: %.c Makefile
	$(CC) -c $< $(DEPFLAGS)

clean:
	rm -f $(objs_one) $(deps_one)

fclean: clean
	rm -f $(NAME_ONE)

re: fclean all

.PHONY: clean all fclean re                                