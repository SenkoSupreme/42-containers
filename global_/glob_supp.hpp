/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_supp.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:28:49 by mbrija            #+#    #+#             */
/*   Updated: 2022/06/04 13:46:34 by mbrija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


namespace ft
{

    template <class Iterator>
    class iterator_traits
    {
        public :
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };
    
    template <class T>
    class iterator_traits<T*>
    {
        public :
        typedef ptrdiff_t						difference_type;
        typedef T								value_type;
        typedef T*								pointer;
        typedef T&								reference;
        typedef std::random_access_iterator_tag	iterator_category;
    };
    template <class T>
    class iterator_traits<const T*>
    {
        public :
        typedef const ptrdiff_t							difference_type;
        typedef const T									value_type;
        typedef const T*								pointer;
        typedef const T&								reference;
        typedef const std::random_access_iterator_tag	iterator_category;
    };
    
    //enable_if and is_integral 
    template<bool Cond, class T = void> struct enable_if {};
    template<class T>
    struct enable_if<true, T>{ typedef T type; };

    template <class T>
    struct is_integral {
        static const bool value = false;
        typedef T value_type;
        typedef T type;
        operator value_type() const { return value; }
    };
    template <>
    struct is_integral <bool>{
        static const bool value = true;
        typedef bool value_type;
        typedef bool type;
        operator value_type() { return value; }
    };
    template <>
    struct is_integral <char> {
        static const bool value = true;
        typedef bool value_type;
        typedef char type;
        operator value_type() { return value; }
    };
    template <>
    struct is_integral <char16_t> {
        static const bool value = true;
        typedef bool value_type;
        typedef char16_t type;
        operator value_type() { return value; }
    };
    template <>
    struct is_integral <char32_t> {
        static const bool value = true;
        typedef bool value_type;
        typedef char32_t type;
        operator value_type() { return value; }
    };
    template <>
    struct is_integral<wchar_t> {
        static const bool value = true;
        typedef bool value_type;
        typedef wchar_t type;
        operator value_type() { return value; }
    };
    template <>
    struct is_integral<signed char> {
        static const bool value = true;
        typedef bool value_type;
        typedef signed char type;
        operator value_type() { return value; }
    };
    template <>
    struct is_integral <short int> {
        static const bool value = true;
        typedef bool value_type;
        typedef short int type;
        operator value_type() { return value; }
    };
    template <>
    struct is_integral <int> {
        static const bool value = true;
        typedef bool value_type;
        typedef int type;
        operator value_type() { return value; }
    };
    template <>
    struct is_integral <long int>{
        static const bool value = true;
        typedef bool value_type;
        typedef long int type;
        operator value_type() { return value; }
    };
    template <>
    struct is_integral <long long int>{
        static const bool value = true;
        typedef bool value_type;
        typedef long long int type;
        operator value_type() { return value; }
    };
    template <>
    struct is_integral <unsigned char> {
        static const bool value = true;
        typedef bool value_type;
        typedef unsigned char type;
        operator value_type() { return value; }
    };
    template <>
    struct is_integral <unsigned short int> {
        static const bool value = true;
        typedef bool value_type;
        typedef unsigned short int type;
        operator value_type() { return value; }
    };
    template <>
    struct is_integral <unsigned int> {
        static const bool value = true;
        typedef bool value_type;
        typedef unsigned int type;
        operator value_type() { return value; }
    };
    template <>
    struct is_integral <unsigned long int> {
        static const bool value = true;
        typedef bool value_type;
        typedef unsigned long int type;
        operator value_type() { return value; }
    };
    template <>
    struct is_integral <unsigned long long int> {
        static const bool value = true;
        typedef bool value_type;
        typedef unsigned long long int type;
        operator value_type() { return value; }
    };

    //lexicraphic compare
    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                    InputIterator2 first2, InputIterator2 last2)
    {
        while (first1!=last1)
        {
            if (first2 == last2 || *first2 < *first1)
                return false;
            else if (*first1 < *first2)
                return true;
            ++first1;
            ++first2;
        }
        return (first2!=last2);
    }
    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                    InputIterator2 first2, InputIterator2 last2,
                                    Compare comp)
    {
        while ((first1 != last1) && (first2 != last2))
        {
            if (comp(*first1, *first2))
                return true;
            if (comp(*first2, *first1))
                return false;
            ++first1;
            ++first2;
        }
        return (first1 == last1) && (first2 != last2);
    }
        
    template <class InputIterator1, class InputIterator2>
    bool equal (InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2)
    {
        while(first1 != last1)
        {
            if (!(*first1 == *first2))
                return false;
            first1++;
            first2++;
        }
        return true;
    }
    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal (InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, BinaryPredicate pred)
    {
        while (first1 != last1)
        {
            if (!(pred(*first1, *first2)))
                return false;
            first1++;
            first2++;
        }
        return true;
    }
    
    // PAIR
    template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;

        pair() : first(), second() {}
        template<class U, class V>
        pair(const pair <U,V>&pr) : first(pr.first) , second(pr.second){}
        pair(const first_type &a, const second_type &b) : first(a) , second(b){}
    };
    //end of iterator traits class

    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first==rhs.first && lhs.second==rhs.second; }

    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs==rhs); }

    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(rhs<lhs); }

    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return rhs<lhs; }

    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs<rhs); }

    template <class T1,class T2>
    pair<T1,T2> make_pair (T1 x, T2 y)
    {
        return ( pair<T1,T2>(x,y) );
    }
}

//somtimes i wonder if any of this is really needed, that was just too much writing and copying.
