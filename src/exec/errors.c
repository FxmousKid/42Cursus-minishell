/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:24:01 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/24 18:56:00 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macros.h"
#include "minishell.h"

void	ft_error(char *text)
{
	write(2, text, ft_strlen(text));
}

void	custom_name_error(char *file, char *text)
{
	ft_error(SH_NAME);
	ft_error(": ");
	ft_error(RED_TXT);
	ft_error(file);
	ft_error(": ");
	ft_error(text);
	ft_error(END_TXT);
}

void	custom_name_perror(char *file)
{
	ft_error(SH_NAME);
	ft_error(": ");
	ft_error(RED_TXT);
	ft_error(file);
	ft_error(": ");
	perror("");
	ft_error(END_TXT);
}

void	exit_from_child(char *debug_text, t_data *data)
{
	free_data_w_env(data, NULL);
	if (debug_text)
		debug(DBG("Failed to execve()"));
	exit(data->exit_code);
}
