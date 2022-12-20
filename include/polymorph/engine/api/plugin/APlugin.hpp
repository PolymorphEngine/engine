/*
** EPITECH PROJECT, 2020
** IPlugin.hpp
** File description:
** header for IPlugin.c
*/


#pragma once
#include "myxmlpp/myxmlpp.hpp"
#include "polymorph/engine/types/safe/safe_ptr.hpp"
#include "polymorph/engine/api/AssetManager.hpp"
#include "polymorph/engine/api/scripting/AComponentFactory.hpp"
#include "polymorph/engine/api/scripting/ASerializableObjectFactory.hpp"
#include "polymorph/engine/api/scripting/AComponentFactory.hpp"
#include "Symbols.hpp"


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
    class AComponentFactory;
    class ASerializableObjectFactory;

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
            std::shared_ptr<myxmlpp::Doc> _doc;
            std::vector<std::shared_ptr<config::XmlEntity>> _prefabs;
            std::vector<std::shared_ptr<myxmlpp::Node>> _templates;
            std::vector<std::shared_ptr<APluginConfig>> _configs;
            std::unique_ptr<AComponentFactory> _factory;
            std::unique_ptr<ASerializableObjectFactory> _objectFactory;
            Engine &_game;
            
//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            /**
             * @brief Get the Plugin Name object
             * @return the plugin name as a string
             */
            std::string getPluginName();

            /**
             * @brief Creates a Component from the plugin
             * @tparam T The type of the component to create
             * @param type The string type of the component
             * @param data The data of the component to create
             * @param entity The entity to which the component will be attached
             * @return a shared pointer to the created component
             */
            template<typename T>
            std::shared_ptr<T>
            createComponent(std::string &type, GameObject entity,
                            std::shared_ptr<myxmlpp::Node> node)
            {
                return _factory->create<T>(type, entity, node);
            }

            /**
             * @brief Creates a Serializable Object from the plugin
             * @tparam T The type of the object to create
             * @param type The string type of the object
             * @param data The data of the object to create
             * @return a shared pointer to the created Serializable Object
             */
            template<typename T, typename TComponent>
            std::shared_ptr<T> createSerializableObject(std::string &type, safe_ptr<TComponent> component, std::shared_ptr<myxmlpp::Node> node)
            {
                return _objectFactory->createComponentObject<T, TComponent>(type, component, node);
            }

            /**
             * @brief Creates an Empty Serializable Object from the plugin
             * @tparam T The type of the object to create
             * @param type The string type of the object
             * @param data The data of the object to create
             * @return a shared pointer to the created Serializable Object
             */
            template<typename T>
            std::shared_ptr<T> createEmptySharedObject(std::string &type, PluginManager &Plugins)
            {
                return _objectFactory->createEmptyObject<T>(type, Plugins);
            }
            
            /**
             * @brief Creates an Serializable Object from the plugin
             * @tparam T The type of the object to create
             * @param type The string type of the object
             * @param data The data of the object to create
             * @return a shared pointer to the created Serializable Object
             */
            template<typename T, typename TConfig>
            std::shared_ptr<T> createConfigObject(std::string &type, safe_ptr<TConfig> config, std::shared_ptr<myxmlpp::Node> node)
            {
                return std::dynamic_pointer_cast<T>(_objectFactory->createConfigObject<T, TConfig>(type, config, node));
            }

            /**
             * @brief Tell whether or not the plugin is enabled
             */
            bool isEnabled() const;

            /**
             * @brief Tell if the plugin is able to create a component of the given type
             * @param type The string type of the component
             */
            bool hasComponent(std::string &type);

            /**
             * @brief Tell if the plugin is able to create a Serializable Object of the given type
             * @param type The string type of the Serializable Object
             */
            bool hasObject(std::string &type);

            /**
             * @brief Tell if the plugin is able to create a Prefab of the given id
             * @param id The string id of the prefab
             */
            bool hasPrefab(const std::string &id);

            /**
             * @brief Gets a prefab from the plugin by its id
             * @param id The string id of the prefab
             */
            std::shared_ptr<config::XmlEntity> &getPrefabConf(const std::string &id);

            /**
             * @brief Fetches all XmlComponent templates from the plugin
             */
            std::vector<std::shared_ptr<myxmlpp::Node>> &getComponentTemplates();

            /**
             * @brief An overridable method that is called every time in the game loop just before the entity update
             * @param scene The scene in which the plugin is running
             */
            virtual void preUpdateInternalSystems(std::shared_ptr<Scene> &scene);

            /**
             * @brief An overridable method that is called every time in the game loop just before the entity update (but after preUpdateInternalSystems)
             * @param scene The scene in which the plugin is running
             */
            virtual void updateInternalSystems(std::shared_ptr<Scene> &scene);

            /**
             * @brief An overridable method that is called every time in the game loop just after the entity update
             * @param scene The scene in which the plugin is running
             */
            virtual void postUpdateInternalSystems(std::shared_ptr<Scene> &scene);

            /**
             * @brief An overridable method that is called once after the scene is loaded
             * @param scene The scene in which the plugin is running
             */
            virtual void startScripts(std::shared_ptr<Scene> &scene);
            
            /**
             * @brief An overridable method that is called once after the scene is unloaded
             * @param scene The scene in which the plugin is running
             */
            virtual void endScripts(std::shared_ptr<Scene> &scene);


            /**
             * @brief An overridable PURE method that must create all Plugin Configs and populate the _configs vector
             * @param configs The vector of configs to populate
             */
            virtual void createConfig(std::vector<std::shared_ptr<APluginConfig>> &configs) = 0;

            /**
             * @brief An overridable PURE method that must create the attached Component Factory
             * @return a unique pointer to the created Component Factory
             */
            virtual std::unique_ptr<AComponentFactory> createComponentFactory() = 0;

            /**
             * @brief An overridable PURE method that must create the attached Serializable Object Factory
             * @return a unique pointer to the created Serializable Object Factory
             */
            virtual std::unique_ptr<ASerializableObjectFactory> createSerializableObjectFactory() = 0;

            /**
             * @brief Gets a config by its type
             */
            template<typename T>
            safe_ptr<T> getConfig()
            {
                for (auto &config : _configs) {
                    if (std::dynamic_pointer_cast<T>(*config))
                        return safe_ptr<T>(std::dynamic_pointer_cast<T>(*config));
                }
                return safe_ptr<T>();
            }            
            
            /**
             * @brief Gets a config by its type
             * @param type the string type of the config
             */
            safe_ptr<APluginConfig> getConfig(const std::string &type);
            
            /**
             * @brief Builds the plugin by initializing its factories, its configs and all other Xml related data
             */
            void build(); 


        private:
            /**
             * @brief Loads all the prefabs from the plugin
             */
            void _loadPrefabs();
            
            /**
             * @brief Loads all the components configs from the plugin
             */
            void _loadTemplates();
            
            /**
             * @brief Loads the main plugin config
             */
            void _loadConfig();
//////////////////////--------------------------/////////////////////////

    };

} // api

SYMBOL_EXPORT(polymorph::engine::api, Plugin, APlugin, (config::XmlNode &data, Engine &game, std::string PluginsPath))
