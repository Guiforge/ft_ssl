/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals_functions_sha.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 17:03:14 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/08 21:53:02 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

uint32_t	sha256_ch(uint32_t x, uint32_t y, uint32_t z)
{
	return((x & y) ^ ( (~ x) & z));
}

uint32_t	sha256_maj(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t	sha256_bsig0(uint32_t x)
{
	return ((right_rot32(x, 2) ^ right_rot32(x, 13) ^ right_rot32(x, 22)));
}

uint32_t	sha256_bsig1(uint32_t x)
{
	return (right_rot32(x, 6) ^ right_rot32(x, 11) ^ right_rot32(x, 25));
}
