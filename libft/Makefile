# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/06 12:53:13 by jmartel           #+#    #+#              #
#    Updated: 2019/11/20 16:38:22 by jdugoudr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
EXEC	= exec

SRCS	=	./lst/ft_lstnew.c ./lst/ft_lstdelone.c \
			./lst/ft_lstdel.c ./lst/ft_lstadd.c \
			./lst/ft_lstiter.c ./lst/ft_lstmap.c \
			./lst/ft_lstlen.c ./lst/ft_lstadd_last.c \
			./lst/ft_lstput_fd.c ./lst/ft_lstaddnew.c\
			./lst/ft_lstaddnew_last.c ./lst/ft_lstaddnew_ptr.c\
			./lst/ft_lstaddnew_ptr_last.c ./lst/ft_lstnew_value.c\
			./lst/ft_lstpop.c ./lst/ft_lstpop_ptr.c \
			./lst/ft_lstdel_value.c ./lst/ft_lstdel_ptr.c\
			./lst/ft_lstpop_node.c ./lst/ft_lstaddnew_ptr_last_list.c

SRCS	+=	./math/ft_max.c ./math/ft_min.c ./math/ft_abs.c \
			./math/ft_pow.c ./math/ft_roundf.c \
			./math/ft_roundl.c ./math/ft_longlen.c

SRCS	+=	./mem/ft_memset.c ./mem/ft_bzero.c \
			./mem/ft_memcpy.c ./mem/ft_memccpy.c \
			./mem/ft_memmove.c ./mem/ft_memchr.c \
			./mem/ft_memcmp.c ./mem/ft_memalloc.c \
			./mem/ft_memdel.c

SRCS	+=	./put/ft_putchar.c ./put/ft_putstr.c \
			./put/ft_putendl.c ./put/ft_putnbr.c \
			./put/ft_putchar_fd.c ./put/ft_putstr_fd.c \
			./put/ft_putendl_fd.c ./put/ft_putnbr_fd.c \
			./put/ft_putcharn.c ./put/ft_putstrn.c \
			./put/ft_putnbrn.c ./put/ft_putnstr_fd.c

SRCS	+=	./str/ft_strlen.c ./str/ft_strdup.c \
			./str/ft_strcpy.c ./str/ft_strncpy.c \
			./str/ft_strcat.c ./str/ft_strncat.c \
			./str/ft_strlcat.c ./str/ft_strchr.c \
			./str/ft_strrchr.c ./str/ft_strstr.c \
			./str/ft_strnstr.c ./str/ft_strcmp.c \
			./str/ft_strncmp.c ./str/ft_isalpha.c \
			./str/ft_isdigit.c ./str/ft_isalnum.c \
			./str/ft_isprint.c ./str/ft_isascii.c \
			./str/ft_iswhite.c ./str/ft_tolower.c \
			./str/ft_isalpha_only.c ./str/ft_isdigit_only.c \
			./str/ft_isalnum_only.c ./str/ft_isascii_only.c \
			./str/ft_isprint_only.c ./str/ft_iswhite_only.c \
			./str/ft_toupper.c ./str/ft_strnew.c \
			./str/ft_strdel.c ./str/ft_strclr.c \
			./str/ft_striter.c ./str/ft_striteri.c \
			./str/ft_strmap.c ./str/ft_strmapi.c \
			./str/ft_strequ.c ./str/ft_strnequ.c \
			./str/ft_strsub.c ./str/ft_strjoin.c \
			./str/ft_strtrim.c ./str/ft_strtrim_side.c \
			./str/ft_strsplit.c \
			./str/ft_strnlen.c ./str/ft_strrev.c \
			./str/ft_strstr_count.c ./str/ft_strtolower.c \
			./str/ft_strjoin_free.c ./str/ft_strinsert_free.c \
			./str/ft_strninsert_free.c \
			./str/ft_strjoin_path.c ./str/ft_strndup.c \
			./str/ft_split_whitespaces.c ./str/ft_strrep_free.c \
			./str/ft_strpbrk.c ./str/ft_strnrest.c ./str/ft_strjoin_3.c \
			./str/ft_strichr.c ./str/ft_strichr_last.c \
			./str/ft_isseparator.c ./str/ft_chpbrk.c \
			./str/ft_strnjoin_free.c ./str/ft_substitute_str.c \
			./str/ft_strjoin_3_free.c ./str/ft_strtok.c ./str/ft_strcontains.c \
			./str/ft_strsep.c

SRCS	+=	./str/ft_strtab_free.c ./str/ft_strtab_put.c \
			./str/ft_strtab_len.c ./str/ft_strtab_new_line.c \
			./str/ft_strdelchar.c

