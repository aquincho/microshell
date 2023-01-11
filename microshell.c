/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:15:51 by aquincho          #+#    #+#             */
/*   Updated: 2023/01/11 13:51:53 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

static t_cmds	*ft_init_cmds(char **argv, char **envp)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		ft_error_exit(NULL, error_fatal, NULL);
	cmds->arg = argv;
	cmds->env = envp;
	cmds->cmd = NULL;
	cmds->pos_start = 1;
	cmds->pos_end = 1;
	return (cmds);
}

void	ft_process_cmd(t_cmds *cmds)
{
	t_cmd	*cmd;

	cmd = ft_cmd_new(cmds);
	ft_cmd_addback(&(cmds->cmd), cmd);
}
#include <stdio.h>
static int	ft_cd(t_cmd *cmd, t_cmds *cmds)
{
	if (cmd->nb_args != 2)
		ft_error_exit(cmds, error_cd_nbargs, NULL);
	else if (chdir(cmd->arg[1]) < 0)
		ft_error_exit(cmds, error_cd, cmd->arg[1]);
	return (0);
}

static int	ft_execute_cmd(t_cmd *cmd, t_cmds *cmds)
{
	pid_t	pid;

	if ((cmd->type == type_pipe || (cmd->prev && cmd->prev->type == type_pipe))
		&& pipe(cmd->pipe_fd) < 0)
		ft_error_exit(cmds, error_fatal, NULL);
	pid = fork();
	if (pid < 0)
		ft_error_exit(cmds, error_fatal, NULL);
	else if (pid == 0)
	{
		if (cmd->type == type_pipe)
		{
			close(cmd->pipe_fd[0]);
			dup2(cmd->pipe_fd[1], 1);
		}
		if (cmd->prev && cmd->prev->type == type_pipe)
			dup2(0, cmd->prev->pipe_fd[0]);
		if (execve(cmd->arg[0], cmd->arg, cmds->env) < 0)
			ft_error_exit(cmds, error_cmd, cmd->arg[0]);
	}
	else
	{
		waitpid(pid, NULL, 0);
		if (cmd->type == type_pipe)
		{
			close(cmd->pipe_fd[1]);
			dup2(cmd->pipe_fd[0], 0);
		}
	}
	return (0);
}

int	ft_execute_cmds(t_cmds *cmds)
{
	t_cmd	*tmp;

	tmp = cmds->cmd;
	while (tmp)
	{
		if (!strcmp(tmp->arg[0], "cd"))
			ft_cd(tmp, cmds);
		else
			ft_execute_cmd(tmp, cmds);
		tmp = tmp->next;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	t_cmds	*cmds;

	if (argc < 2)
		return (0);
	cmds = ft_init_cmds(argv, envp);
	i = 1;
	while (argv[i])
	{
		if (!argv[i + 1] || !strcmp(argv[i + 1], "|") || !strcmp(argv[ i + 1], ";"))
		{
			cmds->pos_end = i + 1;
			ft_process_cmd(cmds);
			if (argv[i + 1])
				i++;
			while (argv[i + 1] && !strcmp(argv[i + 1], ";"))
				i++;
			cmds->pos_start = i + 1;
		}
		i++;
	}
	//ft_print_cmds(cmds);
	//ft_print_cmds(cmds);
	ft_execute_cmds(cmds);
	ft_free_cmds(cmds);
}