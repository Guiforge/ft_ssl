
#include "../../includes/ft_ssl.h"

uint32_t	sha256_ssig0(uint32_t x)
{
	return (right_rot32(x, 7) ^ right_rot32(x, 18) ^ (x >> 3));
}

uint32_t	sha256_ssig1(uint32_t x)
{
	return (right_rot32(x, 17) ^ right_rot32(x, 19) ^ (x >> 10));
}