SRCS	+=	./gnl/get_next_line.c \
			./gnl/get_next_line2.c

SRCS	+=	./atoi/ft_atoi.c ./atoi/ft_ltoa.c \
			./atoi/ft_lltoa.c ./atoi/ft_ulltoa.c \
			./atoi/ft_ftoa.c ./atoi/ft_itoa.c ./atoi/ft_atol.c

SRCS	+=	./ft_printf/ft_printf.c\
			./ft_printf/ft_dprintf.c\
			./ft_printf/ft_sprintf.c\
			./ft_printf/ft_abs.c\
			./ft_printf/ft_atoi.c\
			./ft_printf/ft_atoll.c\
			./ft_printf/ft_bonus_flags.c\
			./ft_printf/ft_display_len_integer.c\
			./ft_printf/ft_display_len_p.c\
			./ft_printf/ft_display_len_string.c\
			./ft_printf/ft_display_len_wchar.c\
			./ft_printf/ft_dlstadd.c\
			./ft_printf/ft_dprintf.c\
			./ft_printf/ft_dprintf.o\
			./ft_printf/ft_fclamp.c\
			./ft_printf/ft_flag_c_maj.c\
			./ft_printf/ft_flags_f.c\
			./ft_printf/ft_flags_integer.c\
			./ft_printf/ft_flags_o.c\
			./ft_printf/ft_flags_others.c\
			./ft_printf/ft_flags_s.c\
			./ft_printf/ft_flags_x_p.c\
			./ft_printf/ft_free_split.c\
			./ft_printf/ft_get_buffer.c\
			./ft_printf/ft_get_casted_values.c\
			./ft_printf/ft_get_casted_values_func.c\
			./ft_printf/ft_get_casted_values_func_2.c\
			./ft_printf/ft_get_casted_values_func_3.c\
			./ft_printf/ft_init.c\
			./ft_printf/ft_max.c\
			./ft_printf/ft_may_error.c\
			./ft_printf/ft_memalloc.c\
			./ft_printf/ft_memccpy.c\
			./ft_printf/ft_memchr.c\
			./ft_printf/ft_memcmp.c\
			./ft_printf/ft_memcpy.c\
			./ft_printf/ft_memdel.c\
			./ft_printf/ft_memmove.c\
			./ft_printf/ft_memset.c\
			./ft_printf/ft_min.c\
			./ft_printf/ft_mod_len.c\
			./ft_printf/ft_onesign.c\
			./ft_printf/ft_padding.c\
			./ft_printf/ft_patof.c\
			./ft_printf/ft_patoi.c\
			./ft_printf/ft_patoi_hex.c\
			./ft_printf/ft_precision.c\
			./ft_printf/ft_prefix_pf.c\
			./ft_printf/ft_print_line.c\
			./ft_printf/ft_printf.c\
			./ft_printf/ft_printf.o\
			./ft_printf/ft_put_wchar.c\
			./ft_printf/ft_put_wchar_len_3_4.c\
			./ft_printf/ft_putbin.c\
			./ft_printf/ft_putchar.c\
			./ft_printf/ft_putchar_buff.c\
			./ft_printf/ft_putchar_fd.c\
			./ft_printf/ft_putdbl.c\
			./ft_printf/ft_putendl.c\
			./ft_printf/ft_putendl_fd.c\
			./ft_printf/ft_puthex_max.c\
			./ft_printf/ft_putnbr.c\
			./ft_printf/ft_putnbr_buff.c\
			./ft_printf/ft_putnbr_fd.c\
			./ft_printf/ft_putnbr_max.c\
			./ft_printf/ft_putnbr_unsigned.c\
			./ft_printf/ft_putnstr.c\
			./ft_printf/ft_putoctal.c\
			./ft_printf/ft_putoctal_max.c\
			./ft_printf/ft_putstr.c\
			./ft_printf/ft_putstr_fd.c\
			./ft_printf/ft_putstr_non_printable.c\
			./ft_printf/ft_return.c\
			./ft_printf/ft_round.c\
			./ft_printf/ft_split_whitespace.c\
			./ft_printf/ft_splitlen.c\
			./ft_printf/ft_sprintf.c\
			./ft_printf/ft_sprintf.o\
			./ft_printf/ft_strichr.c\
			./ft_printf/ft_strichr_last.c\
			./ft_printf/ft_strjoin_3.c\
			./ft_printf/ft_strnjoin_free.c\
			./ft_printf/ft_strnrest.c\
			./ft_printf/ft_strnstr.c\
			./ft_printf/ft_strrchr.c\
			./ft_printf/ft_tools.c

