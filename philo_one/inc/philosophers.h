/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 12:05:56 by hwinston          #+#    #+#             */
/*   Updated: 2021/04/24 08:16:31 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <pthread.h>

# define RED "\e[0;31m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"

# define DIE 0
# define FRK 1
# define EAT 2
# define SLP 3
# define THK 4

typedef struct      s_philo
{
    int             id;
    int             rounds;
    pthread_t       thread;
    int             left_fork;
    int             right_fork;
    struct timeval	t_last;
}                   t_philo;

typedef struct      s_env
{
    int             n_phi;
    int             t_die;
    int             t_eat;
    int             t_slp;
    int             rounds;
    t_philo         *phi;
    int             run;
    pthread_mutex_t *forks;
    pthread_mutex_t lock;
    pthread_mutex_t syslock;
    struct timeval	t_start;
}                   t_env;

extern t_env g_env;

/*
** ********************************* setup.c ***********************************
*/

int         set_environment(char **params);
void        unset_environment();

/*
** ******************************** routine.c **********************************
*/

void        *routine(void *phi);
void        philosopher_die();

/*
** ********************************** run.c ************************************
*/

void        start_simulation();
void        evaluate_simulation();
void        end_simulation();

/*
** **************************** numbers_utility.c ******************************
*/

int         ft_isnumber(char *str);
int		    ft_atoi(const char *str);

/*
** **************************** strings_utility.c ******************************
*/

size_t      ft_strlen(const char *s);
int			ft_isspace(char c);

/*
** ****************************** time_utility.c *******************************
*/

void        get_actual_time(struct timeval *tv);
int         get_time_since(struct timeval reference);
void        wait_for(int ms);

/*
** **************************** display_utility.c ******************************
*/

//void        display_parameters(char **params);
void        display_status(int id, int ms, int status);
int         display_error(char *msg);

#endif