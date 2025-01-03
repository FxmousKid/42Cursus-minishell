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

/* AST Explanation
 *
 * Only node type is the one that represents a command or a file ;
 *	s_ast_cmd :
 *		- char *cmd_name: the name of the executable / builtin 
 *		'echo', 'cat', 'pwd'...
 *		- char **cmd_args: by convention all the args including the 
 *		name to pass to execve :
 *		{'cat', 'Makefile'}, {'pwd'}, ...
 *
 *	s_ast_file :
 *		-char *file_name: the string containing the file name
 *
 * 
 * */

struct s_ast
{
	t_token	token;
	t_ast	*parent_node;
	union
	{
		struct s_ast_cmd
		{
			char	*cmd_name;
			char	**cmd_args;
		}	ast_cmd;
		struct s_ast_file
		{
			char	*file_name;
		}	ast_file;
		struct s_ast_pipe
		{
			t_ast	*left;
			t_ast	*right;
		}	ast_pipe;
		struct s_ast_redir_in
		{
			t_ast	*left;
			t_ast	*right;
		}	ast_redir_in;
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

/* returns the number of tokens that match the passed token in
 * the lexems */
int		get_token_count(t_lexer lex, t_token token);

int		get_token_count_to_idx_n(t_lexer lex, int n, t_token tok);

/* returns the index of the 1st lexem that is a metachar (not HEREDOC, 
 * or HERESTRING) or is a CMD token
 * else returns -1 if none are found */
int		get_next_cmd_or_metachar_idx(t_lexem *lexems, int curr_idx);


/* returns the index of the first lexem of given token, or the next meta if 
 * given true as last param */
int		get_next_tok_idx(t_lexem *lexems, t_token token, int start, bool getmeta);



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

// AST

/* takes a function, and iterates on all children of given node */
void	iterate_ast(t_ast *ast, void (*f)(t_ast *ast));

/* start_idx is the idx of the CMD lexem, and counts all the arguments of 
 * that command, so all WORD, SQ_WORD, DQ_WORD of that command */
int		get_cmd_arg_count(t_lexem *lexems, int start_idx);

/* Takes a allocated t_ast and fill it's command node :
 * uses malloc to allocate char *cmd_name (null terminated)
 * uses malloc to allocate char **cmd_args (null terminated) 
 * takes t_data to access heredocs
 * return false if any allocation fails */
bool	fill_cmd_node(t_ast *ast_child, t_data *data, int cmd_idx);

/* mallocs the ast, fills it according to the t_data passed
 * and returns it's pointer 
 * return false if any allocation fails */
bool	init_and_fill_ast(t_data *data);

/* takes a pointer to the allocated left child, allocate the right child using malloc
 * for the correct struct based on the token tok, and makes the right child's 
 * parent_node the same as the left child's. and makes the parent_node's
 * left and right tree link to the left and right children 
 * P.S. the lchild will point to the right child if the token is :
 * PIPE, OR, AND. because we expect to fill a command node next.
 * return fals if any allocation fails*/
bool	fill_relation(t_ast **lchild, t_lexem *lexems, int idx, t_token tok);

/* returns the root of the given tree by climbing via parent_node
 * if already at root, returns itself */
t_ast	*get_root_node(t_ast *ast);

/* takes in a char * and returns a allocated char * using malloc
 * that expanded the environment variables inside the passed char *
 */
char	*expand_env_var_in_str(char *str, t_data *data);

/* if the given lexem has to be expanded then we expand the value of it
 * else we return a char * containing the original lexem value
 * both cases return a malloced char *
 * */
char	*extract_str_or_env_var(t_lexem lexem, t_data *data);


void	free_ast(t_ast *ast);

#endif
