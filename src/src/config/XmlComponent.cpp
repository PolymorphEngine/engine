/*
** EPITECH PROJECT, 2020
** XmlComponent.cpp
** File description:
** header for XmlComponent.c
*/

#include "polymorph/debug/Logger.hpp"
#include "polymorph/config/XmlPropertyManager.hpp"
#include "polymorph/config/XmlComponent.hpp"

namespace polymorph::engine::config
{
    void config::XmlComponent::_logMissingProperty(std::string type, std::string name, debug::Logger::severity level)
    {
        "missing value for property '" + property + (object.empty() ? "'" : "' for object '"+object+"'") + " for component '" + component + "' of entity '" + entity + "'."
        _logger.log("[ConfigurationException] In component '" + type + "': Ref named '" + name + "': has no attribute for reference value", level);
    }

    void config::XmlComponent::_logWrongValue(std::string type, std::string name, debug::Logger::severity level)
    {
        _logger.log("[ConfigurationException] In component '" + type + "': Ref named '" + name + "': has wrong reference value", level);
    }

    void config::XmlComponent::_onWrongValueExcept(debug::Logger::severity level, std::string propertyName, std::string value)
    {
        if (level != debug::Logger::MAJOR)
            _logWrongValue(_type, propertyName, level);
        else
            throw debug::WrongValueException(_entity->getName() + " (" + _entity->getId() + ")", _type, propertyName, level);
    }

    void config::XmlComponent::_onMissingValueExcept(debug::Logger::severity level, std::string propertyName)
    {
        if (level != debug::Logger::MAJOR)
            _logMissingProperty(_type, propertyName, level);
        else
            throw debug::MissingValueException(_entity->getName() + " (" + _entity->getId() + ")", _type, propertyName, "", level);
    }

    void config::XmlComponent::_onMissingPropertyExcept(debug::Logger::severity level, std::string propertyName)
    {
        XmlPropertyManager::_onMissingPropertyExcept(level, propertyName);
    }

    XmlComponent::XmlComponent(GameObject entity,
                               std::shared_ptr<myxmlpp::Node> &componentNode,
                               debug::Logger &logger) : XmlPropertyManager(componentNode, logger), _entity(entity)
    {

    }
} // config