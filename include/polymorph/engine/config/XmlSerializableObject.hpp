/*
** EPITECH PROJECT, 2020
** XmlSerializableObject.hpp
** File description:
** header for XmlSerializableObject.c
*/


#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>

#include "myxmlpp/myxmlpp.hpp"

#include "polymorph/engine/debug/Logger.hpp"

#include "polymorph/engine/config/XmlPropertyManager.hpp"

#include "polymorph/engine/types/safe/safe_ptr.hpp"

#include "polymorph/engine/core/component/AComponent.hpp"
#include "polymorph/engine/core/entity/Entity.hpp"
#include "polymorph/engine/api/SceneManager.hpp"
#include "polymorph/engine/api/plugin/PluginManager.hpp"
#include "polymorph/engine/api/plugin/APluginConfig.hpp"



namespace polymorph::engine {
    class Entity;
    class AComponent;
    using GameObject = safe_ptr<Entity>;
    namespace api {
        class APluginConfig;
    }
}


namespace polymorph::engine::config
{

    class XmlSerializableObject : public XmlPropertyManager
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            XmlSerializableObject(safe_ptr<AComponent> component, std::shared_ptr<myxmlpp::Node> &componentNode, debug::Logger& logger);
            XmlSerializableObject(safe_ptr<api::APluginConfig> config, std::shared_ptr<myxmlpp::Node> &componentNode, debug::Logger& logger);

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:


        private:
            safe_ptr<AComponent> _component;
            safe_ptr<api::APluginConfig> _config;
            std::string _type;
            bool _isFromConfig = false;
//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:

            std::string getType() const;
            
            template<typename T>
            void set(std::string property, T &toSet, debug::Logger::severity level = debug::Logger::DEBUG) {
                if (_isFromConfig) {
                    this->XmlPropertyManager::set(property, toSet, _config, level);
                } else {
                    this->XmlPropertyManager::set(property, toSet, _component, level);
                }
            }

            template<typename T>
            void save(std::string property, T &toSet, debug::Logger::severity level = debug::Logger::DEBUG) {
                this->XmlPropertyManager::save(property, toSet, level);
            }
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

            void _onWrongValueExcept(debug::Logger::severity level,
                                     std::string propertyName,
                                     std::string value) override;

            void _onMissingValueExcept(debug::Logger::severity level,
                                       std::string propertyName) override;

            void _onMissingPropertyExcept(debug::Logger::severity level,
                                          std::string propertyName) override;

         //////////////////////--------------------------/////////////////////////

    };

} // config
