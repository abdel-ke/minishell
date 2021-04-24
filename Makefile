# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/02 19:19:58 by amouassi          #+#    #+#              #
#    Updated: 2021/04/23 13:38:13 by abdel-ke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell.a
CC = gcc 
FLAGS = -Wall -Wextra -Werror
AR = ar rcs
LIBFT = libft
NAMELIBFT = libft.a
EXE = minishell

SRCLIB =  ft_atoi.c \
		  ft_bzero.c \
	      ft_calloc.c \
	  	  ft_isalnum.c \
	 	  ft_isalpha.c \
		  ft_isascii.c \
		  ft_isdigit.c \
		  ft_isprint.c \
		  ft_itoa.c \
		  ft_memccpy.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_memset.c \
		  ft_putchar_fd.c \
		  ft_putnbr_fd.c \
		  ft_putstr_fd.c \
		  ft_putendl_fd.c \
		  ft_split.c \
		  ft_strchr.c \
		  ft_strdup.c \
		  ft_strjoin.c \
		  ft_strlcat.c \
		  ft_strlcpy.c \
		  ft_strlen.c \
		  ft_strmapi.c \
		  ft_strncmp.c \
		  ft_strnstr.c \
		  ft_strrchr.c \
		  ft_strtrim.c \
		  ft_substr.c \
		  ft_tolower.c \
		  ft_toupper.c \
		  ft_lstadd_back.c \
		  ft_lstadd_front.c \
		  ft_lstlast.c \
		  ft_lstnew.c \
		  ft_lstsize.c \
		  ft_lstdelone.c \
		  ft_lstclear.c \
		  ft_lstiter.c \
		  ft_lstmap.c \
		  ft_strstr.c \
		  ft_strcpy.c \

SRC = utils/utils.c \
	  utils/utils2.c \
	  utils/utils3.c \
	  utils/utils4.c \
	  utils/env_utils.c \
	  utils/list_utils.c \
	  utils/list_utils2.c \
	  utils/list_utils3.c \
	  utils/execute_shell_utils.c \
	  mini_utils.c \
	  sig_handler.c \
	  free.c \
	  init.c \
	  builtins/execute_pwd.c \
	  builtins/execute_cd.c \
	  builtins/execute_env.c \
	  builtins/execute_export.c \
	  builtins/execute_unset.c \
	  builtins/execute_echo.c \
	  builtins/execute_exit.c \
	  builtins/mod_old_pwd.c \
	  errors/errors.c \
	  errors/exec_errors.c \
	  execute_cmd.c \
	  execute_shell.c \
	  call_execve.c \
	  execute_builtins.c \
	  shlvl.c \
	  main.c \
	  redirections/create_files.c \
	  redirections/redir.c \
	  readline.c \
	  termcap.c \
	  history.c \
	  parsing/parsing.c \
	  parsing/symbols.c \
	  parsing/struct.c \
	  parsing/dollar.c \
	  parsing/error.c\
	  parsing/switch_new_line.c\
	  parsing/redirection.c\
	  parsing/push_to_struct.c\
	  parsing/dollar_utils.c\
	  parsing/pipe_semi.c

OBJ = $(SRC:.c=.o)
OBJLIB = $(addprefix $(LIBFT)/,$(SRCLIB:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) $(OBJLIB)
	$(AR) $(NAME) $(OBJ) $(OBJLIB)
	$(CC) -ltermcap $(FLAG) $(NAME) -o $(EXE)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(OBJLIB)
fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)/$(NAMELIBFT)

re: fclean all