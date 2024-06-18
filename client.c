/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkimijim <fkimijim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:22:48 by fkimijim          #+#    #+#             */
/*   Updated: 2024/06/05 13:26:31 by fkimijim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>

int	find_invalid_pid(char *server_pid)
{
	while (*server_pid)
	{
		if (!('0' <= *server_pid && *server_pid <= '9'))
			return (1);
		server_pid++;
	}
	return (0);
}

static void	display_error(int func_value, char *func_n, int correct_value)
{
	if (func_value != correct_value)
	{
		ft_putstr_fd(func_n, 1);
		ft_putstr_fd(" func error\n", 1);
		exit(1);
	}
	else
		return ;
}

void	receive_client_signal(int sig)
{
	if (sig == SIGUSR2)
		exit(0);
}

void	print_line(pid_t server_pid, char *line)
{
	int		i;
	char	c;

	while (*line)
	{
		i = 8;
		c = *line;
		while (i--)
		{
			if (c >> i & 0x01)
				display_error(kill(server_pid, SIGUSR2), "kill", 0);
			else
				display_error(kill(server_pid, SIGUSR1), "kill", 0);
			usleep(50);
		}
		line++;
	}
	i = 8;
	while (i--)
	{
		display_error(kill(server_pid, SIGUSR1), "kill", 0);
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	char	*server_pid;
	char	*line;

	if (argc != 3)
		return (1);
	server_pid = argv[1];
	if (find_invalid_pid(server_pid) == 1)
	{
		ft_putstr_fd("Error", 1);
		exit(1);
	}
	if (server_pid[0] == '0')
	{
		ft_putstr_fd("kill func error\n", 1);
		exit(1);
	}
	line = argv[2];
	if (!line)
		return (1);
	signal(SIGUSR1, receive_client_signal);
	signal(SIGUSR2, receive_client_signal);
	print_line(ft_atoi(server_pid), line);
	while (1)
		display_error(pause(), "pause", -1);
	return (0);
}
