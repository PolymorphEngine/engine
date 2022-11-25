/*
** EPITECH PROJECT, 2020
** AssetManager.hpp
** File description:
** header for AssetManager.c
*/


#pragma once


#include <string>
#include <vector>
#include "polymorph/debug/Logger.hpp"

namespace polymorph::engine::api
{

    class AssetManager
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////
        public:

//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:


        private:
            std::vector<std::string> _paths;

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            /**
             * @brief Tries to resolve the resource path with all registered assets paths
             * @param path The path to resolve
             * @param errorIfNotFound The error level if the path is not found
             * @return The resolved path
             */
            std::string tryResolve(std::string resource,
            debug::Logger::severity errorIfNotFound = debug::Logger::MINOR);
            
            /**
             * @brief Registers a new assets path
             * @param path The path to register
             */
            void addPath(std::string path);


        private:

//////////////////////--------------------------/////////////////////////

    };

} // api
