/*
** EPITECH PROJECT, 2020
** CastHelper.hpp
** File description:
** header for CastHelper.c
*/


#pragma once

#include <type_traits>
#include <valarray>

namespace polymorph::engine::config
{

    class CastHelper
    {
        public:
            template<class ...>
            using void_t = void;

            template<class T, class = void>
            struct is_container : std::false_type
            {
            };

            template<class T>
            struct is_container<T, void_t<decltype(std::begin(
                    std::declval<T>())), decltype(std::end(std::declval<T>()))>>
                    : std::true_type
            {
            };

            template<class T>
            static constexpr auto is_vector = CastHelper::is_container<T>::value;



            template<class T, typename U = int>
            struct is_builtinish : std::false_type
            {
            };

            template<class T>
            struct is_builtinish<T, decltype(T::builtin_type, 0)>
                    : std::true_type
            {
            };

            template<class T>
            static constexpr auto is_builtin = CastHelper::is_builtinish<T>::value;




            template<typename T, typename U = void>
            struct is_mappish_impl : std::false_type
            {
            };

            template<typename T>
            struct is_mappish_impl<T,
                    void_t
                            <
                                    typename T::key_type,
                                    typename T::mapped_type,
                                    decltype(std::declval<T &>()[std::declval<const typename T::key_type &>()])
                            >>
                    : std::true_type
            {
            };
            template<typename T>
            static constexpr auto is_map = CastHelper::is_mappish_impl<T>::value;

            template<typename T, typename U = void>
            struct is_shp_impl : std::false_type
            {
            };

            template<typename T>
            struct is_shp_impl<T,
                    void_t<decltype(&T::operator*), decltype(&T::operator->)>
            >
                    : std::true_type
            {
            };
            template<typename T>
            static constexpr auto is_sharedptr = CastHelper::is_shp_impl<T>::value;

            template<typename T, typename U = void>
            struct is_sp_impl : std::false_type
            {
            };

            template<typename T>
            struct is_sp_impl<T,
                    void_t<decltype(&T::operator*), decltype(&T::operator->), decltype(&T::operator!)>
            >
                    : std::true_type
            {
            };
            template<typename T>
            static constexpr auto is_safeptr = CastHelper::is_sp_impl<T>::value;

    };
}