/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 23:55:12 by mleblanc          #+#    #+#             */
/*   Updated: 2021/11/10 08:21:46 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	update_player(t_player *player, bool keystate[4], float speed)
{
	if (keystate[W])
	{
		player->pos.x += player->dir.x * speed;
		player->pos.y += player->dir.y * speed;
	}
	if (keystate[S])
	{
		player->pos.x -= player->dir.x * speed;
		player->pos.y -= player->dir.y * speed;
	}
}
