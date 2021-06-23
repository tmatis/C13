/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 12:23:09 by tmatis            #+#    #+#             */
/*   Updated: 2021/06/23 13:23:35 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	*btree_search_item(t_btree *root, void *data_ref, int (*cmpf)(void *, void *))
{
	void	*found;
	
	if (root)
	{
		found = btree_search_item(root->left, data_ref, cmpf);
		if (found)
			return (found);
		if (!cmpf(root->item, data_ref))
			return(root->item);
		found = btree_search_item(root->right, data_ref, cmpf);
		if (found)
			return (found);
	}
	return (0x0);
}
