CC := gcc

CFLAGS := -Wall -Wextra -Werror

PROJECT := philo

HEADER_SRCS := includes/philosophers.h

SRCS :=	main.c				\
		routine.c			\
		check_death.c		\
		threads.c			\
		init/init.c			\
		utils/ft_error.c 	\
		utils/utils.c		\
		utils/get_time.c	\
		utils/smart_sleep.c	\
		utils/print_action.c\

OBJS := $(addprefix .objs/, $(SRCS:.c=.o))

OBJS_DIRS := $(sort $(dir $(OBJS)))

INCLUDE := $(addprefix -I,$(dir $(HEADER_SRCS)))

NAME := $(PROJECT)

all: $(NAME)

$(NAME): Makefile $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $@

$(OBJS): | $(OBJS_DIRS)

$(OBJS_DIRS):
	mkdir -p $@

.objs/%.o: srcs/%.c $(HEADER_SRCS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	$(RM) $(NAME)

ffclean:
	rm -rf $(OBJS_DIRS)
	$(RM) $(NAME)

re: fclean all

norme:
	@norminette

.PHONY: all clean fclean ffclean re norme