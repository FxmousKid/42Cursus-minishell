/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:24:01 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/26 02:25:04 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macros.h"
#include "minishell.h"

void	custom_name_error(char *file, char *text)
{
	ft_err(SH_NAME);
	ft_err(": ");
	ft_err(RED_TXT);
	ft_err(file);
	ft_err(": ");
	ft_err(text);
	ft_err(END_TXT);
}

void	custom_name_perror(char *file)
{
	ft_err(SH_NAME);
	ft_err(": ");
	ft_err(RED_TXT);
	ft_err(file);
	ft_err(": ");
	perror("");
	ft_err(END_TXT);
}

void	exit_from_child(char *debug_text, t_data *data)
{
	free_data_w_env(data, NULL);
	if (debug_text)
		debug(DBG("Failed to execve()"));
	exit(data->exit_code);
}

void	close_e_data(t_exec_data *e_data)
{
	int	idx;
	
	if (e_data->pipefd[0] > 0 && close(e_data->pipefd[0]) < 0)
		debug(DBG("Failed to close pipefd[0]"));
	if (e_data->pipefd[1] > 0 && close(e_data->pipefd[1]) < 0)
		debug(DBG("Failed to close pipefd[1]"));
	idx = -1;
	while (e_data->old_read_fds[++idx])
	{
		if (e_data->old_read_fds[idx] > 0 && \
			close(e_data->old_read_fds[idx]) < 0)
			debug(DBG("Failed to close old_read_fds"));
	}
	if (e_data->fd_in > 0 && close(e_data->fd_in) < 0)
		debug(DBG("Failed to close fd_in"));
	if (e_data->fd_out > 0 && close(e_data->fd_out) < 0)
		debug(DBG("Failed to close fd_out"));
}

void	close_prev_command_fds(t_exec_data *e_data)
{
	if (e_data->fd_in > 0)
	{
		if (close(e_data->fd_in) < 0)
			debug(DBG("Failed to close fd_in"));
		e_data->fd_in = -1;
	}
	if (e_data->fd_out > 0)
	{
		if (close(e_data->fd_out) < 0)
			debug(DBG("Failed to close fd_out"));
		e_data->fd_out = -1;
	}
}
