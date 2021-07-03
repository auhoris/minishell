# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: auhoris <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/25 15:29:16 by auhoris           #+#    #+#              #
#    Updated: 2021/05/11 16:22:01 by auhoris          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

SRCDIR		= srcs
OBJDIR		= objs
INCDIR		= includes

SRCS		= $(wildcard $(SRCDIR)/*.c)
INCLUDES	= $(SRCDIR)/libft.h
OBJS		= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

RM			= rm -rf

CC			= gcc
CLAGS		= -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJS)
			ar rcs $@ $^
			@echo "\033[0;32m"$@" compiled\033[0m"

$(OBJDIR)/%.o	: $(SRCDIR)/%.c Makefile $(INCLUDES)
			@mkdir -p $(OBJDIR)
			$(CC) $(CLAGS) -c $< -o $@
			@echo "Compiled "$<" successfully!"

clean:
			$(RM) $(OBJDIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		re fclean clean all

.SILENT:	$(OBJS) $(NAME)
