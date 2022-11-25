/*
** ${PROJECT}, 2022
** uuid.hpp by 0xMemoryGrinder
** File description:
** uuid.hpp
*/

#pragma once

#include <string>

namespace polymorph::engine::uuid
{
#ifdef POLYMORPH_ENGINE_UUID_LENGTH
    static constexpr size_t POLYMORPH_ENGINE_UUID_LENGTH = POLYMORPH_ENGINE_UUID_LENGTH;
#else
    static constexpr size_t POLYMORPH_ENGINE_UUID_LENGTH = 10;
#endif

    /**
     * @details Generate a random UUID of length POLYMORPH_ENGINE_UUID_LENGTH
     * @returns a random UUID
     * @warning This function don't store any history of generated UUID. there is a very very low chance that the same UUID will be generated twice
     */
    std::string uuid();
}