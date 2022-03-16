/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:58:16 by mbrija            #+#    #+#             */
/*   Updated: 2022/03/16 16:16:38 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <deque>

template<
	class T,
	class Allocator = std::allocator<T>
> class vector
{
private:
   
public:
	vector(/* args */){};
	~vector(){};
	vector &operator= (const vector &p){};
	
	// ITERATORS
	/*
	begin
	end
	rbegin
	rend
	*/
   // CAPACITY
	/*
	size
	max_size
	resize
	capacity
	empty
	reserve
	*/
   //ELEMENT ACCESS
   /*
   operator[]
   at
   front
   back
   */
	// MODIFIERS
	/*
	assign
	push_back
	pop_back
	insert
	erase
	swap
	clear
	*/
	// ALLOCATOR
	/*
	get allocator
	*/
	
};
