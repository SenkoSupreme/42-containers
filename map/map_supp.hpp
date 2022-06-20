/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_supp.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:51:35 by mbrija            #+#    #+#             */
/*   Updated: 2022/06/04 13:56:24 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "map_node.hpp"


template < class T>
int height(Node<T>* root) {
   int h = 0;

   if (root != NULL) {
    	int l = height(root->get_left());
    	int r = height(root->get_right());
    	int max = std::max(l, r);
    	h = max + 1;
   }
   return h;
}

template < class T>
Node<T>	*most_left(Node<T>* root)
{
	while (root)
	{
		if (!root->get_left())
			break ;
		root = root->get_left();
	}
	return root;
}

template < class T>
Node<T>	*most_right(Node<T>* root)
{
	while (root)
	{
		if (!root->get_right())
			break ;
		root = root->get_right();
	}
	return root;
}

template < class T>
Node<T>	*left_child_occur(Node<T>* node)
{
	Node<T>	*tmp = node;
	node = tmp->get_parent();
	while(node)
	{
		if (node->get_left() == tmp)
			return node;
		tmp = node;
		node = node->get_parent();
	}
	return node;
}

template < class T>
Node<T>	*right_child_occur(Node<T>* node)
{
	Node<T>	*tmp = node;
	node = tmp->get_parent();
	while(node)
	{
		if (node->get_right() == tmp)
			return node;
		tmp = node;
		node = node->get_parent();
	}
	return node;
}

template < class T>
void	set_to_left(Node<T> *parent, Node<T> *child)
{
	parent->set_left(child);
	if (child)
		child->set_parent(parent);
}

template < class T>
void	set_to_right(Node<T> *parent, Node<T> *child)
{
	parent->set_right(child);
	if (child)
		child->set_parent(parent);
}

template < class T>
void	set_to_parent(Node<T> *parent, Node<T> *child, bool left_right)
{
	if (left_right)
		parent->set_right(child);
	else
		parent->set_left(child);
	child->set_parent(parent);
}

template < class T >
void	left_rotate(Node<T> **node)
{
	Node<T> *tmp = *node;
	Node<T> *tmp1 = tmp->get_left();
	if (tmp1->get_right())
		set_to_left(tmp, tmp1->get_right());
	else
		tmp->set_left(NULL);
	if (tmp->get_parent())
	{
		if (tmp == tmp->get_parent()->get_left())
			set_to_parent(tmp->get_parent(), tmp1, false);
		else
			set_to_parent(tmp->get_parent(), tmp1, true);
	}
	else
		tmp1->set_parent(NULL);
	set_to_right(tmp1, tmp);
	tmp->set_l_h(tmp->get_l_h() - 2);
	tmp1->set_r_h(tmp1->get_r_h() + 1);
	*node = tmp1;
}

template < class T >
void	right_rotate(Node<T> **node)
{
	Node<T> *tmp = *node;
	Node<T> *tmp1 = tmp->get_right();
	if (tmp1->get_left())
		set_to_right(tmp, tmp1->get_left());
	else
		tmp->set_right(NULL);
	if (tmp->get_parent())
	{
		if (tmp == tmp->get_parent()->get_left())
			set_to_parent(tmp->get_parent(), tmp1, false);
		else
			set_to_parent(tmp->get_parent(), tmp1, true);
	}
	else
		tmp1->set_parent(NULL);
	set_to_left(tmp1, tmp);
	tmp->set_r_h(tmp->get_r_h() - 2);
	tmp1->set_l_h(tmp1->get_l_h() + 1);
	*node = tmp1;
}

template < class T >
void	right_left_rotate(Node<T> **node)
{
	Node<T> *tmp = *node;
	Node<T> *tmp1 = tmp->get_right()->get_left();
	Node<T> *tmp2 = tmp->get_right();
	if (tmp1->get_left())
		set_to_right(tmp, tmp1->get_left());
	else
		tmp->set_right(NULL);
	if (tmp1->get_right())	
		set_to_left(tmp2, tmp1->get_right());
	else
		tmp2->set_left(NULL);
	if (tmp->get_parent())
	{
		if (tmp == tmp->get_parent()->get_left())
			set_to_parent(tmp->get_parent(), tmp1, false);
		else
			set_to_parent(tmp->get_parent(), tmp1, true);
	}
	else
		tmp1->set_parent(NULL);
	set_to_left(tmp1, tmp);
	set_to_right(tmp1, tmp2);
	tmp1->set_l_h(tmp1->get_l_h() + 1);
	tmp1->set_r_h(tmp1->get_r_h() + 1);
	tmp2->set_l_h(tmp2->get_l_h() - 1);
	tmp->set_r_h(tmp->get_r_h() - 1);
	*node = tmp1;
}

template < class T >
void	left_right_rotate(Node<T> **node) 
{
	Node<T> *tmp = *node;
	Node<T> *tmp1 = tmp->get_left()->get_right();
	Node<T> *tmp2 = tmp->get_left();
	if (tmp1->get_right())
		set_to_left(tmp, tmp1->get_right());
	else
		tmp->set_left(NULL);
	if (tmp1->get_left())
		set_to_right(tmp2, tmp1->get_left());
	else
		tmp2->set_right(NULL);
	if (tmp->get_parent())
	{
		if (tmp == tmp->get_parent()->get_left())
			set_to_parent(tmp->get_parent(), tmp1, false);
		else
			set_to_parent(tmp->get_parent(), tmp1, true);
	}
	else
		tmp1->set_parent(NULL);
	set_to_left(tmp1, tmp2);
	set_to_right(tmp1, tmp);
	tmp1->set_l_h(tmp1->get_l_h() + 1);
	tmp1->set_r_h(tmp1->get_r_h() + 1);
	tmp2->set_r_h(tmp2->get_r_h() - 1);
	tmp->set_l_h(tmp->get_l_h() - 1);
	*node = tmp1;
}

template < class T >
void	rotate(Node<T> **node , std::string &rot)
{
	std::string LL("LL"), RR("RR"), LR("LR"), RL("RL");

	if (rot.empty())
		return ;
	if (rot == LL)
		right_rotate(node);
	else if (rot == RR)
		left_rotate(node);
	else if (rot == LR)
		left_right_rotate(node);
	else if (rot == RL)
		right_left_rotate(node);
	rot.clear();
}


template < class T >
void	calc_height(Node <T>** root, Node <T>* node)
{
	Node<T> *tmp;
	std::string Rotation;
	int l_max = 0, r_max = 0;

	tmp = node->get_parent();
	while (tmp)
	{
		if (tmp->get_left())
			l_max = std::max(tmp->get_left()->get_l_h(), tmp->get_left()->get_r_h());
		if (tmp->get_right())
			r_max = std::max(tmp->get_right()->get_l_h(), tmp->get_right()->get_r_h());
		if (l_max != 0)
			tmp->set_l_h(l_max + 1);
		if (r_max != 0)
			tmp->set_r_h(r_max + 1);
		tmp->set_balance(tmp->get_l_h() - tmp->get_r_h());
		if (tmp->get_balance() > 1 || tmp->get_balance() < -1)
		{
			if (l_max > r_max)
			{
				if (tmp->get_left() && tmp->get_left()->get_left())
					Rotation = "RR";
				else if (tmp->get_left() && tmp->get_left()->get_right())
					Rotation = "LR";
			} else
			{
				if (tmp->get_right() && tmp->get_right()->get_right())
					Rotation = "LL";
				else if (tmp->get_right() && tmp->get_right()->get_left())
				{
					Rotation = "RL";
				}
			}
			if (*root == tmp)
			{
				rotate(root, Rotation);
				tmp = *root;
			}
			else
				rotate(&tmp, Rotation);
			break ;
		}
		tmp = tmp->get_parent();
	}
}
template < class T >
void	calc_after_delete(Node<T>** root, Node<T>* node)
{
	std::string Rotation;
	while (node)
	{
		node->set_balance(node->get_l_h() - node->get_r_h());
		if (node->get_balance() > 1 || node->get_balance() < -1)
		{
			if (node->get_l_h() > node->get_r_h())
			{
				if (node->get_left() && node->get_left()->get_left())
					Rotation = "RR";
				else if (node->get_left() && node->get_left()->get_right())
					Rotation = "LR";
			} else
			{
				if (node->get_right() && node->get_right()->get_right())
					Rotation = "LL";
				else if (node->get_right() && node->get_right()->get_left())
				{
					Rotation = "RL";
				}
			}
			if (*root == node)
			{
				rotate(root, Rotation);
				node = *root;
			}
			else
				rotate(&node, Rotation);
			break ;
		}
		node = node->get_parent();
	}
}