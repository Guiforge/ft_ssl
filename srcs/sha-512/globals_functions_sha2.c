/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals_functions_sha2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 15:36:39 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/18 15:36:41 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

uint64_t	sha512_ssig0(uint64_t x)
{
	return (right_rot32(x, 1) ^ right_rot32(x, 8) ^ (x >> 7));
}

uint64_t	sha512_ssig1(uint64_t x)
{
	return (right_rot32(x, 19) ^ right_rot32(x, 61) ^ (x >> 6));
}
