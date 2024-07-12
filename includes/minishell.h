/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 07:36:28 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/12 17:01:25 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>

#define MAX_PATH_LENGTH 1024

extern int g_signal;

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

typedef enum s_type { WORD, PIPE, IN, H_DOC, OUT, APPEND, ERR, END } t_type;

typedef struct s_token {
  t_type type;
  struct s_token *next;
  struct s_token *prev;
  char *value;
} t_token;

typedef struct s_cmd {
  t_token *token;
  struct s_cmd *prev;
  struct s_cmd *next;
  int fd_in;
  int fd_out;
  char **args;
} t_cmd;

typedef struct s_env {
  struct s_env *next;
  char *env_name;
  char *env_value;
} t_env;

typedef struct s_ms {
  t_token *token;
  t_cmd *cmd;
  t_env *env_s;
  pid_t *pids;
  int exit_code;
  char *input;
  char **env;
} t_ms;

typedef struct s_lex {
  char *input;
  int pos;
  int sq;
  int dq;
} t_lex;

typedef struct s_ft {
  char *name;
  void (*ft)(char **argv, t_env **env_s, t_ms *ms);
} t_ft;

typedef struct s_builtin {
  t_ft inbuilt[7];
} t_builtin;

void print_commands(t_cmd *cmd);
void print_tokens(t_token *token);

//: main functions: ---------------------

int parse(t_ms *ms);
int lexing(t_ms *ms);
// void		print_cmds(t_ms *mini);

//: main functions end: -----------------
void free_commands(t_cmd *cmd);

//: freeing parser functions:
void free_tokens(t_token *token);

//: token handler functions:
t_token *pipe_token(t_lex *lexer);
t_token *in_token(t_lex *lexer);
t_token *out_token(t_lex *lexer);
t_token *word_token(t_lex *lex);
t_token *eof_token(void);

// helpers (tokenizer_helper.c)

t_token *word_token_value(int start, t_lex *lex);
void quote_token_value(t_lex *lex, char quote);
t_token *unclosed_quote_token(void);
t_token *empty_quotes_token(void);

//: Syntax check functions:

int syntax_error(t_ms *ms);

//: commands functions:
int commands(t_ms *ms);
int has_something(const char *input);

//: commands_helper functions:
int get_args(t_token **token, t_cmd *cmd);
int fill_arg_array(int i, t_cmd **cmd, t_token **token);
char *redirect_to_str(t_token *token);

//: expand :
void expand(t_ms *ms);
int check_and_expand(char **s, t_ms *ms, int *s_flag);
void replace_and_free_args(char ***args, int *n, int *s_flag);

//: expand_utils.c:
int handle_pid_exitcode_ex(const char *str, int *i, char **ex_str, t_ms *ms);
int handle_dquotes(char *str, int *i, char **ex_str, t_ms *ms);
int handle_squotes(char *str, int *i, char **ex_str);
int handle_expansion(char *str, int *i, char **ex_str, t_ms *ms);
char *ft_strnjoin(char *s1, const char *s2, size_t n);

//: expand_utils_helper.c:
void ft_strnjoin_helper(char *dest, const char *src, size_t n);
char *get_env(const char *name, char **env);
char **new_args_maker(char **n_as, char **as, char **s_as, const int *n);
int expand_and_join(char *str, int *i, char **ex_str, t_ms *ms);
void process_args(t_cmd *cmd, t_ms *ms);

//: redrection functions:
int handle_redirection(t_ms *mini);

//: redrection_helper functions:
int check_file(char *path);
int set_fd(char *re, char *path, t_cmd *cmd, t_ms *mini);
int check_if_file_exits(t_ms *mini, char *path);

//: h_doc functions:
void heredoc(int fd, char *del, t_ms *mini);
int ft_strcmp(const char *s1, const char *s2);
void remove_element(char ***arr_ptr, int index);
void remove_cmd_node(t_ms *mini, t_cmd *node_to_remove);

//: executor functions:
void executor(t_ms *ms);
void wait_pids(t_ms *ms, int n_cmd);
int pids_init(pid_t **pids, int n_cmd);
int fds_init(int ***fds, int n_cmd);
void exec_free(t_ms *ms, int n_cmd, int **fds);

// exec_utils functions:
void ft_change_shellvl(t_ms *ms, int i);
int ft_alpha_check(char *name, char *cmd, t_ms *ms);
int ft_alnum_check(char *name, char *arg, int j, t_ms *ms);
void free_array(char **array, int index);

// simple_exec functions:
void simple_exec(t_ms *ms);
void set_pipes(t_cmd *cmd, int *fd);
void set_builtin(char **args, t_env *env_s, int *fd, t_ms *ms);
t_cmd *find_last_node(t_cmd *cmd);
int *set_fds(t_ms *ms);

// multi_exec functions:
int count_cmd(t_cmd *cmd);
void performer(t_ms *ms, int **fds, int ncmd);
void child_process(t_cmd *cmd);
void close_fds(int **fds, int n_cmd);

// ft_execve functions:
void ft_execve(t_cmd *cmd, t_env **env_s, t_ms *ms);
char *get_path(char *cmd, char **env_s);
char **env_to_char(t_env *env_s);

// inbuilds functions:
int is_builtin(t_cmd *cmd);
void exec_builtin(char **argv, t_env **env_s, t_ms *ms);

// ft_echo functions:
void ft_echo_prep(char **cmd, t_env **env_s, t_ms *ms);

// ft_env functions:
void ft_env_prep(char **cmd, t_env **env_s, t_ms *ms);

// ft_pwd functions:
void ft_pwd_prep(char **cmd, t_env **env_s, t_ms *ms);

// ft_cd functions:
void ft_cd_prep(char **cmd, t_env **env_s, t_ms *ms);
char *ft_getenv(char *name, t_env *env_s);
void ft_setenv(char *name, char *value, int overwrite, t_env *env_s);

// ft_export functions:
void ft_export_prep(char **cmd, t_env **env_s, t_ms *ms);
void identifier_error(char *name, char *cmd, t_ms *ms);
int input_checker(char *name, char *cmd, t_ms *ms, t_env **env_s);
void ft_export(char *name, t_env **env_s, t_ms *ms);
void new_env_exp(char *append_env, t_env *tmp, char **newenv);
char *env_strjoin(t_env *tmp, char **newenv);
char *env_strdup(t_env *tmp, char **newenv);

// ft_unset functions:
void ft_unset_prep(char **cmd, t_env **env_s, t_ms *ms);

// ft_exit functions:
void ft_exit_prep(char **cmd, t_env **env_s, t_ms *ms);

// save_env_in_struct functions:
t_env *save_env(char **env, t_env *env_struct);
void append_node(t_env **env_s, char *token, char *type);
void free_struct(t_env **stack);
t_env *find_last(t_env *env_s);

#endif
