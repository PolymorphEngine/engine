/*
** EPITECH PROJECT, 2020
** ASerializableObject.cpp
** File description:
** header for ASerializableObject.c
*/

#include "polymorph/api/scripting/ASerializableObject.hpp"


namespace polymorph::engine::api
{
    api::ASerializableObject::ASerializableObject(
            safe_ptr <AComponent> component,
            std::shared_ptr <myxmlpp::Node> node) 
    : _logger(component->Debug), manager(component, node, component->Debug), _isFromConfig(false), _component(component), _plugin(component->Plugin)
    {
        _type = manager.getType();
    }

    api::ASerializableObject::ASerializableObject(
            safe_ptr <APluginConfig> config,
            std::shared_ptr <myxmlpp::Node> node) 
    : _logger(config->getLogger()), manager(config, node, config->getLogger()), _isFromConfig(true), _config(config), _plugin(config->getPluginManager())
    {
        _type = manager.getType();
    }


    bool ASerializableObject::isFromConfig() const
    {
        return _isFromConfig;
    }

    std::string ASerializableObject::getType() const
    {
        return _type;
    }

    ASerializableObject::ASerializableObject(PluginManager &pluginManager) : _plugin(pluginManager)
    {
        
    }

} // api