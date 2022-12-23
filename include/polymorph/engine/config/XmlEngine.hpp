/*
** EPITECH PROJECT, 2020
** XmlEngine.hpp
** File description:
** header for XmlEngine.c
*/


#pragma once
#include "myxmlpp/myxmlpp.hpp"


namespace polymorph::engine::config
{
    class XmlEngine
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            explicit XmlEngine(std::string projectPath);

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:


        private:
            std::shared_ptr<myxmlpp::Doc> _doc;
            std::string _projectPath;
            std::shared_ptr<myxmlpp::Node> _scenes;
            std::shared_ptr<myxmlpp::Node> _settings;
            std::shared_ptr<myxmlpp::Node> _templates;
            std::shared_ptr<myxmlpp::Node> _plugins;
            std::shared_ptr<myxmlpp::Node> _prefabs;
            

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            std::shared_ptr<myxmlpp::Node> getScenes();
            std::shared_ptr<myxmlpp::Node> getTemplates();
            std::shared_ptr<myxmlpp::Node> getPlugins();
            std::shared_ptr<myxmlpp::Node> getPrefabs();
            bool getDebugMode();
            std::vector<std::string> getExecOrder();
            std::vector<std::string> getPluginsExecOrder();
            


        private:

//////////////////////--------------------------/////////////////////////

    };

} // config
