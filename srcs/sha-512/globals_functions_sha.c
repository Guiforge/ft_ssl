/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals_functions_sha.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 17:03:14 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/19 16:00:59 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

uint64_t	sha512_ch(uint64_t x, uint64_t y, uint64_t z)
{
	return((x & y) ^ ( (~ x) & z));
}

uint64_t	sha512_maj(uint64_t x, uint64_t y, uint64_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint64_t	sha512_bsig0(uint64_t x)
{
	return ((right_rot64(x, 28) ^ right_rot64(x, 34) ^ right_rot64(x, 39)));
}

uint64_t	sha512_bsig1(uint64_t x)
{
	return (right_rot64(x, 14) ^ right_rot64(x, 18) ^ right_rot64(x, 41));
}
