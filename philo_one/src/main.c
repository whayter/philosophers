/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:05:59 by hwinston          #+#    #+#             */
/*   Updated: 2021/04/21 11:50:51 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_env       g_env;

static int  valid_parameters(int ac, char **av)
{
    int i;
    
    if (ac < 5)
        return (display_error("not enough parameters."));
    if ( ac > 6)
        return (display_error("too many parameters."));
    i = 0;
    while (++i < ac)
        if (!ft_isnumber(av[i]))
            return (display_error("parameters must be integers."));
    if (ft_atoi(av[1]) < 2)
        return (display_error("a minimum of two philosophers is needed."));
    return (1);
}

int         main(int ac, char **av)
{
    int i;

    if (!valid_parameters(ac, av))
        return (-1);
    if (!set_environment(av))
        return (-1);
    start_simulation();
    evaluate_simulation();

    
    i = -1;
    while (++i < g_env.n_phi)
        pthread_join(g_env.phi[i].thread, NULL);

    printf("\n\n");
    i = -1;
    while (++i < g_env.n_phi)
        printf("%d has eaten %d times\n", g_env.phi[i].id, g_env.phi[i].rounds);

    unset_environment();
    return (0);
}