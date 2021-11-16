/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:52:26 by mleblanc          #+#    #+#             */
/*   Updated: 2021/11/16 15:07:06 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <libft/libft.h>
# include "keymap.h"

# define SPEED 2.5
# define A_SPEED 4.0

typedef struct s_player
{
	t_vec2	pos;
	t_vec2	dir;
	double	angle;
	t_vec2	c_plane;
}	t_player;

void	update_player(t_player *player, bool keystate[N_KEYS], double dt);

#endif
