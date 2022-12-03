/*
** EPITECH PROJECT, 2020
** Engine.hpp
** File description:
** header for Engine.c
*/


#pragma once

#include <iostream>
#include <myxmlpp/myxmlpp.hpp>
#include <memory>
#include <vector>
#include <atomic>

#include "polymorph/types/safe/safe_ptr.hpp"
#include "polymorph/debug/Logger.hpp"
#include "polymorph/api/AssetManager.hpp"
#include "polymorph/api/plugin/PluginManager.hpp"
#include "polymorph/api/SceneManager.hpp"
#include "polymorph/time/Time.hpp"
#include "polymorph/config/XmlComponent.hpp"
#include "polymorph/config/XmlEngine.hpp"

namespace polymorph::engine
{
    namespace config
    {
        class XmlEntity;
        class XmlEngine;

        class XmlComponent;
    }

    class Entity;

    class Scene;

    using ExitCode = int;

    /**
     * @class Engine Main container class that holds all game data such as :
     *        Scenes, Prefabs, Configuration files, Settings
     */
    class Engine
    {
        public:
////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
            /**
             * @brief Creates an instance of engine by passing the project path containing all resources needed to load it such as config and assets
             * @param projectPath path containing resources to load
             * @param projectName name of the main config file in the projectPath (do not include extension cause it's also the window title / project name)
             */
            explicit Engine(std::string projectName, std::string projectPath, std::string pluginPath);

            ~Engine() = default;
//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        private:
            debug::Logger _logger;

            api::PluginManager _pluginManager;

            api::SceneManager _sceneManager;

            api::AssetManager _assetManager;

            /**
             * @property _time time class of the engine
             */
            time::Time _time;

            /**
             * @property _scenes list of all of the scenes
             */
            std::vector<std::shared_ptr<Scene>> _scenes;



            /**
             * @property _prefabs list of all of the prefabs
             */
            std::vector<std::shared_ptr<config::XmlEntity>> _prefabs;

            /**
             * @property _prefabsConfigs list of all of the configuration of the prefabs
             */
            std::vector<std::shared_ptr<config::XmlEntity>> _prefabsConfigs;

            /**
             * @property _defaultConfigs default configuration for the components
             */
            std::vector<std::shared_ptr<myxmlpp::Node>> _defaultConfigs;

            /**
             * @property _execOrder order of execution of the components
             */
            std::vector<std::string> _execOrder;

            /**
             * @property _pluginsExecOrder order of execution of the plugins
             */
            std::vector<std::string> _pluginsExecOrder;
            /**
             * @property _exit exit or not the program
             */
            std::atomic<bool> _exit = false;

            /**
             * @property _exitCode exit code of the program
             */
            std::atomic<ExitCode> _exitCode = 0;

            /**
             * @property _projectPath path to the project
             */
            std::string _projectPath;
            std::string _pluginsPath;

            /**
             * @property _projectName name of the project
             */
            std::string _projectName;

            /**
             * @property _projectConfig configuration of the project
             */
            std::unique_ptr<config::XmlEngine> _projectConfig;

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            /**
             * @details Getter that fetches the ordered vector of component types.
             *          Order determines which component has to be updated before others.
             * @returns A vector of std::string ordered based on execution order.
             */
            std::vector<std::string> &getExecOrder();

            std::vector<std::string> &getPluginExecOrder();

            api::AssetManager &getAssetManager();

            api::SceneManager &getSceneManager();

            debug::Logger &getLogger();

            time::Time &getTime();



            /**
             * @details Runs the game.
             */
            int run();

            /**
             * @brief Loads the game configuration and inits all gameObjects/Components/Scenes
             */
            void loadEngine();

            api::PluginManager &getPluginManager();

            /**
             * @brief Exit the program with a specified exit code
             * @param code exit code of the program
             */
            void exit(ExitCode code);

            /**
             * @brief Getter to know if we should exit or not
             * @return exit status of the program
             */
            bool isExiting() const
            { return _exit; };

            /**
             * @brief Getter of the project path
             * @return the project path
             */
            std::string getProjectPath();

            /**
             * @brief Getter of the project title
             * @return the project title
             */
            std::string getTitle();

            /**
             * @brief Getter of prefabs
             * @return A list of all the prefabs loaded
             */
            std::vector<std::shared_ptr<config::XmlEntity>> getPrefabs();

            /**
             * @brief Check if the engine is in debug mode or not
             * @return true if debug is on
             */
            bool isDebugMode();
            /**
             * @brief Getter of default configuration of the components
             * @return the default configuration of the components
             */
            std::vector<std::shared_ptr<myxmlpp::Node>> getDefaultConfigs();

            /**
             * @brief Getter of default configuration of a specific component
             * @param type type of the component
             * @return the default configuration of the component type
             */
            std::shared_ptr<myxmlpp::Node> getDefaultConfig(const std::string &type);

            /**
             * @details Find a scene by its name, returns the first matched
             * @param name the name of the scene to find
             * @return the required scene
             */
            std::shared_ptr<Scene> findSceneByName(const std::string &name);

            /**
             * @details Find a scene by its id, returns the first matched
             * @param id the name of the scene to find
             * @return the required scene
             */
            std::shared_ptr<Scene> findSceneById(const std::string &id);

            /**
             * Add the provided scene to the engine's scenes list
             * @param scene the scene to add
             */
            void addScene(const std::shared_ptr<Scene> &scene);


        private:
            /**
             * @details Opens the project configuration
             */
            void _openProject();

            /**
             * @details Inits the execution order informations of components at runtime
             */
            void _initExectutionOrder();

            void _initPluginsExecutionOrder();

            /**
             * @details Inits the debug settings of the engine
             */
            void _initDebugSettings();

            /**
             * @details Inits the game prefabs
             */
            void _initPrefabs();

            /**
             * @details Inits the components default configs
             */
            void _initTemplates();

            /**
             * @details Inits the game data
             */
            void _initGameData();
//////////////////////--------------------------/////////////////////////

    };
} // engine
