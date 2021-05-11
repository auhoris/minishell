# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: auhoris <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/26 13:39:35 by auhoris           #+#    #+#              #
#    Updated: 2021/05/11 16:20:26 by auhoris          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name			= gnl.a


srcdir			= srcs
objdir			= objs
incdir			= $(srcdir)/includes

sources			= $(wildcard $(srcdir)/*.c)
inclds			= $(wildcard $(incdir)/*.h)
objects			= $(sources:$(srcdir)/%.c=$(objdir)/%.o)


cc				= gcc
cflags			= -Wall -Werror -Wextra
dbgf			= -g
sanitize		= -fsanitize=address


rm				= rm -rf


all:			 $(name)

$(name):		$(objects)
				ar rcs $@ $^
				@echo "\033[0;32m"$@" compiled\033[0m"

$(objdir)/%.o	: $(srcdir)/%.c Makefile $(inclds)
				@mkdir -p $(objdir)
				$(cc) $(cflags) -c $< -o $@
				@echo "Compiled "$<" successfully!"

clean:
				$(rm) $(objdir)
fclean:			clean
				$(rm) $(name)
re:				fclean all


.PHONY:			clean fclean re all
.SILENT:		$(name) $(objects)
