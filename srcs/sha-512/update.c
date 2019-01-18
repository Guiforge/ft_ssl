/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 17:43:47 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/18 17:55:57 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void		sha512_update(t_sha512_context *cntx, unsigned char *data, size_t size)
{
	size_t		index;

	index = 0;
	log_debug(" update, cntx->len: %lu, size data: %lu", cntx->len, size);
	if (!data || !size || !cntx)
	{
		log_error(" data/context invalid ptr: %#lx, size: %lu", data, size);
		return ;
	}
	buffer1024_fill(&(cntx->buffer), data, size, &index);
	while (buffer1024_is_full(&(cntx->buffer)))
	{
		for(int i = 0; i < 128; i++)
		{
			printf("[%d] = %x\n", i, cntx->buffer.buff[i]);
		}
		// ft_bzero(cntx->buffer.buff, 128);
		// for(int i = 0; i < 128; i++)
		// {
		// 	printf("[%d] = %x\n", i, cntx->buffer.buff[i]);
		// 	if (i == 6)
		// 		cntx->buffer.buff[i] = 80;
		// 	if (i == 7)
		// 		cntx->buffer.buff[i] = 61;
		// 	if (i == 120)
		// 		cntx->buffer.buff[i] = 8;
		// }
		sha512_operations(cntx);
		buffer1024_clean(&(cntx->buffer));
		buffer1024_fill(&(cntx->buffer), data, size, &index);
	}
	cntx->len += size;
	if (cntx->len >= ULLONG_MAX || cntx->len < size)
	{
		log_error(" length is larger of 2^64");
		cntx->len = cntx->len & 0xffffffff;
	}
}
