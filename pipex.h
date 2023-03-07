/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthomas <rthomas@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 23:03:54 by cclaude           #+#    #+#             */
/*   Updated: 2022/06/01 15:20:42 by rthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_pipe {
	int				i;
	int				j;

	int				ac;
	char			**av;
	char			**env;
	char			*path;
	char			**env2;
	char			*path2;
	int				fd_pipe[2];
	int				fd1;
	int				fd2;
	char			**args;
}				t_pipe;

void	pipex_error(void);
void	ft_free_tab(char **tab);
void	ft_stop(char *s);
int		ft_error_read(char *av);
int		ft_fd_0(t_pipe *pipex);
int		ft_fd_error(t_pipe *pipex, char **av);

#endif
