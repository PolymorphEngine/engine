/*
** EPITECH PROJECT, 2020
** PluginException.hpp
** File description:
** header for PluginException.c
*/


#pragma once


#include "polymorph/debug/exception/ExceptionLogger.hpp"

namespace polymorph::engine::debug
{
    class PluginException : public ExceptionLogger
    {
    
    ////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:
            PluginException(std::string plugin, std::string message, Logger::severity level = Logger::severity::MAJOR);
            PluginException(std::string message, Logger::severity level = Logger::severity::MAJOR);
    
            ~PluginException() override = default;
    
    //////////////////////--------------------------/////////////////////////
    
    
    
    ///////////////////////////// PROPERTIES ////////////////////////////////
        public:
    
    
        private:
    
    //////////////////////--------------------------/////////////////////////
    
    
    
    /////////////////////////////// METHODS /////////////////////////////////
        public:
    
    
        private:
    
    //////////////////////--------------------------/////////////////////////
    
    };
}
