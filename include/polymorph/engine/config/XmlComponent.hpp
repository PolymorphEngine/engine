/*
** EPITECH PROJECT, 2020
** PropertyExctractor.hpp
** File description:
** header for PropertyExctractor.c
*/


#pragma once

#include <string>
#include <map>
#include <memory>
#include <vector>

#include "myxmlpp/myxmlpp.hpp"

#include "polymorph/engine/debug/Logger.hpp"

#include "polymorph/engine/types/safe/safe_ptr.hpp"

#include "polymorph/engine/config/XmlPropertyManager.hpp"

namespace polymorph::engine {
    class Entity;
    class AComponent;
    using GameObject = safe_ptr<Entity>;

}

namespace polymorph::engine::config
{

    class XmlComponent : public XmlPropertyManager
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            XmlComponent(GameObject entity, std::shared_ptr<myxmlpp::Node> &componentNode, debug::Logger& logger);

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:


        private:
            GameObject _entity;
            std::string _type;
            bool _enabled;

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            std::string getType();

            void setGameObject(GameObject entity);

            bool getEnabled();
            
            template<typename T>
            void set(std::string property, T &toSet, debug::Logger::severity level = debug::Logger::DEBUG) {
                this->XmlPropertyManager::set(property, toSet, _entity, _type, level);
            }
            
            template<typename T>
            void save(std::string property, T &toSet, debug::Logger::severity level = debug::Logger::DEBUG) {
                this->XmlPropertyManager::save(property, toSet, level);
            }

        protected:
            /**
             * @brief use the logger to log a meaningful message with given parameters when a property is missing
             * @param type The type of the object the property was part of
             * @param name The searched property name
             * @param level The logger severity level
             */
            void _logMissingProperty(std::string type, std::string name, debug::Logger::severity level);

            /**
             * @brief use the logger to log a meaningful message with given parameters when a property as missing value attribute
             * @param type The type of the object the property was part of
             * @param name The searched property name
             * @param level The logger severity level
             */
            void _logMissingValue(std::string type, std::string name, debug::Logger::severity level);

            /**
             * @brief use the logger to log a meaningful message with given parameters when a property has a wrong value
             * @param type The type of the object the property was part of
             * @param name The searched property name
             * @param level The logger severity level
             */
            void _logWrongValue(std::string type, std::string name, debug::Logger::severity level);

            void _onWrongValueExcept(debug::Logger::severity level,
                                     std::string propertyName,
                                     std::string value) override;

            void _onMissingValueExcept(debug::Logger::severity level,
                                       std::string propertyName) override;

            void _onMissingPropertyExcept(debug::Logger::severity level,
                                          std::string propertyName) override;


//////////////////////--------------------------/////////////////////////


//////////////////////--------------------------/////////////////////////

    };
}