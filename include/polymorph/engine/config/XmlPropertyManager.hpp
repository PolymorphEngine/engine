/*
** EPITECH PROJECT, 2020
** XmlPropertyManager.hpp
** File description:
** header for XmlPropertyManager.c
*/


#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <unordered_map>

#include "myxmlpp/myxmlpp.hpp"

#include "polymorph/engine/core/Engine.hpp"
#include "polymorph/engine/core/entity/Entity.hpp"
#include "polymorph/engine/core/component/AComponent.hpp"

#include "polymorph/engine/api/SceneManager.hpp"
#include "polymorph/engine/api/plugin/APluginConfig.hpp"

#include "polymorph/engine/debug/Logger.hpp"
#include "polymorph/engine/config/CastHelper.hpp"
#include "polymorph/engine/types/safe/safe_ptr.hpp"

namespace polymorph::engine
{
    class Entity;
    class AComponent;

    using GameObject = safe_ptr<Entity>;
}

namespace polymorph::engine::config
{
    /**
     * @class XmlPropertyManager
     * @brief This class is used to extract properties from Xml
     */
    class XmlPropertyManager
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            XmlPropertyManager(std::shared_ptr<myxmlpp::Node> node, debug::Logger& logger);

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:


        protected:
            std::shared_ptr<myxmlpp::Node> node;
            debug::Logger& _logger;





//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:

            std::shared_ptr<myxmlpp::Node> getNode();




            
            
            
            





// section PRIMITIVE/BUILTIN
            /**
             * @brief Extract a PRIMITIVE property from the xml node
             *
             * @tparam T The type of the property
             * @param propertyName The name of the property
             * @param toSet The property to set
             * @param level The level of the error if something goes wrong (not found or wrong value)
             */
            template<typename T, typename T2 = void>
            void set(const std::string &propertyName, T &toSet, Engine &entity, std::string type, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                if constexpr (std::is_enum<T>() && !CastHelper::is_builtin<T>)
                    _setPrimitiveProperty(property, reinterpret_cast<int &>(toSet), level);
                else if constexpr (!std::is_enum<T>() && !CastHelper::is_builtin<T>)
                    _setPrimitiveProperty(property, toSet, level);
                else if constexpr (CastHelper::is_builtin<T>)
                    _setBuiltinProperty(property, toSet, entity.getPluginManager().getConfig(type), level);
            };
            
            /**
             * @brief Extract a PRIMITIVE property from the xml node
             *
             * @tparam T The type of the property
             * @param propertyName The name of the property
             * @param toSet The property to set
             * @param level The level of the error if something goes wrong (not found or wrong value)
             */
            template<typename T, typename T2 = void>
            void set(const std::string &propertyName, T &toSet, safe_ptr<api::APluginConfig> config, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                if constexpr (std::is_enum<T>() && !CastHelper::is_builtin<T>)
                    _setPrimitiveProperty(property, reinterpret_cast<int &>(toSet), level);
                else if constexpr (!std::is_enum<T>() && !CastHelper::is_builtin<T>)
                    _setPrimitiveProperty(property, toSet, level);
                else if constexpr (CastHelper::is_builtin<T>)
                    _setBuiltinProperty(property, toSet, config, level);
            };
            
            /**
             * @brief Extract a PRIMITIVE property from the xml node
             *
             * @tparam T The type of the property
             * @param propertyName The name of the property
             * @param toSet The property to set
             * @param level The level of the error if something goes wrong (not found or wrong value)
             */
            template<typename T, typename T2 = void>
            void set(const std::string &propertyName, T &toSet, safe_ptr<AComponent> config, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                if constexpr (std::is_enum<T>() && !CastHelper::is_builtin<T>)
                    _setPrimitiveProperty(property, reinterpret_cast<int &>(toSet), level);
                else if constexpr (!std::is_enum<T>() && !CastHelper::is_builtin<T>)
                    _setPrimitiveProperty(property, toSet, level);
                else if constexpr (CastHelper::is_builtin<T>)
                    _setBuiltinProperty(property, toSet, config, level);
            };
            
            template<typename T, typename T2 = void>
            void set(const std::string &propertyName, T &toSet, GameObject entity, std::string type, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                if constexpr (std::is_enum<T>() && !CastHelper::is_builtin<T>)
                    _setPrimitiveProperty(property, reinterpret_cast<int &>(toSet), level);
                else if constexpr (!std::is_enum<T>() && !CastHelper::is_builtin<T>)
                    _setPrimitiveProperty(property, toSet, level);
                else if constexpr (CastHelper::is_builtin<T>)
                    _setBuiltinProperty(property, toSet, entity, type, level);
            };


