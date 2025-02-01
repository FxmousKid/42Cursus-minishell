/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 04:07:10 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/31 18:46:47 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macros.h"
#include "minishell.h"

int	builtin_export(t_data *data, t_ast *node)
{
	int		equal_sign_pos;
	char	*pair;
	char	key[ENV_MAX];
	char	value[ENV_MAX];
	char	*expanded_value;

	pair = node->ast_cmd.cmd_args[1];
	ft_bzero(key, sizeof(key));
	ft_bzero(value, sizeof(value));
	equal_sign_pos = ft_strlen_till_char(pair, '=');
	pair[equal_sign_pos] = '\0';
	ft_strlcpy(key, pair, ft_strlen(pair) + 1);
	pair += equal_sign_pos + 1;
	ft_strlcpy(value, pair, ft_strlen(pair) + 1);
	expanded_value = expand_env_var_in_str(value, data);
	add_env_entry(data->env, key, expanded_value);
	free(expanded_value);
	return (true);
}
