/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:44:10 by aquincho          #+#    #+#             */
/*   Updated: 2023/01/11 13:55:33 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void	ft_free_arg(char **arg)
{
	int	i;

	if (!arg)
		return ;
	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free (arg);
}

void	ft_free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	ft_free_arg(cmd->arg);
	close(cmd->pipe_fd[0]);
	close(cmd->pipe_fd[1]);
	ft_free_cmd(cmd->next);
	free(cmd);
}

void	ft_free_cmds(t_cmds *cmds)
{
	if (!cmds)
		return ;
	ft_free_cmd(cmds->cmd);
	free(cmds);
}