/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:06:11 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/30 15:30:04 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function used to debug errors flow, will only trigger when building 
 * project with 'make debug'*/
#ifdef DEBUG

void	debug(char *str)
{
	printf("%s==%d== %s%s", RED_TXT, getpid(), str, END_TXT);
}

#else

void	debug(char *str)
{
	(void) str;
}
#endif
