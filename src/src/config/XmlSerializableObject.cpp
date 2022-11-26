/*
** EPITECH PROJECT, 2020
** XmlSerializableObject.cpp
** File description:
** header for XmlSerializableObject.c
*/

#include "polymorph/config/XmlSerializableObject.hpp"

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
            _logMissingProperty(_type, propertyName, level);
        else
            throw debug::MissingValueException(_component->gameObject->getName() + " (" + _component->gameObject->getId() + ")", _component->getType(), propertyName, _type, level);
    }

    void
    XmlSerializableObject::_onMissingValueExcept(debug::Logger::severity level,
                                                 std::string propertyName)
    {
        XmlPropertyManager::_onMissingValueExcept(level, propertyName);
    }

    void XmlSerializableObject::_onMissingPropertyExcept(
            debug::Logger::severity level, std::string propertyName)
    {
        XmlPropertyManager::_onMissingPropertyExcept(level, propertyName);
    }


} 