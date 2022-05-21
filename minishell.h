/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:29:11 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/29 16:29:25 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PATH_MAX = 1024
# define BUFFER_SIZE 1024

# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <time.h> 
# include <stdlib.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <ncurses.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <limits.h>
# include <string.h>

# define UP "\e[A"
# define DOWN "\e[B"
# define DELETE 127
# define ENTER 10
# define CTRLD 4
# define LEFTRIGHT 27
# define ERROR 1
# define ON 1
# define OFF 0
# define GREEN	"\e[1;32m"
# define RED	"\e[0;31m"
# define WHITE	"\033[0m"
# define BLUE "\e[0;34m"

typedef struct s_termcap
{
	int				ret;
	char			*join;
	char			buffer[5];
	int				c;
	int				lstsize;
	int				prevlen;
	char			*histadd;
	int				histpos;
	int				check;
	int				check2;
	char			*save;
	struct winsize	win;
}				t_termcap;

typedef struct s_exit
{
	int		exit_sig;
	int		exit_status;
}				t_exit;

t_exit		g_check;

typedef struct s_global
{
	int			mini_ret;
	int			b_exit;
	char		**home;
	char		*oldpwd;
	t_list		*commands;
	char		**env_tab;
	int			oldpwd_env;
	int			pwd_env;
	char		*pwd;
	int			shlvl;
	int			fd_in;
	int			exit_pipe;
	int			fd_red;
	int			fd_prv;
}				t_global;

typedef enum e_type
{
	WRITE,
	READ,
	APPEND,
	PIPE,
	END
}			t_type;

typedef struct s_cflist
{
	char				*name;
	t_type				type;
	int					file_dollar;
	struct s_cflist		*next;
}						t_cflist;

typedef struct s_cmds
{
	char		**cmd;
	t_type		type;
	t_cflist	*file;
}				t_cmds;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_symbol
{
	int		semi;
	int		pipe;
	int		d_quote;
	int		s_quote;
	int		read;
	int		write;
	int		append;
	int		error;
	int		already_pipe;
}					t_symbol;

