/*
** ${PROJECT}, 2022
** AComponent.hpp by 0xMemoryGrinder
** File description:
** AComponent.hpp
*/


#pragma once

#include "polymorph/engine/types/safe/safe_ptr.hpp"
#include "polymorph/engine/core/component/AComponent.hpp"
#include "polymorph/engine/core/component/TransformComponent.hpp"
#include "polymorph/engine/core/entity/Entity.hpp"

#include "polymorph/engine/config/XmlComponent.hpp"

namespace polymorph::engine
{

    template<typename T>
    safe_ptr<T> AComponent::getComponent()
    {
        return gameObject->getComponent<T>();
    }

    template<typename T>
    safe_ptr<T> AComponent::getComponentInParent()
    {
        if (transform->parent())
            return transform->parent()->gameObject->getComponent<T>();
        return nullptr;
    }

    template<typename T>
    safe_ptr<T> AComponent::getComponentInChildren()
    {
        for (auto &child: **transform) {
            auto c2 = child->getComponent<T>();
            if (c2)
                return c2;
        }

        for (auto &child: **transform) {
            auto c1 = child->getComponentInChildren<T>();
            if (c1)
                return c1;

        }
        return safe_ptr<T>(nullptr);
    }

    template<typename T>
    safe_ptr<T> AComponent::addComponent()
    {
        return gameObject->addComponent<T>();
    }

    template<typename T>
    bool AComponent::componentExist()
    {
        return gameObject->componentExist<T>();
    }

    template<typename T>
    bool AComponent::deleteComponent()
    {
        return gameObject->deleteComponent<T>();
    }

    template<typename T>
    void
    polymorph::engine::AComponent::saveProperty(std::string propertyName, T &toSave)
    {
        _xmlConfig->save(propertyName, toSave);
    }

    template<typename T>
    void
    polymorph::engine::AComponent::_setProperty(const std::string &propertyName,
                                                T &toSet,
                                                polymorph::engine::debug::Logger::severity level)
    {
        _xmlConfig->set(propertyName, toSet, level);
    }

}