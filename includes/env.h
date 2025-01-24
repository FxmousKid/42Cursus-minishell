/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:04:27 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/24 15:33:52 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "dependencies.h"
# include "macros.h"

typedef struct s_env_pair
{
	char	*key;
	char	*value;
}			t_env_pair;

typedef struct s_env
{
	t_env_pair	env_pairs[ENV_MAX];
	int			env_len;
	char		*paths[128];
}				t_env;

/* fills up out custom made structure with the system provided env */
bool	init_env(t_env *data_env, char *env[]);

/* Free the key and value of each env entry in the passed t_env and frees
 * the t_env allocated structure too */
void	free_env(t_env *env);

/* Returns the ptr to the value of the key if found, else returns NULL */
char	*access_env_value(t_env *env, char *key);

/* if key already is a env entry key, then overwrites existing value with 
 * passed value, leaves total entry count the same
 * else append a new env entry, allocated for key and value with MALLOC, and
 * increments the total entry counts by 1 */
void	add_env_entry(t_env *env, char *key, char *value);

/* Takes a key, and removes that entry, and shift everything on the right
 * of that entry 1 place to the left, to remain contiguous.
 * Does nothing if key isn't found / valid */
void	remove_env_entry(t_env *env, char *key);

/*  */
char	**convert_custom_env_to_compliant_env(t_env *env, char ***env_p);

/* Pretty prints the current state of the passed t_env structure */
void	print_env(t_env env);

#endif