            /**
             * @brief Set Property INT Specialization
             */
            void _setPrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data,
                                       int &toSet, debug::Logger::severity level)
            {
                _setPropertyFromAttr(toSet, data, level);
            }

            /**
             * @brief Set Property FLOAT Specialization
             */
            void _setPrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data,
                                       float &toSet, debug::Logger::severity level)
            {
                _setPropertyFromAttr(toSet, data, level);
            }

            /**
             * @brief Set Property BOOL Specialization
             */
            void _setPrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data,
                                       bool &toSet, debug::Logger::severity level)
            {
                _setPropertyFromAttr(toSet, data, level);
            }

            /**
             * @brief Set Property STRING Specialization
             */
            void _setPrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data,
                                       std::string &toSet,
                                       debug::Logger::severity level)
            {
                _setPropertyFromAttr(toSet, data, level);
            }

            /**
 * @brief Set Property BUILTIN Specialization
 */
            template<typename T, typename T2 = void>
            void _setBuiltinProperty(std::shared_ptr<myxmlpp::Node> &data, T &toSet, safe_ptr<api::APluginConfig> _config,
                                     debug::Logger::severity level = debug::Logger::DEBUG)
            {
                static_assert(!CastHelper::is_map<T>
                              && !CastHelper::is_vector<T>
                              && !CastHelper::is_safeptr<T>
                              && !std::is_enum<T>()
                              && CastHelper::is_builtin<T>);
                toSet = T(_config, data);
            };

            /**
             * @brief Set Property BUILTIN Specialization
             */
            template<typename T, typename T2 = void>
            void _setBuiltinProperty(std::shared_ptr<myxmlpp::Node> &data, T &toSet, safe_ptr<AComponent> _component,
                                     debug::Logger::severity level = debug::Logger::DEBUG)
            {
                static_assert(!CastHelper::is_map<T>
                              && !CastHelper::is_vector<T>
                              && !CastHelper::is_safeptr<T>
                              && !std::is_enum<T>()
                              && CastHelper::is_builtin<T>);
                toSet = T(_component, data);
            };
            
            /**
 * @brief Set Property BUILTIN Specialization
 */
            template<typename T, typename T2 = void> requires CastHelper::is_builtin<T>
            void _setBuiltinProperty(std::shared_ptr<myxmlpp::Node> &data, T &toSet,
                                     GameObject entity, std::string _type,
                                     debug::Logger::severity level = debug::Logger::DEBUG)
            {
                static_assert(!CastHelper::is_map<T>
                              && !CastHelper::is_vector<T>
                              && !CastHelper::is_safeptr<T>
                              && !std::is_enum<T>()
                              && CastHelper::is_builtin<T>);
                toSet = T(entity->getComponent(_type), data);
            };


            /**
             * @brief Extract an PRIMITIVE SUB-property from the xml node
             *
             * @tparam T The type of the property
             * @param propertyName The name of the property
             * @param data The node to search the sub-property in
             * @param toSet The property to set
             * @param level The level of the error if something goes wrong (not found or wrong value)
             */
            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 T &toSet, GameObject entity, std::string type,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                if constexpr (std::is_enum<T>())
                    _setPrimitiveProperty(property, reinterpret_cast<int &>(toSet), level);
                else if constexpr (!std::is_enum<T>() && !CastHelper::is_builtin<T>)
                    _setPrimitiveProperty(property, toSet, level);
                else if constexpr (CastHelper::is_builtin<T>)
                    _setBuiltinProperty(property, toSet, entity, type, level);
            };
            /**
             * @brief Extract an PRIMITIVE SUB-property from the xml node
             *
             * @tparam T The type of the property
             * @param propertyName The name of the property
             * @param data The node to search the sub-property in
             * @param toSet The property to set
             * @param level The level of the error if something goes wrong (not found or wrong value)
             */
            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 T &toSet, Engine &entity, std::string type,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                if constexpr (std::is_enum<T>())
                    _setPrimitiveProperty(property, reinterpret_cast<int &>(toSet), level);
                else if constexpr (!std::is_enum<T>() && !CastHelper::is_builtin<T>)
                    _setPrimitiveProperty(property, toSet, level);
                else if constexpr (CastHelper::is_builtin<T>)
                    _setBuiltinProperty(property, toSet, entity, type, level);
            };
            
            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 T &toSet, safe_ptr<AComponent> component,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                if constexpr (std::is_enum<T>())
                    _setPrimitiveProperty(property, reinterpret_cast<int &>(toSet), level);
                else if constexpr (!std::is_enum<T>() && !CastHelper::is_builtin<T>)
                    _setPrimitiveProperty(property, toSet, level);
                else if constexpr (CastHelper::is_builtin<T>)
                    _setBuiltinProperty(property, toSet, component, level);
            };

            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 T &toSet, safe_ptr<api::APluginConfig> config,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                if constexpr (std::is_enum<T>())
                    _setPrimitiveProperty(property, reinterpret_cast<int &>(toSet), level);
                else if constexpr (!std::is_enum<T>() && !CastHelper::is_builtin<T>)
                    _setPrimitiveProperty(property, toSet, level);
                else if constexpr (CastHelper::is_builtin<T>)
                    _setBuiltinProperty(property, toSet, config, level);
            };


            /**
 * @brief Extract a PRIMITIVE property from the xml node
 *
 * @tparam T The type of the property
 * @param propertyName The name of the property
 * @param toSet The property to set
 * @param level The level of the error if something goes wrong (not found or wrong value)
 */
            template<typename T>
            void save(const std::string &propertyName, T &toSave, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                if constexpr (std::is_enum<T>())
                    _savePrimitiveProperty<int>(property, reinterpret_cast<int &>(toSave), level);
                else if constexpr (!std::is_enum<T>())
                    _savePrimitiveProperty(property, toSave, level);
            };

            template<typename T, typename T2 = void>
            void _savePrimitiveProperty(std::shared_ptr<myxmlpp::Node> &_, T &toSet,
                                        debug::Logger::severity _2 = debug::Logger::DEBUG)
            {
                (void)_; 
                (void)_2;
                static_assert(!CastHelper::is_map<T>
                              && !CastHelper::is_vector<T>
                              && !CastHelper::is_safeptr<T>
                              && !std::is_enum<T>()
                              && CastHelper::is_builtin<T>);
                toSet.saveAll();
            };

            /**
             * @brief Set Property INT Specialization
             */
            template<typename T2 = void>
            void _savePrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data,
                                        int &toSet, debug::Logger::severity level)
            {
                _savePropertyFromAttr(toSet, data, level);
            }

            /**
             * @brief Set Property FLOAT Specialization
             */
            template<typename T2 = void>
            void _savePrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data,
                                        float &toSet, debug::Logger::severity level)
            {
                _savePropertyFromAttr(toSet, data, level);
            }

            /**
             * @brief Set Property BOOL Specialization
             */
            template<typename T2 = void>
            void _savePrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data,
                                        bool &toSet, debug::Logger::severity level)
            {
                _savePropertyFromAttr(toSet, data, level);
            }

            /**
             * @brief Set Property STRING Specialization
             */
            template<typename T2 = void>
            void _savePrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data,
                                        std::string &toSet,
                                        debug::Logger::severity level)
            {
                _savePropertyFromAttr(toSet, data, level);
            }


            template<typename T>
            void _saveSubProperty(const std::string &propertyName,
                                  const std::shared_ptr<myxmlpp::Node> &data,
                                  T &toSet,
                                  debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                if constexpr (std::is_enum<T>())
                    _savePrimitiveProperty<int>(property, reinterpret_cast<int &>(toSet), level);
                else if constexpr (!std::is_enum<T>())
                    _savePrimitiveProperty<T>(property, toSet, level);
            };
            
