/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:58:44 by mbrija            #+#    #+#             */
/*   Updated: 2022/05/19 18:49:07 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <algorithm> 

template <class T>
class Iterator
{
public:
    typedef T value_type;
    typedef ptrdiff_t dif_type;
    typedef T* pointer;
    typedef T& reference;
    typedef typename std::random_access_iterator_tag iterator_category;
    
private:
    /* data */
    pointer ptr;

public:
    Iterator(/* args */) : ptr() {}
    Iterator(pointer p) : ptr(p) {}
    const value_type*	base() const
	{
		return ptr;
	}
	value_type*	base()
	{
		return ptr;
	}
    template <typename S>
    Iterator &operator= (const Iterator<S> &p)
    {
        ptr = p.base();
        return *this;
    }
    template <typename S>
    Iterator &operator= (const Iterator<S> &p) const
    {
        Iterator i(it);
        return i;
    }
    ~Iterator() {}


    /** Comparision **/
    template <typename S>
	bool operator==(const Iterator<S> &it)
	{
		if (this->ptr == it.base())
			return true;
		return false;
	}
	template <typename S>
	bool operator!=(const Iterator<S> &it)
	{
		if (this->ptr != it.base())
			return true;
		return false;
	}
	template <typename S>
	bool operator<(const Iterator<S> &it)
	{
		if (this->ptr < it.base())
			return true;
		return false;
	}
	template <typename S>
	bool operator>(const Iterator<S> &it)
	{
		if (this->ptr > it.base())
			return true;
		return false;
	}
	template <typename S>
	bool operator>=(const Iterator<S> &it)
	{
		if (this->ptr >= it.base())
			return true;
		return false;
	}
	template <typename S>
	bool operator<=(const Iterator<S> &it)
	{
		if (this->ptr <= it.base())
			return true;
		return false;
	}

    /** Overloading Comparision OPs to Accept consts **/
    template <typename S>
	bool operator==(const Iterator<S> &it) const
	{
		if (this->ptr == it.base())
			return true;
		return false;
	}
	template <typename S>
	bool operator!=(const Iterator<S> &it) const
	{
		if (this->ptr != it.base())
			return true;
		return false;
	}
	template <typename S>
	bool operator<(const Iterator<S> &it) const
	{
		if (this->ptr < it.base())
			return true;
		return false;
	}
	template <typename S>
	bool operator>(const Iterator<S> &it) const
	{
		if (this->ptr > it.base())
			return true;
		return false;
	}
	template <typename S>
	bool operator>=(const Iterator<S> &it) const
	{
		if (this->ptr >= it.base())
			return true;
		return false;
	}
	template <typename S>
	bool operator<=(const Iterator<S> &it) const
	{
		if (this->ptr <= it.base())
			return true;
		return false;
	}

    /** next**/
    
};
