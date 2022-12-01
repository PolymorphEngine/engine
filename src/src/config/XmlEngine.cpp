/*
** EPITECH PROJECT, 2020
** XmlEngine.cpp
** File description:
** header for XmlEngine.c
*/

#include "polymorph/config/XmlEngine.hpp"
#include "polymorph/debug/exception/CoreException.hpp"
#include "polymorph/debug/exception/ConfigurationException.hpp"
#include "polymorph/debug/exception/core/NoScenesFoundException.hpp"


namespace polymorph::engine::config
{
    config::XmlEngine::XmlEngine(std::string projectPath)
    {
        _projectPath = projectPath;
        try {
            _doc = std::make_shared<myxmlpp::Doc>(projectPath);
        } catch (const myxmlpp::Exception &e) {
            throw debug::CoreException("Failed to load project file: " + std::string(e.what()));
        } try {             
            _scenes = _doc->getRoot()->findChild("Scenes");
        } catch (const myxmlpp::Exception &e) {
            throw debug::NoScenesFoundException();
        }
        try {
            _settings = _doc->getRoot()->findChild("Settings");
        } catch (const myxmlpp::Exception &e) {
            throw debug::CoreException("Failed to load Settings project data: " + std::string(e.what()));
        }
        try {
            _templates = _doc->getRoot()->findChild("Templates");
        } catch (const myxmlpp::Exception &e) {
            throw debug::CoreException("Failed to load Templates project data: " + std::string(e.what()));
        }
        try {
            _plugins = _doc->getRoot()->findChild("Plugins");
        } catch (const myxmlpp::Exception &e) {
            throw debug::CoreException("Failed to load Plugins project data: " + std::string(e.what()));
        }
        try {
            _prefabs = _doc->getRoot()->findChild("Prefabs");
        } catch (const myxmlpp::Exception &e) {
            throw debug::CoreException("Failed to load Prefabs project data: " + std::string(e.what()));
        }
    }

    std::shared_ptr<myxmlpp::Node> XmlEngine::getScenes()
    {
        return _scenes;
    }

    std::shared_ptr<myxmlpp::Node> XmlEngine::getTemplates()
    {
        return _templates;
    }

    std::shared_ptr<myxmlpp::Node> XmlEngine::getPlugins()
    {
        return _plugins;
    }

    std::shared_ptr<myxmlpp::Node> XmlEngine::getPrefabs()
    {
        return _prefabs;
    }

    bool XmlEngine::getDebugMode()
    {
        try {
            auto debug = _settings->findChild("Debug");
            return debug->findAttribute("value")->getValueBool("true", "false");
        } catch (const myxmlpp::Exception &e) {
            debug::CoreException("Failed to fetch debug mode, set to false by default: " + std::string(e.what())).what();
            return false;
        }
    }

    std::vector<std::string> XmlEngine::getExecOrder()
    {
        try {
            bool foundDefault = false;
            std::vector<std::string> _execOrder;
            auto execOrder = _settings->findChild("ComponentExecutionOrder");

            for (auto &type : *execOrder) {
                auto t = type->findAttribute("value")->getValue();
                if (t == "Default")
                    foundDefault = true;
                _execOrder.push_back(t);
            }
            if (!foundDefault)
                throw debug::ConfigurationException("Default layer order missing !", debug::Logger::MAJOR);
            return _execOrder;
        } catch (myxmlpp::Exception &e) {
            throw debug::ConfigurationException(e.what(), debug::Logger::MAJOR);
        }
    }

    std::vector<std::string> XmlEngine::getPluginsExecOrder()
    {
        try {
            std::vector<std::string> _execOrder;
            auto execOrder = _settings->findChild("PluginExecutionOrder");

            for (auto &type : *execOrder) {
                auto t = type->findAttribute("value")->getValue();
                _execOrder.push_back(t);
            }
            return _execOrder;
        } catch (myxmlpp::Exception &e) {
            throw debug::ConfigurationException(e.what(), debug::Logger::MAJOR);
        }
    }
} // config