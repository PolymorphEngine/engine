/*
** EPITECH PROJECT, 2020
** AScriptFactory.hpp
** File description:
** header for AScriptFactory.c
*/


#pragma once
#include "polymorph/types/safe/safe_ptr.hpp"
#include "polymorph/core/AComponent.hpp"
#include "myxmlpp/Node.hpp"

namespace polymorph::engine {
    class AComponent;
    class Entity;
    using GameObject = safe_ptr<Entity>;
}

namespace polymorph::engine::api
{

    class AComponentFactory
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:
            using FactoryLambda = std::function<std::shared_ptr<AComponent> (GameObject entity, std::shared_ptr<myxmlpp::Node> node)>;


        private:
            std::unordered_map<std::string, FactoryLambda> _buildables;

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            void buildFactory();
            
            /**
             * @brief Tell whether or not the factory can build a component
             * @param type The type of the component to build
             */
            bool hasComponent(const std::string &type) const;

            /**
             * @brief Register a new buildable object
             * @param type The type of the object
             * @param lambda The lambda to call to build the object
             */
            template<typename T>
            static inline FactoryLambda make()
            {
                return [](GameObject entity, std::shared_ptr<myxmlpp::Node> node) -> std::shared_ptr<AComponent> {
                    return std::dynamic_pointer_cast<AComponent>(std::make_shared<T>(entity, node));
                };
            }
            /**
             * @brief Builds a new object
             * @param type The type of the object
             * @param pluginManager The plugin manager
             * @return The new object
             */
            template<class Tobj>
            std::shared_ptr<Tobj> create(std::string type, GameObject entity, std::shared_ptr<myxmlpp::Node> node)
            {
                if (_buildables.find(type) == _buildables.end())
                    return nullptr;
                return std::dynamic_pointer_cast<Tobj>(_buildables[type](entity, node));
            }



        private:
            /**
             * @brief Method to override that has to register all new Components
             */
            virtual void _registerBuildables(std::unordered_map<std::string, FactoryLambda> &buildables) = 0;

//////////////////////--------------------------/////////////////////////

    };

} // api
