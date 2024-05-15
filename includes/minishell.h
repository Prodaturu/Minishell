/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 07:36:28 by sprodatu          #+#    #+#             */
/*   Updated: 2024/05/15 08:35:17 by sprodatu         ###   ########.fr       */
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

typedef struct s_cmd
{
	char			**args;
	struct s_cmd	*prev;
	struct s_cmd	*next;
	int				fd_in;
	int				fd_out;
}			t_cmd;

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
	R_OUT,
	REDIR_APPEND,
	END
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}			t_token;

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
	int		single_q;
	int		double_q;
}		t_lex;

//: main functions: ---------------------

int			parse(t_ms *ms);
int			lexing(t_ms *ms);

//: main functions end: -----------------

//: freeing parser functions:
void		free_tokens(t_token *token);

//: token handler functions:
t_token		*pipe_token(t_lex *lexer);
t_token		*in_token(t_lex *lexer);

#endif