SRCS	+=	./dytab/ft_dy_tab_add_index_ptr.c \
			./dytab/ft_dy_tab_add_ptr.c \
			./dytab/ft_dy_tab_add_str.c \
			./dytab/ft_dy_tab_cpy_ptr.c \
			./dytab/ft_dy_tab_cpy_str.c \
			./dytab/ft_dy_tab_del.c \
			./dytab/ft_dy_tab_del_ptr.c \
			./dytab/ft_dy_tab_new.c \
			./dytab/ft_dy_tab_realloc.c \
			./dytab/ft_dy_tab_suppr_index.c \
			./dytab/ft_dy_tab_suppr_index_ptr.c \
			./dytab/ft_dy_tab_empty.c

SRCS	+=	./dystr/ft_dy_str_new.c \
			./dystr/ft_dy_str_add_index.c \
			./dystr/ft_dy_str_realloc.c \
			./dystr/ft_dy_str_suppr_index.c \
			./dystr/ft_dy_str_free.c \
			./dystr/ft_dy_str_new_str.c \
			./dystr/ft_dy_str_new_ptr.c \
			./dystr/ft_dy_str_cpy_str.c \
			./dystr/ft_dy_str_replace.c \
			./dystr/ft_substitute_dy_str.c

SRCS	+=	./dlst/ft_dlstnew.c \
			./dlst/ft_dlstnew_ptr.c \
			./dlst/ft_dlstadd.c \
			./dlst/ft_dlstpushback.c \
		   	./dlst/ft_add_to_dlist_ptr.c \
			./dlst/ft_add_to_dlist_ptr_back.c \
			./dlst/ft_dlstdel_ptr.c \
			./dlst/ft_dlstpop_ptr.c \
			./dlst/ft_dlstpop.c \
			./dlst/ft_dlstiter.c \
			./dlst/ft_dlstdel.c \
			./dlst/ft_dlstlength.c \
			./dlst/ft_dlstiter_inv.c \
			./dlst/ft_add_to_dlist_back.c \
			./dlst/ft_dlstadd_sorted.c \
			./dlst/ft_dlstdel_value.c

SRCS	+=	./freeturn/ft_free_turn.c \
			./freeturn/ft_free_turn_dy_str.c \
			./freeturn/ft_free_turn_n.c

SRCS	+=	./hash/ft_hash_table_new.c \
			./hash/ft_hash_table_get.c \
			./hash/ft_hash_table_add.c \
			./hash/ft_hash_str.c \
			./hash/ft_hash_table_del_ptr.c \
			./hash/ft_hash_table_del_value.c \
			./hash/ft_hash_table_del.c \
			./hash/ft_hash_table_show_perf.c

OBJS		= $(SRCS:%.c=%.o)

HEADERS		= ./ft_printf/ft_printf.h ./libft.h

INCLUDES	= -I . -I ./ft_printf/

AR			= ar -rcs
CC			= gcc
ECHO		= echo

OS = $(shell uname -s)
EOC = \033[0m
ifeq ($(OS),Linux)
	CFLAGS		= $(INCLUDES)
	OK_COLOR = \033[1;32m
	FLAGS_COLOR = \033[1;34m
	#COMP_COLOR =
else
	CFLAGS		= -Wall -Werror -Wextra $(INCLUDES) -g3
	OK_COLOR = \x1b[32;01m
	#COMP_COLOR = \x1b[34;01m
	FLAGS_COLOR = \x1b[34;01m
#	COMP_COLOR =
endif

ifeq ($(DEBUG), 1)
		CFLAGS += -fsanitize=address
		CC += -g3
endif

all:
	@$(ECHO) "$(FLAGS_COLOR)Compiling with flags $(CFLAGS) $(EOC)"
	@echo make -C . $(NAME)
	@$(MAKE) -C . $(NAME)

debug:
	$(MAKE) all DEBUG=1

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS) && $(ECHO) "${OK_COLOR}Successfully compiled $(NAME) ${EOC}"

$(EXEC): $(NAME) main.c
	@$(CC) $(INCLUDE) $(CFLAGS) -o $(EXEC) main.c $(NAME) && $(ECHO) "${OK_COLOR}Successfully compiled $(EXEC) ${EOC}"

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@$(ECHO) "${COMP_COLOR}$< ${EOC}"

clean:
	@$(RM) -f $(OBJS) && $(ECHO) "${OK_COLOR}Successfully cleaned $(NAME) objects files ${EOC}"
	@$(RM) -f main.o

fclean: clean
	@$(RM) -f $(NAME) && $(ECHO) "${OK_COLOR}Successfully cleaned $(NAME) ${EOC}"
	@$(RM) -f $(EXEC)

re: fclean all
