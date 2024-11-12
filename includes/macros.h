/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:08:21 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/12 22:34:26 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# include "minishell.h"

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

# define SH_NAME "cash"
# define SH_NAME_FANCY GREEN_TXT"ca"END_TXT"@"GREEN_TXT"sh 💵 "END_TXT
# define PS1 SH_NAME_FANCY PURPLE_TXT"❯ "END_TXT

# define PS2 PURPLE_TXT"> "END_TXT
# define PS2_HDOC "heredoc"PS2
# define PS2_SQ "squote"PS2
# define PS2_DQ "dquote"PS2

# define PATH_MAX 4096
# define ENV_MAX 4096
# define CMD_MAX 256
# define ARG_MAX 4096

#endif
