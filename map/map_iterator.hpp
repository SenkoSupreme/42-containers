/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:52:15 by mbrija            #+#    #+#             */
/*   Updated: 2022/06/04 13:58:44 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "map_node.hpp"

template <class T>
class map_iterator 
{
	public:
		typedef T	value_type;
		typedef ptrdiff_t	difference_type;
		typedef T* pointer;
		typedef T&	reference;
		typedef typename std::bidirectional_iterator_tag	iterator_category;

	private:
		typedef Node<value_type>*	node_ptr;
		node_ptr _node;
		node_ptr _copy;
	
	public:
		map_iterator() : _node(), _copy() {}
		map_iterator(node_ptr ptr) : _node(ptr) ,  _copy(){}
		map_iterator(node_ptr ptr, node_ptr cop) : _node(ptr) ,  _copy(cop){}
		map_iterator(const map_iterator &i) : _node(i._node), _copy(i._copy) {}
		operator map_iterator<const T>() {
			Node< const T >*ptr = (Node <const T>*)_node;
			Node< const T >*cop = (Node <const T>*)_copy;
			map_iterator <const T> ret(ptr, cop);
			return ret; 
		}

		map_iterator &operator=(const map_iterator &i)
		{
			_node = i._node;
			_copy = i._copy;
			return *this;
		}
		map_iterator &operator=(const node_ptr i)
		{
			_node = i;
			return *this;
		}
		~map_iterator () {}

		pointer	base() { return _node->value; }

		// comparison overloads
		bool operator==(const map_iterator& x)
		{
			if (_node == x._node)
				return true;
			return false;
		}
		bool operator!=(const map_iterator& x)
		{
			if (_node != x._node)
				return true;
			return false;
		}

		// Dereferencing overloads
		reference	operator*() { return *(_node->value); }
		pointer	operator->() const { return _node->value; }

		//incrementation overloads

		map_iterator &operator++()
		{
			node_ptr tmp = _node;
			if (!_node)
			{
				_node = _copy;
				_copy = NULL;
				return *this;
			}
			if (_node->get_right())
				_node = most_left(_node->get_right());
			else if (_node->get_parent() && _node->get_parent()->get_left() == _node)
				_node = _node->get_parent();
			else
				_node = left_child_occur(_node);
			if (!_node && !_copy)
				_copy = tmp;
			return *this;
		}
		map_iterator operator++(int)
		{
			map_iterator tmp(*this);
			++(*this);
			return tmp;
		}

		// decrementation overloads

		map_iterator &operator--()
		{
			node_ptr tmp = _node;
			if (!_node)
			{
				_node = _copy;
				_copy = NULL;
				return *this;
			}
			else if (_node->get_left())
				_node = most_right(_node->get_left());
			else if (_node->get_parent() && _node->get_parent()->get_right() == _node)
				_node = _node->get_parent();
			else
				_node = right_child_occur(_node);
			if (!_node && !_copy)
				_copy = tmp;
			return *this;
		}
		map_iterator operator--(int)
		{
			map_iterator tmp(*this);
			--(*this);
			return tmp;
		}
};

