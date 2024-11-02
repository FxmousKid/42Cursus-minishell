/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_env_entries.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:19:39 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/02 15:36:09 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*access_env_value(t_env *env, char *key)
{
	int		idx;
	char	*tmp_key;

	idx = 0;
	while (idx < env->env_len)
	{
		tmp_key = env->env_pairs[idx].key;
		if (!strcmp_ex(tmp_key, key))
			return (env->env_pairs[idx].value);
		idx++;
	}
	return (NULL);
}

void	add_env_entry(t_env *env, char *key, char *value)
{
	int		idx;

	idx = 0;
	if (access_env_value(env, key) == NULL)
	{
		env->env_pairs[idx].key = ft_strdup(key);
		env->env_pairs[idx].value = ft_strdup(value);
		env->env_len++;
		return ;
	}
	while (env->env_pairs[idx].key)
	{
		if (!strcmp_ex(env->env_pairs[idx].key, key))
		{
			free(env->env_pairs[idx].value);
			env->env_pairs[idx].value = ft_strdup(value);
			return ;
		}
		idx++;
	}
}

void	remove_env_entry(t_env *env, char *key)
{
	int	idx;
	
	idx = 0;
	while (idx < env->env_len)
	{
		if (!strcmp_ex(env->env_pairs[idx].key, key))
		{
			free(env->env_pairs[idx].key);
			ft_bzero(&env->env_pairs[idx].key, sizeof(char *));
			free(env->env_pairs[idx].value);
			ft_bzero(&env->env_pairs[idx].value, sizeof(char *));
			env->env_len--;
			while (env->env_len - idx > 0)
			{
				env->env_pairs[idx] = env->env_pairs[idx + 1];
				idx++;
			}
		}
		idx++;
	}
}
