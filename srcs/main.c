/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 12:35:25 by tmatis            #+#    #+#             */
/*   Updated: 2021/06/23 13:23:21 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "assert/assert.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

t_btree	*generate_tree(void)
{
	t_btree *root = NULL;

	btree_insert_data(&root, "e", (int (*)(void *, void *))strcmp);
	btree_insert_data(&root, "c", (int (*)(void *, void *))strcmp);
	btree_insert_data(&root, "a", (int (*)(void *, void *))strcmp);
	btree_insert_data(&root, "f", (int (*)(void *, void *))strcmp);
	return (root);
}

void	free_tree(t_btree *root)
{
	if (root)
	{
		free_tree(root->left);
		free_tree(root->right);
		free(root);
	}
}

void	write_node(void *item)
{
	dprintf(STDOUT_FILENO, "%s", (char *)item);
}

int	redirect_out(int *backup)
{
	int	tube[2];

	if (pipe(tube) < 0)
		printf("pipe error\n");
	*backup = dup(STDOUT_FILENO);
	if (backup < 0)
		exit(1);
	dup2(tube[1], STDOUT_FILENO);
	close(tube[1]);
	return (tube[0]);
}

void	test_ex00(t_tests *tester)
{
	t_btree *node = btree_create_node("my text in node");
	ft_assert(node != NULL, "ex00: node allocation", tester);
	if (!node)
		return ;
	ft_assert_strcmp(node->item, "my text in node", "ex00: content", tester);
	ft_assert(node->left == NULL, "ex00: left is null", tester);
	ft_assert(node->right == NULL, "ex00: right is null", tester);
	free(node);
}

void	test_ex01(t_tests *tester)
{
	int		backup_fd;
	int		read_fd;
	char	buff[200];
	int		read_size;
	t_btree *root = generate_tree();

	read_fd = redirect_out(&backup_fd);
	btree_apply_prefix(root, write_node);
	read_size = read(read_fd, buff, sizeof(buff));
	close(read_fd);
	close(STDOUT_FILENO);
	dup2(backup_fd, STDOUT_FILENO);
	close(backup_fd);
	buff[read_size] = 0;
	ft_assert_strcmp(buff, "ecaf", "ex01 Check prefix order", tester);
	free_tree(root);
}

void	test_ex02(t_tests *tester)
{
	int		backup_fd;
	int		read_fd;
	char	buff[200];
	int		read_size;
	t_btree *root = generate_tree();

	read_fd = redirect_out(&backup_fd);
	btree_apply_infix(root, write_node);
	read_size = read(read_fd, buff, sizeof(buff));
	close(read_fd);
	close(STDOUT_FILENO);
	dup2(backup_fd, STDOUT_FILENO);
	close(backup_fd);
	buff[read_size] = 0;
	ft_assert_strcmp(buff, "acef", "ex02 Check infix order", tester);
	free_tree(root);
}

void	test_ex03(t_tests *tester)
{
	int		backup_fd;
	int		read_fd;
	char	buff[200];
	int		read_size;
	t_btree *root = generate_tree();

	read_fd = redirect_out(&backup_fd);
	btree_apply_suffix(root, write_node);
	read_size = read(read_fd, buff, sizeof(buff));
	close(read_fd);
	close(STDOUT_FILENO);
	dup2(backup_fd, STDOUT_FILENO);
	close(backup_fd);
	buff[read_size] = 0;
	ft_assert_strcmp(buff, "acfe", "ex03 Check suffix order", tester);
	free_tree(root);
}

void	test_ex04(t_tests *tester)
{
	t_btree *root = NULL;

	btree_insert_data(&root, "c", (int (*)(void *, void *))strcmp);
	btree_insert_data(&root, "b", (int (*)(void *, void *))strcmp);
	ft_assert(root->left != 0, "ex04: test left insert work", tester);
	ft_assert(root->right == 0, "ex04: test left insert is good", tester);
	btree_insert_data(&root, "a", (int (*)(void *, void *))strcmp);
	ft_assert(root->left->left != 0, "ex04: test left lvl 2 insert work", tester);
	btree_insert_data(&root, "d", (int (*)(void *, void *))strcmp);
	ft_assert(root->right != 0, "ex04: test right insert work", tester);
	free_tree(root);
}

void	test_ex05(t_tests *tester)
{
	t_btree	*root = generate_tree();
	void	*elem;

	elem = btree_search_item(root, "e", (int (*)(void *, void *))strcmp);
	ft_assert_strcmp(elem, "e", "ex05: search test", tester);
	elem = btree_search_item(root, "z", (int (*)(void *, void *))strcmp);
	ft_assert(elem == 0, "ex05: not found", tester);
	elem = btree_search_item(root, "f", (int (*)(void *, void *))strcmp);
	ft_assert_strcmp(elem, "f", "ex05: search test", tester);

}

int		main(void)
{
	t_tests tester = init_tester("C13 TEST", 3);
	tests_header(tester);
	test_ex00(&tester);
	test_ex01(&tester);
	test_ex02(&tester);
	test_ex03(&tester);
	test_ex04(&tester);
	test_ex05(&tester);
	tests_result(&tester);
}
