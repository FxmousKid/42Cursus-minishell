/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:04:03 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/29 15:38:08 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <math.h>
#include <stdbool.h>

/* takes the first letter of a env var and returns all
 * consecutive alpha numerical caracters in a malloced 
 * char *
 * */

char	*get_env_key_name(char *str)
{
	char	key[4096];
	int		idx;

	ft_bzero(key, sizeof(char) * 4096);
	idx = 0;
	while (str[idx])
	{
		if (ft_isalnum(str[idx]))
			key[idx] = str[idx];
		else
			break ;
		idx++;
	}
	return (ft_strdup(key));
}

void	handle_special_dollar(char *new_str, char *str, t_data *data, int *idx)
{	
	int		pid;
	char	*tmp;

	if (str[0] == '$')
	{
		pid = getpid();
		tmp = ft_itoa(pid);
		ft_strlcat(new_str, tmp, 4096);
		free(tmp);
		*idx += 1;
	}
	else if (str[0] == '?')
	{
		tmp = ft_itoa(data->prev_exit_code);
		ft_strlcat(new_str, tmp, 4096);
		free(tmp);
		*idx += 1;
	}
}

void	handle_dollar_sign(char *new_str, char *str, t_data *data, int *idx)
{
	char	*tmp;

	handle_special_dollar(new_str, str, data, idx);
	tmp = get_env_key_name(str);
	if (!access_env_value(data->env, tmp))
		ft_strlcat(new_str, "", 4096);
	else
		ft_strlcat(new_str, access_env_value(data->env, tmp), 4096);
	*idx += ft_strlen(tmp);
	free(tmp);
}

/* takes a char * and allocates a new char * using malloc that
 * will store the expanded env vars (if any are present in) 
 * with the rest of the provided char * 
 * */

char	*expand_env_var_in_str(char *str, t_data *data)
{
	char	new_str[4096];
	bool	in_squotes;
	int		idx;

	ft_bzero(new_str, sizeof(char) * 4096);
	in_squotes = str[0] == '\'';
	idx = -1;
	while (str[++idx])
	{
		if (str[idx] == '$' && !in_squotes)
			handle_dollar_sign(new_str, str + idx + 1, data, &idx);
		else
		{
			if (idx == 0 && (str[idx] == '"' || str[idx] == '\''))
				continue;
			if ((size_t) idx == ft_strlen(str) - 1 && \
				(str[idx] == '"' || str[idx] == '\''))
				continue;
			new_str[ft_strlen(new_str)] = str[idx];
		}
		if (!str[idx])
			break;
	}	
	return ft_strdup(new_str);
}

/* if the given lexem has to be expanded then we expand the value of it
 * else we return a char * containing the original lexem value
 * both cases return a malloced char *
 * the order of the conditions is important, because we want to
 * expand the env vars in the DQ_WORD and CMD lexems
 * */

char	*extract_str_or_env_var(t_lexem lexem, t_data *data)
{
	if (lexem.token == DQ_WORD \
		|| lexem.token == ENV_VAR \
		|| lexem.token == WORD \
		|| lexem.token == SQ_WORD \
		|| (lexem.token == CMD && lexem.value[0] == '"'))
		return (expand_env_var_in_str(lexem.value, data));
	if (lexem.token == CMD)
		return (ft_strdup(lexem.value));
	return (NULL);

}
