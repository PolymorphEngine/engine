/*
** EPITECH PROJECT, 2020
** XmlScene.hpp
** File description:
** header for XmlScene.c
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

namespace polymorph::engine {
    class Engine;
    class Entity;
}

namespace polymorph::engine::config
{

    class XmlScene
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            XmlScene(std::shared_ptr<myxmlpp::Node> &scene, Engine &engine);

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:


        private:
            std::shared_ptr<myxmlpp::Node> _projectNode;
            debug::Logger& _logger;
            std::string _id;
            std::string _name;
            std::shared_ptr<myxmlpp::Doc> _sceneDoc;
            bool _first;
            std::shared_ptr<myxmlpp::Node> _entities;

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            std::string getId();

            std::string getName();

            bool isFirst() const;

            std::shared_ptr<myxmlpp::Node> getEntities();



        private:
            void _loadEntities();

//////////////////////--------------------------/////////////////////////

    };

} // config
