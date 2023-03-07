/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthomas <rthomas@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 14:07:57 by rthomas           #+#    #+#             */
/*   Updated: 2022/06/01 15:26:17 by rthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	openfile(char *filename, int mode)
{
	if (mode == 0)
	{
		if (access(filename, F_OK))
		{
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd("no such file or directory: ", 2);
			ft_putstr_fd(filename, 2);
			ft_putstr_fd("\n", 2);
			return (0);
		}
		return (open(filename, O_RDONLY));
	}
	else
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644));
}

char	*find_path(char *cmd, char **env, t_pipe *pipex)
{
	while (env[++(pipex)->i])
	{
		if (!ft_strncmp(env[(pipex)->i], "PATH=", 5))
		{
			pipex->path = env[(pipex)->i];
			pipex->env2 = ft_split(pipex->path + 5, ':');
			cmd = ft_strjoin("/", cmd);
			(pipex)->j = -1;
			while (pipex->env2 && pipex->env2[++(pipex)->j])
			{
				pipex->path = ft_strjoin(pipex->env2[(pipex)->j], cmd);
				if (access(pipex->path, F_OK) == 0)
				{
					(pipex)->j = -1;
					ft_free_tab(pipex->env2);
					free(cmd);
					return (pipex->path);
				}
				free(pipex->path);
			}
			ft_free_tab(pipex->env2);
			return (NULL);
		}
	}
	return (NULL);
}

int	exec(char *cmd, char **env, t_pipe *pipex)
{
	pipex->args = ft_split(cmd, ' ');
	if (ft_strchr(pipex->args[0], '/'))
			pipex->path = pipex->args[0];
	else
			pipex->path = find_path(pipex->args[0], env, pipex);
	if (!pipex->path)
	{
		ft_putstr_fd("pipex : command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	if (execve(pipex->path, pipex->args, env) == -1)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putstr_fd(pipex->path, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	free(pipex->path);
	free(pipex->args);
	return (1);
}

int	pipe_func(char **av, char **env, t_pipe *pipex)
{
	pid_t	pid;

	pipe(pipex->fd_pipe);
	pid = fork();
	if (pid)
	{
		close(pipex->fd_pipe[1]);
		dup2(pipex->fd_pipe[0], STDIN);
		dup2(pipex->fd2, STDOUT);
		waitpid(pid, NULL, 0);
		if (!exec(av[3], env, pipex))
			return (0);
		close(pipex->fd_pipe[0]);
	}
	else
	{
		close(pipex->fd_pipe[0]);
		dup2(pipex->fd1, STDIN);
		dup2(pipex->fd_pipe[1], STDOUT);
		close(pipex->fd_pipe[1]);
		if (!exec(av[2], env, pipex))
			return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_pipe	pipex;

	if (ac != 5)
	{
		ft_putstr_fd("Invalid number of arguments.\n", 2);
		return (0);
	}
	else
	{
		pipex.fd1 = openfile(av[1], 0);
		pipex.fd2 = openfile(av[4], 1);
		if (pipex.fd1 < 0 || pipex.fd2 < 0)
			return (ft_fd_error(&pipex, av));
		if (pipex.fd1 == 0 || pipex.fd2 == 0)
			return (ft_fd_0(&pipex));
		if (!pipe_func(av, env, &pipex))
			return (0);
	}
	return (0);
}