///////////////////////////// XML PRIMITIVE AND BUILTIN SETTERS END //////////////////////////////























// section REFERENCES

            template<typename T>
            void set(const std::string &propertyName, safe_ptr<T> &toSet, GameObject entity, std::string type, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                _setRefProperty<T>(property, toSet, entity, level);
            };

            template<typename T>
            void set(const std::string &propertyName, safe_ptr<T> &toSet, safe_ptr<AComponent> component, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                _setRefProperty<T>(property, toSet, component, level);
            };



            template<typename T, typename T2 = void>
            void _setRefProperty(std::shared_ptr<myxmlpp::Node> &refProp,
                                 safe_ptr<T> &toSet, GameObject entity,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::string id;
                std::string name = refProp->findAttribute("name")->getValue();
                GameObject gameObject;

                if (!_setPropertyFromAttr(id, refProp, level))
                    return;
                if (entity && (entity->getPrefabId() == id || entity->getId() == id))
                    gameObject = entity;
                if (!gameObject && entity->wasPrefab())
                    gameObject = entity->findByPrefabId(id);
                else if (!gameObject)
                    gameObject = entity->Scene.findById(id);
                if (gameObject)
                    toSet = gameObject->getComponent<T>();
                if (!toSet)
                    _onWrongValueExcept(level, name, id);
            };

            template<typename T2 = void>
            void _setRefProperty(std::shared_ptr<myxmlpp::Node> &refProp, GameObject &toSet,
                                 GameObject &entity, debug::Logger::severity level)
            {
                std::string id;
                std::string name = refProp->findAttribute("name")->getValue();

                if (!_setPropertyFromAttr(id, refProp, level))
                    return;
                if (entity && (entity->getPrefabId() == id || entity->getId() == id))
                    toSet = entity;
                if (!toSet && entity)
                    toSet = entity->findByPrefabId(id);
                if (!toSet)
                    toSet = entity->Scene.findById(id);
                if (!toSet)
                    _onWrongValueExcept(level, name, id);
            };
            template<typename T, typename T2 = void>
            void _setRefProperty(std::shared_ptr<myxmlpp::Node> &refProp,
                                 safe_ptr<T> &toSet, safe_ptr<AComponent> _component,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::string id;
                std::string name = refProp->findAttribute("name")->getValue();
                GameObject gameObject;

                if (!_setPropertyFromAttr(id, refProp, level))
                    return;
                if (_component && (_component->gameObject->getPrefabId() == id || _component->gameObject->getId() == id))
                    gameObject = _component->gameObject;
                if (!gameObject && _component->gameObject->wasPrefab())
                    gameObject = _component->gameObject->findByPrefabId(id);
                else if (!gameObject)
                    gameObject = _component->Scene.findById(id);
                if (gameObject)
                    toSet = gameObject->getComponent<T>();
                if (!toSet)
                    _onWrongValueExcept(level, name, id);
            };

            template<typename T, typename T2 = void>
            void _setRefProperty(std::shared_ptr<myxmlpp::Node> &refProp,
                                 safe_ptr<T> &toSet, safe_ptr<api::APluginConfig> _component,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::string id;
                std::string name = refProp->findAttribute("name")->getValue();
                GameObject gameObject;

                if (!_setPropertyFromAttr(id, refProp, level))
                    return;
                else if (!gameObject)
                    gameObject = _component->Scene.findById(id);
                if (gameObject)
                    toSet = gameObject->getComponent<T>();
                if (!toSet)
                    _onWrongValueExcept(level, name, id);
            };

            template<typename T2 = void>
            void _setRefProperty(std::shared_ptr<myxmlpp::Node> &refProp, GameObject &toSet,
                                 safe_ptr<AComponent> _component, debug::Logger::severity level)
            {
                std::string id;
                std::string name = refProp->findAttribute("name")->getValue();

                if (!_setPropertyFromAttr(id, refProp, level))
                    return;
                if (_component && (_component->gameObject->getPrefabId() == id || _component->gameObject->getId() == id))
                    toSet = _component->gameObject;
                if (!toSet && _component->gameObject)
                    toSet = _component->gameObject->findByPrefabId(id);
                if (!toSet)
                    toSet = _component->Scene.findById(id);
                if (!toSet)
                    _onWrongValueExcept(level, name, id);
            };
            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 safe_ptr<T> &toSet, safe_ptr<AComponent> _component,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                _setRefProperty(property, toSet, _component, level);
            };
            
            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 safe_ptr<T> &toSet, safe_ptr<api::APluginConfig> _component,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                _setRefProperty(property, toSet, _component, level);
            };
            
            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 safe_ptr<T> &toSet, GameObject entity, std::string type,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                _setRefProperty(property, toSet, entity, level);
            };

            
            template<typename T>
            void save(const std::string &propertyName, safe_ptr<T> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                _saveRefProperty(property, toSet, level);
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

            template<typename T>
            void _saveSubProperty(const std::string &propertyName,
                                  const std::shared_ptr<myxmlpp::Node> &data,
                                  safe_ptr<T> &toSet,
                                  debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                if constexpr (std::is_enum<T>())
                    _savePrimitiveProperty<int>(property, reinterpret_cast<int &>(toSet), level);
                else if constexpr (!std::is_enum<T>())
                    _saveRefProperty<T>(property, toSet, level);
            };

//////////////////////// XML REFERENCE SETTERS END ////////////////////////



























// section SERIALIZABLES
            template<typename T>
            void set(const std::string &propertyName, std::shared_ptr<T> &toSet, GameObject entity, std::string type, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                _setSerializableProperty(property, toSet, entity, type, level);
            };
            
            template<typename T>
            void set(const std::string &propertyName, std::shared_ptr<T> &toSet, safe_ptr<AComponent> component, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                _setSerializableProperty(property, toSet, component, level);
            };
            
            template<typename T>
            void set(const std::string &propertyName, std::shared_ptr<T> &toSet, safe_ptr<api::APluginConfig> config, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                _setSerializableProperty(property, toSet, config, level);
            };
            
            template<typename T>
            void set(const std::string &propertyName, std::shared_ptr<T> &toSet, Engine &engine, std::string type, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                _setSerializableProperty(property, toSet, engine, type, level);
            };



            template<typename T, typename T2 = void>
            void _setSerializableProperty(std::shared_ptr<myxmlpp::Node> &data,
                                          std::shared_ptr<T> &toSet, GameObject entity, std::string _type,
                                          debug::Logger::severity level = debug::Logger::DEBUG)
            {
                static_assert(!CastHelper::is_map<T>
                              && !CastHelper::is_vector<T>
                              && !CastHelper::is_safeptr<T>
                              && !std::is_enum<T>());
                if constexpr (CastHelper::is_builtin<T>)
                    return std::make_shared<T>(data, *this);
                else {
                    auto t = data->findAttribute("subtype")->getValue();
                    try {
                        toSet = std::dynamic_pointer_cast<T>(entity->Plugin.tryCreateComponentObject(t, data, entity->getComponent(_type)));
                    }  catch (debug::ExceptionLogger &e) {
                        if (level != debug::Logger::MAJOR)
                            e.what();
                    }
                }
            };

            template<typename T, typename T2 = void>
            void _setSerializableProperty(std::shared_ptr<myxmlpp::Node> &data,
                                          std::shared_ptr<T> &toSet, safe_ptr<AComponent> _component,
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
                        toSet = std::dynamic_pointer_cast<T>(_component->Plugin.tryCreateComponentObject(t, data, _component));
                    }  catch (debug::ExceptionLogger &e) {
                        if (level == debug::Logger::MAJOR)
                            e.what();
                    }
                }
            };

            template<typename T, typename T2 = void>
            void _setSerializableProperty(std::shared_ptr<myxmlpp::Node> &data,
                                          std::shared_ptr<T> &toSet, safe_ptr<api::APluginConfig> _config,
                                          debug::Logger::severity level = debug::Logger::DEBUG)
            {
                static_assert(!CastHelper::is_map<T>
                              && !CastHelper::is_vector<T>
                              && !CastHelper::is_safeptr<T>
                              && !std::is_enum<T>());
                if constexpr (CastHelper::is_builtin<T>)
                    return std::make_shared<T>(data, *this);
                else {
                    auto t = data->findAttribute("subtype")->getValue();
                    try {
                        toSet = std::dynamic_pointer_cast<T>(_config->Plugin.tryCreateConfigObject(t, data, _config));
                    }  catch (debug::ExceptionLogger &e) {
                        if (level == debug::Logger::MAJOR)
                            e.what();
                    }
                }
            };

            template<typename T, typename T2 = void>
            void _setSerializableProperty(std::shared_ptr<myxmlpp::Node> &data,
                                          std::shared_ptr<T> &toSet, Engine &_engine, std::string _type,
                                          debug::Logger::severity level = debug::Logger::DEBUG)
            {
                static_assert(!CastHelper::is_map<T>
                              && !CastHelper::is_vector<T>
                              && !CastHelper::is_safeptr<T>
                              && !std::is_enum<T>());
                if constexpr (CastHelper::is_builtin<T>)
                    return std::make_shared<T>(data, *this);
                else {
                    auto t = data->findAttribute("subtype")->getValue();
                    try {
                        toSet = std::dynamic_pointer_cast<T>(_engine.getPluginManager().tryCreateConfigObject(t, data, _engine.getPluginManager().getConfig(_type)));
                    }  catch (debug::ExceptionLogger &e) {
                        if (level != debug::Logger::MAJOR)
                            e.what();
                    }
                }
            };

            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::shared_ptr<T> &toSet, Engine &_engine, std::string _type,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setSerializableProperty(property, toSet, _engine, _type, level);
            };

            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::shared_ptr<T> &toSet, safe_ptr<api::APluginConfig> _config,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setSerializableProperty(property, toSet, _config, level);
            };

            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::shared_ptr<T> &toSet, safe_ptr<AComponent> _component,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setSerializableProperty(property, toSet, _component, level);
            };

            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::shared_ptr<T> &toSet, GameObject entity, std::string type,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setSerializableProperty(property, toSet, entity, type, level);
            };

            template<typename T>
            void save(const std::string &propertyName, std::shared_ptr<T> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                static_assert(!CastHelper::is_map<T>);
                toSet->saveAll();
            };

            template<typename T>
            void _saveSubProperty(const std::string &propertyName,
                                  const std::shared_ptr<myxmlpp::Node> &data,
                                  std::shared_ptr<T> &toSet,
                                  debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (propertyName != "")
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                toSet->saveAll();
            };

