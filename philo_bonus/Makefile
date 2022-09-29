MANDE 	:= philo
BONUS 	:= philo_bonus
NAME 	:= philo_bonus
ifdef WITH_BONUS
NAME 	:= philo_bonus
endif
LIB	:= ./lib/

LIBFTDIR	:= $(LIB)/libft
LIBFTNAME	:= libft.a
LIBFT		:= $(LIBFTDIR)/$(LIBFTNAME)

OBJDIR		:= ./obj

SRCDIR	:= ./srcs/
SRC	:= ft_atoi.c init_philo.c philo_util.c philo_thread.c philo_stop.c philo_life.c put_logs.c philo_accssesor.c
ENTRY	:= main.c
ENTRYBONUS	:= main.c
DELENTRY	:= $(OBJDIR)/main.o
ifdef WITH_BONUS
ENTRY	:= $(ENTRYBONUS)
DELENTRY	:= $(OBJDIR)/main.o
endif
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
CFLAGS	:= -Wall -Wextra -Werror -pthread
LDFLAGS := $(IFLAGS) $(LFLAGS)

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
			$(RM) $(OBJDIR)/$(ENTRYBONUS:.c=.o)
			$(RM) $(OBJDIR)/$(ENTRYBONUS:.c=.d)

fclean	:	clean
			$(RM) $(MANDE)
			$(RM) $(BONUS)
			$(RM) $(LIBS)

re	:		fclean all

bonus	:	
			@make WITH_BONUS=1

ifeq ($(findstring clean,$(MAKECMDGOALS)),)
-include $(DEPS)
endif

.PHONY: clean fclean bonus re
