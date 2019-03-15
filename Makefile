# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bleveque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/04 11:26:02 by bleveque          #+#    #+#              #
#    Updated: 2019/02/26 12:27:52 by bleveque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re 

NAME = libftprintf.a

SRC_NAME = printf_arg.c \
		   printf_parser.c \
		   printf_reco_options.c \
		   printf_flags.c \
		   printf_getvalue.c \
		   printf_float.c \
		   printf_edit_options.c \
		   printf_precision.c \
		   printf_width.c \
		   printf_width_bis.c \
		   printf_restart.c \
		   libft/ft_itoa_base.c libft/ft_itoa_unsigned_base.c \
		   libft/ft_power.c libft/ft_putchar.c libft/ft_putchar_fd.c \
		   libft/ft_putchar_fd.c libft/ft_putstr.c libft/ft_putstr_fd.c \
		   libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlen.c \
		   libft/ft_strsub.c libft/ft_atoi.c libft/ft_bzero.c \
		   libft/ft_memalloc.c libft/ft_strdel.c libft/ft_memdel.c

SRCS_PATH = srcs/
OBJS_PATH = objs/
OBJS_LIB_PATH = objs/libft
OBJ_NAME = $(SRC_NAME:.c=.o)
SRCS = $(addprefix $(SRCS_PATH),$(SRC_NAME))
OBJS = $(addprefix $(OBJS_PATH),$(OBJ_NAME))

CC = clang
CFLAGS = -Wall -Wextra -Werror
I_FLAG = -I includes

YELLOW = \x1b[33;01m
GREEN = \x1b[32;01m

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@mkdir $(OBJS_LIB_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(I_FLAG) -o $@ -c $<

all : $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS) 
	@ranlib $(NAME)
	@echo "$(YELLOW)ft_printf $(END)$(GREEN)has compiled ✓ $(END)"

clean :
	@/bin/rm -rf $(OBJS)
	@rmdir $(OBJS_LIB_PATH) 2> /dev/null || true
	@rmdir $(OBJS_PATH) 2> /dev/null || true

fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all
