/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:33:23 by aquincho          #+#    #+#             */
/*   Updated: 2023/01/11 13:55:40 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*res;
	int		i;

	if (!str)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

t_cmd	*ft_cmd_new(t_cmds *cmds)
{
	t_cmd	*cmd;
	int		i;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		ft_error_exit(cmds, error_fatal, NULL);
	cmd->arg = malloc(sizeof (char *) * (cmds->pos_end - cmds->pos_start + 1));
	if (!cmd->arg)
		ft_error_exit(cmds, error_fatal, NULL);
	i = 0;
	while (i < cmds->pos_end - cmds->pos_start)
	{
		cmd->arg[i] = ft_strdup(cmds->arg[i + cmds->pos_start]);
		i++;
	}
	cmd->arg[i] = NULL;
	if (cmds->arg[cmds->pos_end] && !strcmp(cmds->arg[cmds->pos_end], "|"))
		cmd->type = type_pipe;
	else if (cmds->arg[cmds->pos_end] && !strcmp(cmds->arg[cmds->pos_end], ";"))
		cmd->type = type_semi;
	else
		cmd->type = type_cmd;
	cmd->nb_args = cmds->pos_end - cmds->pos_start;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

void	ft_cmd_addback(t_cmd **cmd, t_cmd *new)
{
	if (!(*cmd))
	{
		(*cmd) = new;
		return ;
	}
	if (!(*cmd)->next)
	{
		(*cmd)->next = new;
		new->prev = (*cmd);
		return ;
	}
	else
		ft_cmd_addback(&(*cmd)->next, new);
}

#include <stdio.h>
void	ft_print_cmds(t_cmds *cmds)
{
	int	i;
	t_cmd	*tmp;

	if (!cmds)
	{
		printf("pas de cmds\n");
		return ;
	}
	if (!cmds->cmd)
	{
		printf("pas de cmd dans cmds\n");
		return ;
	}
	tmp = cmds->cmd;
	printf("Commandes\n");
	while (tmp)
	{
		printf("Commandes type %d nb %d\n", tmp->type, tmp->nb_args);
		i = 0;
		while (tmp->arg[i])
		{
			printf("   cmd: %s\n", tmp->arg[i]);
			i++;
		}
		tmp = tmp->next;
	}
}
