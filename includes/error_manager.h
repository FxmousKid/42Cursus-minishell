/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:39:46 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/20 15:56:21 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MANAGER_H
# define ERROR_MANAGER_H

# define STRINGIFY(x) #x
# define TOSTRING(x) STRINGIFY(x)

// Debug Helping
# define DBG(reason) reason " at line " \
TOSTRING(__LINE__) " in file " __FILE__ "\n"

// Error Handling
void		ft_err(char *str);

// Debugging
void		debug(char *str);

#endif
