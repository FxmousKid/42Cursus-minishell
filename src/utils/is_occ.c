/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_occ.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 08:58:10 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/16 11:07:38 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_occ_aux(char c, char *sep)
{
	while (*sep)
	{
		if (*sep == c)
			return true;
		sep++;
	}
	return false;
}

bool	is_occ(char *str, char *sep)
{
	while (*str)
	{
		if (is_occ_aux(*str, sep))
			return true;
		str++;
	}
	return false;
}
