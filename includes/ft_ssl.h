/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 16:44:59 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/04 15:46:22 by gpouyat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H

# define FT_SSL_H

# include "../libft/includes/libft.h"

# ifdef DEBUG
#  define INTERN_DEBUG_FT_SSL 1
# else
#  define INTERN_DEBUG_FT_SSL 0
# endif

# define HELP_USAGE "usage: ft_ssl command [command opts] [command args]"

/*
** MISC
*/
typedef struct			s_buffer512 {
	unsigned char		buff[64];
	unsigned char		buff_bytes;
}						t_buffer512;

void					buffer512_clean(t_buffer512 *buffer512);
t_bool					buffer512_is_full(t_buffer512 *buffer512);
void					buffer512_fill(t_buffer512 *buffer512,
							unsigned char *data, size_t size, size_t *index);

/*
**	MD5
*/

# define MD5_ERROR_PADDING "md5: Error step Completion cannot find padding"
# define MD5_ERROR_SIZE_64 "md5: Error size_t is not unsigned long"
# define MD5_BUFFER_CNTX 64

typedef struct			s_md5_flags {
	t_bool				p;
	t_bool				q;
	t_bool				r;
	t_bool				s;

}						t_md5_flags;

typedef struct			s_md5_context {
	uint32_t			h0;
	uint32_t			h1;
	uint32_t			h2;
	uint32_t			h3;
	t_buffer512			buffer;
	size_t				len;
}						t_md5_context;

typedef struct			s_md5_operaions_value {
	uint32_t			a;
	uint32_t			b;
	uint32_t			c;
	uint32_t			d;
	uint32_t			*data;
}						t_md5_operaions_value;

void					md5_put_sum(unsigned char sum[16]);
void					md5_print(t_md5_flags flags, unsigned char sum[16],
																const char *s);
void					md5_print_string(t_md5_flags flags,
										unsigned char sum[16], const char *s);

void					md5_get_sum_string(const char *s,
														unsigned char data[16]);
ssize_t					md5_get_sum_file(const char *filename,
														unsigned char data[16]);
ssize_t					md5_get_sum_out(unsigned char data[16], t_bool	print);

void					md5(int ac, const char **av);
void					md5_init(t_md5_context *cntx);
void					md5_operations(t_md5_context *cntx);
void					md5_update(t_md5_context *cntx, unsigned char *data,
																size_t size);
void					md5_final(t_md5_context *cntx, unsigned char data[16]);
/*
** ***********************************************************************
*/

#endif
