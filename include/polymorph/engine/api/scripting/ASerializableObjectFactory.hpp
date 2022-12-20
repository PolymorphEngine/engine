/*
** EPITECH PROJECT, 2020
** ASerializableObjectFactory.hpp
** File description:
** header for ASerializableObjectFactory.c
*/


#pragma once


#include <memory>
#include <utility>
#include <unordered_map>
#include "polymorph/engine/types/safe/safe_ptr.hpp"
#include "myxmlpp/Node.hpp"

namespace polymorph::engine {
    class AComponent;
}

namespace polymorph::engine::api
{
    class PluginManager;
    class APluginConfig;
    class ASerializableObject;

    class ASerializableObjectFactory
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            ASerializableObjectFactory() = default;
            virtual ~ASerializableObjectFactory() = default;

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:
            using EmptyFactoryLambda = std::function<std::shared_ptr<ASerializableObject> (PluginManager &pluginManager)>;
            using CObjectFactoryLambda = std::function<std::shared_ptr<ASerializableObject> (safe_ptr<AComponent> component, std::shared_ptr<myxmlpp::Node> node)>;
            using PObjectFactoryLambda = std::function<std::shared_ptr<ASerializableObject> (safe_ptr<APluginConfig> config, std::shared_ptr<myxmlpp::Node> node)>;



        private:
            std::unordered_map<std::string, EmptyFactoryLambda> _emptyBuildables;
            std::unordered_map<std::string, CObjectFactoryLambda> _componentBuildables;
            std::unordered_map<std::string, PObjectFactoryLambda> _configBuildables;

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:

            /**
             * @brief Tell whether or not the factory can build an object
             * @param type The type of the object to build
             */
            bool hasObject(std::string type);

            /**
             * @brief Register a new buildable object
             * @param type The type of the object
             * @param lambda The lambda to call to build the object
             */
            template<typename T>
            static inline EmptyFactoryLambda makeEmpty()
            {
                return [](PluginManager &pluginManager) -> std::shared_ptr<ASerializableObject> {
                    return std::dynamic_pointer_cast<ASerializableObject>(std::make_shared<T>(pluginManager));
                };
            }

            /**
             * @brief Register a new component buildable object
             * @param type The type of the object
             * @param lambda The lambda to call to build the object
             */
            template<typename T>
            static inline CObjectFactoryLambda makeCObject()
            {
                return [](safe_ptr<AComponent> component, std::shared_ptr<myxmlpp::Node> node) -> std::shared_ptr<ASerializableObject> {
                    return std::dynamic_pointer_cast<ASerializableObject>(std::make_shared<T>(component, node));
                };
            }

            /**
             * @brief Register a new config buildable object
             * @param type The type of the object
             * @param lambda The lambda to call to build the object
             */
            template<typename T>
            static inline PObjectFactoryLambda makePObject()
            {
                return [](safe_ptr<APluginConfig> config, std::shared_ptr<myxmlpp::Node> node) -> std::shared_ptr<ASerializableObject> {
                    return std::dynamic_pointer_cast<ASerializableObject>(std::make_shared<T>(config, node));
                };
            }

            /**
             * @brief Builds a new object
             * @param type The type of the object
             * @param pluginManager The plugin manager
             * @return The new object
             */
            template<class Tobj>
            std::shared_ptr<Tobj> createEmptyObject(std::string type, PluginManager &pluginManager)
            {
                if (_emptyBuildables.find(type) == _emptyBuildables.end())
                    return nullptr;
                return std::dynamic_pointer_cast<Tobj>(_emptyBuildables[type](pluginManager));
            }

            /**
             * @brief Builds a new object
             * @param type The type of the object
             * @param component The component to link to the object
             * @param node The node to load the object from
             * @return The new object
             */
            template<class Tobj, class Tcpt>
            std::shared_ptr<Tobj> createComponentObject(std::string type, safe_ptr<Tcpt> component, std::shared_ptr<myxmlpp::Node> node)
            {
                auto c = safe_ptr<AComponent>(std::dynamic_pointer_cast<AComponent>(*component));

                if (_componentBuildables.find(type) == _componentBuildables.end())
                    return nullptr;
                return std::dynamic_pointer_cast<Tobj>(_componentBuildables[type](c, std::move(node)));
            }

            /**
             * @brief Builds a new object
             * @param type The type of the object
             * @param config The component to link to the object
             * @param node The node to load the object from
             * @return The new object
             */
            template<class Tobj, class Tcfg>
            std::shared_ptr<Tobj> createConfigObject(std::string type, safe_ptr<Tcfg> config, std::shared_ptr<myxmlpp::Node> node)
            {
                auto c = safe_ptr<APluginConfig>(std::dynamic_pointer_cast<APluginConfig>(*config));

                if (_configBuildables.find(type) == _configBuildables.end())
                    return nullptr;
                return std::dynamic_pointer_cast<Tobj>(_configBuildables[type](c, std::move(node)));
            }

            void buildFactory();


        protected:
            /**
             * @brief Method to override that has to register all new Empty serializable object
             */
            virtual void _registerEmptyBuildables(std::unordered_map<std::string, EmptyFactoryLambda> &emptyBuildables) = 0;

            /**
             * @brief Method to override that has to register all new Component serializable object
             */
            virtual void _registerCObjectBuildables(std::unordered_map<std::string, CObjectFactoryLambda> &componentBuildables) = 0;

            /**
             * @brief Method to override that has to register all new Plugin Config serializable object
             */
            virtual void _registerPObjectBuildables(std::unordered_map<std::string, PObjectFactoryLambda> &configBuildables) = 0;

//////////////////////--------------------------/////////////////////////

    };

} // api
