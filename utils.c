/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthomas <rthomas@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 23:09:20 by cclaude           #+#    #+#             */
/*   Updated: 2022/06/01 15:20:21 by rthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/////////////////////////////////////////////////////
int	ft_fd_error(t_pipe *pipex, char **av)
{
	if (pipex->fd1 < 0)
	{
		ft_error_read(av[1]);
		return (0);
	}
	if (pipex->fd2 < 0)
	{
		ft_error_read(av[4]);
		return (0);
	}
	return (0);
}

int	ft_fd_0(t_pipe *pipex)
{
	dup2(pipex->fd2, STDOUT);
	write(1, "0", 1);
	return (0);
}

void	ft_free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_error_read(char *av)
{
	ft_putstr_fd("pipex: permission denied: ", 2);
	ft_putstr_fd(av, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}
