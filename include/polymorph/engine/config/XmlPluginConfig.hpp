/*
** EPITECH PROJECT, 2020
** XmlPluginConfig.hpp
** File description:
** header for XmlPluginConfig.c
*/


#pragma once

#include "polymorph/engine/config/XmlPropertyManager.hpp"

namespace polymorph::engine {
    class Engine;
}

namespace polymorph::engine::config
{
    class XmlPluginConfig : public XmlPropertyManager
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            XmlPluginConfig(std::shared_ptr<myxmlpp::Doc> doc, Engine &engine);

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:

            void saveConfig(std::string filePath = "");

        private:
            std::string _type;
            std::shared_ptr<myxmlpp::Doc> _doc;
            Engine &_engine;

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            std::string getType();
            
            template<typename T>
            void set(std::string property, T &toSet, debug::Logger::severity level = debug::Logger::DEBUG) {
                this->XmlPropertyManager::set(property, toSet, _engine, _type, level);
            }

            template<typename T>
            void save(std::string property, T &toSet, debug::Logger::severity level = debug::Logger::DEBUG) {
                this->XmlPropertyManager::save(property, toSet, level);
            }
        protected:
            void _onWrongValueExcept(debug::Logger::severity level,
                                     std::string propertyName,
                                     std::string value) override;

            void _onMissingValueExcept(debug::Logger::severity level,
                                       std::string propertyName) override;

            void _onMissingPropertyExcept(debug::Logger::severity level,
                                          std::string propertyName) override;

        private:
            void _logMissingProperty(std::string type, std::string name, debug::Logger::severity level);

            void _logMissingValue(std::string type, std::string name, debug::Logger::severity level);

            /**
             * @brief use the logger to log a meaningful message with given parameters when a property has a wrong value
             * @param type The type of the object the property was part of
             * @param name The searched property name
             * @param level The logger severity level
             */
            void _logWrongValue(std::string type, std::string name, debug::Logger::severity level);

 //////////////////////--------------------------/////////////////////////

    };

} // config
