/*
** ${PROJECT}, 2022
** enable_safe_from_this.hpp by 0xMemoryGrinder
** File description:
** enable_safe_from_this.hpp
*/


#pragma once

#include <memory>
#include "polymorph/engine/types/safe/safe_ptr.hpp"

namespace polymorph::engine
{
    class BaseSafeFromThis : public std::enable_shared_from_this<BaseSafeFromThis>
    {
        public:
            virtual ~BaseSafeFromThis() = default;
    };

    /**
     * @brief Helper class to create safe_ptr from this in inherited classes
     * @tparam T Type of the inherited class
     */
    template <typename T>
    class enable_safe_from_this : public BaseSafeFromThis
    {

/////////////////////////////// METHODS /////////////////////////////////
        public:
            ~enable_safe_from_this() override = default;

            /**
             * @brief Get a safe_ptr to the current object
             * @return safe_ptr<T> to the current object
             */
            safe_ptr<T> safe_from_this()
            {
                return safe_ptr<T>(std::dynamic_pointer_cast<T>(shared_from_this()));
            }


        private:


//////////////////////--------------------------/////////////////////////

    };
}