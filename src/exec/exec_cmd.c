/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:01:49 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/25 06:04:18 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "utils.h"

int	find_path(t_env *env_t, char *cmd, char *cmd_path_to_fill)
{
	char	*path;
	int		len_till_colon;

	if (access(cmd, X_OK) == 0)
		return (ft_strlcpy(cmd_path_to_fill, cmd, 4096), true);
	path = access_env_value(env_t, "PATH");
	if (!path)
		return (debug(DBG("Error : Path not found ")), 0);
	while (*path)
	{
		len_till_colon = ft_strlen_till_char(path, ':');// ft_strlen(path);
		if (ft_strchr(path, ':') == 0)
			len_till_colon = 0;
		path[len_till_colon] = 0;
		ft_strlcpy(cmd_path_to_fill, path, 4096);
		ft_strlcat(cmd_path_to_fill, "/", 4096);
		ft_strlcat(cmd_path_to_fill, cmd, 4096);
		if (access(cmd_path_to_fill, X_OK) == 0)
			return (1);
		if (!len_till_colon)
			break ;
		path += len_till_colon + 1;
	}
	return (debug(DBG("Full path not found")), 0);
}

int	handle_finding_path(t_data *data, char **args, char *cmd_path)
{
	if (!find_path(data->env, args[0], cmd_path))
	{
		debug(DBG("Failed to find_path()"));
		custom_name_error(args[0], CMD_NOT_FOUND);
		data->exit_code = EXIT_COMMAND_NOT_FOUND;
		return (false);
	}
	return (true);
}

void	exec_cmd(t_ast *cmd_node, t_data *data, t_exec_data *e_data)
{
	char	**comp_env;
	char	**args;
	
	comp_env = NULL;
	convert_custom_env_to_compliant_env(data->env, &comp_env);
	args = cmd_node->ast_cmd.cmd_args;
	if (!handle_finding_path(data, args, e_data->curr_cmd_path))
	{
		free_split(comp_env);
		exit_from_child("Failed to handle_finding_path()", data);
	}
	execve(e_data->curr_cmd_path, args, comp_env);
	free_split(comp_env);
	exit_from_child("Failed to execve()", data);
}
