/*
** EPITECH PROJECT, 2020
** AConfigurableSerializableObject.hpp
** File description:
** header for AConfigurableSerializableObject.c
*/


#pragma once


#include "ASerializableObject.hpp"
#include "polymorph/engine/api/plugin/PluginManager.hpp"

namespace polymorph::engine::api
{

    class AConfigurableSerializableObject : public ASerializableObject
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            AConfigurableSerializableObject (safe_ptr<AComponent> component, std::shared_ptr<myxmlpp::Node> node);
            AConfigurableSerializableObject (safe_ptr<APluginConfig> config, std::shared_ptr<myxmlpp::Node> node);
            explicit AConfigurableSerializableObject(PluginManager &pluginManager);

            ~AConfigurableSerializableObject() override = default;

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:


        protected:
            debug::Logger &_logger;
            PluginManager &_plugin;

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:


        private:

//////////////////////--------------------------/////////////////////////

    };

} // api
