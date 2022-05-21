/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:58:44 by mbrija            #+#    #+#             */
/*   Updated: 2022/05/21 13:02:46 by mbrija           ###   ########.fr       */
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
    template <typename V>
    Iterator &operator= (const Iterator<V> &p)
    {
        ptr = p.base();
        return *this;
    }
    template <typename V>
    Iterator &operator= (const Iterator<V> &p) const
    {
        Iterator i(it);
        return i;
    }
    ~Iterator() {}

    /** Comparision **/
    template <typename V>
	bool operator==(const Iterator<V> &it)
	{
		if (this->ptr == it.base())
			return true;
		return false;
	}
	template <typename V>
	bool operator!=(const Iterator<V> &it)
	{
		if (this->ptr != it.base())
			return true;
		return false;
	}
	template <typename V>
	bool operator<(const Iterator<V> &it)
	{
		if (this->ptr < it.base())
			return true;
		return false;
	}
	template <typename V>
	bool operator>(const Iterator<V> &it)
	{
		if (this->ptr > it.base())
			return true;
		return false;
	}
	template <typename V>
	bool operator>=(const Iterator<V> &it)
	{
		if (this->ptr >= it.base())
			return true;
		return false;
	}
	template <typename V>
	bool operator<=(const Iterator<V> &it)
	{
		if (this->ptr <= it.base())
			return true;
		return false;
	}

    /** Overloading Comparision OPs to Accept consts **/
    template <typename V>
	bool operator==(const Iterator<V> &it) const
	{
		if (this->ptr == it.base())
			return true;
		return false;
	}
	template <typename V>
	bool operator!=(const Iterator<V> &it) const
	{
		if (this->ptr != it.base())
			return true;
		return false;
	}
	template <typename V>
	bool operator<(const Iterator<V> &it) const
	{
		if (this->ptr < it.base())
			return true;
		return false;
	}
	template <typename V>
	bool operator>(const Iterator<V> &it) const
	{
		if (this->ptr > it.base())
			return true;
		return false;
	}
	template <typename V>
	bool operator>=(const Iterator<V> &it) const
	{
		if (this->ptr >= it.base())
			return true;
		return false;
	}
	template <typename V>
	bool operator<=(const Iterator<V> &it) const
	{
		if (this->ptr <= it.base())
			return true;
		return false;
	}

    /** Dereferencing **/
    reference operator*() { return *ptr; }
	reference operator*() const { return *ptr; }

	void operator*(T ptr_val) { *ptr = ptr_val; }
	pointer operator->() { return ptr; }
	pointer operator->() const { return ptr; }
    
    /**Post and Pre incrementing**/
    Iterator &operator++()
	{
		ptr++;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator tmp;
		tmp = *this;
		this->ptr++;
		return (tmp);
	}
	Iterator &operator--()
	{
		this->ptr--;
		return *this;
	}
	Iterator operator--(int)
	{
		Iterator tmp;
		tmp = *this;
		this->ptr--;
		return (tmp);
	}
    
    /**Basic Arithmtic OPs **/
    Iterator operator+(dif_type n)
	{
		Iterator tmp = *this;
		tmp += n;
		return tmp;
	}
	const Iterator operator+(dif_type n) const
	{
		Iterator tmp = *this;
		tmp += n;
		return tmp;
	}
	Iterator operator-(dif_type n)
	{
		Iterator tmp = *this;
		tmp -= n;
		return tmp;
	}
	const Iterator operator-(dif_type n) const
	{
		Iterator tmp = *this;
		tmp -= n;
		return tmp;
	}
	dif_type operator-(const Iterator &it)
	{
		return ptr - it.ptr;
	}

	Iterator &operator+=(dif_type n)
	{
		ptr += n;
		return (*this);
	}
	Iterator operator+=(dif_type n) const
	{
		Iterator iter = *this;
		iter += n;
		return (iter);
	}
	Iterator &operator-=(dif_type n)
	{
		ptr -= n;
		return (*this);
	}
	Iterator operator-=(dif_type n) const
	{
		Iterator iter = *this;
		iter -= n;
		return (iter);
	}
	reference operator[](dif_type n)
	{
		return ptr[n];
	}
	const T& operator[](dif_type n) const
	{
		return ptr[n];
	}
    
    template<typename V>
    Iterator<V>	operator+(ptrdiff_t n, const Iterator<V> &it)
    {
        return it + n;
    }

    template<typename V>
    Iterator<V>	operator-(ptrdiff_t n, const Iterator<V> &it)
    {
        return it - n;
    }
    
};
