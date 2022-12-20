/*
** EPITECH PROJECT, 2020
** APluginConfig.cpp
** File description:
** header for APluginConfig.c
*/

#include "polymorph/engine/api/plugin/APluginConfig.hpp"
#include "polymorph/engine/core/Engine.hpp"
#include "polymorph/engine/debug/exception/config/MissingFileException.hpp"
#include "polymorph/engine/debug/exception/CoreException.hpp"

namespace polymorph::engine::api
{

    void APluginConfig::save(bool saveAllPropeties, std::string filePath)
    {
        if (saveAllPropeties)
            saveAll();
        manager->saveConfig(filePath);
    }

    APluginConfig::APluginConfig(Engine &gameEngine, std::string filePath)
    : _filePath(filePath), Debug(gameEngine.getLogger()), time(gameEngine.getTime()), Scene(gameEngine.getSceneManager()), Resource(gameEngine.getAssetManager()), Plugin(gameEngine.getPluginManager()), Game(gameEngine)
    {
        std::shared_ptr<myxmlpp::Doc> doc;

        try {
            doc = std::make_shared<myxmlpp::Doc>(filePath);
        } catch (myxmlpp::Exception &e) {
            throw debug::MissingFileException(filePath);
        }

        manager = std::make_shared<config::XmlPluginConfig>(doc, gameEngine);
    }

    std::string APluginConfig::getType() const
    {
        if (manager)
            return manager->getType();
        throw debug::CoreException("Fatal Error! A Plugin Config doesn't have any xml manager.");
    }
} // api