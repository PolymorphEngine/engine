/*
** EPITECH PROJECT, 2020
** XmlSerializableObject.cpp
** File description:
** header for XmlSerializableObject.c
*/

#include "polymorph/engine/config/XmlSerializableObject.hpp"
#include "polymorph/engine/api/plugin/APluginConfig.hpp"
#include "polymorph/engine/debug/exception/config/MissingPropertyException.hpp"
#include "polymorph/engine/debug/exception/config/WrongValueException.hpp"
#include "polymorph/engine/debug/exception/config/MissingValueException.hpp"

namespace polymorph::engine::config
{

    XmlSerializableObject::XmlSerializableObject(safe_ptr<AComponent> component,
                                                 std::shared_ptr<myxmlpp::Node> &componentNode,
                                                 debug::Logger &logger) : XmlPropertyManager(componentNode, logger), _component(component)
    {
        try {
            _type = node->findAttribute("subtype")->getValue();
        } catch (myxmlpp::Exception &e) {
            throw debug::ConfigurationException("No SerializableObject type found in configuration from component (" + component->getType() + "), in entity ("
            +component->gameObject->getName() + " - "+component->gameObject->getId()+") !");
        }
    }

    XmlSerializableObject::XmlSerializableObject(
            safe_ptr<api::APluginConfig> config,
            std::shared_ptr<myxmlpp::Node> &componentNode,
            debug::Logger &logger) : XmlPropertyManager(componentNode, logger), _config(config)
    {
        _isFromConfig = true;
        try {
            _type = node->findAttribute("subtype")->getValue();
        } catch (myxmlpp::Exception &e) {
            throw debug::ConfigurationException("No SerializableObject type found in configuration from plugin config ( "+ config->getType() + " ) !");
        }
    }

    void
    XmlSerializableObject::_onWrongValueExcept(debug::Logger::severity level,
                                               std::string propertyName,
                                               std::string value)
    {
        if (level != debug::Logger::MAJOR)
            _logWrongValue(_type, propertyName, level);
        else if (!_isFromConfig)
            throw debug::WrongValueException(_component->gameObject->getName() + " (" + _component->gameObject->getId() + ")", _component->getType(), propertyName, value, _type, level);
        else if (_isFromConfig)
            throw debug::WrongValueException(_config->getType(), propertyName, value, level);
    }

    void
    XmlSerializableObject::_onMissingValueExcept(debug::Logger::severity level,
                                                 std::string propertyName)
    {
        if (level != debug::Logger::MAJOR)
            _logMissingValue(_type, propertyName, level);
        else if (!_isFromConfig)
            throw debug::MissingValueException(_component->gameObject->getName() + " (" + _component->gameObject->getId() + ")", _component->getType(), propertyName, _type, level);
        else if (_isFromConfig)
            throw debug::MissingValueException(_config->getType(), propertyName, level);
    }

    void XmlSerializableObject::_onMissingPropertyExcept(
            debug::Logger::severity level, std::string propertyName)
    {
        if (level != debug::Logger::MAJOR)
            _logMissingProperty(_type, propertyName, level);
        else if (!_isFromConfig)
            throw debug::MissingPropertyException(_component->gameObject->getName() + " (" + _component->gameObject->getId() + ")", _component->getType(), propertyName, _type, level);
        else if (_isFromConfig)
            throw debug::MissingPropertyException(_config->getType(), propertyName, level);
    }

    std::string XmlSerializableObject::getType() const
    {
        return _type;
    }

    void XmlSerializableObject::_logMissingProperty(std::string type,
                                                    std::string name,
                                                    debug::Logger::severity level)
    {
        if (!_isFromConfig)
            _logger.log("[ConfigurationException] Missing property '" + name + "' in SerializableObject '" + type + "' from component '" + _component->getType() + "' in entity '" + _component->gameObject->getName() + "' (" + _component->gameObject->getId() + ")", level);
        else
            _logger.log("[ConfigurationException] Missing property '" + name + "' in SerializableObject '" + type + "' from plugin config '" + _config->getType() + "'", level);
    }

    void
    XmlSerializableObject::_logWrongValue(std::string type, std::string name,
                                          debug::Logger::severity level)
    {
        if (!_isFromConfig)
            _logger.log("[ConfigurationException] Wrong value for property '" + name + "' in SerializableObject '" + type + "' from component '" + _component->getType() + "' in entity '" + _component->gameObject->getName() + "' (" + _component->gameObject->getId() + ")", level);
        else
            _logger.log("[ConfigurationException] Wrong value for property '" + name + "' in SerializableObject '" + type + "' from plugin config '" + _config->getType() + "'", level);

    }

    void
    XmlSerializableObject::_logMissingValue(std::string type, std::string name, debug::Logger::severity level)
    {
        if (!_isFromConfig)
            _logger.log("[ConfigurationException] Missing value for property '" + name + "' in SerializableObject '" + type + "' from component '" + _component->getType() + "' in entity '" + _component->gameObject->getName() + "' (" + _component->gameObject->getId() + ")", level);
        else
            _logger.log("[ConfigurationException] Missing value for property '" + name + "' in SerializableObject '" + type + "' from plugin config '" + _config->getType() + "'", level);
    }

}