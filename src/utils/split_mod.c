/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:42:38 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/17 23:44:17 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_mod(char *str, char *sep)
{
	printf("\n%ssplit_mod%s", GREEN_TXT, END_TXT);
	printf("(\"%s\", \" \\t\")\n", str);

	int		wordcount;
	char	**tab;

	wordcount = count_words_mod(str, sep);
	tab = ft_calloc(sizeof(char *), wordcount + 1);
	if (!tab)
		return (debug(DBG("Failed to calloc for split")), NULL);
	while (*str)
	{
		break;
	}
	return (NULL);
}
