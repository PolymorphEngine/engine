/*
** ${PROJECT}, 2022
** TransformComponent.hpp by 0xMemoryGrinder
** File description:
** TransformComponent.hpp
*/


#pragma once

#include <vector>
#include "myxmlpp/Node.hpp"
#include "polymorph/core/component/AComponent.hpp"
#include "polymorph/time/Timer.hpp"
#include "polymorph/types/vector/Vector3.hpp"
#include "polymorph/types/safe/safe_ptr.hpp"
#include "polymorph/types/safe/enable_safe_from_this.hpp"

namespace polymorph::engine
{
    class TransformComponent;
    using Transform = safe_ptr<TransformComponent>;

    class TransformComponent : public enable_safe_from_this<TransformComponent>, public AComponent
    {
            using iterator = std::vector<Transform>::iterator;
////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////

        public:
            /**
             * Create a transform component with the entity which it belongs to
             * @param gameObject the container entity
             */
            TransformComponent(std::shared_ptr<myxmlpp::Node> data, GameObject gameObject);

            ~TransformComponent() override = default;


//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        private:
            /**
             * @property _position Position of the entity
             */
            Vector3 _position;

            /**
             * @property _rotation Rotation of the entity
             */
            Vector3 _rotation;

            /**
             * @property _scale Scale of drawable components in the entity
             */
            Vector3 _scale;

            /**
             * @property _parent A reference to the parent entity's transform (in the case the entity has a parent)
             */
            Transform _parent;

            /**
             * @property _children The list of all references to children's entities transforms
             */
            std::vector<Transform> _children;

            /**
             * @property _smoothMoving Smooth moving enabled or not
             */
            bool _smoothMoving = false;

            /**
             * @property _hasCallback Is there any callback registered for smooth moving end
             */
            bool _hasCallback = false;

            /**
             * @property _smoothTimer Timer for smooth moving to trigger next moves
             */
            time::Timer _smoothTimer;

            /**
             * @property _smoothTarget Destination of smooth moving
             */
            Vector3 _smoothTarget{0, 0, 0};

            /**
             * @property _smoothOrigin Start point of smooth moving
             */
            Vector3 _smoothOrigin{0, 0, 0};

            /**
             * @property _callback Callback to call when smooth moving is finished
             */
            std::function<void(GameObject, Vector3, Vector3)> _callback;


//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            /**
             * @brief with this method, the transform is used as a container of children
             * This method allows to iterate over the list
             * @return An iterator to the begin of the children list
             */
            iterator begin();

            /**
             * @brief with this method, the transform is used as a container of children
             * This method allows to iterate over the list
             * @return An iterator to the end of the children list
             */
            iterator end();

            /**
             * @brief erase the children at the given index
             * @param child The child to add
             */
            void erase(int index);

            /**
             * @brief get the parent of the entity
             * @return A reference to the parent entity's transform
             */
            Transform parent() const;

            /**
             * @brief get the number of children of the entity
             * @return The number of children
             */
            std::size_t nbChildren() const;

            /**
             * @brief check if the entity has children
             * @return true if the entity has children, false otherwise
             */
            bool noChild() const;

            /**
             * @brief get the position of the entity
             * @return The position of the entity in a form of a Vector3
             */
            const Vector3 &getPosition() const;

            /**
             * @brief set the position of the entity
             * @param position The new position of the entity
             */
            void setPosition(const Vector3 &position);

            /**
             * @brief set the position of the entity on the x axis
             * @param posX New position on the x axis
             */
            void setPositionX(float posX);

            /**
             * @brief set the position of the entity on the y axis
             * @param posY New position on the y axis
             */
            void setPositionY(float posY);

            /**
             * @brief set the position of the entity on the z axis
             * @param posZ New position on the z axis
             */
            void setPositionZ(float posZ);

            /**
             * @brief add the delta to the previous position of the entity
             * @param delta The translation to apply
             */
            void move(const Vector3 &delta);


            /**
             * @brief Start a smooth moving from the current position to the given position
             * @param destination The destination of the smooth moving
             * @param time The time to reach the destination
             */
            void smoothMove(Vector3 destination, float time);

            /**
             * @brief Start a smooth moving from the current position to the given position
             * @param destination The destination of the smooth moving
             * @param time The time to reach the destination
             * @param callback The callback to call when the smooth moving is finished
             */
            void smoothMove(Vector3 destination, float time, std::function<void(GameObject, Vector3, Vector3)> callback);

            /**
             * @brief check if the smooth moving is active
             * @return true if the smooth moving is active, false otherwise
             */
            bool isSmoothMoving();

            /**
             * @brief stop the current smooth moving
             */
            void cancelSmoothMove();

            /**
             * @brief get the rotation of the entity
             * @return The rotation of the entity in a form of a Vector3 for the 3 axis
             */
            const Vector3 &getRotation() const;

            /**
             * @brief set the rotation of the entity
             * @param rotation The new rotation of the entity in a form of a Vector3 for the 3 axis
             */
            void setRotation(const Vector3 &rotation);

            /**
             * @brief set the parent of the entity
             * @param parent_ref The new parent of the entity
             */
            void setParent(Transform parent_ref);

            /**
             * @brief remove a child from the entity by a transform reference
             * @param child The reference of the transform of the child to remove
             * @return The reference of the transform of the removed child
             */
            Transform removeChild(Transform child);

            /**
             * @brief remove all children from the entity
             */
            void removeAllChildren();

            /**
             * @brief set the entity index at the given one in parent's children list
             * @param index The new index of the entity in parent's children list
             */
            void setSiblingIndex(int index);

            /**
             * @brief get the entity index in parent's children list
             * @return The index of the entity in parent's children list
             */
            int getSiblingIndex();

            /**
             * @brief move the entity to the end of the parent's children list
             */
            void setLastSibling();


            /**
             * @brief move the entity to the beginning of the parent's children list
             */
            void setFirstSibling();

            /**
             * @brief overridden method from Component that call _updateSmoothMove method
             */
            void update() override;

            void build() override;

            void saveAll() override;

        private:
            /**
             * @brief update the position of the entity if it needs to be moved for smooth moving
             */
            void _updateSmoothMove();

            /**
             * @brief move all the children of the entity with the same delta as their parent
             * @param delta
             */
            void _moveChildren(const Vector3 &delta);

//////////////////////--------------------------/////////////////////////

    };
}
