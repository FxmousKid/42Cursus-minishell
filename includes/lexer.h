/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:45:27 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/16 18:24:33 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

# define MAX_TOKEN 4096
# define META_CHARACTERS "()<>&|;\t\n "

typedef enum e_token
{
	HEREDOC, // '<<'
	HERESTRING, // '<<<'
	REDIR_IN, // '<'
	REDIR_OUT, // '>'
	REDIR_APPEND, // '>>'
	PIPE, // '|'
	OR, // '||'
	AND, // '&&'
	O_PAREN, // '('
	C_PAREN, // ')'
	EQUAL, // '='
	WORD, // hello
	DQ_WORD, // "hello"
	SQ_WORD, // 'hello'
	ERROR,
	CMD, // 'ls'
	F_NAME, // 'file.txt'
	SINGLE_QUOTE, // '
	DOUBLE_QUOTE, // "
	DOLLAR_SIGN, // '$'
}	t_token;

typedef struct s_lexem
{
	bool			is_meta;
	t_token			token;
	char			*value;
}					t_lexem;

typedef struct s_lexer
{
	char	**words;
	t_lexem	lexems[MAX_TOKEN];
	int		words_idx;
	int		open_double_q;
	int		open_single_q;
	int		open_paren;
	int		closed_paren;
}			t_lexer;

typedef struct s_ast	t_ast;

struct s_ast
{
	t_token	token;
	union
	{
		struct s_ast_file
		{
			char	*filename;
		}	ast_file;
		struct s_ast_cmd
		{
			char	*cmd;
			char	*cmd_args;
		}	ast_cmd;
		struct s_ast_pipe
		{
			t_ast	*left;
			t_ast	*right;
		}	ast_pipe;
		struct s_ast_redir_in
		{
			t_ast	*left;
			t_ast	*right;
		}	ast_redin_in;
		struct s_ast_redir_out
		{
			t_ast	*left;
			t_ast	*right;
		}	ast_redir_out;
		struct s_ast_redir_append
		{
			t_ast	*left;
			t_ast	*right;
		}	ast_redir_append;
		struct s_ast_heredoc
		{
			t_ast	*left;
			t_ast	*right;
		}	ast_heredoc;
		struct s_ast_equal
		{
			t_ast	*left;
			t_ast	*right;
		}	ast_equal;
		struct s_ast_dollar_sign
		{
			t_ast	*left;
			t_ast	*right;
		}	ast_dollar_sign;
	};
};

// Lex Utils
void	free_lex(t_lexer *lex);
void	fill_lexem(t_lexer *lex, char *str, t_token token, bool meta);
void	dislay_lexem(t_lexer *lex);

// Lex
void	lexer(t_lexer *lex, char *str);
void	lex_meta_chars(t_lexer *lex, char *str);


#endif
