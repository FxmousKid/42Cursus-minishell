/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:14:24 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/31 18:35:52 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_custom_env_to_compliant_env(t_env *env, char ***env_p)
{
	char	pair[4096];
	char	**comp_env;
	int		idx;

	*env_p = ft_calloc(sizeof(char *), env->env_len + 1);
	if (!*env_p)
		return (debug(DBG("Failed to ft_calloc()")), NULL);
	idx = -1;
	comp_env = *env_p;
	while (++idx < env->env_len)
	{
		ft_bzero(pair, 4096);
		ft_strlcat(pair, env->env_pairs[idx].key, 4096);
		ft_strlcat(pair, "=", 4096);
		ft_strlcat(pair, env->env_pairs[idx].value, 4096);
		comp_env[idx] = ft_strdup(pair);
	}
	comp_env[idx] = NULL;
	return (comp_env);
}
