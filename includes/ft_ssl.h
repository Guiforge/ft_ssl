/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 16:44:59 by gpouyat           #+#    #+#             */
/*   Updated: 2019/01/21 18:03:39 by gpouyat          ###   ########.fr       */
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
# define SSL_ERROR_SIZE_64 "Error size_t is not unsigned long"
# define SSL_ERROR_PADDING "Error step Completion cannot find padding"
# define SSL_SIZE_BUFF_READ 4096
# define SSL_MAX_SUM_SIZE 64

# define BUFFER_512_BYTES 64
# define BUFFER_1024_BYTES 128

typedef struct			s_ssl_hash {
	char				*buff;
	int					(*f)(int, const char **);
}						t_ssl_hash;

/*
** MISC
** *****************************************************************************
*/
typedef struct			s_buffer512 {
	unsigned char		buff[64];
	unsigned char		buff_bytes;
}						t_buffer512;

typedef struct			s_buffer1024 {
	unsigned char		buff[128];
	unsigned char		buff_bytes;
}						t_buffer1024;

typedef struct			s_digst_flags {
	t_bool				p;
	t_bool				q;
	t_bool				r;
	t_bool				s;
}						t_digst_flags;

typedef struct			s_ssl_digst {
	void				*context;
	void				(*init) (void *);
	void				(*update) (void *, unsigned char *, size_t);
	void				(*final) (void *, unsigned char *);
	size_t				size_sum;
	t_digst_flags		flags;
	char				*name;
	t_list				*lst_str;
}						t_ssl_digst;

int						digst_main(t_ssl_digst *d, int ac, const char *av[]);

ssize_t					digst_get_sum_out(t_ssl_digst *digst,\
							unsigned char sum[SSL_MAX_SUM_SIZE], t_bool print);
ssize_t					digst_get_sum_file(t_ssl_digst *digst,\
					const char *filename, unsigned char sum[SSL_MAX_SUM_SIZE]);
void					digst_get_sum_string(t_ssl_digst *digst, const char *s,\
										unsigned char sum[SSL_MAX_SUM_SIZE]);

void					digst_put_sum(unsigned char *sum, int size);
void					digst_print(t_ssl_digst *d, unsigned char *sum,\
																const char *s);
void					digst_print_string(t_ssl_digst *d, unsigned char *sum,\
																const char *s);
int						digst_parse_options(t_ssl_digst *d, int ac,\
															char const *av[]);

void					buffer512_clean(t_buffer512 *buffer512);
t_bool					buffer512_is_full(t_buffer512 *buffer512);
void					buffer512_fill(t_buffer512 *buffer512,
							unsigned char *data, size_t size, size_t *index);

void					buffer1024_clean(t_buffer1024 *buffer1024);
t_bool					buffer1024_is_full(t_buffer1024 *buffer1024);
void					buffer1024_fill(t_buffer1024 *buffer1024,
							unsigned char *data, size_t size, size_t *index);
void					buffer1024_swap64(t_buffer1024 *b);

/*
** SHA-512
** *****************************************************************************
*/
typedef struct			s_sha512_flags {
	t_bool				p;
	t_bool				q;
	t_bool				r;
	t_bool				s;
}						t_sha512_flags;

typedef struct			s_sha512_operaions_value {
	uint64_t			a;
	uint64_t			b;
	uint64_t			c;
	uint64_t			d;
	uint64_t			e;
	uint64_t			f;
	uint64_t			g;
	uint64_t			h;
	uint64_t			data[80];
}						t_sha512_operations_value;

typedef struct			s_sha512_context {
	uint64_t			h0;
	uint64_t			h1;
	uint64_t			h2;
	uint64_t			h3;
	uint64_t			h4;
	uint64_t			h5;
	uint64_t			h6;
	uint64_t			h7;
	t_buffer1024		buffer;
	size_t				len;
}						t_sha512_context;

uint64_t				sha512_ssig0(uint64_t x);
uint64_t				sha512_ssig1(uint64_t x);
uint64_t				sha512_bsig1(uint64_t x);
uint64_t				sha512_bsig0(uint64_t x);
uint64_t				sha512_ch(uint64_t x, uint64_t y, uint64_t z);
uint64_t				sha512_maj(uint64_t x, uint64_t y, uint64_t z);

