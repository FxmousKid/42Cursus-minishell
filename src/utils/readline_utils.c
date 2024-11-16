/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:03:29 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/16 02:46:12 by inazaria         ###   ########.fr       */
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

static inline void add_exit_code_to_prompt(char *arr, int code)
{
	*arr = ' ';
	arr++;
	if (code < 10)
	{
		*arr = '0' + code;
		return ;
	}
	if (code < 100)
	{
		*arr++ = code / 10;
		*arr = code % 10;
		return ;
	}
	if (code <= 127)
	{
		*arr++ = 1;
		code -= 100;
		*arr++ = code / 10;
		*arr = code % 10;
	}
}

static void	copy_ps_one_in_array(char *arr, t_data *data)
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
	if (data && data->exit_code)
		add_exit_code_to_prompt(arr + ft_strlen(arr), data->exit_code);
	if (data)
		printf("\nexit code = %d\n", data->exit_code);
}

/* prompts the user for the command, uses readline for entire prompt
 * displaying, return the readline allocated char * .
 * Takes the t_data main DS for non-zero exit code display */

char	*read_command(t_data *data)
{
	char	prompt_arr[PROMPT_MAX];

	ft_bzero(prompt_arr, sizeof(char) * PROMPT_MAX);
	copy_ps_one_in_array(prompt_arr, data);
	return (readline(prompt_arr));
}
