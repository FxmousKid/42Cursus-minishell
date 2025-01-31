/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:53:59 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/31 18:54:59 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "dependencies.h"
# include "macros.h"
# include "lexer.h" 

/* Error as the 1st token is important because it will be the default one 
 * on initialization */

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
 *	int done : used by the execution process for bookkeeping
 *		- if 0, we haen't come across this node yet
 *		- if 1, we have executed this node once
 *		- if 2, we are finished with this node
 * 
 * */

struct s_ast
{
	t_token	token;
	t_ast	*parent_node;
	t_ast	*left;
	t_ast	*right;
	int		status;
	union
	{
		struct s_ast_cmd
		{
			char	*cmd_name;
			char	**cmd_args;
			bool	is_hdoc;
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

// Parser
bool	parser(t_data *data, t_lexer *lex);
bool	search_parse_error(t_lexer *lex);
bool	prompt_for_partial_sq_dq(t_lexer *lex);
bool	prompt_for_partial_pipe(t_lexer *lex);
bool	prompt_for_heredocs(t_lexer *lex, char **heredocs, char **heredocs_dq);

// AST

/* takes a function, and iterates on all children of given node */
void	iterate_ast(t_ast *ast, void (*f)(t_ast *ast));

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

/* takes a pointer to the allocated left child, allocate the right child using
 * malloc for the correct struct based on the token tok, and makes the right 
 * child's parent_node the same as the left child's. and makes the parent_node's
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

void	set_child_easy_access(t_ast *node);

void	free_ast(t_ast *ast);

/* takes a node X, frees its right child, its left child becomes the 
 * left child of X's parent and all the linking is arranged. 
 * Frees X at the end, and makes the passed node point to X's parent 
 * */
void	cut_tree_one_level_and_free(t_ast **node);

/* returns true if the current node needs to be removed and trimed */
bool	need_to_cut_tree(t_ast *node);

/* returns true if we need to close previously opened files after we cut
 * the current level */
bool	need_to_close_after_cut(t_ast *node);

#endif
