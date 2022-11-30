/*
** EPITECH PROJECT, 2020
** XmlEntity.hpp
** File description:
** header for XmlEntity.c
*/


#pragma once

#include <memory>
#include <string>
#include <vector>
#include "polymorph/debug/Logger.hpp"

namespace myxmlpp {
    class Doc;
    class Node;
}

namespace polymorph::engine::config
{
    class XmlEntity
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            XmlEntity(std::shared_ptr<myxmlpp::Node> &entity, debug::Logger& logger);

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:


        private:
            std::shared_ptr<myxmlpp::Node> _node;
            std::string _path;
            std::string _fileName;
            std::string _name;
            std::shared_ptr<myxmlpp::Doc> _entity;
            debug::Logger& _logger;
            bool _isPrefab;
            bool _isActive;
            std::string _prefabId;
            std::string _id;
            std::vector<std::string> _tags;
            std::shared_ptr<myxmlpp::Node> _components;

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            std::string getName() const;
            
            void saveConfig(std::string filePath);

            bool isActive() const;

            bool isPrefab();
            
            void addComponent(std::shared_ptr<myxmlpp::Node> component);

            std::string getPrefabId();

            std::shared_ptr<myxmlpp::Node> getComponents();

            std::string getId() const;

            [[nodiscard]] std::vector<std::string> getTags() const;



        private:
            void _loadTags();

//////////////////////--------------------------/////////////////////////

    };

} // config
