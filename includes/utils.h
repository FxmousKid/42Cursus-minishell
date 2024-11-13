/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:35:33 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/13 12:39:58 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "dependencies.h"

/* Utils functions */
bool	is_occ(char *str, char *sep);
bool	is_occ_aux(char c, char *sep);
void	print_split(char **split, char *name);
int		count_words_mod(char *str, char *sep);
int		strcmp_ex(const char *s1, const char *s2);
void	fill_quotes_states(char *str, bool *dq_sq);

// printing

/* prints the current working directory (with ~) in cyan */
void	print_formatted_cwd(void);
/* prints the multi line ca@sh logo */ 
void	print_start_text(void);
/* appends the passed char * with the ~ based cwd, assumes char * is at least
 * sizeof(PATH_MAX) */
bool	append_cwd_in_arr(char *cwd);



// Readline functions

/* Initializes some readline parameters, e.g. history, binds, etc...*/
void	init_readline();
/* prinpts the prompt, and returns the user input, uses readline() */
char	*read_command(void);

// Signals

/* Restore the behavior of SIGINT and SIGQUIT in the Process that calls it */
void	restore_signals(void);
/* Sets up the signal handlers -- to launch in the beginning of main */
void	setup_signals(void);

#endif
