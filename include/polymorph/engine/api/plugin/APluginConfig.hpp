/*
** EPITECH PROJECT, 2020
** APluginConfig.hpp
** File description:
** header for APluginConfig.c
*/


#pragma once


#include "myxmlpp/Doc.hpp"
#include "polymorph/engine/config/XmlPluginConfig.hpp"

namespace polymorph::engine {
    class Engine;
    
    namespace debug {
        class Logger;
    }
    namespace time {
        class Time;
    }
}
namespace polymorph::engine::api
{
    class SceneManager;
    class AssetManager;
    class PluginManager;
    
    class APluginConfig
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            APluginConfig(Engine &gameEngine, std::string filePath);

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:
            debug::Logger &Debug;
            time::Time &time;
            SceneManager &Scene;
            AssetManager &Resource;
            PluginManager &Plugin;
            Engine &Game;
            


        protected:
            std::shared_ptr<config::XmlPluginConfig> manager;

        private:
            std::string _filePath;
            myxmlpp::Doc _doc;

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:

            /**
             * @brief Virtual Pure method to be implemented in any Plugin Config implementation
             * that will be called when the object is loaded from a file to set all properties
             */
            virtual void build() = 0;

            /**
             * @brief Virtual Pure method to be implemented in any Plugin Config implementation
             * that will be called when the object is Saved to save all properties
             */
            virtual void saveAll() = 0;
            
            std::string getType() const;
            
            /**
             * @brief Save the config to a file
             * @param saveAllProperties if true, will call saveAll() before saving
             * @param filePath the path to the file to save to (if empty, will use the path given in the constructor)
             */
            void save(bool saveAllProperties = false, std::string filePath = "");

            /**
             * @brief Saves a property in the Xml data by its name
             * @param name The name of the property
             * @tparam T The type of the property
             * @param value The value of the property
             */
            template<typename T>
            void saveProperty(std::string propertyName, T &toSave)
            {
                manager->XmlPropertyManager::save(propertyName, toSave);
            }

            /**
             * @brief Saves a property in the Xml data by its name
             * @param name The name of the property
             * @tparam T The type of the property
             * @param value The value of the property
             */
            template<typename T>
            void saveProperty(std::string propertyName, std::shared_ptr<T> &toSave)
            {
                manager->save(propertyName, toSave);
            }

            /**
             * @brief Saves a property in the Xml data by its name
             * @param name The name of the property
             * @tparam T The type of the property
             * @param value The value of the property
             */
            template<typename T>
            void saveProperty(std::string propertyName, safe_ptr<T> &toSave)
            {
                manager->save(propertyName, toSave);
            }


        protected:
            /**
             * @brief Sets a property from the Xml data by its name
             * @param name The name of the property
             * @tparam T The type of the property
             * @param value The property to set
             */
            template<typename T>
            void _setProperty(const std::string &propertyName, std::shared_ptr<T> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                manager->set(propertyName, toSet, level);
            }

            /**
             * @brief Sets a property from the Xml data by its name
             * @param name The name of the property
             * @tparam T The type of the property
             * @param value The property to set
             */
            template<typename T>
            void _setProperty(const std::string &propertyName, safe_ptr<T> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                manager->set(propertyName, toSet, level);
            }

            /**
             * @brief Sets a property from the Xml data by its name
             * @param name The name of the property
             * @tparam T The type of the property
             * @param value The property to set
             */
            template<typename T>
            void _setProperty(const std::string &propertyName, T &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                manager->XmlPropertyManager::set(propertyName, toSet, level);
            }
//////////////////////--------------------------/////////////////////////
    };

} // api
