/*
** EPITECH PROJECT, 2020
** AssetManager.cpp
** File description:
** header for AssetManager.c
*/

#include <filesystem>
#include "polymorph/api/AssetManager.hpp"
#include "polymorph/debug/Logger.hpp"
#include "polymorph/debug/exception/CoreException.hpp"


namespace polymorph::engine::api
{
    std::string api::AssetManager::tryResolve(std::string resource,
                                              debug::Logger::severity errorIfNotFound)
    {
        for (auto &folder: _paths) {
            std::string path = folder + "/" + resource;
            if (std::filesystem::exists(path) && !std::filesystem::is_directory(path))
                return path;
        }
        throw debug::CoreException("Asset not found: " + resource, errorIfNotFound);
    }

    void api::AssetManager::addPath(std::string path)
    {
        std::string p;
        if (path[path.size() - 1] == '/')
            p = path.substr(0, path.size() - 1);
        else
            p = path;
        while(p.find("//") != std::string::npos)
            p.replace(p.find("//"), 2, "/");
        _paths.push_back(p);
    }
} // api