/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:29:38 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/30 16:08:15 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "dependencies.h"
# include "macros.h"

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

typedef struct s_data t_data;

// Lex Utils
int		is_meta_char(char *str);
bool	split_cl(t_lexer *lex);
void	free_lex(t_lexer *lex);
void	fill_lexem(t_lexem *lexem, char *str, t_token token, bool meta);
void	print_lexems(t_lexer *lex, t_data *data);
/* Check the passed lexer structure has a certain token
 * takes the lexems array to enable offset checks */
bool	has_token(t_lexem *lexems, t_token token);
/* checks if the lexems contain n lexems whose token are the same
 * as the passed token argument */
bool	has_n_token(t_lexer *lex, t_token token, size_t n);

/* returns the number of tokens that match the passed token in
 * the lexems */
int		get_token_count(t_lexer lex, t_token token);

int		get_token_count_to_idx_n(t_lexer lex, int n, t_token tok);

/* return if tok in (REDIR_IN, REDIR_OUT, REDIR_APPEND) */
bool	is_tok_redir_type(t_token tok);

/* return if tok in (PIPE, AND, OR) */
bool	is_tok_dual_cmd_type(t_token tok);

/* returns if tok in (REDIR_OUT, REDIR_APPEND) */
bool	is_tok_redir_out_type(t_token tok);

/* returns the index of the 1st lexem that is a metachar (not HEREDOC, 
 * or HERESTRING) or is a CMD token
 * else returns -1 if none are found */
int		get_next_cmd_or_metachar_idx(t_lexem *lexems, int curr_idx);

/* returns the index of the first lexem of given token, or the next meta if 
 * given true as last param */
int		get_next_tok_idx(t_lexem *lexems, t_token token, int start, bool getmeta);

/* if the given lexem has to be expanded then we expand the value of it
 * else we return a char * containing the original lexem value
 * both cases return a malloced char *
 * */
char	*extract_str_or_env_var(t_lexem lexem, t_data *data);

/* swap all field values of both lexems at index i and j */
void	swap_lexems(t_lexer *lex, size_t i, size_t j);

/* offsets all the lexems on the i-th index, leaving the i-th lexems blank */
void	offset_lexems_right(t_lexer *lex, size_t i);

/* start_idx is the idx of the CMD lexem, and counts all the arguments of 
 * that command, so all WORD, SQ_WORD, DQ_WORD of that command */
int		get_cmd_arg_count(t_lexem *lexems, int start_idx);


// Lexer
bool	lex_if_meta_chars(t_lexem *lexem, char *str);
bool	lexer(t_lexer *lex, char *input);

#endif
