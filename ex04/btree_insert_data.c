/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 12:07:17 by tmatis            #+#    #+#             */
/*   Updated: 2021/06/22 12:29:46 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	btree_insert_data(t_btree **root, void *item,
			int (*cmpf)(void *, void *))
{
	t_btree 	*new;

	if (!(*root))
	{
		new = btree_create_node(item);
		*root = new;
	}
	else
	{
		if (cmpf((*root)->item, (item)) < 0)
			btree_insert_data((&(*root)->left), item, cmpf);
		else
			btree_insert_data((&(*root)->right), item, cmpf);
	}
}