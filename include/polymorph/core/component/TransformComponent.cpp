/*
** ${PROJECT}, 2022
** TransformComponent.cpp by 0xMemoryGrinder
** File description:
** TransformComponent.cpp
*/


#include "TransformComponent.hpp"

polymorph::engine::TransformComponent::TransformComponent(std::shared_ptr<myxmlpp::Node> data, polymorph::engine::GameObject gameObject)
    : AComponent(data, gameObject), _smoothTimer(gameObject, 0)
{

}

polymorph::engine::TransformComponent::iterator polymorph::engine::TransformComponent::begin()
{
    return _children.begin();
}

polymorph::engine::TransformComponent::iterator polymorph::engine::TransformComponent::end()
{
    return _children.end();
}

void polymorph::engine::TransformComponent::erase(int index)
{
    _children.erase(_children.begin() + index);
}

polymorph::engine::Transform polymorph::engine::TransformComponent::parent() const
{
    return _parent;
}

std::size_t polymorph::engine::TransformComponent::nbChildren() const
{
    return _children.size();
}

bool polymorph::engine::TransformComponent::noChild() const
{
    return _children.empty();
}

const polymorph::engine::Vector3 &polymorph::engine::TransformComponent::getPosition() const
{
    return _position;
}

void polymorph::engine::TransformComponent::setPosition(const Vector3 &position)
{
    Vector3 diff = position - _position;

    _position = position;
    _moveChildren(diff);
}

void polymorph::engine::TransformComponent::setPositionX(float posX)
{
    Vector3 diff(posX - _position.x, 0, 0);

    _position.x = posX;
    _moveChildren(diff);
}

void polymorph::engine::TransformComponent::setPositionY(float posY)
{
    Vector3 diff(0, posY - _position.y, 0);

    _position.y = posY;
    _moveChildren(diff);
}

void polymorph::engine::TransformComponent::setPositionZ(float posZ)
{
    Vector3 diff(0, 0, posZ - _position.z);

    _position.z = posZ;
    _moveChildren(diff);
}

void polymorph::engine::TransformComponent::move(const Vector3 &delta)
{
    _position += delta;
    _moveChildren(delta);
}

void polymorph::engine::TransformComponent::smoothMove(Vector3 destination, float time)
{
    if (_smoothMoving)
        return;
    _smoothMoving = true;
    _smoothTimer = Timer(this->time, time);
    _smoothTarget = destination;
    _smoothOrigin = _position;
}

void polymorph::engine::TransformComponent::smoothMove(Vector3 destination, float time,
                                                       std::function<void(polymorph::engine::GameObject, Vector3,
                                                                          Vector3)> callback)
{
    smoothMove(destination, time);
    _callback = std::move(callback);
}

bool polymorph::engine::TransformComponent::isSmoothMoving()
{
    return _smoothMoving;
}

void polymorph::engine::TransformComponent::cancelSmoothMove()
{
    _smoothMoving = false;
}

const polymorph::engine::Vector3 &polymorph::engine::TransformComponent::getRotation() const
{
    return _rotation;
}

void polymorph::engine::TransformComponent::setRotation(const Vector3 &rotation)
{
    _rotation = rotation;
}

void polymorph::engine::TransformComponent::setParent(polymorph::engine::Transform parent_ref)
{
    _parent = parent_ref;
}

polymorph::engine::Transform polymorph::engine::TransformComponent::removeChild(polymorph::engine::Transform child)
{
    int pos = 0;

    for (auto &tchild: *this)
    {
        if (tchild->gameObject->getId() == child->gameObject->getId())
        {
            erase(pos);
            child->_parent.reset();
            //TODO: reset in scene
            return (tchild);
        }
        ++pos;
    }
    return Transform(nullptr);
}

void polymorph::engine::TransformComponent::removeAllChildren()
{

}

void polymorph::engine::TransformComponent::setSiblingIndex(int index)
{

}

int polymorph::engine::TransformComponent::getSiblingIndex()
{
    return 0;
}

void polymorph::engine::TransformComponent::setLastSibling()
{

}

void polymorph::engine::TransformComponent::setFirstSibling()
{

}

void polymorph::engine::TransformComponent::update()
{
    _updateSmoothMove();
}

void polymorph::engine::TransformComponent::_updateSmoothMove()
{

}

void polymorph::engine::TransformComponent::_moveChildren(const Vector3 &delta)
{

}

void polymorph::engine::TransformComponent::build()
{
    _setProperty("position", _position);
    _setProperty("rotation", _rotation);
    _setProperty("scale", _scale);

    std::vector<GameObject> refs;
    _setProperty("children", refs);
    Transform test(safe_from_this());

    for (auto &ref: refs) {
        if (!ref)
            continue;
        if (ref->isPrefab())
            ref->Scene.instantiate(ref, safe_from_this(), false);
        else
            ref->transform->setParent(shared_from_this());
    }
}

void polymorph::engine::TransformComponent::saveAll()
{
    saveProperty("position", _position);
    saveProperty("rotation", _rotation);
    saveProperty("scale", _scale);
}
