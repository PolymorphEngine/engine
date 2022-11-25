/*
** EPITECH PROJECT, 2022
** uuid.cpp
** File description:
** uuid.cpp
*/

#include <random>
#include <sstream>
#include "polymorph/types/uuid.hpp"

namespace polymorph::engine::uuid
{
    static inline std::random_device rd;
    static inline std::mt19937 gen(rd());
    static inline std::uniform_int_distribution<> dis(0, 15);

    std::string uuid()
    {
        std::stringstream ss;
        ss << std::hex;
        for (int i = 0; i < POLYMORPH_ENGINE_UUID_LENGTH; i++)
            ss << dis(gen);
        return ss.str();
    }
}