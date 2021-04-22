/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 15:30:56 by hwinston          #+#    #+#             */
/*   Updated: 2021/04/22 14:47:35 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void        philosopher_die()
{
    int i;
    int strt;

    i = -1;
    while (++i < g_env.n_phi)
    {
        //strt = get_time_since(g_env.phi[i].t_start);
        strt = get_time_since(g_env.t_start);
        if (!g_env.phi[i].rounds)
        {
            if (strt >= g_env.t_die)
            {
                display_status(g_env.phi[i].id, strt, DIE);
                g_env.run = 0;
            }
        }
        else if (get_time_since(g_env.phi[i].t_last) >= g_env.t_die)
        {
            display_status(g_env.phi[i].id, strt, DIE);
            g_env.run = 0;
        }
    }
}

static void philosopher_eat(t_philo *phi)
{
    pthread_mutex_lock(&g_env.lock);
    pthread_mutex_lock(&g_env.forks[phi->left_fork]);
    //display_status(phi->id, get_time_since(phi->t_start), FRK);
    display_status(phi->id, get_time_since(g_env.t_start), FRK);

    pthread_mutex_lock(&g_env.forks[phi->right_fork]);
    //display_status(phi->id, get_time_since(phi->t_start), FRK);
    display_status(phi->id, get_time_since(g_env.t_start), FRK);
    
    pthread_mutex_unlock(&g_env.lock);
    if (g_env.run)
    {
        //display_status(phi->id, get_time_since(phi->t_start), EAT);
        display_status(phi->id, get_time_since(g_env.t_start), EAT);
        usleep(g_env.t_eat * 1000);
        get_actual_time(&phi->t_last);
        phi->rounds++;
    }
    pthread_mutex_unlock(&g_env.forks[phi->left_fork]);
    pthread_mutex_unlock(&g_env.forks[phi->right_fork]);
}

static void philosopher_sleep(t_philo *phi)
{
    //display_status(phi->id, get_time_since(phi->t_start), SLP);
    display_status(phi->id, get_time_since(g_env.t_start), SLP);
    usleep(g_env.t_slp * 1000);
}

static void philosopher_think(t_philo *phi)
{
    //display_status(phi->id, get_time_since(phi->t_start), THK);
    display_status(phi->id, get_time_since(g_env.t_start), THK);
}

void        *routine(void *phi)
{
    while (g_env.run)
    {
        philosopher_eat(phi);
        philosopher_sleep(phi);
        philosopher_think(phi);
    }
    return (NULL);
}