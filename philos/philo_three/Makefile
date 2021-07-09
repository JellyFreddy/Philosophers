NAME_THREE	:= philo_three
objs_three	:= ./eat_slepp_think.o ./ft_atoi.o .//help_functions.o ./init.o ./philo_three.o
CC		:= gcc
CFLAGS	:= -Wall -Werror -Wextra

all: $(NAME_THREE)

deps_three := $(patsubst %.o, %.d, $(objs_three))
-include $(deps_three)
DEPFLAGS = -MMD -MF $(@:.o=.d)

$(NAME_THREE): $(objs_three)
	$(CC) $(CFLAGS) $(objs_three) -o $(NAME_THREE)

%.o: %.c Makefile
	$(CC) -c $< $(DEPFLAGS)

clean:
	rm -f $(objs_three) $(deps_three)

fclean: clean
	rm -f $(NAME_THREE)

re: fclean all

.PHONY: clean all fclean re                                