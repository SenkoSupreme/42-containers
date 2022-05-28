/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_supp.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrija <mbrija@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:28:49 by mbrija            #+#    #+#             */
/*   Updated: 2022/05/28 13:29:28 by mbrija           ###   ########.fr       */
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
}
