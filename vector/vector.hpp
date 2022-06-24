/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:58:16 by mbrija            #+#    #+#             */
/*   Updated: 2022/06/04 13:19:42 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "../global_/glob_supp.hpp"
#include "../global_/reverse_iterator.hpp"
#include "iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class Vector
	{
		public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
	
	private:
		pointer _buffer;
		size_type _S;
		size_type _C;
		allocator_type allocator_copy;
		ft::Iterator<T> iter;


	public:
		typedef Iterator<value_type> iterator;
		typedef Iterator<const value_type> const_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		//things are looking clearer
		explicit Vector(const allocator_type &alloc = allocator_type()) : _buffer(), _S(), _C(), allocator_copy(alloc) {}
		explicit Vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _buffer(), _S(n), _C(n), allocator_copy(alloc)
		{
			try
			{
			_buffer = allocator_copy.allocate(n);
			for (size_type i = 0; i < n; i++)
				allocator_copy.construct(&_buffer[i], val);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
			
		}
		
		template <class InputIterator>
		Vector  (InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename enable_if<!(is_integral<InputIterator>::value), int>::type = 0)
		: _buffer(), _S(), _C(),allocator_copy (alloc)
		{
			assign(first, last);
		}
		
		Vector(const Vector &x) : _buffer(), _S(), _C(), allocator_copy(x.allocator_copy)
		{
			*this = x;
		}
		~Vector()
		{
			if (_buffer)
			{
				for (iterator it = begin(); it != end(); it++)
					allocator_copy.destroy(it.base());
				allocator_copy.deallocate(_buffer, _C);
			}
		}

		Vector& operator= (const Vector& x)
		{
			try
			{
				if (_buffer)
				{
					size_type i = 0;
					for (iterator it = begin(); it != this->end(); it++)
					{
						allocator_copy.destroy(it.base());
						i++;
					}
					allocator_copy.deallocate(_buffer, _C);
					_buffer = NULL;
				}
				_S = x.size();
				_C = x.capacity();
				allocator_copy = x.get_allocator();
				if (_C == 0)
					return *this;
				_buffer = allocator_copy.allocate(_C);
				size_type i = 0;
				const_iterator it = x.begin();
				while (it != x.end())
				{
					allocator_copy.construct(&(_buffer[i++]), *it);
					it++;
				}	
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
			
			return *this;
		}


		// Iterator Methods
		iterator begin()
		{
			return iterator (_buffer);
		}
		const_iterator begin() const
		{
			return const_iterator(_buffer);
		}
		iterator end()
		{
			return iterator (&_buffer[_S]);
		}
		const_iterator end() const
		{
			return const_iterator(&_buffer[_S]);
		}
		

		// Reverse Iterator rbegin() and rend()
		reverse_iterator rbegin()
		{
			iterator it(end());
			return reverse_iterator (it);
		}
		const_reverse_iterator rbegin() const
		{
			const_iterator it(end());
			return const_reverse_iterator(it);
		}
		reverse_iterator rend()
		{
			iterator it(begin());
			
			return reverse_iterator (it);
		}
		const_reverse_iterator rend() const
		{
			const_iterator it(begin());
			return const_reverse_iterator (it);
		}


		// Size and Capacity
		size_type size() const { return _S; }

		size_type max_size() const { return allocator_copy.max_size(); }

		void resize (size_type n, value_type val = value_type())
		{
			if (n < _S)
			{
				for(; _S > n;)
					pop_back();
			}
			else
				insert(end(), n - _S, val);
		}

		size_type capacity() const
		{
			return _C;
		}

		bool empty() const
		{
			return !(_S);
		}

		void	reserve(size_type n)
		{
			if (n > max_size())
				throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
			if (n > _C)
			{
				try
				{
					pointer tmp;
					tmp = allocator_copy.allocate(n);
					iterator it = this->begin();
					size_type i = 0;
					while(it != this->end())
					{
						allocator_copy.construct(&(tmp[i]), *it);
						allocator_copy.destroy(&(_buffer[i]));
						i++;
						it++;
					}
					allocator_copy.deallocate(_buffer, _C);
					_buffer = tmp;
					_C = n;
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << std::endl;
				}
			}
		}


		// Element Access Operators and Methods
		reference operator[] (size_type n)
		{
			return _buffer[n];
		}
		const_reference operator[] (size_type n) const
		{
			return _buffer[n];
		}

		reference at (size_type n)
		{
			if (n >= _S)
				throw std::out_of_range("Vector");
			return _buffer[n];
		}
		const_reference at (size_type n) const
		{
			if (n >= _S)
				throw std::out_of_range("Vector");
			return _buffer[n];
		}

		reference front()
		{
			return _buffer[0];
		}
		const_reference front() const
		{
			return _buffer[0];
		}
		reference back()
		{
			return _buffer[_S - 1];
		}
		const_reference back() const
		{
			return _buffer[_S - 1];
		}


		// Modifiers Methods
		template <class InputIterator>
  		void assign (InputIterator first, InputIterator last, typename enable_if<!(is_integral<InputIterator>::value), int>::type = 0)
		{
			_S = 0;
			typedef typename iterator_traits<InputIterator>::iterator_category category;
			if (typeid(category()) != typeid(std::random_access_iterator_tag()) && typeid(category()) != typeid(std::bidirectional_iterator_tag()))
			{
				while (first != last)
				{
					push_back(*first);
					first++;
				}
			}
			else
			{
				try
				{
					InputIterator tmp = first;
					size_type c = 0;
					while(tmp != last)
					{
						c++;
						tmp++;
					}
					if (c > _C)
					{
						for (size_t i = 0; i < _C; i++)
							allocator_copy.destroy(&(_buffer[i]));
						allocator_copy.deallocate(_buffer, _C);
						_C = c;
						_buffer = allocator_copy.allocate(_C);
					}
					while (c <= _C && first != last)
					{
						push_back(*first);
						first++;
					}
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << std::endl;
				}

			}
		}
		void assign (size_type n, const value_type& val)
		{
			try
			{
				_S = 0;
				size_type i = 0;
				if (n > _C)
				{
					for (size_t i = 0; i < _C; i++)
						allocator_copy.destroy(&(_buffer[i]));
					allocator_copy.deallocate(_buffer, _C);
					_C = n;
					_buffer = allocator_copy.allocate(_C);
				}
				while (i < n)
				{
					push_back(val);
					i++;
				}
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
			
		}

		void	push_back(const value_type& val)
		{
			if (_S == 0 && _C == 0)
			{
				try
				{
					_buffer = allocator_copy.allocate(1);
					allocator_copy.construct(&(_buffer[0]), val);
					_S = 1;
					_C = 1;
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << std::endl;
				}
			}
			else if (_C > _S)
			{
				allocator_copy.construct(&(_buffer[_S]), val);
				_S++;
			}
			else
			{
				try
				{
					pointer tmp;
					tmp = allocator_copy.allocate((_C * 2));
					iterator it = this->begin();
					size_type i = 0;
					while(it != this->end())
					{
						allocator_copy.construct(&(tmp[i]), *it);
						allocator_copy.destroy(&(_buffer[i]));
						i++;
						it++;
					}
					allocator_copy.deallocate(_buffer, _C);
					_buffer = tmp;
					_C *= 2;
					_S++;
					allocator_copy.construct(&(_buffer[i]),val);
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << std::endl;
				}
			}
		}

		void	pop_back()
		{
			allocator_copy.destroy(&(_buffer[_S - 1]));
			_S--;
		}

		iterator insert (iterator position, const value_type& val)
		{
			if (_S == 0)
			{
				push_back(val);
				return begin();
			}
			if (_C == _S)
			{
				size_type i = position - begin();
				reserve(_C * 2);
				position = begin() + i;
			}
			push_back(val);
			iterator ite = end();
			iterator tmp, tmp1;
			ite--;
			while(ite != position)
			{
				tmp = ite;
				tmp1 = tmp - 1;
				std::swap(*tmp, *tmp1);
				ite--;
			}
			return position;
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			Vector tmp;

			if (_S + n <= _C)
			{
				tmp.assign(position, end());
				for (iterator it = position; it != end(); it++)
					allocator_copy.destroy(it.base());
				for (size_t i = 0; i < n; i++)
				{
					allocator_copy.construct(position.base(), val);
					position++;
				}
				for (iterator it = tmp.begin(); it != tmp.end(); it++)
				{
					allocator_copy.construct(position.base(), *it);
					position++;
				}
				_S += n;
				return;
			}
			else if (_S + n <= _C * 2)
				tmp.reserve(_C * 2);
			else if (_S + n > _C * 2)
				tmp.reserve(_S + n);
			tmp.assign(begin(), position);
			while (n--)
				tmp.push_back(val);
			while (position != end())
			{
				tmp.push_back(*position);
				position++;
			}
			swap(tmp);
		}

		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last, typename enable_if<!(is_integral<InputIterator>::value), int>::type = 0)
		{
			Vector tmp(first, last), tmp2;

			if (tmp.size() == 0)
				return;
			if (tmp.size() + _S <= _C)
			{
				tmp2.assign(position, end());
				iterator it = tmp.begin();
				for (iterator it = position; it != end(); it++)
					allocator_copy.destroy(it.base());
				for (iterator it = tmp.begin(); it != tmp.end(); it++)
				{
					allocator_copy.construct(position.base(), *it);
					position++;
				}
				for (iterator it = tmp2.begin(); it != tmp2.end(); it++)
				{
					allocator_copy.construct(position.base(), *it);
					position++;
				}
				_S += tmp.size();
				return;
			}
			else if (_S + tmp.size() <= _C * 2)
				tmp2.reserve(_C * 2);
			else if (_S + tmp.size() > _C * 2)
				tmp2.reserve(_S + tmp.size());
			tmp2.assign(begin(), position);
			size_type n = tmp.size();
			iterator it = tmp.begin();
			while (n--)
				tmp2.push_back(*(it++));
			while (position != end())
			{
				tmp2.push_back(*position);
				position++;
			}
			swap(tmp2);
		}

		iterator erase (iterator position)
		{
			iterator ret = position;
			iterator e = end();
			while (position != e)
			{
				if ((position + 1) != e)
					std::swap(*position, *(position + 1));
				position++;
			}
			e--;
			allocator_copy.destroy(e.base());
			_S--;
			return ret;
		}
		iterator erase (iterator first, iterator last)
		{
			iterator save_first = first;
			iterator ret = first;
			size_type diff = last - first;
			while (save_first != last)
			{
				allocator_copy.destroy(&(*save_first));
				save_first++;
			}
			while (save_first != end())
			{
				*first = *save_first;
				allocator_copy.destroy(&(*save_first));
				save_first++;
				first++;
			}
			_S -= diff;
			return ret;
		}

		void swap (Vector& x)
		{
			std::swap(_S, x._S);
			std::swap(_C, x._C);
			std::swap(_buffer, x._buffer);
			std::swap(allocator_copy, x.allocator_copy);
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				allocator_copy.destroy(it.base());
				it++;
			}
			_S = 0;
		}
		
		allocator_type get_allocator() const
		{
			return Alloc();
		}
	};
	// end of Vector class

	
	template <class T, class Alloc>
  	bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	  	return false;
	}

	template <class T, class Alloc>
  	bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
			return !(ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		return true;
	}

	template <class T, class Alloc>
  	bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
  	bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
  	bool operator>  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Alloc>
  	bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
	{
		return !(rhs > lhs);
	}

	template <class T, class Alloc>
  	void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y)
	{
		x.swap(y);
	}
	
}