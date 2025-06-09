# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nafarid <nafarid@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 14:41:13 by nafarid           #+#    #+#              #
#    Updated: 2025/05/31 14:34:54 by nafarid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = main.c tokens/tokenizer.c tokens/tokens_utils.c parsing/parse.c parsing/parse_utils.c env_to_lst.c \
		 parsing/parse_helpers.c parsing/parse_opers.c change_stat.c p_expansion.c cleaning/quote_del.c \
		argument_count.c word_split.c lstadd_front.c lstadd_back.c heredoc.c  cleaning/lst_clear.c  lst_new_ele.c arr_free.c tokens/toks_trim.c \
		tokens/lstadd_back_token.c env_lst_to_arr.c tokens/lst_last_token.c ft_lstlast.c cleaning/lst_del.c utils.c signals.c \
		
OBJS = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra
FLAGS = -lreadline
LIBFT_DIR = libft
LIB = $(LIBFT_DIR)/libft.a
all: $(NAME)

$(NAME) : $(OBJS)
	cd $(LIBFT_DIR) && $(MAKE) -s
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME) $(FLAGS)

.o :.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@cd $(LIBFT_DIR) && $(MAKE) -s clean
	@rm -f $(OBJS)

fclean: clean
	@cd $(LIBFT_DIR) && $(MAKE) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
