# Minishell project
# Authors: auhoris & skitsch

# Bin
name			= minishell

# Directories
srcdir			= srcs
objdir			= objs
libdir			= libs
incdir			= $(srcdir)/includes
gnldir			= $(libdir)/get_next_line
libftdir		= $(libdir)/libft

# Files
sources			= $(wildcard $(srcdir)/*.c)
inclds			= $(wildcard $(incdir)/*.h)
objects			= $(sources:$(srcdir)/%.c=$(objdir)/%.o)

# Flags and linkers
cc				= gcc
cflags			= -Wall -Werror -Wextra
dbgf			= -g
sanitize		= -fsanitize=address

# Additional libraries
libft_a			= libft.a
gnl_a			= gnl.a
libs			= $(gnldir)/$(gnl_a) $(libftdir)/$(libft_a)

# Utils
rm				= rm -rf


all:			 $(name)

$(name):		$(objects)
				$(cc) $(cflags) $^ -o $@
				@echo ""$@" compiled"

$(objdir)/%.o	: $(srcdir)/%.c Makefile $(inclds)
				$(cc) $(cflags) -c $< -o $@


clean:
				@make -C $(gnldir) clean
				@make -C $(libftdir) clean
				$(rm) $(objects)
fclean:			clean
				@make -C $(gnldir) fclean
				@make -C $(libftdir) fclean
				$(rm) $(name)
re:				fclean all


.PHONY:			clean fclean re all
.SILENT:		$(name)
