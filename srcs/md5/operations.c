/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 15:37:41 by gpouyat           #+#    #+#             */
/*   Updated: 2018/12/30 22:49:51 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

static int r[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,\
5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11,\
16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15,\
21, 6, 10, 15, 21};

static unsigned int k[64] = {3614090360, 3905402710, 606105819, 3250441966,\
4118548399, 1200080426, 2821735955, 4249261313, 1770035416, 2336552879,\
4294925233, 2304563134, 1804603682, 4254626195, 2792965006, 1236535329,\
4129170786, 3225465664, 643717713, 3921069994, 3593408605, 38016083,\
3634488961,3889429448, 568446438, 3275163606, 4107603335, 1163531501,\
2850285829, 4243563512, 1735328473, 2368359562, 4294588738, 2272392833,\
1839030562, 4259657740, 2763975236, 1272893353, 4139469664, 3200236656,\
681279174, 3936430074, 3572445317, 76029189, 3654602809, 3873151461, 530742520,\
3299628645, 4096336452, 1126891415, 2878612391, 4237533241, 1700485571,\
2399980690, 4293915773, 2240044497, 1873313359, 4264355552, 2734768916,\
1309151649, 4149444226, 3174756917, 718787259, 3951481745};

static void md5_operations_init_val(t_md5_context *cntx,
									t_md5_operaions_value *val)
{
	val->a = cntx->h0;
	val->b = cntx->h1;
	val->c = cntx->h2;
	val->d = cntx->h3;
	val->data = (uint32_t *)cntx->buffer;
}

static void md5_operations_end_loop(t_md5_operaions_value *val, uint32_t f,
									unsigned char i, uint32_t g)
{
	uint32_t				tmp;

	tmp = val->d;
	val->d = val->c;
	val->c = val->b;
	val->b = left_rot32((val->a + f + k[i] + val->data[g]), r[i]) + val->b; //((val->a + f + k[i] + val->data[g]) << r[i]) + val->b;
	val->a = tmp;
}

static void md5_operations_loop(t_md5_operaions_value *val, unsigned char i)
{
	uint32_t	f;
	uint32_t	g;

	if (0 <= i && i <= 15)
	{
		f = (val->b & val->c) | ((~ val->b) & val->d);
		g = i;
	}
	else if (16 <= i && i <= 31)
	{
		f = (val->d & val->b) | ((~ val->d) & val->c);
		g = (5 * i + 1) % 16;
	}
	else if (32 <= i && i <= 47)
	{
		f = val->b ^ val->c ^ val->d;
		g = (3 * i + 5) % 16;
	}
	else
	{
		f = val->c ^ (val->b | (~ val->d));
		g = (7 * i) % 16;
	}
	md5_operations_end_loop(val, f, i, g);
}


void	md5_operations(t_md5_context *cntx)
{
	t_md5_operaions_value	val;
	unsigned char			i;

	i = 0;
	md5_operations_init_val(cntx, &val);
	while(i != 64)
	{
		md5_operations_loop(&val, i);
		i++;
	}
	cntx->h0 = cntx->h0 + val.a;
	cntx->h1 = cntx->h1 + val.b;
	cntx->h2 = cntx->h2 + val.c;
	cntx->h3 = cntx->h3 + val.d;
}