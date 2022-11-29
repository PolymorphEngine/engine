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
            virtual void build() = 0;
            bool isFromConfig() const;
            std::string getType() const;
            
            template<typename T>
            safe_ptr<T> getComponent() const 
            {
                return safe_ptr<T>(std::dynamic_pointer_cast<T>(*_component));
            }
            
            template<typename T>
            safe_ptr<T> getPluginConfig() const
            {
                return safe_ptr<T>(std::dynamic_pointer_cast<T>(*_config));
            }
            

        protected:
            template<typename T>
            void setProperty(const std::string &propertyName, std::shared_ptr<T> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                manager.set(propertyName, toSet, level);
            }
            template<typename T>
            void setProperty(const std::string &propertyName, T &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                manager.XmlPropertyManager::set(propertyName, toSet, level);
            }
//////////////////////--------------------------/////////////////////////

    };

} // api
