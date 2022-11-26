/*
** EPITECH PROJECT, 2020
** XmlPropertyManager.cpp
** File description:
** header for XmlPropertyManager.c
*/

#include "polymorph/config/XmlPropertyManager.hpp"
#include "polymorph/debug/exception/config/MissingValueException.hpp"


namespace polymorph::engine::config
{
    void config::XmlPropertyManager::_logMissingProperty(std::string type, std::string name, debug::Logger::severity level)
    {
        _logger.log("In component '" + type + "': Ref named '" + name + "': has no attribute for reference value", level);
    }

    void config::XmlPropertyManager::_logWrongValue(std::string type, std::string name, debug::Logger::severity level)
    {
        _logger.log("In component '" + type + "': Ref named '" + name + "': has wrong reference value", level);
    }


    std::shared_ptr<myxmlpp::Node>
    XmlPropertyManager::_findProperty(const std::string &name,
                                      debug::Logger::severity level)
    {
        return std::shared_ptr<myxmlpp::Node>();
    }

    std::shared_ptr<myxmlpp::Node>
    XmlPropertyManager::_findProperty(const std::string &name,
                                      const std::shared_ptr<myxmlpp::Node> &data,
                                      debug::Logger::severity level)
    {
        return std::shared_ptr<myxmlpp::Node>();
    }

    
    
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
            std::shared_ptr<myxmlpp::Node> &node,
            debug::Logger &logger) : _logger(logger), node(node)
    {

    }

    void XmlPropertyManager::_onWrongValueExcept(debug::Logger::severity level,
                                                 std::string propertyName,
                                                 std::string value)
    {

    }

    void
    XmlPropertyManager::_onMissingValueExcept(debug::Logger::severity level,
                                              std::string propertyName)
    {

    }

    void
    XmlPropertyManager::_onMissingPropertyExcept(debug::Logger::severity level,
                                                 std::string propertyName)
    {

    }


} // config