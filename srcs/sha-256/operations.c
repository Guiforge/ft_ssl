/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 15:37:41 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/04 16:54:30 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"


static unsigned int	g_k[64] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,\
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,\
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,\
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,\
	0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,\
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,\
	0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,\
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,\
	0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,\
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,\
	0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void			sha256_operations_init_val(t_sha256_context *cntx,
												t_sha256_operations_value *val)
{
	val->a = cntx->h0;
	val->b = cntx->h1;
	val->c = cntx->h2;
	val->d = cntx->h3;
	val->e = cntx->h4;
	val->f = cntx->h5;
	val->g = cntx->h6;
	val->h = cntx->h7;
	val->data = (uint32_t *)cntx->buffer.buff;
}

static void			sha256_operations_end_loop(t_sha256_operaions_value *val,
									uint32_t f, unsigned char i, uint32_t g)
{
	uint32_t		tmp;

	tmp = val->d;
	val->d = val->c;
	val->c = val->b;
	val->b = left_rot32((val->a + f + g_k[i] + val->data[g]), g_r[i]) + val->b;
	val->a = tmp;
}

static void			sha256_operations_loop(t_sha256_operaions_value *val,
															unsigned char i)
{
	uint32_t	f;
	uint32_t	g;

	if (0 <= i && i <= 15)
	{
		f = (val->b & val->c) | ((~val->b) & val->d);
		g = i;
	}
	else if (16 <= i && i <= 31)
	{
		f = (val->d & val->b) | ((~val->d) & val->c);
		g = (5 * i + 1) % 16;
	}
	else if (32 <= i && i <= 47)
	{
		f = val->b ^ val->c ^ val->d;
		g = (3 * i + 5) % 16;
	}
	else
	{
		f = val->c ^ (val->b | (~val->d));
		g = (7 * i) % 16;
	}
	sha256_operations_end_loop(val, f, i, g);
}

void				sha256_operations(t_sha256_context *cntx)
{
	t_sha256_operaions_value	val;
	unsigned char			i;

	i = 0;
	sha256_operations_init_val(cntx, &val);
	while (i != 64)
	{
		sha256_operations_loop(&val, i);
		i++;
	}
	cntx->h0 = cntx->h0 + val.a;
	cntx->h1 = cntx->h1 + val.b;
	cntx->h2 = cntx->h2 + val.c;
	cntx->h3 = cntx->h3 + val.d;
}
