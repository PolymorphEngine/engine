/*
** EPITECH PROJECT, 2020
** CorruptedPluginException.cpp
** File description:
** header for CorruptedPluginException.c
*/

#include "polymorph/engine/debug/exception/plugin/CorruptedPluginException.hpp"

polymorph::engine::debug::CorruptedPluginException::CorruptedPluginException(
        std::string plugin) : PluginException(plugin, "Corrupted plugin", Logger::severity::MAJOR)
{

}
