/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:04:05 by gakarbou          #+#    #+#             */
/*   Updated: 2024/11/27 19:08:37 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	send_addr(int pid, char *str, int len)
{
	char	*malloced;
	size_t	addr;

	malloced = malloc(sizeof(char) * (len + 2));
	if (!malloced)
		return ;
	malloced[len] = 0;
	malloced[len + 1] = '*';
	while (--len >= 0)
		malloced[len] = str[len];
	addr = (size_t)malloced;
	printf("addr = %p\n", malloced);
	while (++len < 64)
	{
		if (addr & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		addr = addr >> 1;
		usleep(500);
	}
}
*/

void	send_msg(int signum, siginfo_t *infos, void *truc)
{
	(void)truc;
	(void)infos;
	if (signum == SIGUSR1)
		ft_printf("Message envoye!\n");
	else
		ft_printf("Erreur!\n");
	exit(0);
}

void	send_character(int pid, char c)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (c & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c >> 1;
		usleep(90);
	}
}

void	send_msg(int signum, siginfo_t *infos, void *truc);

int	main(int argc, char **argv)
{
	int					i;
	int					serv_pid;
	struct sigaction	action;

	if (argc != 3)
		exit(1);
	action.sa_flags = 0;
	action.sa_sigaction = &send_msg;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	i = -1;
	serv_pid = ft_atoi(argv[1]);
	while (argv[2][++i])
		send_character(serv_pid, argv[2][i]);
	send_character(serv_pid, argv[2][i]);
	send_msg(SIGUSR2, 0, 0);
}
