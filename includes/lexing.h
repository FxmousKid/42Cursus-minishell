/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:45:27 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/01 00:51:41 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "minishell.h"

typedef enum e_token_type
{
	CMD, // 'ls'
	WORD, // 'ABC'
	PIPE, // '|'
	SEMICOLON, // ';'
	REDIR_IN, // '<'
	REDIR_OUT, // '>'
	REDIR_APPEND, // '>>'
	HEREDOC, // '<<'
	EQUAL, // '='
	SINGLE_QUOTE, // '
	DOUBLE_QUOTE, // "
	DOLLAR_SIGN, // '$'
}	t_token_type;

#endif
