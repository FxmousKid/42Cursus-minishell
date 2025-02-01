/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strptr_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:14:58 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/17 17:16:15 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

size_t	strptr_len(char **tab, size_t size)
{
	size_t	len;

	len = 0;
	while (tab[len] && len < size)
		len++;
	return (len);
}
