/*
** EPITECH PROJECT, 2020
** APluginConfig_templated.hpp
** File description:
** header for APluginConfig_templated.c
*/


#pragma once
#include "APluginConfig.hpp"
#include "polymorph/engine/config/XmlPluginConfig.hpp"


namespace polymorph::engine::api
{
    template<typename T>
    void APluginConfig::saveProperty(std::string name, T &value)
    {
        manager->save(name, value);
    }    
    
    template<typename T>
    void APluginConfig::_setProperty(const std::string &propertyName, T &toSet,
                                      debug::Logger::severity level)
    {
        manager->set(propertyName, toSet, level);
    }

}