//////////////////////// XML SERIALIZABLE SETTERS END ////////////////////////






















// section VECTORS
            /**
             * @brief Extract a VECTOR property from the xml node
             *
             * @tparam T The type of the property
             * @param propertyName The name of the property
             * @param toSet The property to set
             * @param level The level of the error if something goes wrong (not found or wrong value)
             */

            template<typename T>
            void set(const std::string &propertyName, std::vector<T> &toSet, GameObject &entity, std::string &type, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                _setVectorProperty(property, toSet, entity, type, level);
            };

            template<typename T>
            void set(const std::string &propertyName, std::vector<T> &toSet, safe_ptr<AComponent> component, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                _setVectorProperty(property, toSet, component, level);
            };

            template<typename T>
            void set(const std::string &propertyName, std::vector<T> &toSet, safe_ptr<api::APluginConfig> config, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                _setVectorProperty(property, toSet, config, level);
            };

            template<typename T>
            void set(const std::string &propertyName, std::vector<T> &toSet, Engine &engine, std::string _type, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                _setVectorProperty(property, toSet, engine, _type, level);
            };

            /**
 * @brief Set Property VECTOR Specialization
 */
            template<typename T>
            void _setVectorProperty(std::shared_ptr<myxmlpp::Node> &data,
                                    std::vector<T> &toSet, GameObject entity, std::string type,
                                    debug::Logger::severity level = debug::Logger::DEBUG)
            {
                for (auto &elem: *data)
                {
                    T tmp;

                    _setSubProperty("", elem, tmp, entity, type, level);
                    toSet.push_back(tmp);
                }
            };
            /**
             * @brief Set Property VECTOR Specialization
             */
            template<typename T>
            void _setVectorProperty(std::shared_ptr<myxmlpp::Node> &data,
                                    std::vector<T> &toSet, Engine &engine, std::string type,
                                    debug::Logger::severity level = debug::Logger::DEBUG)
            {
                for (auto &elem: *data)
                {
                    T tmp;

                    _setSubProperty("", elem, tmp, engine, type, level);
                    toSet.push_back(tmp);
                }
            };
            
            /**
             * @brief Set Property VECTOR Specialization
             */
            template<typename T>
            void _setVectorProperty(std::shared_ptr<myxmlpp::Node> &data,
                                    std::vector<T> &toSet, safe_ptr<AComponent> component,
                                    debug::Logger::severity level = debug::Logger::DEBUG)
            {
                for (auto &elem: *data)
                {
                    T tmp;

                    _setSubProperty("", elem, tmp, component, level);
                    toSet.push_back(tmp);
                }
            };
            
            /**
             * @brief Set Property VECTOR Specialization
             */
            template<typename T>
            void _setVectorProperty(std::shared_ptr<myxmlpp::Node> &data,
                                    std::vector<T> &toSet, safe_ptr<api::APluginConfig> config,
                                    debug::Logger::severity level = debug::Logger::DEBUG)
            {
                for (auto &elem: *data)
                {
                    T tmp;

                    _setSubProperty("", elem, tmp, config, level);
                    toSet.push_back(tmp);
                }
            };

            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::vector<T> &toSet, GameObject entity, std::string type,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setVectorProperty(property, toSet, entity, type, level);
            };

            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::vector<T> &toSet, Engine &engine, std::string type,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setVectorProperty(property, toSet, engine, type, level);
            };
            
            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::vector<T> &toSet, safe_ptr<AComponent> component,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setVectorProperty(property, toSet, component, level);
            };

            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::vector<T> &toSet, safe_ptr<api::APluginConfig> config,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setVectorProperty(property, toSet, config, level);
            };

            /**
 * @brief Extract a VECTOR property from the xml node
 *
 * @tparam T The type of the property
 * @param propertyName The name of the property
 * @param toSave The property to set
 * @param level The level of the error if something goes wrong (not found or wrong value)
 */
            template<typename T>
            void save(const std::string &propertyName, std::vector<T> &toSave, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                _saveVectorProperty(property, toSave, level);
            };

            /**
 * @brief Set Property VECTOR Specialization
 */
            template<typename T>
            void _saveVectorProperty(std::shared_ptr<myxmlpp::Node> &data,
                                     std::vector<T> &toSet,
                                     debug::Logger::severity level = debug::Logger::DEBUG)
            {
                int i = 0;
                int countToPop = 0;

                std::vector<std::shared_ptr<myxmlpp::Node>> toKeep;

                for (auto &elem: *data)
                {
                    if (i >= toSet.size()) {
                        countToPop++;
                        continue;
                    }
                    _saveSubProperty("", elem, toSet[i], level);
                    i++;
                }
                toKeep.insert(toKeep.end(), data->begin(), data->begin() + i);
                data->rmChildren();
                for (auto &elem: toKeep)
                    data->addChild(elem);
            };


            /**
 * @brief Extract an VECTOR SUB-property from the xml node
 *
 * @tparam T The type of the property
 * @param propertyName The name of the property
 * @param data The node to search the sub-property in
 * @param toSet The property to set
 * @param level The level of the error if something goes wrong (not found or wrong value)
 */
            template<typename T>
            void _saveSubProperty(const std::string &propertyName,
                                  const std::shared_ptr<myxmlpp::Node> &data,
                                  std::vector<T> &toSet,
                                  debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                static_assert(!CastHelper::is_map<T>);
                _saveVectorProperty<T>(property, toSet, level);
            };

