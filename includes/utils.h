/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:35:33 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/22 00:59:44 by inazaria         ###   ########.fr       */
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


typedef struct s_ast t_ast;
void print_ast(t_ast *ast);

/* returns the number of contiguous non-null char * in tab, 
 * as long len <= size */
size_t	strptr_len(char **tab, size_t size);

/* free the non-null sub arrays and the passed array of arrays */
void	free_split(char **split);
/* only frees the non-null sub arrays */
void	free_sub_split_only(char **split);

// forward declaration
typedef struct s_data t_data;

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
char	*read_command(int exit_code);

// Signals

/* Restore the behavior of SIGINT and SIGQUIT in the Process that calls it */
void	restore_signals(void);
/* Sets up the signal handlers -- to launch in the beginning of main */
void	setup_signals(void);

#endif
