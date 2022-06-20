/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:19:42 by mbrija            #+#    #+#             */
/*   Updated: 2022/06/04 13:47:49 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../vector/vector.hpp"

namespace ft
{
    template <class T, class Container = ft::Vector<T> >
class Stack
{
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;
	
	private:
		template<typename U, typename C>
		friend bool operator==(const Stack<U,C>& lhs, const Stack<U,C>& rhs);
		template<typename U, typename C>
		friend bool operator!=(const Stack<U,C>& lhs, const Stack<U,C>& rhs);
		template<typename U, typename C>
		friend bool operator<(const Stack<U,C>& lhs, const Stack<U,C>& rhs);
		template<typename U, typename C>
		friend bool operator<=(const Stack<U,C>& lhs, const Stack<U,C>& rhs);
		template<typename U, typename C>
		friend bool operator>(const Stack<U,C>& lhs, const Stack<U,C>& rhs);
		template<typename U, typename C>
		friend bool operator>=(const Stack<U,C>& lhs, const Stack<U,C>& rhs);
	protected:
		container_type c;
	
	public:
		explicit Stack (const container_type& ctnr = container_type()) : c(ctnr) {}
		~Stack() { c.clear(); }

		bool empty() const { return c.empty(); }
		size_type size() const { return c.size(); }
		value_type& top() { return c.back(); }
		const value_type& top() const { return c.back(); }
		void push (const value_type& val) { c.push_back(val); }
		void pop() { c.pop_back(); }
};
//   end of stack class

template <class T, class Container>
  bool operator== (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
  {
	return lhs.c == rhs.c;
  }
template <class T, class Container>
  bool operator!= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
  {
	return lhs.c != rhs.c;
  }
template <class T, class Container>
  bool operator<  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
  {
	return lhs.c < rhs.c;
  }
template <class T, class Container>
  bool operator<= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
  {
	return lhs.c <= rhs.c;
  }
template <class T, class Container>
  bool operator>  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
  {
	return lhs.c > rhs.c;
  }
template <class T, class Container>
  bool operator>= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
  {
	return lhs.c >= rhs.c;
  }

}