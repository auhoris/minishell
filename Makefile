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



all:			 lib gnl $(name)

gnl:
				@make -C $(gnldir)
lib:
				@make -C $(libftdir)


$(name):		$(objects) $(libs)
				$(cc) $(cflags) $^ -o $@
				@echo "\033[0;32m"$@" compiled"

$(objdir)/%.o	: $(srcdir)/%.c Makefile $(inclds)
				@mkdir -p $(objdir)
				$(cc) $(cflags) -c $< -o $@
				@echo "Compiled "$<" successfully!"


clean:
				@make -C $(gnldir) clean
				@make -C $(libftdir) clean
				$(rm) $(objdir)
fclean:			clean
				@make -C $(gnldir) fclean
				@make -C $(libftdir) fclean
				$(rm) $(name)
re:				fclean all

shclean:		
				$(rm) $(objdir)


.PHONY:			clean fclean re all
.SILENT:		$(name) $(objects)
