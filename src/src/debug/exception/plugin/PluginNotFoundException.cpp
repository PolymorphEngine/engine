/*
** EPITECH PROJECT, 2020
** PluginNotFoundException.cpp
** File description:
** header for PluginNotFoundException.c
*/

#include "polymorph/debug/exception/plugin/PluginNotFoundException.hpp"

polymorph::engine::debug::PluginNotFoundException::PluginNotFoundException(
        std::string objectType) : PluginException("Cannot find plugin for object type '" + objectType+"'", Logger::severity::MAJOR)
{

}
