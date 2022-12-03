/*
** EPITECH PROJECT, 2020
** XmlScene.cpp
** File description:
** header for XmlScene.c
*/

#include "polymorph/config/XmlScene.hpp"
#include "polymorph/core/Engine.hpp"
#include "myxmlpp/myxmlpp.hpp"
#include "polymorph/debug/exception/ConfigurationException.hpp"
#include "polymorph/debug/exception/config/EmptySceneException.hpp"
#include "polymorph/debug/exception/config/CorruptedFileException.hpp"
#include "polymorph/debug/exception/config/MissingFileException.hpp"

namespace polymorph::engine::config
{
    config::XmlScene::XmlScene(std::shared_ptr<myxmlpp::Node> &scene, polymorph::engine::Engine &engine) : _logger(engine.getLogger())
    {
        _projectNode = scene;
        std::string fullPath;

        try {
            auto path =  _projectNode->findAttribute("path")->getValue();
#ifdef _WIN32
            std::replace(_path.begin(), _path.end(), '/', '\\');
#endif
            fullPath = engine.getAssetManager().tryResolve(path);
            _sceneDoc = std::make_shared<myxmlpp::Doc>(fullPath);

        } catch (myxmlpp::AttributeNotFoundException &e) {
            throw debug::ConfigurationException(e.what(), debug::Logger::MAJOR);
        } catch (myxmlpp::NoFileException &e) {
            throw debug::MissingFileException(fullPath, debug::Logger::MAJOR);
        } catch (myxmlpp::FileException &e) {
            throw debug::CorruptedFileException(fullPath, debug::Logger::MAJOR);
        }

        try {
            _name = _sceneDoc->getRoot()->findAttribute("name")->getValue();
            _id = _sceneDoc->getRoot()->findAttribute("id")->getValue();
            _first = _sceneDoc->getRoot()->findAttribute("first")->getValueBool();
        } catch (myxmlpp::Exception &e) {
            _logger.log("[XmlScene] Corrupted file: " + e.baseWhat(), debug::Logger::MAJOR);
            throw debug::CorruptedFileException(fullPath, debug::Logger::MAJOR);
        }
        _loadEntities();
    }

    void XmlScene::_loadEntities()
    {
        std::shared_ptr<myxmlpp::Node> list;

        try {
            _entities = _sceneDoc->getRoot()->findChild("Entities");
        } catch (myxmlpp::Exception &e) {
            throw debug::EmptySceneException(_name);
        }
    }

    std::string XmlScene::getId()
    {
        return _id;
    }

    std::string XmlScene::getName()
    {
        return _name;
    }

    bool XmlScene::isFirst() const
    {
        return _first;
    }

    std::shared_ptr<myxmlpp::Node> XmlScene::getEntities()
    {
        return _entities;
    }
} // config