//////////////////////// XML VECTOR SETTERS END ////////////////////////

























// section MAPS
            /**
             * @brief Extract a MAP property from the xml node
             *
             * @tparam T1 The type of the Key
             * @tparam T2 The type of the Value
             * @param propertyName The name of the property
             * @param toSet The property to set
             * @param level The level of the error if something goes wrong (not found or wrong value)
             */
            template<typename T1, typename T2>
            void set(const std::string &propertyName, std::map<T1, T2> &toSet, GameObject entity, std::string type, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setMapProperty<T1, T2>(property, toSet, entity, type, level);
            };

            /**
             * @brief Extract a MAP property from the xml node
             *
             * @tparam T1 The type of the Key
             * @tparam T2 The type of the Value
             * @param propertyName The name of the property
             * @param toSet The property to set
             * @param level The level of the error if something goes wrong (not found or wrong value)
             */
            template<typename T1, typename T2>
            void set(const std::string &propertyName, std::map<T1, T2> &toSet, Engine &engine, std::string type, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setMapProperty<T1, T2>(property, toSet, engine, type, level);
            };

            /**
             * @brief Extract a MAP property from the xml node
             *
             * @tparam T1 The type of the Key
             * @tparam T2 The type of the Value
             * @param propertyName The name of the property
             * @param toSet The property to set
             * @param level The level of the error if something goes wrong (not found or wrong value)
             */
            template<typename T1, typename T2>
            void set(const std::string &propertyName, std::map<T1, T2> &toSet, safe_ptr<AComponent> component, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setMapProperty<T1, T2>(property, toSet, component, level);
            };

            /**
             * @brief Extract a MAP property from the xml node
             *
             * @tparam T1 The type of the Key
             * @tparam T2 The type of the Value
             * @param propertyName The name of the property
             * @param toSet The property to set
             * @param level The level of the error if something goes wrong (not found or wrong value)
             */
            template<typename T1, typename T2>
            void set(const std::string &propertyName, std::map<T1, T2> &toSet, safe_ptr<api::APluginConfig> config, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setMapProperty<T1, T2>(property, toSet, config, level);
            };


            /**
             * @brief Set Property MAP Specialization
             */
            template<typename T1, typename T2>
            void _setMapProperty(std::shared_ptr<myxmlpp::Node> &data,
                                 std::map<T1, T2> &toSet, GameObject entity, std::string type,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                for (auto &elem: *data)
                {
                    T1 key;
                    auto keyElem = elem->begin();
                    T2 value;
                    auto valueElem = elem->begin() + 1;
                    _setSubProperty("", *keyElem, key, entity, type, level);
                    _setSubProperty("", *valueElem, value, entity, type, level);
                    toSet.insert_or_assign(key, value);
                }
            };

            template<typename T1, typename T2>
            void _setMapProperty(std::shared_ptr<myxmlpp::Node> &data,
                                 std::map<T1, T2> &toSet, Engine &entity, std::string type,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                for (auto &elem: *data)
                {
                    T1 key;
                    auto keyElem = elem->begin();
                    T2 value;
                    auto valueElem = elem->begin() + 1;
                    _setSubProperty("", *keyElem, key, entity, type, level);
                    _setSubProperty("", *valueElem, value, entity, type, level);
                    toSet.insert_or_assign(key, value);
                }
            };

            template<typename T1, typename T2>
            void _setMapProperty(std::shared_ptr<myxmlpp::Node> &data,
                                 std::map<T1, T2> &toSet, safe_ptr<AComponent> &entity,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                for (auto &elem: *data)
                {
                    T1 key;
                    auto keyElem = elem->begin();
                    T2 value;
                    auto valueElem = elem->begin() + 1;
                    _setSubProperty("", *keyElem, key, entity, level);
                    _setSubProperty("", *valueElem, value, entity, level);
                    toSet.insert_or_assign(key, value);
                }
            };

            template<typename T1, typename T2>
            void _setMapProperty(std::shared_ptr<myxmlpp::Node> &data,
                                 std::map<T1, T2> &toSet, safe_ptr<api::APluginConfig> &entity,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                for (auto &elem: *data)
                {
                    T1 key;
                    auto keyElem = elem->begin();
                    T2 value;
                    auto valueElem = elem->begin() + 1;
                    _setSubProperty("", *keyElem, key, entity, level);
                    _setSubProperty("", *valueElem, value, entity, level);
                    toSet.insert_or_assign(key, value);
                }
            };

            template<typename T1, typename T2>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::map<T1, T2> &toSet, safe_ptr<api::APluginConfig> config,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setMapProperty<T1, T2>(property, toSet, config, level);
            };

            template<typename T1, typename T2>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::map<T1, T2> &toSet, safe_ptr<AComponent> config,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setMapProperty<T1, T2>(property, toSet, config, level);
            };

            template<typename T1, typename T2>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::map<T1, T2> &toSet, GameObject config, std::string type,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setMapProperty<T1, T2>(property, toSet, config, type, level);
            };

            template<typename T1, typename T2>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::map<T1, T2> &toSet, Engine &config, std::string type,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setMapProperty<T1, T2>(property, toSet, config, type, level);
            };

            /**
 * @brief Extract a MAP property from the xml node
 *
 * @tparam T1 The type of the Key
 * @tparam T2 The type of the Value
 * @param propertyName The name of the property
 * @param toSave The property to set
 * @param level The level of the error if something goes wrong (not found or wrong value)
 */
            template<typename T1, typename T2>
            void save(const std::string &propertyName, std::map<T1, T2> &toSave, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _saveMapProperty<T1, T2>(property, toSave, level);
            };



            /**
 * @brief Extract an MAP SUB-property from the xml node
 *
 * @tparam T1 The type of the Key
 * @tparam T2 The type of the Value
 * @param propertyName The name of the property
 * @param data The node to search the sub-property in
 * @param toSet The property to set
 * @param level The level of the error if something goes wrong (not found or wrong value)
 */
            template<typename T1, typename T2>
            void _saveSubProperty(const std::string &propertyName,
                                  const std::shared_ptr<myxmlpp::Node> &data,
                                  std::map<T1, T2> &toSet,
                                  debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _saveMapProperty<T1, T2>(property, toSet, level);
            };


            /**
             * @brief Set Property MAP Specialization
             */
            template<typename T1, typename T2>
            void _saveMapProperty(std::shared_ptr<myxmlpp::Node> &data,
                                  std::map<T1, T2> &toSet,
                                  debug::Logger::severity level = debug::Logger::DEBUG)
            {
                int i = 0;
                int countToPop = 0;

                std::vector<std::string> toPop;
                std::vector<std::shared_ptr<myxmlpp::Node>> toKeep;
                for (auto &elem: *data)
                {
                    if (i >= toSet.size()) {
                        countToPop++;
                        continue;
                    }
                    auto keyElem = elem->begin();
                    auto valueElem = elem->begin() + 1;
                    _saveSubProperty("", *keyElem, (toSet.begin() + i)->first, level);
                    _saveSubProperty("", *valueElem, (toSet.begin() + i)->second, level);
                }
                toKeep.insert(toKeep.end(), data->begin(), data->begin() + i);
                data->rmChildren();
                for (auto &elem: toKeep)
                    data->addChild(elem);

            };
