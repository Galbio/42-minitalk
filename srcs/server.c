/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:03:07 by gakarbou          #+#    #+#             */
/*   Updated: 2024/11/26 00:37:36 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	ft_repeat_char(char c, int times)
{
	while (times)
		times -= write(1, &c, 1);
}

void	ft_check_addr(void *addr)
{
	int				i;
	unsigned char	*ptr;

	ptr = (unsigned char *)addr;
	i = 0;
	while (ptr[i])
	{
		write(1, ptr + i, 1);
		i++;
	}
	if (ptr[i + 1] != 42)
		return ;
}

void	ft_interpret(int signum, siginfo_t *a, void *truc)
{
	static char		saw = 0;
	static char		addr = 0;

	(void)truc;
	(void)a;
	if (signum == SIGUSR2)
		addr |= 1 << saw;
	saw++;
	if (saw == 8)
	{
		write(1, &addr, 1);
		if (!addr)
			write(1, "\n>> ", 4);
		saw = 0;
		addr = 0;
	}
}

void	super_header(int pid)
{
	write(1, " ", 1);
	ft_repeat_char('_', 77);
	write(1, "\n", 1);
	ft_printf("/   _%24.s_%48.s\\\n", "", "");
	ft_printf("|  | |__   ___  ___ _ __    | |__   ___   ___  _ __");
	ft_printf("     ___  ___ _ ____   __  |\n");
	ft_printf("|  | '  \\ / _ \\/ _ \\ '_ \\   | '_ \\ / _ \\ / _ \\| '_ \\");
	ft_printf("   / __|/ _ \\ '__\\ \\ / /  |\n");
	ft_printf("|  | |_) |  __/  __/ |_) |  | |_) | (_) | (_) | |_) |  \\__ \\");
	ft_printf("  __/ |   \\ V /   |\n");
	ft_printf("|  |_.__/ \\___|\\___| .__/   |_.__/ \\___/ \\___/| .__/");
	ft_printf("   |___/\\___|_|    \\_/    |\n");
	ft_printf("|%18.s|_|%24.s|_|%29.s|\n", "", "", "");
	ft_printf("|%77.s|\n", "");
	ft_printf("|   01100010 01111001 00100000 01000111 01100001 01100010");
	ft_printf(" 01101001 01101111   |\n");
	write(1, "\\", 1);
	ft_repeat_char('_', 77);
	write(1, "/\n", 2);
	ft_printf("PID = %d\n", pid);
}

void	ft_interpret(int signum, siginfo_t *, void *truc);
int	main(void)
{
	struct sigaction	action;
	int					pid;

	pid = getpid();
	super_header(pid);
	action.sa_flags = 0;
	action.sa_sigaction = &ft_interpret;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	write(1, ">> ", 3);
	while (1)
		;
	return (0);
}
