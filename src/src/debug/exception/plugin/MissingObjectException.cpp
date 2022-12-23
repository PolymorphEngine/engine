/*
** EPITECH PROJECT, 2020
** MissingObjectException.cpp
** File description:
** header for MissingObjectException.c
*/

#include "polymorph/engine/debug/exception/plugin/MissingObjectException.hpp"

polymorph::engine::debug::MissingObjectException::MissingObjectException(
        std::string objectType,
        polymorph::engine::debug::Logger::severity level) : PluginException("Cannot find object type '" + objectType+"' in plugins", level)
{

}
