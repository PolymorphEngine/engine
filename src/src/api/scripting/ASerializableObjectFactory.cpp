/*
** EPITECH PROJECT, 2020
** ASerializableObjectFactory.cpp
** File description:
** header for ASerializableObjectFactory.c
*/

#include "polymorph/api/scripting/ASerializableObjectFactory.hpp"

namespace polymorph::engine::api
{



    void ASerializableObjectFactory::buildFactory()
    {
        _registerEmptyBuildables(_emptyBuildables);
        _registerCObjectBuildables(_componentBuildables);
        _registerPObjectBuildables(_configBuildables);
    }
} // api