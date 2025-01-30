/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:05:05 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/29 14:33:18 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "utils.h"

int	handle_cd_aux(t_data *data, t_ast *node)
{
	int		ret;

	ret = 1;
	if (node->ast_cmd.cmd_args[1] && node->ast_cmd.cmd_args[2])
	{
		custom_name_error("cd", TOO_MANY_ARGS);
		data->exit_code = 1;
		return (-1);
	}
	if (!node->ast_cmd.cmd_args[1] || \
		!strcmp_ex(node->ast_cmd.cmd_args[0], "~"))
	{
		ret = 0;
		if (chdir(access_env_value(data->env, "HOME")))
			return (custom_name_perror(access_env_value(data->env, "HOME")), \
		data->exit_code = 1, -1);
	}
	add_env_entry(data->env, "-", access_env_value(data->env, "PWD"));
	return (ret);
}

int	builtin_cd(t_data *data, t_ast *node)
{
	char	*target_path;
	
	if (handle_cd_aux(data, node) != 1)
		return (true);
	target_path = node->ast_cmd.cmd_args[1];
	if (!strcmp_ex(target_path, "-"))
	{
		printf("%s\n", access_env_value(data->env, "-"));
		if (chdir(access_env_value(data->env, "-")))
			return (custom_name_perror(access_env_value(data->env, "-")), \
			false);
	}
	else if (chdir(target_path))
	{
		custom_name_perror(target_path);
		return (false);
	}
	add_env_entry(data->env, "-", access_env_value(data->env, "PWD"));
	return (true);
}