typedef struct s_minishell
{
	t_cmds			cmds;
	t_cflist		*scmd;
	t_list			*env;
	t_list			*export_env;
	t_list			*unset;
	t_global		glob;
	char			*cmdline;
	t_list			*history;
	int				sig_status;
	pid_t			pid;
	int				fd[2];
	t_cflist		*tmp;
	char			*tmpline;
	struct termios	term;
	int				fds;
	char			*check_env;
	char			*under_score;
	int				cp;
	char			*file_nme;
	t_env			*env2;
	t_symbol		*smbl;
}	t_mini;
/*
** utils
*/
char			*ft_strndup(char *s, size_t len);
void			ft_putstr(char *s);
int				ft_maxlen(char *s1, char *s2);
int				check_isnumeriq(char *str);
int				check_spec_char(char *str);
int				check_syntax_export(char *cmd);
int				check_syntax_unset(char *cmd);
void			free_tabl(char **s);
int				ft_strcmp(char *s1, char *s2);
void			ft_sort_tabl(char **tabll);
char			*search_replace(char *str, char *org, char *rep);
int				ft_sort_str(char *s1, char *s2);
int				check_valid(char *str);
char			*get_export_value(char *name);
void			print_export(t_list *export, int fd);
void			init(t_mini *mini, char **environ);
void			set_terminal(struct termios term);
void			free_mini(t_mini *mini);
void			free_help_main(t_mini *mini, char **env);
void			help_main(t_mini *mini, t_cflist *tmp);
void			sub_free_mini(t_mini *mini);
int				minishell(t_mini *mini);
/*
** list utils
*/
void			sort_list(t_list *list);
void			print_list(t_list *list, int fd);
t_list			*init_list(void);
char			**list_to_tabl(t_list *list);
t_cflist		*cf_lst_new(void *name, int type);
void			cf_lstadd_back(t_cflist **alst, t_cflist *new);
void			cf_lstdelone(t_cflist *lst, void (*del)(void*));
void			cf_lstclear(t_cflist **lst, void (*del)(void*));
/*
** execute cmd
*/
void			execute_cmd(t_mini *mini);
void			execute_shell(t_mini *mini);
void			shlvl(t_mini *mini);
int				help_execve(t_mini *mini, char **env, char *path);
int				s_help_execve(t_mini *mini);
void			call_execve(t_mini *mini, char **env, char *path);
int				check_permission(char *path);
int				check_dir(char *path);
void			get_path(t_mini *mini, char **split, char **path, int *perm);
void			help_cd_home_cur(t_mini *mini);
void			execute_cd_home_cur(t_mini *mini);
/*
** execute builtins
*/
void			execute_builtins(t_mini *mini);
int				check_isbuiltin(char *cmd);
int				check_pipe_builtins(t_mini *mini);
void			execute_cd(t_mini *mini);
void			execute_echo(char **cmd, t_mini *mini);
void			execute_env(t_mini *mini);
void			execute_exit(t_mini *mini);
void			execute_export(t_mini *mini);
void			execute_pwd(t_mini *mini);
void			execute_unset(t_mini *mini);
void			mod_oldpwd(t_mini *mini);
void			reset_oldpwd(t_mini *mini, char *save_oldpwd);
void			mod_pwd(t_mini *mini);
void			mod_old(t_mini *mini, char *cwd);
int				check_n(char *str);
void			echo_dollar(t_mini *mini, char *cmd);
int				get_n(char **cmd, int *b);
/*
** error functions
*/
void			error_pwd(char *str, int err);
void			error_export(char *str, t_mini *mini);
void			error_cd(char *path, int err);
void			error_unset(char *str, t_mini *mini);
void			error_exit(char *str);
void			error_command(char *command);
void			error_nodir(char *command);
void			error_file_nodir(char *command);
void			error_permission(char *command);
void			current_dir_err(void);
int				wapp_error(t_cflist *tmp, int *fd);
int				r_error(t_cflist *tmp, int *fd);
/*
** environ functions
*/
void			mod_env(t_list *env, char *name, char *var);
int				check_in_env(t_list *env, char *str);
t_list			*init_env_environ(char **environ);
t_list			*init_export_environ(char **environ);
char			**ft_getenv(char *name, t_list *env);
void			error_dir(char *command);
void			unset_env(char *str, t_list **env);
/*
** termcap functions
*/
void			delete(char **cmdline, t_termcap *term);
void			exec_ctrld(char *cmdline);
void			readline(char **cmdline, t_list **history);
int				fd_put(int c);
int				termcap(t_termcap *term, char **cmdline);
void			get_cmdline(t_termcap *term, char **cmdline);
void			uphistory(t_termcap *term, t_list **history, char **cmdline);
void			downhistory(t_termcap *term, t_list **history, char **cmdline);
/*
** sig handler
*/
void			child_sig_handler(int status);
void			sig_handler(int sig);
/*
** redir functions
*/
int				create_files(t_mini *mini, t_cflist **w, t_cflist **r, int *fd);
int				redir(t_mini *mini);
int				redir_builtins(t_mini *mini);
/*
** parsing functions
*/
void			splitpipesemi(t_mini *mini);
void			error_red(t_symbol *smbl, char c);
int				count_back(char *line);
void			ft_error(t_symbol *smbl, char *str);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
char			*partition_stage(t_symbol *smbl, char *line);
char			*check_space(t_symbol *smbl, char *line, int i);
void			initial_symbol(t_symbol *sbl);
char			*check_symbols(t_symbol *smbl, char *line, int i);
char			*check_d_quote(t_symbol *smbl, char *line, int i);
char			*check_s_quote(t_symbol *smbl, char *line, int i);
char			*check_semicolone(t_symbol *smbl, char *line, int i);
char			*check_semi_off(t_symbol *smbl, char *line, int i);
char			*check_pipe_off(t_symbol *smbl, char *line, int i);
char			*check_pipe(t_symbol *smbl, char *line, int i);
char			*check_redirection(t_symbol *smbl,
					char *line, int i, int *type);
int				check_flags(t_symbol *smbl);
void			off_flags(t_symbol *smbl);
char			*reverse_cmd(t_mini *mini, char *line, int i, int j);
char			*ft_substr2(char *s, unsigned int start, size_t len);
void			push_to_struct(t_mini *mini, char *line);
int				compare(char *str, char *str2);
void			file_lstadd_back(t_cflist **alst, t_cflist *new);
t_cflist		*file_lst_new(void *filename, int filetype);
void			free_cmds_struct(t_mini *mini);
void			ft_free_tab(char **s);
void			ft_free(t_mini *mini);
char			*dollar(t_mini *mini, char *line);
char			*check_dollr(t_mini *mini, char *line);
char			*ft_turn_dollar(t_symbol *smbl, char *line, int i);
char			*sort_redirection(char *line);
int				redirection(t_symbol *smbl);
char			*check_redirection(t_symbol *smbl, char *line,
					int i, int *type);
void			initail_struct(t_mini *mini);
void			split_semi_pipe(t_mini *mini, char *line, int len, int i);
t_cflist		*lstnew_cmd(char *v_cmd, int type);
void			lstadd_cmd(t_cflist **alst, t_cflist *new);
t_env			*create_env_list(char **env);
void			env_lstclear(t_env **lst, void (*del)(void*));
t_env			*create_env_list(char **env);
char			*get_path_dollar(t_mini *mini, char *line, int *j);
char			*add_dollar_path(char *path);
char			*file_dollar(char *line, char *path);
void			add_new_env_element(t_env *curr_node, char *env);
char			*dollar_digit(char *line, int *i);
char			*dollar_simple(t_mini *mini, char *line, int *i);
void			off_red(t_symbol *smbl);
char			*get_path_dollar(t_mini *mini, char *line, int *j);
char			*add_dollar_path(char *path);
char			*file_dollar(char *line, char *path);
#endif