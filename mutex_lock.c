/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_lock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:42:07 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/15 18:22:00 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_details *thread)
{
	if (thread->philo->nb_philo == 1)
	{
		pthread_mutex_lock(&thread->philo->fork[thread->id]);
		print_log(thread, "has taken a fork");
		own_sleep(thread->philo->time_die);
		pthread_mutex_lock(&thread->philo->m_is_dead);
		thread->philo->is_died = 1;
		pthread_mutex_unlock(&thread->philo->m_is_dead);
		pthread_mutex_unlock(&thread->philo->fork[thread->id]);
		return (0);
	}
	return (1);
}

int	mutex_lock(t_details *thread)
{
	pthread_mutex_lock(&thread->philo->fork[thread->id]);
	pthread_mutex_lock(&thread->philo->fork[(thread->id + 1)
		% thread->philo->nb_philo]);
	pthread_mutex_lock(&thread->philo->m_last_eat_time);
	if (get_time() - thread->last_eat_time >= thread->philo->time_die)
	{
		print_log(thread, "died");
		thread->philo->is_died = 1;
		pthread_mutex_unlock(&thread->philo->m_last_eat_time);
		// printf("here-------------------------\n");
		// pthread_mutex_lock(&threads[i].philo->m_is_dead);
		// pthread_mutex_unlock(&threads[i].philo->m_is_dead);
		// pthread_mutex_unlock(&threads[i].philo->m_last_eat_time);
		return (0) ;
	}
	pthread_mutex_unlock(&thread->philo->m_last_eat_time);
	print_log(thread, "has taken a fork");
	print_log(thread, "has taken a fork");
	print_log(thread, "is eating");
	pthread_mutex_lock(&thread->philo->m_last_eat_time);
	thread->last_eat_time = get_time();
	pthread_mutex_unlock(&thread->philo->m_last_eat_time);
	own_sleep(thread->philo->time_eat);

	pthread_mutex_lock(&thread->philo->m_nb_eat);
	thread->nb_eat++;
	pthread_mutex_unlock(&thread->philo->m_nb_eat);

	pthread_mutex_unlock(&thread->philo->fork[thread->id]);
	pthread_mutex_unlock(&thread->philo->fork[(thread->id + 1)
		% thread->philo->nb_philo]);
	return (1);
}
