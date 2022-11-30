/*
** EPITECH PROJECT, 2020
** XmlEntity.cpp
** File description:
** header for XmlEntity.c
*/

#include "polymorph/config/XmlEntity.hpp"
#include "myxmlpp/exceptions/Exception.hpp"
#include "myxmlpp/Node.hpp"
#include "myxmlpp/Doc.hpp"
#include "polymorph/debug/exception/config/MissingEntityException.hpp"
#include "polymorph/debug/exception/config/CorruptedFileException.hpp"


namespace polymorph::engine::config
{
    config::XmlEntity::XmlEntity(std::shared_ptr<myxmlpp::Node> &entity,
                                 debug::Logger &logger) : _logger(logger)
    {
        std::string name;
        try {
            _path = _node->findAttribute("path")->getValue();
#ifdef _WIN32
            std::replace(_fileName.begin(), _fileName.end(), '/', '\\');
#endif
        } catch (myxmlpp::Exception &e) {
            throw debug::ConfigurationException("Missing path attribute in entity", debug::Logger::MAJOR);
        }

        try {
#ifdef _WIN32
            _entity = std::make_shared<myxmlpp::Doc>(_path + "\\" +_fileName);
#else
            _entity = std::make_shared<myxmlpp::Doc>(_path);
#endif
            _entity->getRoot();
            
        } catch (myxmlpp::Exception &e) {
            throw debug::MissingEntityException(name);
        }
        try {
            _name = _entity->getRoot()->findAttribute("name")->getValue();
            _id = _entity->getRoot()->findAttribute("id")->getValue();
            _isPrefab = _entity->getRoot()->findAttribute("prefab")->getValueBool();
            _prefabId = _entity->getRoot()->findAttribute("prefabid")->getValue();
            _isActive = _entity->getRoot()->findAttribute("active")->getValueBool();
            _components = _entity->getRoot()->findChild("Components");
            _loadTags();
        } catch (myxmlpp::Exception &e) {
            _logger.log("[XmlEntity] Corrupted file: " + e.baseWhat(), debug::Logger::MAJOR);
            throw debug::CorruptedFileException(_path + "/" +_fileName);
        }
    }


    std::string XmlEntity::getName() const
    {
        return _name;
    }

    bool XmlEntity::isActive() const
    {
        return _isActive;
    }

    bool XmlEntity::isPrefab()
    {
        return _isPrefab;
    }


    std::string XmlEntity::getPrefabId()
    {
        return _prefabId;
    }

    std::string XmlEntity::getId() const
    {
        return _id;
    }

    std::vector<std::string> XmlEntity::getTags() const
    {
        return _tags;
    }

    void XmlEntity::_loadTags()
    {
        auto tags = _entity->getRoot()->findChild("Tags");
        for (auto &tag : *tags) {
            _tags.push_back(tag->findAttribute("value")->getValue());
        }
    }

    std::shared_ptr<myxmlpp::Node> XmlEntity::getComponents()
    {
        return _components;
    }

    void XmlEntity::saveConfig(std::string filePath)
    {
        _entity->writeF(filePath);
    }
    void XmlEntity::addComponent(std::shared_ptr<myxmlpp::Node> component)
    {
        _components->addChild(component);
    }
} // config