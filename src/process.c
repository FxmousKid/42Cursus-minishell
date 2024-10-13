/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 22:38:55 by ptheo             #+#    #+#             */
/*   Updated: 2024/10/13 21:03:51 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_access(t_data *data, char *cmd)
{
	char	*path;
	char	*tmp;
	int		j;
	int		i;

	i = 0;
	while (data->env->key[i])
	{
		if (ft_strncmp(data->env->key[i], "PATH",
				ft_strlen(data->env->key[i])) == 0)
			break ;
		i++;
	}
	j = 0;
	while (data->env->value[i][j])
	{
		path = ft_strjoin(data->env->value[i][j], cmd);
		if (access(path, X_OK) == 0)
			return (tmp = cmd, cmd = path, free(tmp), 0);
		free(path);
		j++;
	}
	return (-1);
}

int	find_process(t_data *data, t_ast *pro)
{
	if (pro->token == CMD)
		return (cmd_process(data, pro));
	if (pro->token == PIPE)
		return (pipe_process(data, pro));
	if (pro->token == REDIR_IN)
		return (redirin_process(data, pro));
	if (pro->token == REDIR_OUT)
		return (redirout_process(data, pro));
	if (pro->token == REDIR_APPEND)
		return (redirin_append_process(data, pro));
	if (pro->token == HEREDOC)
		return (heredoc_process(data, pro));
	if (pro->token == EQUAL)
		return (equal_process(data, pro));
	if (pro->token == OR)
		return (or_process(data, pro));
	if (pro->token == AND)
		return (and_process(data, pro));
	return (0);
}
