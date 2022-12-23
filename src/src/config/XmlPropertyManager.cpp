/*
** EPITECH PROJECT, 2020
** XmlPropertyManager.cpp
** File description:
** header for XmlPropertyManager.c
*/

#include "polymorph/engine/config/XmlPropertyManager.hpp"
#include "polymorph/engine/debug/exception/config/MissingValueException.hpp"


namespace polymorph::engine::config
{
    bool XmlPropertyManager::_setPropertyFromAttr(int &toSet, std::shared_ptr<myxmlpp::Node> data, debug::Logger::severity level)
    {
        auto name = data->findAttribute("name")->getValue();

        try {
            toSet = data->findAttribute("value")->getValueInt();
            return true;
        } catch (const myxmlpp::AttributeNotFoundException &e) {
            _onMissingValueExcept(level, name);
        } catch (const myxmlpp::IllegalValueException &e) {
            _onWrongValueExcept(level, name, data->findAttribute("value")->getValue());
        }
        return false;
    }

    bool
    XmlPropertyManager::_setPropertyFromAttr(float &toSet, std::shared_ptr<myxmlpp::Node> data, debug::Logger::severity level)
    {
        auto name = data->findAttribute("name")->getValue();

        try {
            toSet = data->findAttribute("value")->getValueFloat();
            return true;
        } catch (const myxmlpp::AttributeNotFoundException &e) {
            _onMissingValueExcept(level, name);
        } catch (const myxmlpp::IllegalValueException &e) {
            _onWrongValueExcept(level, name, data->findAttribute("value")->getValue());
        }
        return false;
    }

    bool XmlPropertyManager::_setPropertyFromAttr(bool &toSet, std::shared_ptr<myxmlpp::Node> data, debug::Logger::severity level)
    {
        auto name = data->findAttribute("name")->getValue();

        try {
            toSet = data->findAttribute("value")->getValueBool();
            return true;
        } catch (const myxmlpp::AttributeNotFoundException &e) {
            _onMissingValueExcept(level, name);
        } catch (const myxmlpp::IllegalValueException &e) {
            _onWrongValueExcept(level, name, data->findAttribute("value")->getValue());
        }
        return false;
    }

    bool XmlPropertyManager::_setPropertyFromAttr(std::string &toSet, std::shared_ptr<myxmlpp::Node> data, debug::Logger::severity level)
    {
        auto name = data->findAttribute("name")->getValue();
        
        try {
            toSet = data->findAttribute("value")->getValue();
            return true;
        } catch (const myxmlpp::AttributeNotFoundException &e) {
            _onMissingValueExcept(level, name);
        } catch (const myxmlpp::IllegalValueException &e) {
            _onWrongValueExcept(level, name, data->findAttribute("value")->getValue());
        }
        return false;
    }

    XmlPropertyManager::XmlPropertyManager(
            std::shared_ptr<myxmlpp::Node> node,
            debug::Logger &logger) : _logger(logger), node(node)
    {

    }

    std::shared_ptr<myxmlpp::Node>
    XmlPropertyManager::_findProperty(const std::string &name)
    {
        for (auto &child: *node) {
            try {
            if (child->findAttribute("name")->getValue() == name)
                return child;
            } catch (myxmlpp::Exception &e) {}
        }
        return nullptr;
    }

    std::shared_ptr<myxmlpp::Node>
    XmlPropertyManager::_findProperty(const std::string &name,
                                      const std::shared_ptr<myxmlpp::Node> &data)
    {
        for (auto &child: *data) {
            try {
                if (child->findAttribute("name")->getValue() == name)
                    return child;
            } catch (myxmlpp::Exception &e) {}
        }
        return nullptr;
    }

    bool XmlPropertyManager::_savePropertyFromAttr(int &toSet,
                                                   std::shared_ptr<myxmlpp::Node> data,
                                                   debug::Logger::severity level)
    {
        try {
            data->findAttribute("value")->setValueInt(toSet);
            return true;
        } catch (myxmlpp::AttributeNotFoundException &e) {
            _onMissingValueExcept(level, data->findAttribute("name")->getValue());
        }
        return false;
    }

    bool XmlPropertyManager::_savePropertyFromAttr(float &toSet,
                                                   std::shared_ptr<myxmlpp::Node> data,
                                                   debug::Logger::severity level)
    {

        try {
            data->findAttribute("value")->setValueFloat(toSet);
            return true;
        } catch (myxmlpp::AttributeNotFoundException &e) {
            _onMissingValueExcept(level, data->findAttribute("name")->getValue());
        }
        return false;
    }

    bool XmlPropertyManager::_savePropertyFromAttr(bool &toSet,
                                                   std::shared_ptr<myxmlpp::Node> data,
                                                   debug::Logger::severity level)
    {
        try {
            data->findAttribute("value")->setValueBool(toSet);
            return true;
        } catch (myxmlpp::AttributeNotFoundException &e) {
            _onMissingValueExcept(level, data->findAttribute("name")->getValue());
        }
        return false;
    }

    bool XmlPropertyManager::_savePropertyFromAttr(std::string &toSet,
                                                   std::shared_ptr<myxmlpp::Node> data,
                                                   debug::Logger::severity level)
    {
        try {
            data->findAttribute("value")->setValue(toSet);
            return true;
        } catch (myxmlpp::AttributeNotFoundException &e) {
            _onMissingValueExcept(level, data->findAttribute("name")->getValue());
        }
        return false;
    }

    std::shared_ptr<myxmlpp::Node> XmlPropertyManager::getNode()
    {
        return node;
    }


} // config