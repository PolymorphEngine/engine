/*
** EPITECH PROJECT, 2020
** XmlPluginConfig.hpp
** File description:
** header for XmlPluginConfig.c
*/


#pragma once


#include "XmlPropertyManager.hpp"

namespace polymorph::engine {
    class Engine;
}

namespace polymorph::engine::config
{
    class XmlPluginConfig : public XmlPropertyManager
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            XmlPluginConfig(std::shared_ptr<myxmlpp::Doc> &doc, Engine &engine);

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:
            
            void saveConfig(std::string filePath = "");
            
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

        private:
            std::string _type;
            std::shared_ptr<myxmlpp::Doc> _doc;
            Engine &_engine;

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            std::string getType();

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
                        toSet = std::dynamic_pointer_cast<T>(_engine.getFactory().createSerializableObject(t, data, *this, _engine.getPluginManager()));
                    }  catch (debug::ExceptionLogger &e) {
                        if (level == debug::Logger::MAJOR)
                            e.what();
                        toSet = std::dynamic_pointer_cast<T>(_engine.getPluginManager().tryCreateSharedObject(t, *this, data, _engine.getPluginManager()));
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
                    _onMissingPropertyExcept(level, propertyName);
                _setSerializableProperty<T>(property, toSet, level);
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

                if (property == nullptr)
                    _onMissingPropertyExcept(level, propertyName);
                toSet->saveAll();
            };
//////////////////////--------------------------/////////////////////////

    };

} // config
