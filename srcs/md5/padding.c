/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 23:43:38 by gpouyat           #+#    #+#             */
/*   Updated: 2018/12/28 00:00:36 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"
#include <limits.h>

static void debug_md5_check_padding(t_array_byte arr)
{
	log_func_start(__FUNCTION__);
	if (!arr.bytes)
		log_fatal("Padding Error the array of bytes doesn't exist");
	if (arr.nb * 8 % 512)
		log_fatal("Padding Error the number of bytes is not a multiple of 512");
	log_func_end(__FUNCTION__);
	
}

static size_t	md5_find_padding_nb(size_t len)
{
	size_t start;

	log_func_start(__FUNCTION__);
	start = len * 8;
	while(++len % 512 != 448)
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
	return ((len - start)/8);
}


t_array_byte md5_padding(t_array_byte bits)
{
	char			super_padd;
	t_array_byte	padding;
	t_array_byte	len;

	log_func_start(__FUNCTION__);
	super_padd = 0x80;
	padding = b_new_secu(md5_find_padding_nb(bits.nb), M_LVL_FUNCT);
	log_debug("padding length: %lu", padding.nb);
	if (padding.bytes)
		ft_memcpy(padding.bytes, &super_padd, 1);
	len.bytes = ft_itochar_secu(sizeof(size_t), &bits.nb, False, M_LVL_FUNCT);
	len.nb = len.bytes ? sizeof(size_t) : 0;
	bits = b_joinf_secu(bits, padding, 3, M_LVL_FUNCT);
	bits = b_joinf_secu(bits, len, 3, MALLOC_LVL_DEFAULT);
	if (INTERN_DEBUG_FT_SSL)
		debug_md5_check_padding(bits);
	log_func_end(__FUNCTION__);	
	return(bits);
}