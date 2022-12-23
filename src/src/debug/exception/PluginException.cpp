/*
** EPITECH PROJECT, 2020
** PluginException.cpp
** File description:
** header for PluginException.c
*/

#include "polymorph/engine/debug/exception/PluginException.hpp"

polymorph::engine::debug::PluginException::PluginException(std::string plugin,
std::string message, polymorph::engine::debug::Logger::severity level) : ExceptionLogger("[PluginException("+plugin+")] " + message, level)
{

}

polymorph::engine::debug::PluginException::PluginException(std::string message,
                                                           polymorph::engine::debug::Logger::severity level)
        : ExceptionLogger("[PluginException] "+message, level)
{

}
