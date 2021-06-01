/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:53:50 by hwinston          #+#    #+#             */
/*   Updated: 2021/04/25 16:47:35 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	register_parameters(char **params)
{
	g_env.n_phi = ft_atoi(params[1]);
	g_env.n_phi = ft_atoi(params[1]);
	g_env.t_die = ft_atoi(params[2]);
	g_env.t_eat = ft_atoi(params[3]);
	g_env.t_slp = ft_atoi(params[4]);
	if (params[5])
		g_env.rounds = ft_atoi(params[5]);
	else
		g_env.rounds = -1;
}

static int	set_philosophers(void)
{
	int i;

	if (!(g_env.phi = malloc(sizeof(t_philo) * g_env.n_phi)))
		return (0);
	i = -1;
	while (++i < g_env.n_phi)
	{
		g_env.phi[i].id = i + 1;
		g_env.phi[i].rounds = 0;
	}
	return (1);
}

int			set_environment(char **params)
{
	register_parameters(params);
	sem_unlink("/forks");
	sem_unlink("/lock");
	sem_unlink("/syslock");
	g_env.forks = sem_open("/forks", O_CREAT | O_RDWR, 0660, g_env.n_phi);
	g_env.lock = sem_open("/lock", O_CREAT | O_RDWR, 0660, 1);
	g_env.syslock = sem_open("/syslock", O_CREAT | O_RDWR, 0660, 1);
	if (!set_philosophers())
		return (display_error("memory allocation failed."));
	return (1);
}

void		unset_environment(void)
{
	sem_close(g_env.forks);
	sem_close(g_env.lock);
	sem_close(g_env.syslock);
	sem_unlink("/forks");
	sem_unlink("/lock");
	sem_unlink("/syslock");
	free(g_env.phi);
}
