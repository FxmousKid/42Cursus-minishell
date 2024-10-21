/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 22:38:55 by ptheo             #+#    #+#             */
/*   Updated: 2024/10/21 17:23:52 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_access(t_data *data, char *cmd)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (data->path_arg[i])
	{
		path = ft_strjoin(data->path_arg[i], cmd);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		path = NULL;
		i++;
	}
	return (NULL);
}

int	create_path(t_data *data)
{
	int		i;

	i = 0;
	while (data->env->key[i])
	{
		if (ft_strncmp(data->env->key[i], "PATH",
				ft_strlen(data->env->key[i])) == 0)
			break ;
		i++;
	}
	data->path_arg = ft_split(data->env->value[i], ':');
	i = 0;
	while (data->path_arg[i])
	{
		data->path_arg[i] = ft_strjoin(data->path_arg[i], "/");
		i++;
	}
	return (0);
}

int	find_process(t_data *data, t_ast *pro)
{
	if (pro->token == CMD)
		return (cmd_process(data, pro));
	if (pro->token == PIPE)
		return (pipe_process(data, pro));
/*	if (pro->token == REDIR_IN)
		return (redirin_process(data, pro));
	if (pro->token == REDIR_OUT)
		return (redirout_process(data, pro));
	if (pro->token == REDIR_APPEND)
		return (redirin_append_process(data, pro));
	if (pro->token == HEREDOC)
		return (heredoc_process(data, pro));
	if (pro->token == EQUAL)
		return (equal_process(data, pro));*/
	if (pro->token == OR)
		return (or_process(data, pro));
	if (pro->token == AND)
		return (and_process(data, pro));
	return (-1);
}
