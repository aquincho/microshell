/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:38:09 by aquincho          #+#    #+#             */
/*   Updated: 2023/01/11 11:28:24 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

static char	*ft_error_msg(t_error err_type)
{
	char	*msg;

	if (err_type == error_fatal)
		msg = "fatal";
	else if (err_type == error_cmd)
		msg = "cannot execute ";
	else if (err_type == error_cd)
		msg = "cd: cannot change to ";
	else if (err_type == error_cd_nbargs)
		msg = "bad argumets";
	else
		msg = "quit";
	return (msg);
}

void	ft_error_exit(t_cmds *cmds, t_error err_type, char *arg)
{
	char	*msg;

	msg = ft_error_msg(err_type);
	write (2, "error: ", 7);
	write (2, msg, ft_strlen(msg));
	if (arg && (err_type == error_cmd || err_type == error_cd))
		write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
	ft_free_cmds(cmds);
	exit (1);
}