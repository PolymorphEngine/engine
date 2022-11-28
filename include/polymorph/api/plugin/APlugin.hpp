/*
** EPITECH PROJECT, 2020
** IPlugin.hpp
** File description:
** header for IPlugin.c
*/


#pragma once
#include "myxmlpp/myxmlpp.hpp"
#include "polymorph/types/safe/safe_ptr.hpp"
#include "polymorph/api/AssetManager.hpp"


namespace polymorph::engine
{
    class Entity;
    using GameObject = safe_ptr<Entity>;
    class Scene;
    class Engine;
    class AComponent;
    class ASerializableObject;
    
    namespace config
    {
        class XmlComponent;
        
        class XmlSerializableObject;
        
        class XmlPluginConfig;

        class XmlEntity;

        using XmlNode = myxmlpp::Node;
    }
}

namespace polymorph::engine::api
{
    class AssetManager;
    class PluginManager;
    class APluginConfig;

    class APlugin
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            APlugin(config::XmlNode &data, Engine &game, std::string PluginsPath);

            virtual ~APlugin() = default;


        public:
            PluginManager &pluginManager;
            AssetManager &assetManager;

        private:

            std::string _packageName;
            bool _isEnabled = true;
            std::string _pluginsPath;
            config::XmlNode &_data;
            std::vector<std::shared_ptr<config::XmlEntity>> _prefabs;
            std::vector<config::XmlComponent> _templates;
            std::unique_ptr<IScriptFactory> _factory;
            std::unique_ptr<ISerializableObjectFactory> _objectFactory;
            Engine &_game;
            
//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            virtual std::string getPackageName() = 0;

            virtual std::shared_ptr<AComponent> createComponent(std::string &type, config::XmlComponent &data, GameObject entity) = 0;

            virtual std::shared_ptr<ASerializableObject> createSharedObject(std::string &type, config::XmlComponent &data, std::shared_ptr<config::XmlNode> &node, PluginManager &Plugins) = 0;

            virtual std::shared_ptr<ASerializableObject> createEmptySharedObject(std::string &type, PluginManager &Plugins) = 0;

            virtual bool isEnabled() = 0;

            virtual bool hasComponent(std::string &type) = 0;
            virtual bool hasObject(std::string &type) = 0;

            virtual bool hasPrefab(const std::string &id) = 0;

            virtual std::shared_ptr<config::XmlEntity> &getPrefabConf(const std::string &id) = 0;

            virtual std::vector<config::XmlComponent> &getComponentTemplates() = 0;

            virtual void preUpdateInternalSystems(std::shared_ptr<Scene> &scene) = 0;

            virtual void updateInternalSystems(std::shared_ptr<Scene> &scene) = 0;

            virtual void postUpdateInternalSystems(std::shared_ptr<Scene> &scene) = 0;

            virtual void startScripts(std::shared_ptr<Scene> &scene) = 0;

            virtual void endScripts(std::shared_ptr<Scene> &scene) = 0;


        private:

//////////////////////--------------------------/////////////////////////

    };

} // api
