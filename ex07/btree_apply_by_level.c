/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_by_level.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:33:56 by tmatis            #+#    #+#             */
/*   Updated: 2021/06/23 18:36:37 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

static int	btree_level_count(t_btree *root)
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

static void	apply_level(t_btree *root, int target_level, int current_level,
				void (*applyf)(void *item, int current_level, int is_first_elem))
{
	if (root && current_level <= target_level)
	{
		apply_level(root->left, target_level, current_level + 1, applyf);
		if (current_level == target_level)
			applyf(root->item, current_level, current_level == 0);
		apply_level(root->right, target_level, current_level + 1, applyf);
	}
}


void	btree_apply_by_level(t_btree *root, void (*applyf)(void *item, int current_level, int is_first_elem))
{
	int	tree_size;
	int	target_level;

	tree_size = btree_level_count(root);
	target_level = 0;
	while (target_level <= tree_size)
	{
		apply_level(root, target_level, 0, applyf);
		target_level++;
	}
}
