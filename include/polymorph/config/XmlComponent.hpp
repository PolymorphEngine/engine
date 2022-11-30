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

#include "polymorph/debug/Logger.hpp"
#include "polymorph/debug/exception/config/MissingValueException.hpp"
#include "polymorph/debug/exception/config/WrongValueException.hpp"

#include "polymorph/config/XmlPropertyManager.hpp"

#include "polymorph/types/safe/safe_ptr.hpp"

#include "polymorph/api/plugin/PluginManager.hpp"

#include "polymorph/core/entity/Entity.hpp"
#include "polymorph/core/Scene.hpp"

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
            void set(const std::string &propertyName, safe_ptr<T> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                static_assert(!CastHelper::is_map<T>);
                _setRefProperty<T>(property, toSet, level);
            };

            template<typename T>
            void save(const std::string &propertyName, safe_ptr<T> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                static_assert(!CastHelper::is_map<T>);
                _saveRefProperty<T>(property, toSet, level);
            };

            template<typename T>
            void set(const std::string &propertyName, std::shared_ptr<T> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                static_assert(!CastHelper::is_map<T>);
                _setSerializableProperty<T>(property, toSet, level);
            };

            template<typename T>
            void save(const std::string &propertyName, std::shared_ptr<T> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                static_assert(!CastHelper::is_map<T>);
                toSet->saveAll();
            };
            
            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                const std::shared_ptr<myxmlpp::Node> &data,
                                std::shared_ptr<T> &toSet,
                                debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (propertyName != "")
                        ? _findProperty(propertyName, data) 
                        : data;

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                _setSerializableProperty<T>(property, toSet, level);
            };

            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                const std::shared_ptr<myxmlpp::Node> &data,
                                safe_ptr<T> &toSet,
                                debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (propertyName != "")
                        ? _findProperty(propertyName, data) 
                        : data;

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                static_assert(!CastHelper::is_map<T>);
                _setRefProperty<T>(property, toSet, level);
            };

            template<typename T, typename T2 = void>
            void _setSerializableProperty(std::shared_ptr<myxmlpp::Node> &data,
                                          std::shared_ptr<T> &toSet,
                                          debug::Logger::severity level = debug::Logger::DEBUG)
            {
                
                //TODO: rework with new XmlSeralizableObject
                static_assert(!CastHelper::is_map<T>
                        && !CastHelper::is_vector<T>
                        && !CastHelper::is_safeptr<T>
                        && !std::is_enum<T>());
                if constexpr (CastHelper::is_builtin<T>)
                    return std::make_shared<T>(data, *this);
                else {
                    auto t = data->findAttribute("subtype")->getValue();
                    try {
                        toSet = std::dynamic_pointer_cast<T>(_entity->Plugin.tryCreateComponentObject(t, data, _entity->getComponent(_type)));
                    }  catch (debug::ExceptionLogger &e) {
                        if (level != debug::Logger::MAJOR)
                            e.what();
                    }
                }
            };


            template<typename T, typename T2 = void>
            void _setRefProperty(std::shared_ptr<myxmlpp::Node> &refProp,
                                 safe_ptr<T> &toSet,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::string id;
                std::string name = refProp->findAttribute("name")->getValue();
                GameObject gameObject;

                if (!_setPropertyFromAttr(id, refProp, level))
                    return;
                if (_entity && (_entity->getPrefabId() == id || _entity->getId() == id))
                    gameObject = _entity;
                if (!gameObject && _entity)
                    gameObject = _entity->findByPrefabId(id);
                if (!gameObject)
                    gameObject = _entity->Scene.findById(id);
                if (gameObject)
                    toSet = gameObject->getComponent<T>();
                if (!toSet)
                    _onWrongValueExcept(level, name, id);
            };

            template<typename T2 = void>
            void _setRefProperty(std::shared_ptr<myxmlpp::Node> &refProp,
                                 GameObject &toSet, debug::Logger::severity level)
            {
                std::string id;
                std::string name = refProp->findAttribute("name")->getValue();

                if (!_setPropertyFromAttr(id, refProp, level))
                    return;
                if (_entity && (_entity->getPrefabId() == id || _entity->getId() == id))
                    toSet = _entity;
                if (!toSet && _entity)
                    toSet = _entity->findByPrefabId(id);
                if (!toSet)
                    toSet = _entity->Scene.findById(id);
                if (!toSet)
                    _onWrongValueExcept(level, name, id);
            };

            template<typename T, typename T2 = void>
            void _saveRefProperty(std::shared_ptr<myxmlpp::Node> &refProp,
                                 safe_ptr<T> &toSet,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::string id = (toSet) ? toSet->gameObject->getId() : "";

                if (!_savePropertyFromAttr(id, refProp, level))
                    return;
            };

            template<typename T2 = void>
            void _saveRefProperty(std::shared_ptr<myxmlpp::Node> &refProp,
                                 GameObject &toSet, debug::Logger::severity level)
            {
                std::string id = (toSet) ? toSet->getId() : "";

                if (!_savePropertyFromAttr(id, refProp, level))
                    return;
            };


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