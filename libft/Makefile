# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scoron <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 17:44:30 by scoron            #+#    #+#              #
#    Updated: 2020/06/08 01:34:19 by scoron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =  ft_memset.c \
        ft_memcpy.c \
        ft_memccpy.c \
        ft_bzero.c \
        ft_memmove.c \
        ft_memchr.c \
        ft_memcmp.c \
        ft_strlen.c \
        ft_strdup.c \
        ft_strndup.c \
        ft_strcpy.c \
        ft_strncpy.c \
        ft_strcat.c \
        ft_strncat.c \
        ft_strlcat.c \
        ft_strchr.c \
        ft_strrchr.c \
        ft_strstr.c \
        ft_strnstr.c \
        ft_strcmp.c \
        ft_strncmp.c \
        ft_atoi.c \
        ft_isalpha.c \
        ft_isdigit.c \
        ft_isalnum.c \
        ft_isascii.c \
        ft_isprint.c \
        ft_isspace.c \
        ft_toupper.c \
        ft_tolower.c \
        ft_memalloc.c \
        ft_memdel.c \
        ft_strnew.c \
        ft_strdel.c \
        ft_strclr.c \
        ft_striter.c \
        ft_striteri.c \
        ft_strmap.c \
        ft_strmapi.c \
        ft_strequ.c \
        ft_strnequ.c \
        ft_strsub.c \
        ft_strjoin.c \
        ft_strtrim.c \
        ft_strsplit.c \
        ft_putchar.c \
        ft_itoa.c \
        ft_uitoa.c \
        ft_putstr.c \
        ft_putendl.c \
        ft_putnbr.c \
        ft_putchar_fd.c \
        ft_putstr_fd.c \
        ft_putendl_fd.c \
        ft_putnbr_fd.c \
        ft_lstnew.c \
        ft_lstdelone.c \
        ft_lstdel.c \
        ft_lstadd.c \
        ft_lstiter.c \
        ft_lstmap.c \
        ft_advanced_sort_wordtab.c \
        ft_convert_base.c \
        ft_uconvert_base.c \
        ft_any.c \
        ft_swap.c \
        ft_atoi_base.c \
        ft_uatoi_base.c \
        ft_strcutuntil.c \
        ft_strshorten.c \
        get_next_line.c \
        get_next_line_ps.c \
        get_next_line_lm.c \
        ft_power.c \
        ft_annex_float.c \
        ft_putstab.c \
        ft_align_right.c \
        ft_options.c \
        ft_size_convert.c \
        ft_annex_float.c \
        Printf/parse.c \
        Printf/printf.c \
        Printf/float_print.c \
        Printf/convert_speci.c \
        Printf/int_print.c \
        Printf/size.c \
        ft_array/ar_alloc.c \
        ft_array/ar_append.c \
        ft_array/ar_clear.c \
        ft_array/ar_del.c \
        ft_array/ar_new.c \
        ft_array/ar_popindex.c \
        ft_array/ar_reserve.c \
        ft_array/ar_resize.c \
        ft_array/ar_macros.c \
        ft_dico/dic_alloc.c \
        ft_dico/dic_del.c \
        ft_dico/dic_get.c \
        ft_dico/dic_set.c


BASE_SRC = $(shell find . -type f | grep -E "\.c" | sed 's/\.c//g' | sed 's/\.\///g')
DIRS = $(shell find . -type d | grep -v "include" | grep -v "obj" | sed 's/\.\///g')
OBJ_DIRS = $(addprefix $(O_PATH),$(DIRS))
OBJ_DIRS_V = $(addprefix $(O_PATH_V),$(DIRS))
RED =       \033[0;31m
GREEN =     \033[0;32m
MAGENTA =   \033[0;35m
YELLOW =	\033[33m
CYAN =		\033[36m
NC = \033[0m
INC_PATH = include/
INC = $(addprefix -I, $(INC_PATH))
O_PATH = obj/
O_PATH_V = obj_v/
W_FLAGS = -Wall -Wextra -Werror
FSANITIZE= -fsanitize=address,undefined
FLAGS= $(W_FLAGS) $(FSANITIZE)
CC = clang
OBJ:=$(addprefix $(O_PATH),$(addsuffix .o,$(BASE_SRC)))
OBJ_V:=$(addprefix $(O_PATH_V),$(addsuffix .o,$(BASE_SRC)))

all : $(NAME)

$(NAME) : $(OBJ)
	@echo "\n--- Making $(YELLOW)$(NAME)$(NC) ---"
	@echo "$(CYAN)>>> Making $(NAME) binary$(NC)"
	@ar -rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "$(GREEN)$@ is ready\n\n$(NC)"

val : $(OBJ_V)
	@/bin/rm -f $(NAME)
	@echo "\n--- Making $(YELLOW)$(NAME)$(NC) for valgrind... ---"
	@echo "$(CYAN)>>> Making $(NAME) binary$(NC)"
	@ar -rc $(NAME) $(OBJ_V)
	@ranlib $(NAME)
	@echo "$(GREEN)$(NAME) is ready$(NC)"
	

$(O_PATH)%.o : %.c $(INC_PATH)$(HEADER)
	@mkdir -p $(O_PATH)
	@mkdir -p $(OBJ_DIRS)
	@echo "$(MAGENTA)>>> Making $@$(NC)"
	@clang $(FLAGS) $(INC) -c $< -o $@

$(O_PATH_V)%.o : %.c $(INC_PATH)$(HEADER)
	@mkdir -p $(O_PATH_V)
	@mkdir -p $(OBJ_DIRS_V)
	@echo "$(MAGENTA)>>> Making $@$(NC)"
	@clang $(W_FLAGS) $(INC) -c $< -o $@

clean :
	@$(RM) -rf $(O_PATH)

fclean : clean
	@$(RM) -rf $(NAME)

clean_val :
	@$(RM) -rf $(O_PATH_V)

fclean_val : clean_val
	@$(RM) -rf $(NAME)

re : fclean all

push : fclean
	@git add -A
	@git commit -m "quick push"
	@git push origin master
	git status

norme:
	norminette $(INC_PATH) $(SRC_PATH)

.PHONY: all, clean, fclean, re, push, norme