void					sha512_init(t_sha512_context *cntx);
int						sha512(int ac, const char **av);
void					sha512_operations(t_sha512_context *cntx);
void					sha512_put_sum(unsigned char sum[64]);
void					sha512_print(t_sha512_flags flags,
										unsigned char sum[64], const char *s);
void					sha512_print_string(t_sha512_flags flags,
										unsigned char sum[64], const char *s);
void					sha512_update(t_sha512_context *cntx,
											unsigned char *data, size_t size);
ssize_t					sha512_get_sum_out(unsigned char sum[64],
																t_bool print);
void					sha512_get_sum_string(const char *s,
														unsigned char sum[64]);
ssize_t					sha512_get_sum_file(const char *filename,
														unsigned char sum[64]);
void					sha512_final(t_sha512_context *cntx,
														unsigned char sum[64]);

/*
** SHA-512
** *****************************************************************************
*/

void					sha384_init(t_sha512_context *cntx);
int						sha384(int ac, const char **av);

/*
** SHA-256
** *****************************************************************************
*/
typedef struct			s_sha256_flags {
	t_bool				p;
	t_bool				q;
	t_bool				r;
	t_bool				s;
}						t_sha256_flags;

typedef struct			s_sha256_operaions_value {
	uint32_t			a;
	uint32_t			b;
	uint32_t			c;
	uint32_t			d;
	uint32_t			e;
	uint32_t			f;
	uint32_t			g;
	uint32_t			h;
	uint32_t			data[64];
}						t_sha256_operations_value;

typedef struct			s_sha256_context {
	uint32_t			h0;
	uint32_t			h1;
	uint32_t			h2;
	uint32_t			h3;
	uint32_t			h4;
	uint32_t			h5;
	uint32_t			h6;
	uint32_t			h7;
	t_buffer512			buffer;
	__uint128_t			len;
}						t_sha256_context;

uint32_t				sha256_ssig0(uint32_t x);
uint32_t				sha256_ssig1(uint32_t x);
uint32_t				sha256_bsig1(uint32_t x);
uint32_t				sha256_bsig0(uint32_t x);
uint32_t				sha256_ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t				sha256_maj(uint32_t x, uint32_t y, uint32_t z);

void					sha256_init(t_sha256_context *cntx);
int						sha256(int ac, const char **av);
void					sha256_operations(t_sha256_context *cntx);
void					sha256_put_sum(unsigned char sum[32]);
void					sha256_print(t_sha256_flags flags,
										unsigned char sum[32], const char *s);
void					sha256_print_string(t_sha256_flags flags,
										unsigned char sum[32], const char *s);
void					sha256_update(t_sha256_context *cntx,
											unsigned char *data, size_t size);
ssize_t					sha256_get_sum_out(unsigned char sum[32],
																t_bool print);
void					sha256_get_sum_string(const char *s,
														unsigned char sum[32]);
ssize_t					sha256_get_sum_file(const char *filename,
														unsigned char sum[32]);
void					sha256_final(t_sha256_context *cntx,
														unsigned char sum[32]);

/*
**	sha224
** *****************************************************************************
*/

void					sha224_init(t_sha256_context *cntx);
int						sha224(int ac, const char **av);

/*
**	MD5
** *****************************************************************************
*/

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
}						t_md5_operations_value;

void					md5_put_sum(unsigned char sum[16]);
void					md5_print(t_md5_flags flags, unsigned char sum[16],
																const char *s);
void					md5_print_string(t_md5_flags flags,
										unsigned char sum[16], const char *s);

void					md5_get_sum_string(const char *s,
														unsigned char sum[16]);
ssize_t					md5_get_sum_file(const char *filename,
														unsigned char sum[16]);
ssize_t					md5_get_sum_out(unsigned char sum[16], t_bool	print);

int						md5(int ac, const char **av);
void					md5_init(t_md5_context *cntx);
void					md5_operations(t_md5_context *cntx);
void					md5_update(t_md5_context *cntx, unsigned char *data,
																size_t size);
void					md5_final(t_md5_context *cntx, unsigned char sum[16]);
/*
** ***********************************************************************
** *****************************************************************************
*/

#endif
