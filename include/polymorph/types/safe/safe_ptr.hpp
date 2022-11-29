/*
** EPITECH PROJECT, 2020
** SafePtr.hpp
** File description:
** header for SafePtr.c
*/

#pragma once

#include <memory>
#include "polymorph/debug/exception/core/MissingReferenceException.hpp"


namespace polymorph::engine
{
    template<typename T>
    class safe_ptr : std::weak_ptr<T>
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            safe_ptr() : std::weak_ptr<T>()
            {};
            explicit safe_ptr(std::shared_ptr<T> data): std::weak_ptr<T>(data)
            {};

            ~safe_ptr() = default;

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:


        private:

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            safe_ptr<T> &operator=(std::shared_ptr<T> &t)
            {
                this->_M_assign(t);
                return *this;
            }

            std::shared_ptr<T> operator*() const
            {
                return this->lock();
            }

            T *operator->() const
            {
                if (this->expired())
                    throw debug::MissingReferenceException();
                return this->lock().get();
            }

            bool operator==(std::shared_ptr<T> &t) const
            {
                return this->lock() == t;
            }

            bool operator==(safe_ptr<T> &t) const
            {
                return this->lock() == t.lock();
            }

            bool operator!() const
            {
                return this->expired();
            }
            
            explicit operator bool() const
            {
                return !this->expired();
            }
//////////////////////--------------------------/////////////////////////

    };

} // polymorph::engine
