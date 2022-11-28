/*
** EPITECH PROJECT, 2020
** XmlSerializableObject.cpp
** File description:
** header for XmlSerializableObject.c
*/

#include "polymorph/config/XmlSerializableObject.hpp"
#include "polymorph/debug/exception/config/MissingPropertyException.hpp"

namespace polymorph::engine::config
{

    XmlSerializableObject::XmlSerializableObject(safe_ptr<AComponent> component,
                                                 std::shared_ptr<myxmlpp::Node> &componentNode,
                                                 debug::Logger &logger) : XmlPropertyManager(componentNode, logger), _component(component)
    {

    }

    void
    XmlSerializableObject::_onWrongValueExcept(debug::Logger::severity level,
                                               std::string propertyName,
                                               std::string value)
    {
        if (level != debug::Logger::MAJOR)
            _logWrongValue(_type, propertyName, level);
        else
            throw debug::WrongValueException(_component->gameObject->getName() + " (" + _component->gameObject->getId() + ")", _component->getType(), propertyName, _type, level);
    }

    void
    XmlSerializableObject::_onMissingValueExcept(debug::Logger::severity level,
                                                 std::string propertyName)
    {
        if (level != debug::Logger::MAJOR)
            _logMissingValue(_type, propertyName, level);
        else
            throw debug::MissingValueException(_component->gameObject->getName() + " (" + _component->gameObject->getId() + ")", _component->getType(), propertyName, _type, level);
    }

    void XmlSerializableObject::_onMissingPropertyExcept(
            debug::Logger::severity level, std::string propertyName)
    {
        if (level != debug::Logger::MAJOR)
            _logMissingProperty(_type, propertyName, level);
        else
            throw debug::MissingPropertyException(_component->gameObject->getName() + " (" + _component->gameObject->getId() + ")", _component->getType(), propertyName, _type, level);
    }

    std::string XmlSerializableObject::getType() const
    {
        return _type;
    }

    void XmlSerializableObject::_logMissingProperty(std::string type,
                                                    std::string name,
                                                    debug::Logger::severity level)
    {
        _logger.log("[ConfigurationException] missing property '" + name + " for object '" + _type, level);
    }

    void
    XmlSerializableObject::_logWrongValue(std::string type, std::string name,
                                          debug::Logger::severity level)
    {
        _logger.log("[ConfigurationException] wrong value for property '" + name + " for object '" + _type, level);
    }

    void
    XmlSerializableObject::_logMissingValue(std::string type, std::string name, debug::Logger::severity level)
    {
        _logger.log("[ConfigurationException] missing value for property '" + name + " for object '" + _type, level);
    }


} 