//////////////////////// XML MAP SETTERS END ////////////////////////


















// section UN_MAPS
            /**
             * @brief Extract a MAP property from the xml node
             *
             * @tparam T1 The type of the Key
             * @tparam T2 The type of the Value
             * @param propertyName The name of the property
             * @param toSet The property to set
             * @param level The level of the error if something goes wrong (not found or wrong value)
             */
            template<typename T1, typename T2>
            void set(const std::string &propertyName, std::unordered_map<T1, T2> &toSet, GameObject entity, std::string type, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setUMapProperty<T1, T2>(property, toSet, entity, type, level);
            };

            /**
             * @brief Extract a MAP property from the xml node
             *
             * @tparam T1 The type of the Key
             * @tparam T2 The type of the Value
             * @param propertyName The name of the property
             * @param toSet The property to set
             * @param level The level of the error if something goes wrong (not found or wrong value)
             */
            template<typename T1, typename T2>
            void set(const std::string &propertyName, std::unordered_map<T1, T2> &toSet, Engine &engine, std::string type, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setUMapProperty<T1, T2>(property, toSet, engine, type, level);
            };

            /**
             * @brief Extract a MAP property from the xml node
             *
             * @tparam T1 The type of the Key
             * @tparam T2 The type of the Value
             * @param propertyName The name of the property
             * @param toSet The property to set
             * @param level The level of the error if something goes wrong (not found or wrong value)
             */
            template<typename T1, typename T2>
            void set(const std::string &propertyName, std::unordered_map<T1, T2> &toSet, safe_ptr<AComponent> component, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setUMapProperty<T1, T2>(property, toSet, component, level);
            };

            /**
             * @brief Extract a MAP property from the xml node
             *
             * @tparam T1 The type of the Key
             * @tparam T2 The type of the Value
             * @param propertyName The name of the property
             * @param toSet The property to set
             * @param level The level of the error if something goes wrong (not found or wrong value)
             */
            template<typename T1, typename T2>
            void set(const std::string &propertyName, std::unordered_map<T1, T2> &toSet, safe_ptr<api::APluginConfig> config, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setUMapProperty<T1, T2>(property, toSet, config, level);
            };


            /**
             * @brief Set Property MAP Specialization
             */
            template<typename T1, typename T2>
            void _setUMapProperty(std::shared_ptr<myxmlpp::Node> &data,
                                 std::unordered_map<T1, T2> &toSet, GameObject entity, std::string type,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                for (auto &elem: *data)
                {
                    T1 key;
                    auto keyElem = elem->begin();
                    T2 value;
                    auto valueElem = elem->begin() + 1;
                    _setSubProperty("", *keyElem, key, entity, type, level);
                    _setSubProperty("", *valueElem, value, entity, type, level);
                    toSet.insert_or_assign(key, value);
                }
            };

            template<typename T1, typename T2>
            void _setUMapProperty(std::shared_ptr<myxmlpp::Node> &data,
                                 std::unordered_map<T1, T2> &toSet, Engine &entity, std::string type,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                for (auto &elem: *data)
                {
                    T1 key;
                    auto keyElem = elem->begin();
                    T2 value;
                    auto valueElem = elem->begin() + 1;
                    _setSubProperty("", *keyElem, key, entity, type, level);
                    _setSubProperty("", *valueElem, value, entity, type, level);
                    toSet.insert_or_assign(key, value);
                }
            };

            template<typename T1, typename T2>
            void _setUMapProperty(std::shared_ptr<myxmlpp::Node> &data,
                                 std::unordered_map<T1, T2> &toSet, safe_ptr<AComponent> &entity,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                for (auto &elem: *data)
                {
                    T1 key;
                    auto keyElem = elem->begin();
                    T2 value;
                    auto valueElem = elem->begin() + 1;
                    _setSubProperty("", *keyElem, key, entity, level);
                    _setSubProperty("", *valueElem, value, entity, level);
                    toSet.insert_or_assign(key, value);
                }
            };

            template<typename T1, typename T2>
            void _setUMapProperty(std::shared_ptr<myxmlpp::Node> &data,
                                 std::unordered_map<T1, T2> &toSet, safe_ptr<api::APluginConfig> &entity,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                for (auto &elem: *data)
                {
                    T1 key;
                    auto keyElem = elem->begin();
                    T2 value;
                    auto valueElem = elem->begin() + 1;
                    _setSubProperty("", *keyElem, key, entity, level);
                    _setSubProperty("", *valueElem, value, entity, level);
                    toSet.insert_or_assign(key, value);
                }
            };

            template<typename T1, typename T2>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::unordered_map<T1, T2> &toSet, safe_ptr<api::APluginConfig> config,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setUMapProperty<T1, T2>(property, toSet, config, level);
            };

            template<typename T1, typename T2>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::unordered_map<T1, T2> &toSet, safe_ptr<AComponent> config,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setUMapProperty<T1, T2>(property, toSet, config, level);
            };

            template<typename T1, typename T2>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::unordered_map<T1, T2> &toSet, GameObject config, std::string type,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setUMapProperty<T1, T2>(property, toSet, config, type, level);
            };

            template<typename T1, typename T2>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::unordered_map<T1, T2> &toSet, Engine &config, std::string type,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _setUMapProperty<T1, T2>(property, toSet, config, type, level);
            };

            /**
 * @brief Extract an UNORDERED MAP property from the xml node
 *
 * @tparam T1 The type of the Key
 * @tparam T2 The type of the Value
 * @param propertyName The name of the property
 * @param toSave The property to set
 * @param level The level of the error if something goes wrong (not found or wrong value)
 */
            template<typename T1, typename T2>
            void save(const std::string &propertyName, std::unordered_map<T1, T2> &toSave, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _saveUMapProperty<T1, T2>(property, toSave, level);
            };
            
            /**
 * @brief Set Property UNORDERED MAP Specialization
 */
            template<typename T1, typename T2>
            void _saveUMapProperty(std::shared_ptr<myxmlpp::Node> &data,
                                   std::unordered_map<T1, T2> &toSet,
                                   debug::Logger::severity level = debug::Logger::DEBUG)
            {
                int i = 0;
                int countToPop = 0;

                std::vector<std::string> toPop;
                std::vector<std::shared_ptr<myxmlpp::Node>> toKeep;
                for (auto &elem: *data)
                {
                    if (i >= toSet.size()) {
                        countToPop++;
                        continue;
                    }
                    auto keyElem = elem->begin();
                    auto valueElem = elem->begin() + 1;
                    _saveSubProperty("", *keyElem, (toSet.begin() + i)->first, level);
                    _saveSubProperty("", *valueElem, (toSet.begin() + i)->second, level);
                }
                toKeep.insert(toKeep.end(), data->begin(), data->begin() + i);
                data->rmChildren();
                for (auto &elem: toKeep)
                    data->addChild(elem);
            };

            /**
 * @brief Extract an UNORDERED MAP SUB-property from the xml node
 *
 * @tparam T1 The type of the Key
 * @tparam T2 The type of the Value
 * @param propertyName The name of the property
 * @param data The node to search the sub-property in
 * @param toSet The property to set
 * @param level The level of the error if something goes wrong (not found or wrong value)
 */
            template<typename T1, typename T2>
            void _saveSubProperty(const std::string &propertyName,
                                  const std::shared_ptr<myxmlpp::Node> &data,
                                  std::unordered_map<T1, T2> &toSet,
                                  debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (!propertyName.empty())
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr) {
                    _onMissingPropertyExcept(level, propertyName); 
                   return;
                   }
                _saveUMapProperty<T1, T2>(property, toSet, level);
            };


