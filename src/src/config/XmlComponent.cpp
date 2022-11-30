/*
** EPITECH PROJECT, 2020
** XmlComponent.cpp
** File description:
** header for XmlComponent.c
*/

#include "polymorph/debug/Logger.hpp"
#include "polymorph/config/XmlPropertyManager.hpp"
#include "polymorph/config/XmlComponent.hpp"
#include "polymorph/debug/exception/config/MissingComponentTypeException.hpp"
#include "polymorph/debug/exception/config/MissingPropertyException.hpp"

namespace polymorph::engine::config
{
    void config::XmlComponent::_logMissingProperty(std::string type, std::string name, debug::Logger::severity level)
    {
        _logger.log("[ConfigurationException] missing value for property '" + name + " for component '" + _type + "' of entity '" + _entity->getName() +"("+ _entity->getId() +")"+ "'.", level);
    }

    void config::XmlComponent::_logWrongValue(std::string type, std::string name, debug::Logger::severity level)
    {
        _logger.log("[ConfigurationException] wrong value for property '" + name + " for component '" + _type + "' of entity '" + _entity->getName() +"("+ _entity->getId() +")"+ "'.", level);
    }

    void config::XmlComponent::_onWrongValueExcept(debug::Logger::severity level, std::string propertyName, std::string value)
    {
        if (level != debug::Logger::MAJOR)
            _logWrongValue(_type, propertyName, level);
        else
            throw debug::WrongValueException(_entity->getName() + " (" + _entity->getId() + ")", _type, propertyName, "", level);
    }

    void config::XmlComponent::_onMissingValueExcept(debug::Logger::severity level, std::string propertyName)
    {
        if (level != debug::Logger::MAJOR)
            _logMissingValue(_type, propertyName, level);
        else
            throw debug::MissingValueException(_entity->getName() + " (" + _entity->getId() + ")", _type, propertyName, "", level);
    }

    void config::XmlComponent::_onMissingPropertyExcept(debug::Logger::severity level, std::string propertyName)
    {
        if (level != debug::Logger::MAJOR)
            _logMissingProperty(_type, propertyName, level);
        else
            throw debug::MissingPropertyException(_entity->getName() + " (" + _entity->getId() + ")", _type, propertyName, "", level);
    }

    XmlComponent::XmlComponent(GameObject entity,
                               std::shared_ptr<myxmlpp::Node> &componentNode,
                               debug::Logger &logger) : XmlPropertyManager(componentNode, logger), _entity(entity)
    {
        try {
            _type = node->findAttribute("type")->getValue();
        } catch (myxmlpp::Exception &e) {
            throw debug::MissingComponentTypeException(_entity->getName() + " (" + _entity->getId() + ")");
        }
        try {
            _enabled = node->findAttribute("enabled")->getValueBool();
        } catch (myxmlpp::Exception &e) {
            _logger.log("[ConfigurationException] missing value for property 'enabled' for component '" + _type + "' of entity '" + _entity->getName() + "', setting 'true' by default", debug::Logger::DEBUG);
            _enabled = true;
        }
    }

    std::string XmlComponent::getType()
    {
        return _type;
    }

    bool XmlComponent::getEnabled()
    {
        return _enabled;
    }

    void XmlComponent::_logMissingValue(std::string type, std::string name,
                                        debug::Logger::severity level)
    {
        _logger.log("[ConfigurationException] missing value for property '" + name + " for component '" + _type + "' of entity '" + _entity->getName() +"("+ _entity->getId() +")"+ "'.", level);
    }

    void XmlComponent::setGameObject(GameObject entity)
    {
        _entity = entity;
        entity->getConfig()->addComponent(*this);
    }
} // config