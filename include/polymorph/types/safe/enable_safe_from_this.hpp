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
    /**
     * @brief Helper class to create safe_ptr from this in inherited classes
     * @tparam T Type of the inherited class
     */
    template <typename T>
    class enable_safe_from_this : private std::enable_shared_from_this<T>
    {

/////////////////////////////// METHODS /////////////////////////////////
        public:
            /**
             * @brief Get a safe_ptr to the current object
             * @return safe_ptr<T> to the current object
             */
            safe_ptr<T> safe_from_this() const
            {
                return safe_ptr<T>(this->shared_from_this());
            }

            /**
             * @brief Get a shared_ptr to the current object
             * @return shared_ptr<T> to the current object
             */
            std::shared_ptr<T> shared_from_this() const
            {
                return std::enable_shared_from_this<T>::shared_from_this();
            }


        private:


//////////////////////--------------------------/////////////////////////

    };
}