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

#include "polymorph/debug/Logger.hpp"
#include "polymorph/config/CastHelper.hpp"
#include "polymorph/types/safe/safe_ptr.hpp"

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
            /**
             * @brief Extract a PRIMITIVE property from the xml node
             *
             * @tparam T The type of the property
             * @param propertyName The name of the property
             * @param toSet The property to set
             * @param level The level of the error if something goes wrong (not found or wrong value)
             */
            template<typename T>
            void set(const std::string &propertyName, T &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                static_assert(!CastHelper::is_map<T>);
                if constexpr (std::is_enum<T>())
                    _setPrimitiveProperty<int>(property, reinterpret_cast<int &>(toSet), level);
                else if constexpr (!std::is_enum<T>())
                    _setPrimitiveProperty<T>(property, toSet, level);
            };

            /**
             * @brief Extract a VECTOR property from the xml node
             *
             * @tparam T The type of the property
             * @param propertyName The name of the property
             * @param toSet The property to set
             * @param level The level of the error if something goes wrong (not found or wrong value)
             */

            template<typename T>
            void set(const std::string &propertyName, std::vector<T> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                static_assert(!CastHelper::is_map<T>);
                _setVectorProperty(property, toSet, level);
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
            void set(const std::string &propertyName, std::map<T1, T2> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                _setMapProperty<T1, T2>(property, toSet, level);
            };

            /**
             * @brief Extract an UNORDERED MAP property from the xml node
             *
             * @tparam T1 The type of the Key
             * @tparam T2 The type of the Value
             * @param propertyName The name of the property
             * @param toSet The property to set
             * @param level The level of the error if something goes wrong (not found or wrong value)
             */
            template<typename T1, typename T2>
            void set(const std::string &propertyName, std::unordered_map<T1, T2> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                _setUMapProperty<T1, T2>(property, toSet, level);
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

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                static_assert(!CastHelper::is_map<T>);
                if constexpr (std::is_enum<T>())
                    _savePrimitiveProperty<int>(property, reinterpret_cast<int &>(toSave), level);
                else if constexpr (!std::is_enum<T>())
                    _savePrimitiveProperty<T>(property, toSave, level);
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

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                static_assert(!CastHelper::is_map<T>);
                _saveVectorProperty(property, toSave, level);
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

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                _saveMapProperty<T1, T2>(property, toSave, level);
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

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                _saveUMapProperty<T1, T2>(property, toSave, level);
            };

            std::shared_ptr<myxmlpp::Node> getNode();







        protected:
            /* ***********************************************
             * @group Set Sub Property specializations
             * ***********************************************/


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
                                 T &toSet,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (propertyName != "")
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                static_assert(!CastHelper::is_map<T>);
                if constexpr (std::is_enum<T>())
                    _setPrimitiveProperty<int>(property, reinterpret_cast<int &>(toSet), level);
                else if constexpr (!std::is_enum<T>())
                    _setPrimitiveProperty<T>(property, toSet, level);
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
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::vector<T> &toSet,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (propertyName != "")
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                static_assert(!CastHelper::is_map<T>);
                _setVectorProperty<T>(property, toSet, level);
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
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::map<T1, T2> &toSet,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (propertyName != "")
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                _setMapProperty<T1, T2>(property, toSet, level);
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
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::unordered_map<T1, T2> &toSet,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (propertyName != "")
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                _setUMapProperty<T1, T2>(property, toSet, level);
            };







            template<typename T>
            void _saveSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 T &toSet,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (propertyName != "")
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                static_assert(!CastHelper::is_map<T>);
                if constexpr (std::is_enum<T>())
                    _savePrimitiveProperty<int>(property, reinterpret_cast<int &>(toSet), level);
                else if constexpr (!std::is_enum<T>())
                    _savePrimitiveProperty<T>(property, toSet, level);
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
                std::shared_ptr<myxmlpp::Node> property = (propertyName != "")
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                static_assert(!CastHelper::is_map<T>);
                _saveVectorProperty<T>(property, toSet, level);
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
                std::shared_ptr<myxmlpp::Node> property = (propertyName != "")
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                _saveMapProperty<T1, T2>(property, toSet, level);
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
                std::shared_ptr<myxmlpp::Node> property = (propertyName != "")
                                                          ? _findProperty(propertyName, data)
                                                          : data;

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                _saveUMapProperty<T1, T2>(property, toSet, level);
            };










            /* ***********************************************
             * @group Set Property Specializations
             * ***********************************************/


            /**
             * @brief Set Property BUILTIN Specialization
             */
            template<typename T, typename T2 = void>
            void _setPrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data, T &toSet,
                                       debug::Logger::severity level = debug::Logger::DEBUG)
            {
                static_assert(!CastHelper::is_map<T>
                              && !CastHelper::is_vector<T>
                              && !CastHelper::is_safeptr<T>
                              && !std::is_enum<T>()
                              && CastHelper::is_builtin<T>);
                toSet = T(data, *this);
            };

            /**
             * @brief Set Property INT Specialization
             */
            template<typename T2 = void>
            void _setPrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data,
                                       int &toSet, debug::Logger::severity level)
            {
                _setPropertyFromAttr(toSet, data, level);
            }

            /**
             * @brief Set Property FLOAT Specialization
             */
            template<typename T2 = void>
            void _setPrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data,
                                       float &toSet, debug::Logger::severity level)
            {
                _setPropertyFromAttr(toSet, data, level);
            }

            /**
             * @brief Set Property BOOL Specialization
             */
            template<typename T2 = void>
            void _setPrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data,
                                       bool &toSet, debug::Logger::severity level)
            {
                _setPropertyFromAttr(toSet, data, level);
            }

            /**
             * @brief Set Property STRING Specialization
             */
            template<typename T2 = void>
            void _setPrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data,
                                       std::string &toSet,
                                       debug::Logger::severity level)
            {
                _setPropertyFromAttr(toSet, data, level);
            }


            /**
             * @brief Set Property VECTOR Specialization
             */
            template<typename T>
            void _setVectorProperty(std::shared_ptr<myxmlpp::Node> &data,
                                    std::vector<T> &toSet,
                                    debug::Logger::severity level = debug::Logger::DEBUG)
            {
                for (auto &elem: *data)
                {
                    T tmp;

                    _setSubProperty("", elem, tmp, level);
                    toSet.push_back(tmp);
                }
            };

            /**
             * @brief Set Property MAP Specialization
             */
            template<typename T1, typename T2>
            void _setMapProperty(std::shared_ptr<myxmlpp::Node> &data,
                                 std::map<T1, T2> &toSet,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                for (auto &elem: *data)
                {
                    T1 key;
                    auto keyElem = elem->begin();
                    T2 value;
                    auto valueElem = elem->begin() + 1;
                    _setSubProperty("", *keyElem, key, level);
                    _setSubProperty("", *valueElem, value, level);
                    toSet.insert_or_assign(key, value);
                }
            };

            /**
             * @brief Set Property UNORDERED MAP Specialization
             */
            template<typename T1, typename T2>
            void _setUMapProperty(std::shared_ptr<myxmlpp::Node> &data,
                                  std::unordered_map<T1, T2> &toSet,
                                  debug::Logger::severity level = debug::Logger::DEBUG)
            {
                for (auto &elem: *data)
                {
                    T1 key;
                    auto keyElem = elem->begin();
                    auto valueElem = elem->begin() + 1;
                    T2 value;
                    _setSubProperty("", *keyElem, key, level);
                    _setSubProperty("", *valueElem, value, level);
                    toSet.emplace(key, value);
                }
            };

            /**
             * @brief Set Property MAP from node Specialization
             */
            template<typename T0, typename T1, typename T2>
            void _setMapPropertyFromNode(std::shared_ptr<myxmlpp::Node> &data,
                                         std::map<T1, T2> &toSet,
                                         debug::Logger::severity level = debug::Logger::DEBUG)
            {
                static_assert(std::is_same<T0, typename std::map<T1, T2>>::value);
                _setMapProperty(data, toSet, level);
            };

            /**
             * @brief Set Property UNORDERED MAP from node Specialization
             */
            template<typename T0, typename T1, typename T2>
            void _setMapPropertyFromNode(std::shared_ptr<myxmlpp::Node> &data,
                                         std::unordered_map<T1, T2> &toSet,
                                         debug::Logger::severity level = debug::Logger::DEBUG)
            {
                static_assert(std::is_same<T0, typename std::unordered_map<T1, T2>>::value);
                _setUMapProperty(data, toSet, level);
            };


                  template<typename T, typename T2 = void>
            void _savePrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data, T &toSet,
                                       debug::Logger::severity level = debug::Logger::DEBUG)
            {
                static_assert(!CastHelper::is_map<T>
                              && !CastHelper::is_vector<T>
                              && !CastHelper::is_safeptr<T>
                              && !std::is_enum<T>()
                              && CastHelper::is_builtin<T>);
                toSet = T(data, *this);
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
             * @brief Set Property MAP from node Specialization
             */
            template<typename T0, typename T1, typename T2>
            void _saveMapPropertyFromNode(std::shared_ptr<myxmlpp::Node> &data,
                                         std::map<T1, T2> &toSet,
                                         debug::Logger::severity level = debug::Logger::DEBUG)
            {
                static_assert(std::is_same<T0, typename std::map<T1, T2>>::value);
                _saveMapProperty(data, toSet, level);
            };

            /**
             * @brief Set Property UNORDERED MAP from node Specialization
             */
            template<typename T0, typename T1, typename T2>
            void _saveMapPropertyFromNode(std::shared_ptr<myxmlpp::Node> &data,
                                         std::unordered_map<T1, T2> &toSet,
                                         debug::Logger::severity level = debug::Logger::DEBUG)
            {
                static_assert(std::is_same<T0, typename std::unordered_map<T1, T2>>::value);
                _saveUMapProperty(data, toSet, level);
            };






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
