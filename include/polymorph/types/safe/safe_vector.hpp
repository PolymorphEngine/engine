/*
** EPITECH PROJECT, 2020
** safe_vector.hpp
** File description:
** header for safe_vector.c
*/


#pragma once
#include <vector>
#include <algorithm>
#include "safe_ptr.hpp"

namespace polymorph::engine
{
    template<class T>
    class safe_vector final : public std::vector<safe_ptr<T>>
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            safe_vector() : std::vector<safe_ptr<T>>()
            {};
            
            safe_vector(std::vector<safe_ptr<T>> data): std::vector<safe_ptr<T>>(data)
            {};
            
            safe_vector(int size) : std::vector<safe_ptr<T>>(size)
            {};
            safe_vector(int size, safe_ptr<T> data) : std::vector<safe_ptr<T>>(size, data)
            {};
            ~safe_vector() final = default; 


//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:


        private:

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            /**
             * @brief Remove all expired weak_ptr from the vector
             */
            void clean() {
                auto it = std::find_if(this->begin(), this->end(),
                                       [](safe_ptr<T> instance) { return !instance; });
                while (it != this->end())
                {
                    this->erase(it);
                    it = std::find_if(this->begin(), this->end(),
                                      [](safe_ptr<T> instance) { return !instance; });
                }
            }
            
            /**
             * @brief checks if the vector contains any expired weak_ptr
             */
            bool countainsExpired() {
                auto it = std::find_if(this->begin(), this->end(),
                                       [](safe_ptr<T> instance) { return !instance; });
                return it != this->end();
            }
            
            


        private:

//////////////////////--------------------------/////////////////////////

    };

} // polymorph::engine
