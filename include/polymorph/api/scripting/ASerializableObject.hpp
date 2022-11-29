/*
** EPITECH PROJECT, 2020
** ASerializableObject.hpp
** File description:
** header for ASerializableObject.c
*/


#pragma once


#include "polymorph/debug/Logger.hpp"
#include "polymorph/config/XmlSerializableObject.hpp"

namespace polymorph::engine::api
{
    class APluginConfig;

    class ASerializableObject
    {
////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            ASerializableObject(safe_ptr<AComponent> component, std::shared_ptr<myxmlpp::Node> node);
            ASerializableObject(safe_ptr<APluginConfig> config, std::shared_ptr<myxmlpp::Node> node);

            virtual ~ASerializableObject() = default;

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:
            config::XmlSerializableObject manager;


        protected:
            debug::Logger &_logger;

        private:
            safe_ptr<AComponent> _component;
            safe_ptr<APluginConfig> _config;
            std::string _type;
            bool _isFromConfig = false;

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            
            /**
             * @brief Virtual Pure method to be implemented in any SerializableObject implementation
             * that will be called when the object is loaded from a file to set all properties
             */
            virtual void build() = 0;

            /**
             * @brief Virtual Pure method to be implemented in any SerializableObject implementation
             * that will be called when the object is Saved to save all properties
             */
            virtual void saveAll() = 0;
            
            /**
             * @brief Returns whether the object is currently stored in a component or in a plugin config file
             * 
             * @return True if the object is stored in a plugin config file, false otherwise
             */
            bool isFromConfig() const;
            
            /**
             * @brief Returns the type of the serializable object
             * @return The string type of the object
             */
            std::string getType() const;
            
            /**
             * @brief Returns the Component that owns the serializable object
             * @tparam T The component type
             * @return The casted safe_ptr of the Component
             */
            template<typename T>
            safe_ptr<T> getComponent() const 
            {
                return safe_ptr<T>(std::dynamic_pointer_cast<T>(*_component));
            }

            /**
             * @brief Returns the PluginConfig that owns the serializable object
             * @tparam T The PluginConfig type
             * @return The casted safe_ptr of the PluginConfig
             */
            template<typename T>
            safe_ptr<T> getPluginConfig() const
            {
                return safe_ptr<T>(std::dynamic_pointer_cast<T>(*_config));
            }
            
            /**
             * @brief Saves a property in the Xml data by its name
             * @param name The name of the property
             * @tparam T The type of the property
             * @param value The value of the property
             */

            template<typename T>
            void saveProperty(std::string propertyName, T &toSave)
            {
                manager.XmlPropertyManager::save(propertyName, toSave);
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
                manager.save(propertyName, toSave);
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
                manager.save(propertyName, toSave);
            }

        protected:
            /**
             * @brief Sets a property from the Xml data by its name
             * @param name The name of the property
             * @tparam T The type of the property
             * @param value The property to set
             */
            template<typename T>
            void setProperty(const std::string &propertyName, std::shared_ptr<T> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                manager.set(propertyName, toSet, level);
            }

            /**
             * @brief Sets a property from the Xml data by its name
             * @param name The name of the property
             * @tparam T The type of the property
             * @param value The property to set
             */
            template<typename T>
            void setProperty(const std::string &propertyName, safe_ptr<T> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                manager.set(propertyName, toSet, level);
            }

            /**
             * @brief Sets a property from the Xml data by its name
             * @param name The name of the property
             * @tparam T The type of the property
             * @param value The property to set
             */
            template<typename T>
            void setProperty(const std::string &propertyName, T &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                manager.XmlPropertyManager::set(propertyName, toSet, level);
            }

//////////////////////--------------------------/////////////////////////

    };

} // api
