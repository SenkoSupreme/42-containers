/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:58:16 by mbrija            #+#    #+#             */
/*   Updated: 2022/05/28 13:35:58 by mbrija           ###   ########.fr       */
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
	class vector
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
	};
}