/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 15:37:41 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/07 19:12:16 by gpouyat          ###   ########.fr       */
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
	unsigned char	i;
	uint32_t		s0;
	uint32_t		s1;
	uint32_t		*d;

	i = 15;
	val->a = cntx->h0;
	val->b = cntx->h1;
	val->c = cntx->h2;
	val->d = cntx->h3;
	val->e = cntx->h4;
	val->f = cntx->h5;
	val->g = cntx->h6;
	val->h = cntx->h7;
	d = (uint32_t *)cntx->buffer.buff;	
	while (++i < 64)
	{
		s0 = (right_rot32(d[i - 15], 7)) ^ (right_rot32(d[i - 15], 18)) ^ (right_rot32(d[i - 15], 3));
		s1 = (right_rot32(d[i - 2], 17)) ^ (right_rot32(d[i - 2], 19)) ^ (right_rot32(d[i - 2], 10));
		d[i] = d[i - 16] + s0 + d[ i - 7] + s1;
	}
	val->data = d;
}

static void sha256_operations_loop(t_sha256_operations_value *val, unsigned char i)
{
	uint32_t		s0;
	uint32_t		s1;
	uint32_t		ch;
	uint32_t		tmp[2];
	uint32_t		maj;

	s1 = right_rot32(val->e, 6) ^ right_rot32(val->e, 11) ^ right_rot32(val->e, 25);
	ch = (val->e & val->f) ^ ((~ val->e) & val->g);
	tmp[0] = val->h + s1 + ch + g_k[i] + val->data[i];
	s0 = right_rot32(val->a, 2) ^ right_rot32(val->a, 13) ^ right_rot32(val->a, 22);
	maj = (val->a & val->b) ^ (val->a & val->c) ^ (val->b & val->c);
	tmp[1] = s0 + maj;

	val->h = val->g;
	val->g = val->f;
	val->f = val->e;
	val->e = val->d + tmp[0];
	val->d = val->c;
	val->c = val->b;
	val->b = val->a;
	val->a = tmp[0] + tmp[1];
}



void				sha256_operations(t_sha256_context *cntx)
{
	t_sha256_operations_value	val;
	unsigned char				i;

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
	cntx->h4 = cntx->h4 + val.e;
	cntx->h5 = cntx->h5 + val.f;
	cntx->h6 = cntx->h6 + val.g;
	cntx->h7 = cntx->h7 + val.h;
}
