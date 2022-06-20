/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:19:52 by mbrija            #+#    #+#             */
/*   Updated: 2022/06/04 13:58:44 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <functional>
#include <iostream>
#include "../global_/glob_supp.hpp"
#include "../global_/reverse_iterator.hpp"
#include "map_supp.hpp"
#include "map_iterator.hpp"
#include "map_node.hpp"


namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
	class map
	{
		public:
			typedef	Key	key_type;
			typedef T	mapped_type;
			typedef pair<const key_type, mapped_type>	value_type;
			typedef	Compare	key_compare;
			class 	value_compare;
			typedef Alloc	allocator_type;
			typedef	typename	allocator_type::reference reference;
			typedef	typename	allocator_type::const_reference const_reference;
			typedef	typename	allocator_type::pointer	pointer;
			typedef	typename	allocator_type::const_pointer	const_pointer;
			typedef ptrdiff_t	difference_type;
			typedef	size_t	size_type;
		
		private:
			typedef Node<value_type> node_type;
			typedef Node<const value_type> const_node_type;
			typedef typename allocator_type::template rebind<node_type>::other _node_alloc_class;
			typedef typename allocator_type::template rebind<const_node_type>::other const_node_alloc_class;
			key_compare _key_compare_copy;
			allocator_type _allocator_copy;
			_node_alloc_class _node_alloc;
			const_node_alloc_class const_node_alloc;
			size_type	_S;
			node_type *_root, *_min, *_max;
		
		public :
			typedef map_iterator< value_type >	iterator;
			typedef map_iterator< const value_type >	const_iterator;
			typedef	ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		private :

			pair<iterator,bool> insert_node (node_type* new_node)
			{
				pair<iterator, bool> ret;
				iterator it;
				if (!_root)
				{
					_root = new_node;
					it = _root;
					ret.first = it;
					ret.second = true;
				}
				else
				{
					node_type *tmp;
					tmp = _root;
					while (tmp)
					{
						if (_key_compare_copy(new_node->value->first, tmp->value->first))
						{
							if (!tmp->get_left())
							{
								set_to_left(tmp, new_node);
								tmp->set_l_h(1);
								it = new_node;
								break ;
							}
							tmp = tmp->get_left();
						}
						else
						{
							if (new_node->value->first == tmp->value->first)
							{
								it = tmp;
								ret.first = it;
								ret.second = false;
								return ret;
							}
							if (!tmp->get_right())
							{
								set_to_right(tmp, new_node);
								tmp->set_r_h(1);
								it = new_node;
								break ;
 							}
							tmp = tmp->get_right();
						}
					}
					ret.first = iterator (new_node);
					calc_height(&_root ,new_node);
					ret.second = true;
				}
				_S++;
				return ret;
			}

			void	delete_node(node_type** root, node_type* node)
			{
				node_type *parent = node->get_parent();
				if (!node->get_left() && !node->get_right()) // Node without child
				{
					if (parent && parent->get_right() == node)
					{
						parent->set_right(NULL);
						parent->set_r_h(parent->get_r_h() - 1);
					}
					else if (parent)
					{
						parent->set_left(NULL);
						parent->set_l_h(parent->get_l_h() - 1);
					}
					else
						*root = NULL;
					_node_alloc.deallocate(node, 1);
					if (parent)
						calc_after_delete(root, parent);
				}
				else if ( (node->get_left() && !node->get_right()) || (!node->get_left() && node->get_right()) ) //Node with only One child
				{
					if (node->get_left())
					{
						if (parent && parent->get_left() == node)
						{
							set_to_left(parent, node->get_left());
							parent->set_l_h(parent->get_l_h() - 1);
						}
						else if (parent)
						{
							set_to_right(parent, node->get_left());
							parent->set_r_h(parent->get_r_h() - 1);
						}
						else
						{
							*root = node->get_left();
							(*root)->set_parent(NULL);
						}
					}
					else
					{
						if (parent && parent->get_left() == node)
						{
							set_to_left(parent, node->get_right());
							parent->set_l_h(parent->get_l_h() - 1);
						}
						else if (parent)
						{
							set_to_right(parent, node->get_right());
							parent->set_r_h(parent->get_r_h() - 1);
						}
						else
						{
							*root = node->get_right();
							(*root)->set_parent(NULL);
						}
					}
					_node_alloc.deallocate(node, 1);
					if (parent)
						calc_after_delete(root, parent);
				}
				else // node with Two childs
				{
					node_type *most_r, *most_r_parent;
					most_r = most_right(node->get_left());
					most_r_parent = most_r->get_parent();
					if (most_r_parent != node)
					{
						set_to_right(most_r_parent, most_r->get_left());
						set_to_left(most_r, node->get_left());
					}
					if (parent && parent->get_left() == node)
					{
						set_to_left(parent, most_r);
						parent->set_l_h(parent->get_l_h() - 1);
					}
					else if (parent)
					{
						set_to_right(parent, most_r);
						parent->set_r_h(parent->get_r_h() - 1);
					}
					set_to_right(most_r, node->get_right());
					_node_alloc.deallocate(node, 1);
					if (parent && most_r_parent == node) //from where need to recalculate the balance
						calc_after_delete(root, most_r);
					else if (parent)
						calc_after_delete(root, most_r_parent);
					else
					{
						most_r->set_parent(NULL);
						*root = most_r;
						calc_after_delete(root, most_left(most_r));
					}
				}
			}

			void insert_from (node_type* here, node_type *new_node)
			{
				if (_key_compare_copy(new_node->value->first, here->value->first)) //MIN
					set_to_left(here, new_node);
				else if (_key_compare_copy(here->value->first, new_node->value->first)) //MAX
					set_to_right(here, new_node);
				calc_height(&_root, new_node);
			}

			node_type* node_with(const key_type &k)
			{
				node_type *tmp = _root;
				while (tmp)
				{
					if (_key_compare_copy(k, tmp->value->first))
						tmp = tmp->get_left();
					else
					{
						if (k == tmp->value->first)
							return tmp;
						tmp = tmp->get_right();
					}
				}
				return tmp;
			}
		
		public :

			explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) :  _key_compare_copy(comp) , _allocator_copy(alloc), _node_alloc(), const_node_alloc(), _S(), _root(), _min(), _max() {}
			
			template <class InputIterator>
  			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :  _key_compare_copy(comp) , _allocator_copy(alloc), _S(), _root(), _min(), _max()
			{
				insert (first, last);
			}
			
			map (const map& x) : _key_compare_copy(x._key_compare_copy), _allocator_copy(x._allocator_copy), _node_alloc(x._node_alloc), const_node_alloc(x.const_node_alloc), _S(), _root(), _min(), _max()
			{ 
				insert(x.begin(),  x.end());
			}

			~map() { clear(); }
				

			map& operator= (const map& x)
			{
				if (_root)
					clear();
				_allocator_copy = x.get_allocator();
				_key_compare_copy = x._key_compare_copy;
				_node_alloc = x._node_alloc;
				const_node_alloc = x.const_node_alloc;
				_min = nullptr;
				_max = nullptr;
				insert(x.begin(), x.end());
				return *this;
			}

			// Iterator / Element Access Operators and Methods
			iterator begin()
			{
				iterator it(most_left(_root));
				return it;
			}
			const_iterator begin() const
			{
				const_node_type* tmp = (const_node_type*) most_left(_root);
				const_iterator it(tmp);
				return it;
			}

			iterator end()
			{
				iterator it(most_right(_root));
				it++;
				return it;
			}
			const_iterator end() const
			{
				const_node_type* tmp = (const_node_type*) most_right(_root);
				const_iterator it(tmp);
				it++;
				return it;
			}

			reverse_iterator rbegin()
			{
				iterator it = end();
				reverse_iterator rit(it);
				return rit;
			}
			const_reverse_iterator rbegin() const
			{
				const_iterator it = end();
				const_reverse_iterator rit(it);
				return rit;
			}

			reverse_iterator rend()
			{
				iterator it = begin();
				reverse_iterator rit(it);
				return rit;
			}
			const_reverse_iterator rend() const
			{
				const_iterator it = begin();
				const_reverse_iterator rit(it);
				return rit;
			}

			bool empty() const {
				if (_S != 0)
					return false;
				return true;
			}
			size_type size() const { return _S; }
			size_type max_size() const { return _allocator_copy.max_size(); }

			mapped_type& operator[] (const key_type& k)
			{
				value_type tmp = ft::make_pair(k, mapped_type());
				pair<iterator, bool> ret = insert(tmp);
				return ret.first->second;
			}


			pair<iterator,bool> insert (const value_type& val)
			{
				pair<iterator, bool> ret;
				try
				{
					pointer tmp = _allocator_copy.allocate(1);
					_allocator_copy.construct(tmp, val);
					node_type *node = _node_alloc.allocate(1);
					_node_alloc.construct(node, tmp);
					if (_min && _key_compare_copy(val.first, _min->value->first))
					{
						_min->set_l_h(1);
						insert_from(_min, node);
						_min = node;
						ret.first = iterator (_min);
						ret.second = true;
						_S++;
					}
					else if (_max && _key_compare_copy(_max->value->first, val.first))
					{
						_max->set_r_h(1);
						insert_from(_max, node);
						_max = node;
						ret.first = iterator (_max);
						ret.second = true;
						_S++;
					}
					else
					{
						ret = insert_node(node);
						if (!ret.second)
						{
							_allocator_copy.destroy(tmp);
							_allocator_copy.deallocate(tmp, 1);
							_node_alloc.deallocate(node, 1);
						}
						if (!_min && !_max)
						{
							_min = node;
							_max = node;
						}
					}
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << std::endl;
				}
				
				return (ret);
			}
			iterator insert (iterator position, const value_type& val)
			{
				iterator it = position;
				try
				{
					pair<iterator, bool> ret;
					pointer tmp = _allocator_copy.allocate(1);
					_allocator_copy.construct(tmp, val);
					node_type *node = _node_alloc.allocate(1);
					_node_alloc.construct(node, tmp);
					ret = insert_node(node);
					if (!ret.second)
					{
						_allocator_copy.destroy(tmp);
						_allocator_copy.deallocate(tmp, 1);
						_node_alloc.deallocate(node, 1);
					}
					it = node;
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << std::endl;
				}
				return it;
			}

			template <class InputIterator>
  			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					insert(*first);
					first++;
				}
			}

			void swap (map& x)
			{
				std::swap(_root, x._root);
				std::swap(_min, x._min);
				std::swap(_max, x._max);
				std::swap(_S, x._S);
				std::swap(_node_alloc, x._node_alloc);
				std::swap(const_node_alloc, x.const_node_alloc);
				std::swap(_allocator_copy, x._allocator_copy);
				std::swap(_key_compare_copy, x._key_compare_copy);
			}

			void clear() {
				while (_root)
				{
					_allocator_copy.destroy(_root->value);
					_allocator_copy.deallocate(_root->value, 1);
					delete_node(&_root, _root);
				}
				_S = 0;
				_min = nullptr;
				_max = nullptr;
			}

			void erase (iterator position)
			{
				if (!_root || position == end())
					return ;
				node_type *tmp;
				if (position->first == _min->value->first)
				{
					tmp = _min;
					if (_min->get_right())
						_min = most_left(_min->get_right());
					else
						_min = _min->get_parent();
					_allocator_copy.destroy(tmp->value);
					_allocator_copy.deallocate(tmp->value, 1);
					delete_node(&_root, tmp);
					_S--;
					return;
				}
				else if (position->first == _max->value->first)
				{
					tmp = _max;
					if (_max->get_left())
						_max = most_right(_max->get_left());
					else
						_max = _max->get_parent();
					_allocator_copy.destroy(tmp->value);
					_allocator_copy.deallocate(tmp->value, 1);
					delete_node(&_root, tmp);
					_S--;
					return;
				}
				node_type* node = node_with(position->first);
				if (node)
				{
					pointer tmp = node->value;
					delete_node(&_root, node);
					_allocator_copy.destroy(tmp);
					_allocator_copy.deallocate(tmp, 1);
					_S--;
				}
			}
			size_type erase (const key_type& k)
			{
				iterator it = find(k);
				if (it != end())
				{
					erase(it);
					return 1;
				}
				return 0;
			}

			void erase (iterator first, iterator last)
			{
				iterator tmp;
				while (first != last)
				{
					tmp = first;
					++first;
					erase(tmp);
				}
			}

			iterator find (const key_type& k)
			{
				node_type *tmp = _root;
				while (tmp)
				{
					if (_key_compare_copy(k, tmp->value->first))
						tmp = tmp->get_left();
					else
					{
						if (k == tmp->value->first)
							return iterator(tmp);
						tmp = tmp->get_right();
					}
				}
				return end();
			}

			key_compare key_comp() const { return _key_compare_copy;}
			value_compare value_comp() const { return value_compare(_key_compare_copy); }

			const_iterator find (const key_type& k) const
			{
				node_type *tmp = _root;
				while (tmp)
				{
					if (_key_compare_copy(k, tmp->value->first))
						tmp = tmp->get_left();
					else
					{
						if (k == tmp->value->first)
						{
							iterator it(tmp);
							return const_iterator(it);
						}
						tmp = tmp->get_right();
					}
				}
				return end();
			}

			size_type count (const key_type& k) const
			{
				const_iterator it = find(k);
				if (it != end())
					return 1;
				return 0;
			}
			iterator lower_bound (const key_type& k)
			{
				if (_min->value->first > k)
					return begin();
				if (_max->value->first < k)
					return end();
				node_type *tmp = _root;
				node_type *ret = NULL;
				while (tmp)
				{
					if (!_key_compare_copy(tmp->value->first, k))
					{
						ret = tmp;
						tmp = tmp->get_left();
					}
					else
						tmp = tmp->get_right();
				}
				return iterator(ret);
			}
			const_iterator lower_bound (const key_type& k) const
			{
				if (_min->value->first > k)
					return begin();
				if (_max->value->first < k)
					return end();
				node_type *ret = NULL;
				node_type *tmp = _root;
				while (tmp)
				{
					if (!_key_compare_copy(tmp->value->first, k))
					{
						ret = tmp;
						tmp = tmp->get_left();
					}
					else
						tmp = tmp->get_right();
				}
				iterator it(ret);
				return const_iterator(it);
			}

			iterator upper_bound (const key_type& k)
			{
				if (_min->value->first > k)
					return begin();
				if (_max->value->first < k)
					return end();
				node_type *tmp = _root;
				iterator it;
				while (tmp)
				{
					if (!_key_compare_copy(tmp->value->first, k))
					{
						it = tmp;
						if (it->first == k)
							return ++it;
						tmp = tmp->get_left();
					}
					else
						tmp = tmp->get_right();
				}
				return it;
			}
			const_iterator upper_bound (const key_type& k) const 
			{
				if (_min->value->first > k)
					return begin();
				if (_max->value->first < k)
					return end();
				node_type *tmp = _root;
				iterator it;
				while (tmp)
				{
					if (!_key_compare_copy(tmp->value->first, k))
					{
						it = tmp;
						if (it->first == k)
							return const_iterator(++it);
						tmp = tmp->get_left();
					}
					else
						tmp = tmp->get_right();
				}
				return const_iterator(it);
			}

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				pair<const_iterator, const_iterator> ret;
				ret.first = lower_bound(k);
				ret.second = upper_bound(k);
				return ret;
			}
			pair<iterator,iterator>             equal_range (const key_type& k)
			{
				pair<iterator, iterator> ret;
				ret.first = lower_bound(k);
				ret.second = upper_bound(k);
				return ret;
			}
			
			allocator_type get_allocator() const { return _allocator_copy; }
	};

	template< class Key, class T, class  Compare, class Alloc >
	class 	map<Key, T, Compare, Alloc >::value_compare
	{
		friend class map;
		protected:
		  Compare comp;
		  value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
		public:
  		typedef bool result_type;
  		typedef value_type first_argument_type;
  		typedef value_type second_argument_type;
  		bool operator() (const value_type& x, const value_type& y) const
  		{
  		  return comp(x.first, y.first);
  		}
	};
	
	template <class Key, class T, class Compare, class Alloc>
	bool operator== ( const ft::map<Key,T,Compare,Alloc>& lhs,
						const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() != lhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class Key, class T, class Compare, class Alloc>
  	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}
	template <class Key, class T, class Compare, class Alloc>
  	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs )
	{
		return !(rhs < lhs);
	}
	template <class Key, class T, class Compare, class Alloc>
  	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}
	template <class Key, class T, class Compare, class Alloc>
  	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
  	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
	}
}