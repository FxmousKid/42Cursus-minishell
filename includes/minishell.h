/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:35:10 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/02 23:50:13 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "dependencies.h"
# include "error_manager.h"
# include "lexer.h"

# define RED_TXT		"\e[0;31m"
# define GREEN_TXT		"\e[0;32m"
# define YELLOW_TXT		"\e[0;33m"
# define BLUE_TXT		"\e[0;34m"
# define PURPLE_TXT		"\e[0;35m"
# define CYAN_TXT		"\e[0;36m"
# define GREY_TXT		"\e[0;37m"
# define WHITE_TXT		"\e[0;39m"
# define BOLD_TXT		"\e[1m"
# define UNDERLINE_TXT	"\e[4m"
# define REVERSE_TXT	"\e[7m"
# define HIDDEN_TXT		"\e[8m"
# define END_TXT		"\e[0m"



# define PROMPT "\e[0;35m❯\e[0m "
# define SH_NAME "cash"
# define MAX_PATH 4096
# define MAX_CMD 256
# define MAX_ARG 4096
# define MAX_TOKEN 4096

typedef struct s_env_pair
{
	char	key[4096];
	char	*value;
}			t_env_pair;


#endif
