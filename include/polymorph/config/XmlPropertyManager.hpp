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
            XmlPropertyManager(std::shared_ptr<myxmlpp::Node> &node, debug::Logger& logger);

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:


        protected:
            std::shared_ptr<myxmlpp::Node> node;
            debug::Logger& _logger;


            
            
            
//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            template<typename T>
            void set(const std::string &propertyName, T &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName, level);

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                static_assert(!CastHelper::is_map<T>);
                if constexpr (std::is_enum<T>())
                    _setPrimitiveProperty<int>(property, reinterpret_cast<int &>(toSet), level);
                else if constexpr (!std::is_enum<T>())
                    _setPrimitiveProperty<T>(property, toSet, level);
            };

            template<typename T>
            void set(const std::string &propertyName, std::vector<T> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName, level);

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                static_assert(!CastHelper::is_map<T>);
                _setVectorProperty(property, toSet, level);
            };

            template<typename T1, typename T2>
            void set(const std::string &propertyName, std::map<T1, T2> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName, level);

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                _setMapProperty<T1, T2>(property, toSet, level);
            };

            template<typename T1, typename T2>
            void set(const std::string &propertyName, std::unordered_map<T1, T2> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName, level);

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                _setUMapProperty<T1, T2>(property, toSet, level);
            };

            
            
            
            
            
            

        protected:
            /**
             * @group Set Sub Property specializations
            **/
            
            
            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 T &toSet,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (propertyName != "")
                                                          ? _findProperty(propertyName, data, level)
                                                          : data;

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                static_assert(!CastHelper::is_map<T>);
                if constexpr (std::is_enum<T>())
                    _setPrimitiveProperty<int>(property, reinterpret_cast<int &>(toSet), level);
                else if constexpr (!std::is_enum<T>())
                    _setPrimitiveProperty<T>(property, toSet, level);
            };


            template<typename T>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::vector<T> &toSet,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (propertyName != "")
                                                          ? _findProperty(propertyName, data, level)
                                                          : data;

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                static_assert(!CastHelper::is_map<T>);
                _setVectorProperty<T>(property, toSet, level);
            };

            template<typename T1, typename T2>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::map<T1, T2> &toSet,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (propertyName != "")
                                                          ? _findProperty(propertyName, data, level)
                                                          : data;

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                _setMapProperty<T1, T2>(property, toSet, level);
            };

            template<typename T1, typename T2>
            void _setSubProperty(const std::string &propertyName,
                                 const std::shared_ptr<myxmlpp::Node> &data,
                                 std::unordered_map<T1, T2> &toSet,
                                 debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = (propertyName != "")
                                                          ? _findProperty(propertyName, data, level)
                                                          : data;

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                _setUMapProperty<T1, T2>(property, toSet, level);
            };


            
            
            
            
            



            /**
             * @group Set Property Specializations
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
            
            template<typename T2 = void>
            void _setPrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data,
                                       int &toSet, debug::Logger::severity level)
            {
                _setPropertyFromAttr(toSet, data, level);
            }

            template<typename T2 = void>
            void _setPrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data,
                                       float &toSet, debug::Logger::severity level)
            {
                _setPropertyFromAttr(toSet, data, level);
            }

            template<typename T2 = void>
            void _setPrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data,
                                       bool &toSet, debug::Logger::severity level)
            {
                _setPropertyFromAttr(toSet, data, level);
            }

            template<typename T2 = void>
            void _setPrimitiveProperty(std::shared_ptr<myxmlpp::Node> &data,
                                       std::string &toSet,
                                       debug::Logger::severity level)
            {
                _setPropertyFromAttr(toSet, data, level);
            }

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

            template<typename T0, typename T1, typename T2>
            void _setMapPropertyFromNode(std::shared_ptr<myxmlpp::Node> &data,
                                         std::map<T1, T2> &toSet,
                                         debug::Logger::severity level = debug::Logger::DEBUG)
            {
                static_assert(std::is_same<T0, typename std::map<T1, T2>>::value);
                _setMapProperty(data, toSet, level);
            };

            template<typename T0, typename T1, typename T2>
            void _setMapPropertyFromNode(std::shared_ptr<myxmlpp::Node> &data,
                                         std::unordered_map<T1, T2> &toSet,
                                         debug::Logger::severity level = debug::Logger::DEBUG)
            {
                static_assert(std::is_same<T0, typename std::unordered_map<T1, T2>>::value);
                _setUMapProperty(data, toSet, level);
            };

            
            
            


            /**
             * @group Find property utilities
             */
            
            std::shared_ptr<myxmlpp::Node> _findProperty(const std::string &name,
            debug::Logger::severity level = debug::Logger::DEBUG);
            
            std::shared_ptr<myxmlpp::Node>
            _findProperty(const std::string &name, const std::shared_ptr<myxmlpp::Node> &data, debug::Logger::severity level = debug::Logger::DEBUG);

            
            
            bool
            _setPropertyFromAttr(int &toSet, std::shared_ptr<myxmlpp::Node> data,
             debug::Logger::severity level = debug::Logger::DEBUG);

            bool
            _setPropertyFromAttr(float &toSet, std::shared_ptr<myxmlpp::Node> data,
            debug::Logger::severity level = debug::Logger::DEBUG);

            bool
            _setPropertyFromAttr(bool &toSet, std::shared_ptr<myxmlpp::Node> data,
            debug::Logger::severity level = debug::Logger::DEBUG);

            bool
            _setPropertyFromAttr(std::string &toSet, std::shared_ptr<myxmlpp::Node> data,
            debug::Logger::severity level = debug::Logger::DEBUG);

            
            
            
            void _logMissingProperty(std::string type, std::string name, debug::Logger::severity level);
            
            void _logWrongValue(std::string type, std::string name, debug::Logger::severity level);
            
            virtual void _onWrongValueExcept(debug::Logger::severity level,
                                             std::string propertyName,
                                             std::string value);
            virtual void _onMissingValueExcept(debug::Logger::severity level, std::string propertyName);
            virtual void _onMissingPropertyExcept(debug::Logger::severity level, std::string propertyName);

//////////////////////--------------------------/////////////////////////           

    };

} // config
