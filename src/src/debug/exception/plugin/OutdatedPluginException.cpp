/*
** EPITECH PROJECT, 2020
** OutdatedPluginException.cpp
** File description:
** header for OutdatedPluginException.c
*/

#include "polymorph/engine/debug/exception/plugin/OutdatedPluginException.hpp"

polymorph::engine::debug::OutdatedPluginException::OutdatedPluginException(
        std::string plugin) : PluginException(plugin, "Outdated plugin", Logger::severity::MAJOR)
{

}
