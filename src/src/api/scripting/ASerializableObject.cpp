/*
** EPITECH PROJECT, 2020
** ASerializableObject.cpp
** File description:
** header for ASerializableObject.c
*/

#include "polymorph/engine/api/scripting/ASerializableObject.hpp"
#include "polymorph/engine/api/plugin/APluginConfig.hpp"


namespace polymorph::engine::api
{
    api::ASerializableObject::ASerializableObject(
            safe_ptr <AComponent> component,
            std::shared_ptr <myxmlpp::Node> node)
    : _isFromConfig(false), _component(component)
    {
        manager = std::make_shared<config::XmlSerializableObject>(component, node, component->Debug);
        _type = manager->getType();
    }

    api::ASerializableObject::ASerializableObject(
            safe_ptr <APluginConfig> config,
            std::shared_ptr <myxmlpp::Node> node)
    : _isFromConfig(true), _config(config)
    {
        manager = std::make_shared<config::XmlSerializableObject>(config, node, config->Debug);
        _type = manager->getType();
    }


    bool ASerializableObject::isFromConfig() const
    {
        return _isFromConfig;
    }

    std::string ASerializableObject::getType() const
    {
        return _type;
    }

} // api