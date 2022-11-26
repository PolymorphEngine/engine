/*
** ${PROJECT}, 2022
** enable_safe_from_this.hpp by 0xMemoryGrinder
** File description:
** enable_safe_from_this.hpp
*/


#pragma once

#include <memory>
#include "polymorph/types/safe/safe_ptr.hpp"

namespace polymorph::engine
{
    template <typename T>
    class enable_safe_from_this : private std::enable_shared_from_this<T>
    {

/////////////////////////////// METHODS /////////////////////////////////
        public:
            safe_ptr<T> safe_from_this() const
            {
                return safe_ptr<T>(this->shared_from_this());
            }

            std::shared_ptr<T> shared_from_this() const
            {
                return std::enable_shared_from_this<T>::shared_from_this();
            }


        private:


//////////////////////--------------------------/////////////////////////

    };
}