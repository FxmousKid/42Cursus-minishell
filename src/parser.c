/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:36:25 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/27 21:59:24 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* the Goal here is to analyze syntax.
 * 1) Check for definitive syntaxically unfixable tokens : "echo |||"
 *	  cash : parse error near `META_CHARACTER' 
 * 2) Check for wrong but syntaxically fixable tokens, and prompt the
 *    user to finish them : echo |
 *    pipe> 
 * 3) Fill the AST for the execution
 * */
