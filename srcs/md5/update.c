/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 17:43:47 by gpouyat           #+#    #+#             */
/*   Updated: 2018/12/30 19:24:17 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

static void		md5_clean_buff(t_md5_context *cntx)
{
	cntx->buff_bytes = 0;
	// ft_bzero(cntx->buffer, sizeof(cntx->buffer));
}

static t_bool	md5_buff_is_full(t_md5_context *cntx)
{
	return (cntx->buff_bytes == MD5_BUFFER_CNTX);
}

static void		md5_fill_buff(t_md5_context *cntx, unsigned char *data, size_t size, size_t *index)
{
	unsigned char size_to_fill;

	if (!(size - *index))
	{
		log_warn("%s: Nothing to read into data", __FUNCTION__);
		return ;
	}
	size_to_fill = MD5_BUFFER_CNTX - cntx->buff_bytes;
	if (size_to_fill > size - *index)
		size_to_fill = (unsigned char)(size - *index);
	ft_memcpy(&cntx->buffer[cntx->buff_bytes], &data[*index], size_to_fill);
	*index += size_to_fill;
	cntx->buff_bytes += size_to_fill;
}


void			md5_update(t_md5_context *cntx, unsigned char *data, size_t size)
{
	size_t		index;

	index = 0;
	log_debug("Md5 update, cntx->len: %lu, size data: %lu", cntx->len, size);
	if (!data || !size || !cntx)
	{
		log_error("Md5 data/context invalid ptr: %#lx or size: %lu", data, size);
		return;
	}
	md5_fill_buff(cntx, data, size, &index);
	while(md5_buff_is_full(cntx))
	{
		//operation
		md5_operations(cntx);
		md5_clean_buff(cntx);
		md5_fill_buff(cntx, data, size, &index);
	}
	cntx->len += size;
	if (cntx->len >= ULLONG_MAX || cntx->len < size)
	{
		log_error("Md5 length is larger of 2^64");
		// TODO: when length is larger of 2^64
	}
}