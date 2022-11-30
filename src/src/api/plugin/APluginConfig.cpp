/*
** EPITECH PROJECT, 2020
** APluginConfig.cpp
** File description:
** header for APluginConfig.c
*/

#include "polymorph/api/plugin/APluginConfig.hpp"
#include "polymorph/debug/exception/config/MissingFileException.hpp"

namespace polymorph::engine::api
{

    void APluginConfig::save(bool saveAllPropeties, std::string filePath)
    {
        if (saveAllPropeties)
            saveAll();
        manager->saveConfig(filePath);
    }

    APluginConfig::APluginConfig(Engine &gameEngine, std::string filePath)
    : _filePath(filePath), Debug(gameEngine.Debug), time(gameEngine.time), Scene(gameEngine.Scene), Resource(gameEngine.Resource), Plugin(gameEngine.Plugin), Game(gameEngine)
    {
        std::shared_ptr<myxmlpp::Doc> doc;

        try {
            doc = std::make_shared<myxmlpp::Doc>(filePath);
        } catch (myxmlpp::Exception &e) {
            throw debug::MissingFileException(filePath);
        }

        manager = std::make_shared<config::XmlPluginConfig>(doc, gameEngine);
    }
} // api