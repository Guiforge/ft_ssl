/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 17:49:08 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/08 11:43:17 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

static size_t	find_padding_nb(size_t len)
{
	size_t start;

	log_func_start(__FUNCTION__);
	len *= 8;
	start = len;
	log_debug("start: %lu", start);
	while (++len % 512 != 448)
	{
		if (len == ULLONG_MAX)
			return (over_p("sha256:", SSL_ERROR_PADDING, 0));
	}
	if (len % 8)
	{
		log_fatal("sha256: padding en is not a multiple of 8 len: %lu", len);
		return (over_p("sha256:", SSL_ERROR_PADDING, 0));
	}
	log_func_end(__FUNCTION__);
	return ((len - start) / 8);
}

static	void	padding(t_sha256_context *cntx)
{
	size_t			size_padd;
	unsigned char	padd[64];
	unsigned char	super_padd;
	uint64_t		len_tmp;

	super_padd = 0x80;
	ft_bzero(padd, sizeof(padd));
	ft_memcpy(padd, &super_padd, 1);
	len_tmp = ft_swap_int64(cntx->len * 8);
	sha256_update(cntx, padd, find_padding_nb(cntx->len));
	size_padd = 64 - cntx->buffer.buff_bytes;
	if (size_padd >= 64 || size_padd != 8)
		log_fatal("%lu != 8, func: %s:%u", size_padd, __FUNCTION__, __LINE__);
	sha256_update(cntx, (unsigned char *)&len_tmp, 8);
}

void			sha256_final(t_sha256_context *cntx, unsigned char data[64])
{
	uint32_t	*data_cast;

	padding(cntx);
	log_debug("final: %x, %x, %x, %x, %x, %x, %x, %x", cntx->h0, cntx->h1, cntx->h2, cntx->h3, cntx->h4, cntx->h5, cntx->h6, cntx->h7);
	data_cast = (uint32_t *)data;
	data_cast[0] = ft_swap_int32(cntx->h0);
	data_cast[1] = ft_swap_int32(cntx->h1);
	data_cast[2] = ft_swap_int32(cntx->h2);
	data_cast[3] = ft_swap_int32(cntx->h3);
	data_cast[4] = ft_swap_int32(cntx->h4);
	data_cast[5] = ft_swap_int32(cntx->h5);
	data_cast[6] = ft_swap_int32(cntx->h6);
	data_cast[7] = ft_swap_int32(cntx->h7);
}
