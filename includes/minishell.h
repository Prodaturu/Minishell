/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 07:36:28 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/26 07:00:30 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_PATH_LENGTH 1024

extern int	g_signal;

// To store the type of token and its value
// Example: ls | cat
// ls is a WORD token
// | is a PIPE token
// cat is a WORD token
// This will be used to parse the input
// and create a linked list of tokens
// to be used in the execution of the command
// Example: ls | cat
// The linked list will be:
// ls -> | -> cat

typedef enum s_type
{
	WORD,
	PIPE,
	IN,
	H_DOC,
	OUT,
	APPEND,
	ERR,
	END
}	t_type;

typedef struct s_token
{
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
	char			*value;
}			t_token;

typedef struct s_cmd
{
	t_token			*token;
	struct s_cmd	*prev;
	struct s_cmd	*next;
	int				fd_in;
	int				fd_out;
	char			**args;
}			t_cmd;

typedef struct s_env
{
	struct s_env	*next;
	char			*env_name;
	char			*env_value;
}	t_env;

typedef struct s_ms
{
	t_token	*token;
	t_cmd	*cmd;
	t_env	*env_s;
	pid_t	*pids;
	int		exit_code;
	char	*input;
	char	**env;
}		t_ms;

typedef struct s_lex
{
	char	*input;
	int		pos;
	int		sq;
	int		dq;
}		t_lex;

typedef struct s_ft
{
	char	*name;
	void	(*ft)(char **argv, t_env **env_s, t_ms *ms);
}	t_ft;

typedef struct s_builtin
{
	t_ft	inbuilt[7];
}	t_builtin;

void		print_commands(t_cmd *cmd);

//: main functions: ---------------------

int			parse(t_ms *ms);
int			lexing(t_ms *ms);

//: main functions end: -----------------

//: freeing parser functions:
void		free_tokens(t_token *token);

//: token handler functions:
t_token		*pipe_token(t_lex *lexer);
t_token		*in_token(t_lex *lexer);
t_token		*out_token(t_lex *lexer);
t_token		*word_token(t_lex *lex);
t_token		*eof_token(void);

// helpers (tokenizer_helper.c)

t_token		*word_token_value(int start, t_lex *lex);
void		quote_token_value(t_lex *lex, char quote);
t_token		*unclosed_quote_token(void);
t_token		*empty_quotes_token(void);

//: Syntax check functions:

int			syntax_error(t_ms *ms);

//: commands functions:
int			commands(t_ms *ms);

//: commands_helper functions:
int			get_args(t_token **token, t_cmd *cmd);
int			fill_arg_array(int i, t_cmd **cmd, t_token **token);
char		*redirect_to_str(t_token *token);

//: expand functions:
void		remove_element(char ***arr_ptr, int index);
void		expand(t_ms *ms);
char		*get_env(const char *name, char **env);
char		*ft_strnjoin(char *s1, const char *s2, size_t n);
void		ft_strnjoin_helper(char *dest, const char *src, size_t n);
int			handle_pid_exitcode_ex(char *str, int *i, char **ex_str, t_ms *ms);
int			expand_and_join(char *str, int *i, char **ex_str, t_ms *ms);
int			handle_dquotes(char *str, int *i, char **ex_str, t_ms *ms);
int			handle_squotes(char *str, int *i, char **ex_str);
void		replace_and_free_args(char ***args, int *n, int *s_flag);
int			handle_expansion(char *str, int *i, char **ex_str, t_ms *ms);
int			check_and_expand(char **s, t_ms *ms, int *s_flag);
void		expand(t_ms *ms);

//: redrection functions:
void		handle_redirection(t_ms *mini);
void		heredoc(int fd, char *del, t_ms *mini);
void		remove_cmd_node(t_ms *mini, t_cmd *node_to_remove);
void		print_cmds(t_ms *mini);
int			check_if_file_exits(t_ms *mini, char *path);
int			check_file(char *path);
int			set_fd(char *re, char *path, t_cmd *cmd, t_ms *mini);
char		*ft_strnjoin(char *s1, const char *s2, size_t n);
char		*get_env(const char *name, char **env);
int			ft_strcmp(const char *s1, const char *s2);

//Execution
void		executor(t_ms *ms);
void		wait_pids(t_ms *ms, int n_cmd);
int			pids_init(pid_t **pids, int n_cmd);
int			fds_init(int ***fds, int n_cmd);
void		exec_free(t_ms *ms, int n_cmd, int **fds);

//exec_utils.c
void		ft_change_shellvl(t_ms *ms);
int			ft_alpha_check(char *name, char *cmd, t_ms *ms);
int			ft_alnum_check(char *name, char *arg, int j, t_ms *ms);

//simple_exec.c
void		simple_exec(t_ms *ms);
void		set_pipes(t_cmd *cmd, int *fd);
void		set_builtin(char **args, t_env *env_s, int *fd, t_ms *ms);
t_cmd		*find_last_node(t_cmd *cmd);
int			*set_fds(t_ms *ms);

//multi_exec.c
int			count_cmd(t_cmd *cmd);
void		performer(t_ms *ms, int **fds, int ncmd);
void		child_process(t_cmd *cmd);
void		close_fds(int **fds, int n_cmd);

//ft_execve.c
void		ft_execve(t_cmd *cmd, t_env **env_s, t_ms *ms);
char		*get_path(char *cmd, char **env_s);
char		**env_to_char(t_env *env_s);

//inbuilds.c
int			is_builtin(t_cmd *cmd);
void		exec_builtin(char **argv, t_env **env_s, t_ms *ms);
//ft_echo.c
void		ft_echo_prep(char **cmd, t_env **env_s, t_ms *ms);
//ft_env.c
void		ft_env_prep(char **cmd, t_env **env_s, t_ms *ms);
//ft_pwd.c
void		ft_pwd_prep(char **cmd, t_env **env_s, t_ms *ms);
//ft_cd.c
void		ft_cd_prep(char **cmd, t_env **env_s, t_ms *ms);
char		*ft_getenv(char *name, t_env *env_s);
void		ft_setenv(char *name, char *value, int overwrite, t_env *env_s);
//ft_export.c
void		ft_export_prep(char **cmd, t_env **env_s, t_ms *ms);
void		identifier_error(char *name, char *cmd, t_ms *ms);
int			input_checker(char *name, char *cmd, t_ms *ms, t_env **env_s);
void		ft_export(char *name, t_env **env_s, t_ms *ms);

//ft_unset.c
void		ft_unset_prep(char **cmd, t_env **env_s, t_ms *ms);
//ft_exit.c
void		ft_exit_prep(char **cmd, t_env **env_s, t_ms *ms);
//save_env_in_struct.c
t_env		*save_env(char **env, t_env *env_struct);

//to delete later
int			check_if_file_exits(t_ms *ms, char *path);
void		handle_directory(char *path);

#endif
