MANDE 	:= philo
NAME 	:= philo
LIB	:= ./lib/

LIBFTDIR	:= $(LIB)/libft
LIBFTNAME	:= libft.a
LIBFT		:= $(LIBFTDIR)/$(LIBFTNAME)

OBJDIR		:= ./obj

SRCDIR	:= ./srcs/
SRC	:= ft_atoi.c init_philo.c philo_util.c philo_thread.c philo_stop.c philo_life.c put_logs.c philo_accssesor.c philo_flag_accssesor.c
ENTRY	:= main.c
SRC	+= $(ENTRY)

SRCS	:= $(addprefix $(SRCDIR), $(SRC))
OBJS	:= $(SRCS:.c=.o)
OBJECTS	:= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEPS	:= $(OBJECTS:.o=.d)
INCS	:= ./include 

LIBDIRS	:= 
IFLAGS	:= $(addprefix -I,$(INCS))
LFLAGS	:= $(addprefix -L,$(LIBDIRS))
LIBS	:= 

CC	:= cc
#CFLAGS	:= -Wall -Wextra -Werror -lpthread -fsanitize=thread -g3
CFLAGS	:= -Wall -Wextra -Werror
LDFLAGS := $(IFLAGS) $(LFLAGS) -lpthread

all:
	@make $(NAME)	

$(NAME)	:	$(OBJECTS) $(LIBS) 
		$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $@
		$(RM) $(DELENTRY)


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR) / $(*D)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -MMD -MP -MF $(OBJDIR)/$*.d  -o $@
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

clean	:
			$(RM) $(OBJECTS)
			$(RM) $(DEPS)

fclean	:	clean
			$(RM) $(MANDE)
			$(RM) $(LIBS)

re	:		fclean all


ifeq ($(findstring clean,$(MAKECMDGOALS)),)
-include $(DEPS)
endif

.PHONY: clean fclean re
