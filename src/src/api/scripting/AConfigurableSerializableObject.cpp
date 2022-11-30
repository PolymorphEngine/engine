/*
** EPITECH PROJECT, 2020
** AConfigurableSerializableObject.cpp
** File description:
** header for AConfigurableSerializableObject.c
*/

#include "polymorph/api/scripting/AConfigurableSerializableObject.hpp"

namespace polymorph::engine::api
{
    AConfigurableSerializableObject::AConfigurableSerializableObject(
            safe_ptr<AComponent> component,
            std::shared_ptr<myxmlpp::Node> node)
            : ASerializableObject(component, node), _plugin(component->Plugin), _logger(component->Debug)
    {

    }

    AConfigurableSerializableObject::AConfigurableSerializableObject(
            safe_ptr<APluginConfig> config,
            std::shared_ptr<myxmlpp::Node> node)
            : ASerializableObject(config, node), _plugin(config->getPluginManager()), _logger(config->getLogger())
    {

    }

    AConfigurableSerializableObject::AConfigurableSerializableObject(
            PluginManager &pluginManager) : _plugin(pluginManager), _logger(pluginManager->getLogger())
    {

    }
} // api