/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquincho <aquincho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:14:52 by aquincho          #+#    #+#             */
/*   Updated: 2023/01/11 13:56:39 by aquincho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef enum e_error
{
	error_fatal,
	error_cmd,
	error_cd,
	error_cd_nbargs
}	t_error;

typedef enum e_type
{
	type_cmd,
	type_pipe,
	type_semi
}	t_type;

typedef struct s_cmd	t_cmd;

struct s_cmd
{
	char	**arg;
	t_type	type;
	int		nb_args;
	int		pipe_fd[2];
	int		pipe_open;
	t_cmd	*next;
	t_cmd	*prev;
};

typedef struct s_cmds
{
	char	**arg;
	char	**env;
	t_cmd	*cmd;
	int		pos_end;
	int		pos_start;
}	t_cmds;

/* utils.c */
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
t_cmd	*ft_cmd_new(t_cmds *cmds);
void	ft_cmd_addback(t_cmd **cmd, t_cmd *new);
/* free.c */
void	ft_free_cmds(t_cmds *cmds);
void	ft_free_cmd(t_cmd *cmd);
void	ft_free_arg(char **arg);
/* error.c */
void	ft_error_exit(t_cmds *cmds, t_error err_type, char *arg);

void	ft_print_cmds(t_cmds *cmds);

#endif