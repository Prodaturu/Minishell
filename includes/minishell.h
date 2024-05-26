/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 07:36:28 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/26 03:18:12 by sprodatu         ###   ########.fr       */
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
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}			t_token;

typedef struct s_cmd
{
	char			**args;
	struct s_cmd	*prev;
	struct s_cmd	*next;
	int				fd_in;
	int				fd_out;
	t_token			*token;
}			t_cmd;
typedef struct s_ms
{
	pid_t	*pids;
	char	*input;
	t_token	*token;
	char	**env;
	t_cmd	*cmd;
	int		exit_code;
}		t_ms;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_lex
{
	char	*input;
	int		pos;
	int		sq;
	int		dq;
}		t_lex;

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

// int			handle_quotes(char *str, int *i, char **ex_str);
// void		check_and_ex_helper(char *str, char **es, t_ms *ms, int *sf);
// void		replace_and_free_args(char ***args, int *n, int *s_flag);
// int			check_and_expand(char **s, t_ms *ms, int *s_flag);
// int			expand(t_ms *ms);

// //: expand_utils functions:
// void		merge_helper(char **new, char ***array1, char **array2, int *i);
// void		merge_arrays(char ***new_array, char **array1, int *i);
// char		*ft_strnjoin(char *s1, char *s2, int n);
// char		*get_env(const char *name, char **env);
// void		print_cmds(t_ms *mini);

// //: expand_utils_helper functions:
// void		remove_element(char ***array_ptr, int index);
// int			handle_pid_exitcode_ex(char *str, int *i, char **ex_str, t_ms *m);
// int			expand_and_join(char *str, int *i, char **ex_str, t_ms *mini);
// int			handle_dquotes(char *str, int *i, char **ex_str, t_ms *m);
// int			handle_expansion(char *str, int *i, char **ex_str, t_ms *mini);

#endif
