/*
** EPITECH PROJECT, 2020
** ASerializableObjectFactory.cpp
** File description:
** header for ASerializableObjectFactory.c
*/

#include "polymorph/engine/api/scripting/ASerializableObjectFactory.hpp"

namespace polymorph::engine::api
{

    void ASerializableObjectFactory::buildFactory()
    {
        _registerEmptyBuildables(_emptyBuildables);
        _registerCObjectBuildables(_componentBuildables);
        _registerPObjectBuildables(_configBuildables);
    }

    bool ASerializableObjectFactory::hasObject(std::string type)
    {
        return _componentBuildables.find(type) != _componentBuildables.end() ||
               _configBuildables.find(type) != _configBuildables.end() ||
               _emptyBuildables.find(type) != _emptyBuildables.end();
    }
} // api