/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:53:50 by hwinston          #+#    #+#             */
/*   Updated: 2021/04/22 22:18:55 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void register_parameters(char **params)
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

static int  set_forks()
{
    int i;
    
    if (!(g_env.forks = malloc(sizeof(pthread_mutex_t) * g_env.n_phi)))
        return (0);
    i = -1;
    while (++i < g_env.n_phi)
        pthread_mutex_init(&g_env.forks[i], NULL);
    return (1);
}

static int  set_philosophers()
{
    int i;

    if (!(g_env.phi = malloc(sizeof(t_philo) * g_env.n_phi)))
        return (0);
    i = -1;
    while (++i < g_env.n_phi)
    {
        g_env.phi[i].id = i + 1;
        g_env.phi[i].rounds = 0;
        g_env.phi[i].left_fork = i;
        g_env.phi[i].right_fork = (i + 1) % g_env.n_phi;
        g_env.phi[i].t_last.tv_sec = 0;
        g_env.phi[i].t_last.tv_usec = 0;
    }
    return (1);
}

int        set_environment(char **params)
{
    register_parameters(params);
    if (!set_forks())
        return (display_error("memory allocation failed."));
    if (!set_philosophers())
    {
        free(g_env.forks);
        return (display_error("memory allocation failed."));
    }
    pthread_mutex_init(&g_env.lock, NULL);
    return (1);
}

void        unset_environment()
{
    int i = -1;
    while (++i < g_env.n_phi)
        pthread_mutex_destroy(&g_env.forks[i]);
    pthread_mutex_destroy(&g_env.lock);
    free(g_env.forks);
    free(g_env.phi);
}