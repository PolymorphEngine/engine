/*
** EPITECH PROJECT, 2020
** PluginDisabledException.cpp
** File description:
** header for PluginDisabledException.c
*/

#include "polymorph/engine/debug/exception/plugin/PluginDisabledException.hpp"

polymorph::engine::debug::PluginDisabledException::PluginDisabledException(
        std::string plugin, std::string objectType, Logger::severity level)
        : PluginException(plugin, (objectType == "") ? "Plugin disabled" : "Plugin disabled, cannot create object of type '" +objectType+"'", level)
{
 
}