///////////////////////////// XML UMAP SETTERS END /////////////////////////////


            


        protected:
            /* ***********************************************
             * @group Find property utilities
             * ***********************************************/

            /**
             * @brief Tries to find a property node from name
             * @param name The name of the property to find
             * @return the property found
             */
            std::shared_ptr<myxmlpp::Node> _findProperty(const std::string &name);

            /**
             * @brief Tries to find a property node from name and sub-node
             * @param name The name of the property to find
             * @param data The sub-node to search in
             * @return the property found
             */
            std::shared_ptr<myxmlpp::Node>
            _findProperty(const std::string &name, const std::shared_ptr<myxmlpp::Node> &data);




            /**
             * @brief Tries to set an INT property
             * @param toSet The variable to set
             * @param data The node containing the property
             * @param level The error level if the value is not found or as illegal value
             * @return True if the property is found
             */
            bool
            _setPropertyFromAttr(int &toSet, std::shared_ptr<myxmlpp::Node> data,
             debug::Logger::severity level = debug::Logger::DEBUG);

            /**
             * @brief Tries to set an FLOAT property
             * @param toSet The variable to set
             * @param data The node containing the property
             * @param level The error level if the value is not found or as illegal value
             * @return True if the property is found
             */
            bool
            _setPropertyFromAttr(float &toSet, std::shared_ptr<myxmlpp::Node> data,
            debug::Logger::severity level = debug::Logger::DEBUG);


            /**
             * @brief Tries to set an BOOL property
             * @param toSet The variable to set
             * @param data The node containing the property
             * @param level The error level if the value is not found or as illegal value
             * @return True if the property is found
             */
            bool
            _setPropertyFromAttr(bool &toSet, std::shared_ptr<myxmlpp::Node> data,
            debug::Logger::severity level = debug::Logger::DEBUG);


            /**
             * @brief Tries to set an STRING property
             * @param toSet The variable to set
             * @param data The node containing the property
             * @param level The error level if the value is not found or as illegal value
             * @return True if the property is found
             */
            bool
            _setPropertyFromAttr(std::string &toSet, std::shared_ptr<myxmlpp::Node> data,
            debug::Logger::severity level = debug::Logger::DEBUG);




            /**
             * @brief Tries to set an INT property
             * @param toSet The variable to set
             * @param data The node containing the property
             * @param level The error level if the value is not found or as illegal value
             * @return True if the property is found
             */
            bool
            _savePropertyFromAttr(int &toSet, std::shared_ptr<myxmlpp::Node> data,
             debug::Logger::severity level = debug::Logger::DEBUG);

            /**
             * @brief Tries to set an FLOAT property
             * @param toSet The variable to set
             * @param data The node containing the property
             * @param level The error level if the value is not found or as illegal value
             * @return True if the property is found
             */
            bool
            _savePropertyFromAttr(float &toSet, std::shared_ptr<myxmlpp::Node> data,
            debug::Logger::severity level = debug::Logger::DEBUG);


            /**
             * @brief Tries to set an BOOL property
             * @param toSet The variable to set
             * @param data The node containing the property
             * @param level The error level if the value is not found or as illegal value
             * @return True if the property is found
             */
            bool
            _savePropertyFromAttr(bool &toSet, std::shared_ptr<myxmlpp::Node> data,
            debug::Logger::severity level = debug::Logger::DEBUG);


            /**
             * @brief Tries to set an STRING property
             * @param toSet The variable to set
             * @param data The node containing the property
             * @param level The error level if the value is not found or as illegal value
             * @return True if the property is found
             */
            bool
            _savePropertyFromAttr(std::string &toSet, std::shared_ptr<myxmlpp::Node> data,
            debug::Logger::severity level = debug::Logger::DEBUG);

            /**
             * @brief overridable method to determine logic (log or throw an exception) in case of wrong value in the config of a property
             * @param level The severity of the error
             * @param propertyName the property which has wrong value in configuration
             * @param value the retrieved (wrong) value
             */
            virtual void _onWrongValueExcept(debug::Logger::severity level,
                                             std::string propertyName,
                                             std::string value) = 0;
            /**
             * overridable method to determine logic (log or throw an exception) in case of a missing value for a property in configuration
             * @param level The severity of the error
             * @param propertyName The name of the property which has missing value in configuration
             */
            virtual void _onMissingValueExcept(debug::Logger::severity level, std::string propertyName) = 0;

            /**
             * overridable method to determine logic (log or throw an exception) in case of a missing property in configuration
             * @param level The severity of the error
             * @param propertyName The property which is missing in configuration
             */
            virtual void _onMissingPropertyExcept(debug::Logger::severity level, std::string propertyName) = 0;

//////////////////////--------------------------/////////////////////////

    };

} // config
