/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 16:44:59 by gpouyat           #+#    #+#             */
/*   Updated: 2018/12/28 23:06:02 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H

#include "../libft/includes/libft.h"

#ifdef DEBUG
# define INTERN_DEBUG_FT_SSL 1
#else
# define INTERN_DEBUG_FT_SSL 0
#endif

#define HELP_USAGE "usage: ft_ssl command [command opts] [command args]"


/*
**	MD5
*/

#define MD5_ERROR_PADDING "md5: Error step Completion cannot find padding"
#define MD5_ERROR_SIZE_64 "md5: Error size_t is not unsigned long"
#define MD5_BUFFER_CNTX 64
typedef struct			s_md5_flags {
	t_bool				a;
}						t_md5_flags;

typedef struct			s_md5_context {
	unsigned int		h0;// = 0x67452301
	unsigned int		h1;// = 0xEFCDAB89
	unsigned int		h2;// = 0x98BADCFE
	unsigned int		h3;// = 0x10325476
	unsigned char		buffer[MD5_BUFFER_CNTX];
	size_t				len; 
	unsigned char		buff_bytes;
}						t_md5_context;

t_array_byte	md5_padding(t_array_byte bits);



char	*md5(int ac, const char **av);
/*
** ***********************************************************************
*/

#endif