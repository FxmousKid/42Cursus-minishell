/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:45:27 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/18 17:14:55 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_token
{
	CMD, // 'ls'
	F_NAME, // 'file.txt'
	WORD, // 'ABC'
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

typedef struct s_ast t_ast ;

typedef struct s_ast
{
	enum e_token token;
	union
	{
		struct ast_cmd {char *cmd; char **cmd_args; int in_fd; int out_fd;} ast_cmd;
		struct ast_file {char *filename;} ast_file;
		struct ast_pipe {t_ast *left; t_ast *right;} ast_pipe;
		struct ast_redir_in {t_ast *left; t_ast *right;} ast_redin_in;
		struct ast_redir_out {t_ast *left; t_ast *right;} ast_redir_out;
		struct ast_redir_append {t_ast *left; t_ast *right;} ast_redir_append;
		struct ast_heredoc {t_ast *left; t_ast *right;} ast_heredoc;
		struct ast_equal {t_ast *left; t_ast *right;} ast_equal;
		struct ast_dollar_sign {t_ast *left; t_ast *right;} ast_dollar_sign;
		struct ast_or {t_ast *left; t_ast *right;} ast_or;
		struct ast_and {t_ast *left; t_ast *right;} ast_and;
	};
}				t_ast;







#endif
