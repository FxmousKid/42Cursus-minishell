/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:45:27 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/28 10:47:35 by inazaria         ###   ########.fr       */
/*   Updated: 2024/10/27 21:17:16 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANALYSIS_H
# define ANALYSIS_H

# include "dependencies.h"
# include "macros.h"

/* Error as the 1st token is important because it will be the default one 
 * on initialization */

typedef enum e_token
{
	ERROR,
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
	CMD, // 'ls'
	F_NAME, // 'file.txt'
	LIMITER, // << 'EOF'
	Q_LIMITER, // << "EOF"
	SINGLE_QUOTE, // '
	DOUBLE_QUOTE, // "
	ENV_VAR, // $ABC
}	t_token;

typedef struct s_lexem
{
	bool			is_meta;
	t_token			token;
	char			*value;
}					t_lexem;

typedef struct s_lexer
{
	char	input[MAX_TOKEN];
	char	*words[MAX_TOKEN];
	t_lexem	lexems[MAX_TOKEN];
	size_t	lexem_count;
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
			char	**cmd_args;
			int		fd_in;
			int		fd_out;
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
		// struct s_ast_dollar_sign
		// {
		// 	t_ast	*left;
		// 	t_ast	*right;
		// }	ast_dollar_sign;
		struct s_ast_herestring
		{
			t_ast	*left;
			t_ast	*right;
		}	ast_herestring;
		struct s_ast_and
		{
			t_ast	*left;
			t_ast	*right;
		}	ast_and;
		struct s_ast_or
		{
			t_ast	*left;
			t_ast	*right;
		}	ast_or;
	};
};

typedef struct s_data t_data;

// Lex Utils
int		is_meta_char(char *str);
bool	split_cl(t_lexer *lex);
void	free_lex(t_lexer *lex);
void	fill_lexem(t_lexem *lexem, char *str, t_token token, bool meta);
void	print_lexems(t_lexer *lex);
/* Check the passed lexer structure has a certain token
 * takes the lexems array to enable offset checks */
bool	has_token(t_lexem *lexems, t_token token);
/* checks if the lexems contain n lexems whose token are the same
 * as the passed token argument */
bool	has_n_token(t_lexer *lex, t_token token, size_t n);

/* swap all field values of both lexems at index i and j */
void	swap_lexems(t_lexer *lex, size_t i, size_t j);
/* offsets all the lexems on the i-th index, leaving the i-th lexems blank */
void	offset_lexems_right(t_lexer *lex, size_t i);

// Lexer
bool	lex_if_meta_chars(t_lexem *lexem, char *str);
bool	lexer(t_lexer *lex, char *input);

// Parser
bool	parser(t_data *data, t_lexer *lex);
bool	search_parse_error(t_lexer *lex);
bool	prompt_for_partial_sq_dq(t_lexer *lex);
bool	prompt_for_partial_pipe(t_lexer *lex);
bool	prompt_for_heredocs(t_lexer *lex, char **heredocs, char **heredocs_dq);

#endif
