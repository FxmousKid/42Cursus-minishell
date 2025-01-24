/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:35:10 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/27 16:09:29 by inazaria         ###   ########.fr       */
/*   Updated: 2024/10/24 14:46:36 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "dependencies.h"
# include "analysis.h"
# include "error_manager.h"
# include "macros.h"
# include "env.h"
# include "utils.h"
# include "exec.h"
#include <fcntl.h>

typedef struct s_data
{
	t_env		*env;
	t_lexer		lex;
	t_ast		*ast;
	pid_t		pids[MAX_PIDS];
	int			cmd_idx;
	int			cmd_count;
	char		*heredocs[MAX_HEREDOCS];
	char		*heredocs_dq[MAX_HEREDOCS];
	int			exit_code;
}				t_data;


// Free functions

/* Free allocated contents of stack-allocated data. Takes also the
 * string malloced by readline to free it, if you dont want that, just 
 * pass NULL as readline_input*/
void	free_data(t_data *data, char *readline_input);

/* frees the allocate env too */
void	free_data_w_env(t_data *data, char *readline_input);

/* bzero's the content of the passed *t_data */
void	init_t_data(t_data *data);

/* Frees the content of the passed stack-allocated *data, and 
 * bzero's it to use it again, since it's stack-allocated 
 * Takes also the string malloced by readline to free it, if you 
 * dont want that, just pass NULL as readline_input */
void	free_and_init_data(t_data *data, char *readline_input);

/* free all the allocated char * pointers to store the heredocs */
void	free_env_heredocs(t_data *data);



#endif
