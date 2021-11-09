/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 00:11:04 by mleblanc          #+#    #+#             */
/*   Updated: 2021/11/09 00:55:55 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# include <libft/libft.h>

typedef struct s_buffer
{
	void	*mlx;
	void	*img;
	char	*data;
	int32_t	bpp;
	int32_t	pitch;
	int32_t	endian;
}	t_buffer;

t_buffer	*new_buffer(void *mlx_ptr, int32_t width, int32_t height);
void		destroy_buffer(t_buffer *buf);
void		put_pixel(t_buffer *buf, int32_t x, int32_t y, uint32_t trgb);

#endif
