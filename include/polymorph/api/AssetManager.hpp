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
            std::string tryResolve(std::string resource,
            debug::Logger::severity errorIfNotFound = debug::Logger::MINOR);
            void addPath(std::string path);


        private:

//////////////////////--------------------------/////////////////////////

    };

} // api
