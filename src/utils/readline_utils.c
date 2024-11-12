/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:03:29 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/13 00:08:53 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_readline()
{
 	// rl_bind_key('\t', rl_insert);
	rl_bind_key('!', rl_insert);
	using_history();
}

char	*read_command(void)
{
	printf("\n");
	print_formatted_cwd();
	return (readline(PS1));
}
