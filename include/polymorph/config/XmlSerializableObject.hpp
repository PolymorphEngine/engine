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

#include "polymorph/debug/Logger.hpp"
#include "polymorph/debug/exception/config/MissingValueException.hpp"
#include "polymorph/debug/exception/config/WrongValueException.hpp"
#include "polymorph/config/CastHelper.hpp"
#include "polymorph/config/XmlPropertyManager.hpp"
#include "polymorph/types/safe/safe_ptr.hpp"

namespace polymorph::engine {
    class Entity;
    class AComponent;
    using GameObject = safe_ptr<Entity>;

}


namespace polymorph::engine::config
{

    class XmlSerializableObject : public XmlPropertyManager
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            XmlSerializableObject(safe_ptr<AComponent> component, std::shared_ptr<myxmlpp::Node> &componentNode, debug::Logger& logger);

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:


        private:
            safe_ptr<AComponent> _component;
            std::string _type;
//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            
            std::string getType() const;
            
            template<typename T>
            void set(const std::string &propertyName, std::shared_ptr<T> &toSet, debug::Logger::severity level = debug::Logger::DEBUG)
            {
                std::shared_ptr<myxmlpp::Node> property = _findProperty(propertyName);

                if (property == nullptr)
                    return;
                static_assert(!CastHelper::is_map<T>);
                _setSharedProperty<T>(property, toSet, level);
            };


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
            
            template<typename T, typename T2 = void>
            void _setSharedProperty(std::shared_ptr<myxmlpp::Node> &data,
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
                        toSet = std::dynamic_pointer_cast<T>(_component->Factory.createSerializableObject(t, data, *this, _component->Plugin));
                    }  catch (debug::ExceptionLogger &e) {
                        if (level == debug::Logger::MAJOR)
                            e.what();
                        toSet = std::dynamic_pointer_cast<T>(_component->Plugin.tryCreateSharedObject(t, *this, data, _component->Plugin));
                    }
                }
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
                    return;
                _setSharedProperty<T>(property, toSet, level);
            };
//////////////////////--------------------------/////////////////////////

    };

} // config
