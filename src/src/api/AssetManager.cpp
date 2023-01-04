/*
** EPITECH PROJECT, 2020
** AssetManager.cpp
** File description:
** header for AssetManager.c
*/

#include <filesystem>
#include "polymorph/engine/api/AssetManager.hpp"
#include "polymorph/engine/debug/Logger.hpp"
#include "polymorph/engine/debug/exception/CoreException.hpp"


namespace polymorph::engine::api
{
    std::string api::AssetManager::tryResolve(std::string resource,
                                              debug::Logger::severity errorIfNotFound)
    {
        for (auto &folder: _paths) {
            std::string path = folder + "/" + resource;
            if (!std::filesystem::exists(path))
            {
                //debug::CoreException("Path incorrect for: " + path, debug::Logger::DEBUG).what();
                continue;
            }
            if (std::filesystem::is_directory(path))
            {
                debug::CoreException("Path is a directory for: " + path, debug::Logger::DEBUG).what();
                continue;
            }
            /*auto perm = std::filesystem::status(path).permissions();
            if ( perm != (std::filesystem::perms::others_read) && perm != std::filesystem::perms::owner_read && perm != std::filesystem::perms::group_read)
            {
                debug::CoreException("Path is not readable forTTT: " + path, debug::Logger::DEBUG).what();
                continue;
            }*/
            return path;
        }
        debug::CoreException("Asset not found: " + resource, errorIfNotFound).what();
        return "";
        //TODO: CE DE
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