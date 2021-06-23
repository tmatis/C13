/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_level_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 15:18:14 by tmatis            #+#    #+#             */
/*   Updated: 2021/06/23 17:23:40 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

int	btree_level_count(t_btree *root)
{
	int	res_right;
	int	res_left;

	if (root)
	{
		res_left = btree_level_count(root->left);
		res_right = btree_level_count(root->right);
		if (res_right > res_left)
			return (res_right + 1);
		else
			return (res_left + 1);
	}
	else
		return (0);
}
