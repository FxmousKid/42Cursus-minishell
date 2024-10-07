/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:45:27 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/07 13:33:22 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

# define MAX_TOKEN 4096

typedef enum e_token
{
	CMD, // 'ls'
	F_NAME, // 'file.txt'
	WORD, // 'ABC' or command for all we know at the lexing stage
	PIPE, // '|'
	REDIR_IN, // '<'
	REDIR_OUT, // '>'
	REDIR_APPEND, // '>>'
	HEREDOC, // '<<'
	EQUAL, // '='
	SINGLE_QUOTE, // '
	DOUBLE_QUOTE, // "
	DOLLAR_SIGN, // '$'
	O_PAREN, // '('
	C_PAREN, // ')'
	OR, // '||'
	AND, // '&&'
	
}	t_token;

typedef struct s_lexem
{
	t_token token;
	char	*value;
}			t_lexem;

typedef struct s_lexer
{
	char	*line;
	int		idx;
	int		mayb_word;
	int		open_double_q;
	int		open_single_q;
	int		open_paren;
	int		close_paren;
	t_lexem	*lexems[MAX_TOKEN];
}			t_lexer;

typedef struct s_ast t_ast ;

struct t_ast
{
	enum e_token token;
	union
	{
		struct ast_file {char *filename;} ast_file;
		struct ast_cmd {char *cmd; char *cmd_args;} ast_cmd;
		struct ast_pipe {t_ast *left; t_ast *right;} ast_pipe;
		struct ast_redir_in {t_ast *left; t_ast *right;} ast_redin_in;
		struct ast_redir_out {t_ast *left; t_ast *right;} ast_redir_out;
		struct ast_redir_append {t_ast *left; t_ast *right;} ast_redir_append;
		struct ast_heredoc {t_ast *left; t_ast *right;} ast_heredoc;
		struct ast_equal {t_ast *left; t_ast *right;} ast_equal;
		struct ast_dollar_sign {t_ast *left; t_ast *right;} ast_dollar_sign;
	};
};



void	lexer(t_lexer *lex, char *str);


#endif
