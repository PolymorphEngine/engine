/*
** EPITECH PROJECT, 2020
** EmptySceneException.cpp
** File description:
** header for EmptySceneException.c
*/

#include "polymorph/engine/debug/exception/config/EmptySceneException.hpp"

polymorph::engine::debug::EmptySceneException::EmptySceneException(
        std::string name, bool isFirst)
        : ConfigurationException("Scene: '" + name + "' is empty.", (isFirst ? Logger::severity::MAJOR : Logger::severity::MINOR))
{

}
