/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 17:49:08 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/04 15:49:44 by gpouyat          ###   ########.fr       */
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
			return (over_p("md5:", MD5_ERROR_PADDING, 0));
	}
	if (len % 8)
	{
		log_fatal("md5: padding en is not a multiple of 8 len: %lu", len);
		return (over_p("md5:", MD5_ERROR_PADDING, 0));
	}
	log_func_end(__FUNCTION__);
	return ((len - start) / 8);
}

static	void	padding(t_md5_context *cntx)
{
	size_t			size_padd;
	unsigned char	padd[64];
	unsigned char	super_padd;
	size_t			len_tmp;

	super_padd = 0x80;
	ft_bzero(padd, sizeof(padd));
	ft_memcpy(padd, &super_padd, 1);
	len_tmp = cntx->len * 8;
	md5_update(cntx, padd, find_padding_nb(cntx->len));
	size_padd = MD5_BUFFER_CNTX - cntx->buffer.buff_bytes;
	if (size_padd >= MD5_BUFFER_CNTX || size_padd != 8)
		log_fatal("%lu != 8, func: %s:%u", size_padd, __FUNCTION__, __LINE__);
	md5_update(cntx, (unsigned char *)&len_tmp, 8);
}

void			md5_final(t_md5_context *cntx, unsigned char data[16])
{
	uint32_t	*data_cast;

	padding(cntx);
	log_debug("final: %x, %x, %x, %x", cntx->h0, cntx->h1, cntx->h2, cntx->h3);
	data_cast = (uint32_t *)data;
	data_cast[0] = cntx->h0;
	data_cast[1] = cntx->h1;
	data_cast[2] = cntx->h2;
	data_cast[3] = cntx->h3;
}
