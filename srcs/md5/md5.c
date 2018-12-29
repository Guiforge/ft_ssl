/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 16:56:55 by gpouyat           #+#    #+#             */
/*   Updated: 2018/12/29 23:55:53 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

// static int r[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,\
// 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11,\
// 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15,\
// 21, 6, 10, 15, 21};

// static unsigned int k[64] = {3614090360, 3905402710, 606105819, 3250441966,\
// 4118548399, 1200080426, 2821735955, 4249261313, 1770035416, 2336552879,\
// 4294925233, 2304563134, 1804603682, 4254626195, 2792965006, 1236535329,\
// 4129170786, 3225465664, 643717713, 3921069994, 3593408605, 38016083,\
// 3634488961,3889429448, 568446438, 3275163606, 4107603335, 1163531501,\
// 2850285829, 4243563512, 1735328473, 2368359562, 4294588738, 2272392833,\
// 1839030562, 4259657740, 2763975236, 1272893353, 4139469664, 3200236656,\
// 681279174, 3936430074, 3572445317, 76029189, 3654602809, 3873151461, 530742520,\
// 3299628645, 4096336452, 1126891415, 2878612391, 4237533241, 1700485571,\
// 2399980690, 4293915773, 2240044497, 1873313359, 4264355552, 2734768916,\
// 1309151649, 4149444226, 3174756917, 718787259, 3951481745};

void md5_clean_buff(t_md5_context *cntx)
{
	cntx->buff_bytes = 0;
	ft_bzero(cntx->buffer, sizeof(cntx->buffer));
}

t_bool	md5_buff_is_full(t_md5_context *cntx)
{
	return (cntx->buff_bytes == MD5_BUFFER_CNTX);
}

void	md5_fill_buff(t_md5_context *cntx, unsigned char *data, size_t size, size_t *index)
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

void	md5_init(t_md5_context *cntx)
{
	if (cntx)
	{	
		cntx->h0 = 0x67452301;
		cntx->h1 = 0xEFCDAB89;
		cntx->h2 = 0x98BADCFE;
		cntx->h3 = 0x10325476;
		ft_bzero(cntx->buffer, sizeof(cntx->buffer));
		cntx->len = 0;
		cntx->buff_bytes = 0;
	}
	else
		log_fatal("Md5: error context invalid (NULL)");
}


void	md5_update(t_md5_context *cntx, unsigned char *data, size_t size)
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

	#include <math.h>
	#include <stdlib.h>
char	*md5(int ac, const char **av)
{
	t_array_byte	bits;

	(void)ac;
	(void)av;
	if (sizeof(size_t) != 8)
	{
		log_fatal("%s, sizeof(size_t): %lu", MD5_ERROR_SIZE_64, sizeof(size_t));
		return(over_str(MD5_ERROR_SIZE_64));
	}
	// bits = b_dump_secu(av[1], ft_strlen(av[1]), M_LVL_FUNCT);
	// bits = md5_padding(bits);

	t_md5_context	cntx;
	md5_init(&cntx);
	md5_update(&cntx, (unsigned char *)av[1], ft_strlen(av[1]));
	bits.bytes = (char *)cntx.buffer;
	bits.nb = MD5_BUFFER_CNTX;
	b_print_array(bits, ", ");

	for(int i = 0; i < 64; i++)
	{
		printf("%lu, ", (size_t)floor(fabs(sin(i + 1)) * pow(2, 32)));
	}
	return (NULL);
}