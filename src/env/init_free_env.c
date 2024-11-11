/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:45:09 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/10 22:31:17 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*join_value_strings(char **env_line)
{
	char	values[ARG_MAX];

	ft_bzero(values, sizeof(char) * ARG_MAX);
	while (*++env_line)
		ft_strlcat(values, *env_line, ARG_MAX);	
	return (ft_strdup(values));
}

// *++env_line to ignore 1st elem (the key)

bool	init_env(t_env *data_env, char *env[])
{
	char	**env_pair;
	size_t	i;
	size_t	idx_free;

	i = 0;
	while (env[i])
	{
		env_pair = ft_split(env[i], '=');
		data_env->env_pairs[i].key = ft_strdup(env_pair[0]);
		data_env->env_pairs[i].value = join_value_strings(env_pair);
		idx_free = 0;
		while (env_pair[idx_free])
			free(env_pair[idx_free++]);
		free(env_pair);
		i++;
	}
	data_env->env_len = i;
	return (true);
}

// char	*remove_env_pair(t_env env, )

void	free_env(t_env *env)
{
	int	idx;

	idx = 0;
	while (idx < env->env_len)
	{
		free(env->env_pairs[idx].key);
		free(env->env_pairs[idx].value);
		idx++;
	}
	free(env);
}
