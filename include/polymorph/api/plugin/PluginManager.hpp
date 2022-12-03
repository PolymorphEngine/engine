/*
** EPITECH PROJECT, 2020
** PluginManager.hpp
** File description:
** header for PluginManager.c
*/


#pragma once
#include <string>
#include <vector>
#include <memory>
#include "polymorph/api/DynamicLoader.hpp"
#include "polymorph/api/plugin/APlugin.hpp"

#include "polymorph/types/safe/safe_ptr.hpp"
#include "myxmlpp/Node.hpp"


namespace polymorph::engine {
    class Engine;
    class AComponent;
    class Entity;
    using GameObject = safe_ptr<Entity>;

    namespace config {
        class XmlComponent;
        class XmlSerializableObject;
        class XmlPluginConfig;
        class XmlEntity;
        using XmlNode = myxmlpp::Node;
    }

}

namespace polymorph::engine::api
{
    class APlugin;
    class DynamicLoader;
    class ASerializableObject;
    class AssetManager;

    class PluginManager
    {
        public:
            explicit PluginManager(Engine &game);

        private:
            std::vector<std::string> _pluginsPath;
            std::vector<DynamicLoader> _pluginsLoaders;
            std::vector<std::shared_ptr<APlugin>> _plugins;
            std::vector<std::shared_ptr<Entity>> _prefabs;
            std::vector<std::string> _pluginsOrder;
            Engine &_game;

        public:
            /**
             * @brief Loads all Plugins
             * @param pluginsPath The directory path holding all plugins
             * @param list the node containing the paths of the plugins
             * @param game the engine instance
             */
            void loadPlugins(const std::string &pluginsPath, config::XmlNode &list, Engine &game);

            /**
             * @brief Gets the asset manager
             */
            AssetManager &getAssetManager();


            /**
             * @brief Tries to load a symbol from plugins
             * @tparam symbol the symbol signature
             * @param symbolName the string symbol
             * @return the pointer holding the symbol
             */
            template<typename symbol>
            symbol getSymbol(const std::string &symbolName)
            {
                for (auto &plugin : _pluginsLoaders) {
                    auto s = plugin.loadSymbol<symbol>(symbolName, true);
                    if (s)
                        return s;
                }
                return nullptr;
            }

            /**
             * @brief Tries to create a component from plugins
             * @param type the type of the component to create
             * @param node the xml data to build the component
             * @param entity the entity to attach the component with
             * @return A pointer to the newly created component
             */
            std::shared_ptr<AComponent>
            tryCreateComponent(std::string &type, GameObject entity, std::shared_ptr<myxmlpp::Node> node);

            /**
             * @brief Tries to create a serializable object from plugins
             * @param type the type of the serializable object to create
             * @param data the xml data to create the object
             * @param component the component to attach the object with
             * @return A pointer to the newly created object
             */
            std::shared_ptr<ASerializableObject> tryCreateComponentObject(std::string &type, std::shared_ptr<myxmlpp::Node> &data, safe_ptr<AComponent> component);

            /**
             * @brief Tries to create a serializable object from plugins
             * @param type the type of the serializable object to create
             * @param data the xml data to create the object
             * @param config the plugin config to attach the object with
             * @return A pointer to the newly created object
             */
            std::shared_ptr<ASerializableObject> tryCreateConfigObject(std::string &type, std::shared_ptr<myxmlpp::Node> &data, safe_ptr<APluginConfig> config);

            /**
             * @brief Tries to create a serializable object from plugins
             * @param type the type of the serializable object to create
             * @return A pointer to the newly created object
             */
            std::shared_ptr<ASerializableObject> tryCreateEmptyObject(std::string &type);

            /**
             * @brief Gets the component templates from all plugin
             */
            std::vector<std::shared_ptr<myxmlpp::Node>> getTemplates();

            /**
             * @brief Gets and instantiate a prefab from plugins by id
             * @param id the id of the prefab
             */
            GameObject getPrefab(const std::string &id);

            /**
             * @brief Gets a plugin conf by its type
             * @param type The string type of the config
             */
            safe_ptr<APluginConfig> getConfig(const std::string &type);

            /**
             * @brief Gets a plugin conf by its type
             * @tparam T The type of the config
             */
            template<class T>
            safe_ptr<T> getConfig()
            {
                for (auto &plugin: _plugins){
                    auto retrieved = plugin->getConfig<T>();
                    if (retrieved)
                        return retrieved;
                }
                return safe_ptr<T>(nullptr);
            }

            /**
             * @brief Starts all plugins
             */
            void startingScripts();

            /**
             * @brief pre update all plugins
             */
            void preProcessing();

            /**
             * @brief update all plugins
             */
            void lateUpdate();

            /**
             * @brief post update all plugins
             */
            void postProcessing();

            /**
             * @brief Stops all plugins
             */
            void endingScripts();

        private:
            bool _isPluginPrioritary(const std::string &pluginName);


            std::shared_ptr<APlugin> _loadPlugin(std::shared_ptr<config::XmlNode> node, const std::string &pluginPath, Engine &game, const std::string &name);

    };

} // api
