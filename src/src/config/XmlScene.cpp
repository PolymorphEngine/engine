/*
** EPITECH PROJECT, 2020
** XmlScene.cpp
** File description:
** header for XmlScene.c
*/

#include "polymorph/config/XmlScene.hpp"
#include "myxmlpp/myxmlpp.hpp"
#include "polymorph/debug/exception/ConfigurationException.hpp"
#include "polymorph/debug/exception/config/EmptySceneException.hpp"
#include "polymorph/debug/exception/config/CorruptedFileException.hpp"
#include "polymorph/debug/exception/config/MissingFileException.hpp"

namespace polymorph::engine::config
{
    config::XmlScene::XmlScene(std::shared_ptr<myxmlpp::Node> &scene,
    debug::Logger &logger, std::string &path) : _logger(logger)
    {
        _projectNode = scene;
        
        try {
            _path = path + "/" + _projectNode->findAttribute("path")->getValue();
#ifdef _WIN32
            std::replace(_path.begin(), _path.end(), '/', '\\');
#endif
            _sceneDoc = std::make_shared<myxmlpp::Doc>(_path);

        } catch (myxmlpp::Exception &e) {
            throw debug::MissingFileException(_path);
        }

        try {
            _name = _sceneDoc->getRoot()->findAttribute("name")->getValue();
            _id = _sceneDoc->getRoot()->findAttribute("id")->getValue();
            _first = _sceneDoc->getRoot()->findAttribute("first")->getValueBool();
        } catch (myxmlpp::Exception &e) {
            _logger.log("[XmlScene] Corrupted file: " + e.baseWhat(), debug::Logger::MAJOR);
            throw debug::CorruptedFileException(_path, debug::Logger::MAJOR);
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