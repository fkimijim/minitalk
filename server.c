/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkimijim <fkimijim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:22:55 by fkimijim          #+#    #+#             */
/*   Updated: 2024/06/05 13:34:07 by fkimijim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <unistd.h>

static void	display_error(char *func_n, int func_value, int correct_value)
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

void	get_pid(void)
{
	int		pid;
	char	*pid_s;

	pid = getpid();
	pid_s = ft_itoa(pid);
	ft_putstr_fd(pid_s, 1);
}

void	print_c_display_err(char c, pid_t *client_pid)
{
	if (c == '\0')
	{
		ft_putchar_fd('\n', 1);
		display_error("kill", kill(*client_pid, SIGUSR2), 0);
		*client_pid = 0;
	}
	else
	{
		ft_putchar_fd(c, 1);
		display_error("kill", kill(*client_pid, SIGUSR1), 0);
	}
}

void	receive_server_signal(int sig, siginfo_t *info, void *context)
{
	static pid_t			client_pid;
	static int				bit_count;
	static unsigned char	c;

	(void)context;
	if (client_pid != info->si_pid)
	{
		client_pid = info->si_pid;
		bit_count = 0;
		c = 0;
	}
	if (sig == SIGUSR2)
		c |= (1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8)
	{
		print_c_display_err(c, &client_pid);
		bit_count = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr_fd("Server PID :", 1);
	get_pid();
	ft_putchar_fd('\n', 1);
	sa.sa_sigaction = receive_server_signal;
	sa.sa_flags = SA_SIGINFO;
	display_error("sigaction", sigaction(SIGUSR1, &sa, 0), 0);
	display_error("sigaction", sigaction(SIGUSR2, &sa, 0), 0);
	while (1)
		display_error("pause", pause(), -1);
	return (0);
}
