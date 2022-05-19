/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:58:44 by mbrija            #+#    #+#             */
/*   Updated: 2022/05/19 12:34:14 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <algorithm> 

template <class T>
class iterator
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

Public:
    iterator(/* args */) : ptr();
    iterator(pointer p) : ptr(p);
    template <typename S>
    iterator &operator= (const iterator<S> &p)
    {
        
    }
    ~iterator();
    
};
