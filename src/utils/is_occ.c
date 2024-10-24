/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_occ.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 08:58:10 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/23 19:54:15 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

/* gives true to strings like : "abc", "awd" and false for : "a", "aaa" */

/*
static inline bool	is_len2(char *str)
{
	return (*(str + 1) && !*(str + 2));
}


static inline bool	is_len(int len, char *str)
{
	if (len == 2)
		return (*(str + 1) && !*(str + 2));
	else if (len == 3)
		return (*(str + 1) && *(str + 2) && !*(str + 3));
	return (-1);
}

int	len_curr_meta_char(char *str)
{
	if (is_len(2, str) && !ft_strncmp(str, "&&", 2))
		return (2);
	if (is_len2(2, str) && !ft_strncmp(str, "||", 2))
		return (2);
	if (is_len3(str) && !ft_strncmp(str, ">>", 2))
		return (2);
	if (is_len3(str) && !ft_strncmp(str, "<<", 2))
}
*/

bool	is_occ_aux(char c, char *sep)
{
	while (*sep)
	{
		if (*sep == c)
			return (true);
		sep++;
	}
	return (false);
}

bool	is_occ(char *str, char *sep)
{
	while (*str)
	{
		if (is_occ_aux(*str, sep))
			return (true);
		str++;
	}
	return (false);
}
