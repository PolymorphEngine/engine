/*
** EPITECH PROJECT, 2020
** ConflictingPluginException.cpp
** File description:
** header for ConflictingPluginException.c
*/

#include "polymorph/engine/debug/exception/plugin/ConflictingPluginException.hpp"

polymorph::engine::debug::ConflictingPluginException::ConflictingPluginException(
        std::string plugin) : PluginException(plugin, "Conflicting plugin", Logger::severity::MAJOR)
{

}
