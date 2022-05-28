/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:29:48 by mbrija            #+#    #+#             */
/*   Updated: 2022/05/28 13:32:42 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "glob_supp.hpp"


namespace ft
{
    template <class iterator>
    class reverse_iterator
    {

    public :
        typedef	iterator	iterator_type;
        typedef typename iterator_traits<iterator>::iterator_category iterator_category;
        typedef typename iterator_traits<iterator>::value_type value_type;
        typedef typename iterator_traits<iterator>::difference_type	difference_type;
        typedef typename iterator_traits<iterator>::pointer	pointer;
        typedef typename iterator_traits<iterator>::reference reference;

    private:
        iterator_type iter;

    public:
        reverse_iterator() : iter() {}
        explicit reverse_iterator(iterator_type it) : iter(it){}
        template <class Iter>
        reverse_iterator (const reverse_iterator<Iter>& rev_it) : iter(rev_it.base()) {}
        template <class Iter>
        reverse_iterator& operator= (const reverse_iterator<Iter>& rev_it)
        {
            iter = rev_it.base();
            return *this;
        }
        iterator_type base() const
        {
            return iter;
        }
        reference	operator*() const
        {
            iterator_type tmp = iter;
            tmp--;
            return *tmp;
        }
        reverse_iterator operator+(difference_type n) 
        {
            return reverse_iterator(iter - n);
        }
        const reverse_iterator operator+(difference_type n) const
        {
            return const_reverse_iterator(iter - n);
        }
        reverse_iterator& operator++()
        {
            iter--;
            return *this;
        }
        reverse_iterator operator++(int) {
            reverse_iterator temp = *this;
            --iter;
            return temp;
        }
        reverse_iterator& operator+= (difference_type n)
        {
            iter -= n;
            return (*this);
        }
        reverse_iterator operator-(difference_type n) const 
        {
            return reverse_iterator(iter + n);
        }
        reverse_iterator operator-=(difference_type n) const
        {
            iter += n;
            return *this;
        }
        reverse_iterator& operator--()
        {
            iter++;
            return *this;
        }
        reverse_iterator  operator--(int)
        {
            reverse_iterator tmp = *this;
            iter++;
            return tmp;
        }
        reverse_iterator& operator-= (difference_type n)
        {
            iter += n;
            return (*this);
        }
        pointer operator->() const {
            return &(operator*());
        }
        reference operator[] (difference_type n)
        {
            return iter[n - 1];
        }

    };

    template <class Iterator>
    bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() == rhs.base());
    }
    template <class Iterator>
    bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() != rhs.base());
    }
    template <class Iterator>
    bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() > rhs.base());
    }
    template <class Iterator>
    bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }
    template <class Iterator>
    bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() < rhs.base());
    }
    template <class Iterator>
    bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }
    template <class Iterator>
    reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
    {
        return reverse_iterator<Iterator> (rev_it.base() - n);
    }
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return rhs.base() - lhs.base();
    }

}