/*
** EPITECH PROJECT, 2020
** XmlPluginConfig.cpp
** File description:
** header for XmlPluginConfig.c
*/

#include "polymorph/config/XmlPluginConfig.hpp"
#include "polymorph/debug/exception/config/CorruptedFileException.hpp"


namespace polymorph::engine::config
{
    config::XmlPluginConfig::XmlPluginConfig(
            std::shared_ptr <myxmlpp::Doc> &doc, debug::Logger &logger) : XmlPropertyManager(doc->getRoot(), logger)
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
} // config