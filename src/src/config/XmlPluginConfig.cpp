/*
** EPITECH PROJECT, 2020
** XmlPluginConfig.cpp
** File description:
** header for XmlPluginConfig.c
*/

#include "polymorph/engine/config/XmlPluginConfig.hpp"
#include "polymorph/engine/core/Engine.hpp"
#include "polymorph/engine/debug/exception/config/CorruptedFileException.hpp"
#include "polymorph/engine/debug/exception/config/WrongValueException.hpp"
#include "polymorph/engine/debug/exception/config/MissingPropertyException.hpp"
#include "polymorph/engine/debug/exception/config/MissingValueException.hpp"


namespace polymorph::engine::config
{
    config::XmlPluginConfig::XmlPluginConfig(
            std::shared_ptr<myxmlpp::Doc> doc, Engine &engine) : XmlPropertyManager(doc->getRoot(), engine.getLogger()) , _engine(engine), _doc(doc)
    {
        try {
            _type = node->findAttribute("type")->getValue();
        } catch (myxmlpp::AttributeNotFoundException &e) {
            throw debug::CorruptedFileException("Plugin config corrupted, missing type ("+doc->getFilepath()+").");
        }
    }

    std::string XmlPluginConfig::getType()
    {
        return _type;
    }

    void XmlPluginConfig::_onWrongValueExcept(debug::Logger::severity level,
                                              std::string propertyName,
                                              std::string value)
    {
        if (level != debug::Logger::MAJOR)
            _logWrongValue(_type, propertyName, level);
        else
            throw debug::WrongValueException(_type, propertyName, value, level);
    }

    void XmlPluginConfig::_onMissingValueExcept(debug::Logger::severity level,
                                                std::string propertyName)
    {
        if (level != debug::Logger::MAJOR)
            _logMissingValue(_type, propertyName, level);
        else
            throw debug::MissingValueException(_type, propertyName, level);
    }

    void
    XmlPluginConfig::_onMissingPropertyExcept(debug::Logger::severity level,
                                              std::string propertyName)
    {
        if (level != debug::Logger::MAJOR)
            _logMissingProperty(_type, propertyName, level);
        else
            throw debug::MissingPropertyException(_type, propertyName, level);
    }

    void
    XmlPluginConfig::_logMissingProperty(std::string type, std::string name,
                                         debug::Logger::severity level)
    {
        _logger.log("[ConfigurationException] Missing property '" + name + "' in config type '" + type + "'", level);
    }

    void XmlPluginConfig::_logMissingValue(std::string type, std::string name,
                                           debug::Logger::severity level)
    {
        _logger.log("[ConfigurationException] Missing property value '" + name + "' in config type '" + type + "'", level);

    }

    void XmlPluginConfig::_logWrongValue(std::string type, std::string name,
                                         debug::Logger::severity level)
    {
        _logger.log("[ConfigurationException] Wrong property value '" + name + "' in config type '" + type + "'", level);
    }

    void XmlPluginConfig::saveConfig(std::string file)
    {
        _doc->writeF(file);
    }
} // config