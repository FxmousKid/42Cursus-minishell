/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:03:29 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/13 12:51:35 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macros.h"
#include "minishell.h"
#include <linux/limits.h>

void	init_readline()
{
 	// rl_bind_key('\t', rl_insert);
	rl_bind_key('!', rl_insert);
	using_history();
}

/* copy the PS1 prompt in the passed array, assumes the passed char *
 * is at least of sizeof(PATH_MAX) */

static void	copy_ps_one_in_array(char *arr)
{
	ft_strlcat(arr, "\n", PATH_MAX);
	ft_strlcat(arr, BLUE_TXT, PATH_MAX);
	if (!append_cwd_in_arr(arr))
	{
		ft_strlcpy(arr, RED_TXT, PATH_MAX);
		ft_strlcat(arr, "X", PATH_MAX);
	}
	ft_strlcat(arr, END_TXT, PATH_MAX);
	ft_strlcat(arr, "\n", PATH_MAX);
	ft_strlcat(arr, PS1, PATH_MAX);
}

/* prompts the user for the command, uses readline for entire prompt
 * displaying, return the readline allocated char * */

char	*read_command(void)
{
	char	prompt[PROMPT_MAX];

	ft_bzero(prompt, sizeof(char) * PROMPT_MAX);
	copy_ps_one_in_array(prompt);
	return (readline(prompt));
}
