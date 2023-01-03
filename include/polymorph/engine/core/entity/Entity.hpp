/*
** ${PROJECT}, 2022
** Entity.hpp by 0xMemoryGrinder
** File description:
** Entity.hpp
*/


#pragma once

#include <vector>
#include <unordered_map>
#include "polymorph/engine/types/safe/enable_safe_from_this.hpp"
#include "myxmlpp/myxmlpp.hpp"

namespace polymorph::engine
{
    class AComponent;
    class TransformComponent;
    class Engine;
    class Scene;
    
    namespace api
    {
        class SceneManager;
        class PluginManager;
        class AssetManager;
    }
    namespace debug { class Logger;}
    namespace time { class Time; }
    
    namespace config
    {
        class XmlEntity;
        class XmlComponent;
    }

    class Entity;

    using Transform = safe_ptr<TransformComponent>;
    using GameObject = safe_ptr<Entity>;

    /**
     * @class Entity a container class which is defined by the components it
     * holds.
     */
    class Entity : public enable_safe_from_this<Entity>
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////

        public:
            Entity(std::shared_ptr<config::XmlEntity> data, Engine &game);
            Entity(std::shared_ptr<myxmlpp::Node> data, Engine &game);


//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:
            /**
             * @property The unique mandatory component of an entity
             *           It's used to define the position, rotation and scale of the entity and parent it to another entity
             */
            Transform transform = Transform(nullptr);

            api::PluginManager &Plugin;

            api::SceneManager &Scene;

            api::AssetManager &Resource;

            debug::Logger &Debug;

            time::Time &time;

            /**
             * @property A reference to the engine
             */
            Engine &Game;

            /**
             * @property The entity's name (not necessarily unique)
             */
            std::string name;

        private:
            /**
             * @property Is the current entity prefab
             */
            bool _isPrefab;

            /**
             * @property Has been a prefab (instantiated)
             */
            bool _wasPrefab;

            /**
             * @property Is the entity active
             */
            bool _active = true;


            /**
             * @property Is the entity previously awoken
             */
            bool _isAwoken = false;
            
            /**
             * @property As the entity been enabled after last update
             */
            bool _asBeenEnabled = false;

            /**
             * @property As the entity been disabled after last update
             */
            bool _asBeenDisabled = false;

            /**
             * @property Is the entity transform initialized
             */
            bool _transformInitialized = false;

            /**
             * @property Represent the entity id
             */
            std::string _stringId;

            /**
             * @property Represent the prefab id
             */
            std::string _prefabId;

            /**
             * @details Tags are used to store a list of string that can be used to identify an entity or some behavior.
             * @property Contains the entity's tags
             */
            std::vector<std::string> _tags;


            /**
             * @property Reference to the XmlEntity used to read the entity data and components
             */
            std::shared_ptr<config::XmlEntity> _xmlConfig;

            /**
             * @property Unordered map of the components of the entity
             */
            std::unordered_map<std::string, std::vector<std::shared_ptr<AComponent>>> _components;

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:
            /**
             * @details Check for game object state
             * @returns The state of the game object
             */
            bool isActive() const;

            /**
             * @details Check for prefab value
             * @returns The prefab value
             */
            bool isPrefab() const;

            /**
             * @details Check for was prefab value
             * @returns The was a prefab value
             */
            bool wasPrefab() const;

            /**
             * @details Changes the entity is prefab value
             * @param value: the new value of the entity is prefab
             */
            void setIsPrefab(bool value);

            /**
             * @details Changes the entity was prefab value
             * @param value: the new value of the entity was prefab
             */
            void setWasPrefab(bool value);

            /**
             * @details Changes the game object state
             * @param active: the new state of the object
             */
            void setActive(bool active);

            /**
             * @details Check if the game object has the tag passed as parameter.
             * @param tag: The tag to look for.
             * @returns True if the game object has the tag, False otherwise.
             */
            bool hasTag(const std::string &tag) const;

            /**
             * @details Return all the game objects tags that start with the string passed as parameter.
             * @param tag: The begin of tag to look for.
             * @returns All matched tags
             */
            std::vector<std::string> getTagsStartingWith(const std::string &begin) const;

            /**
             * @details Adds to the game object the tag passed as parameter.
             * @param tag: The tag to add
             */
            void addTag(const std::string &tag);



            /**
             * @details Deletes from the game object the tag passed as parameter.
             * @param tag: The tag to delete
             */
            void deleteTag(const std::string &tag);

            /**
             * @details Awakes the entity by calling onAwake() of the components
             */
            void awake(bool rescurse = false);

            /**
             * @details start the game object by starting the components
             */
            void start();

            /**
             * @details start the game object by starting the components
             */
            void startChildren();

            /**
             * @details builds all components
             */
            void build();

            /**
             * @details builds all components
             */
            void buildChildren();

            /**
             * @details Updates the game object by updating in the component execution order
             *          all components.
             */
            void update();

            /**
             * @details Updates the game object by updating in the component execution order
             *          all components.
             */
            void updateChildren();
            
            
            /**
             * @details Updates the game object by updating in the component execution order
             *          all components (after all updates).
             */
            void lateUpdate();            

            /**
             * @details Updates the game object by updating in the component execution order
             *          all components (after all updates).
             */
            void lateUpdateChildren();

            /**
             * @details Calls every onEnable() method of the components when the entity is enabled
             */
            void onEnable();
            /**
             * @details Calls every onEnable() method of the components when the entity is enabled
             */
            void onEnableChildren();

            /**
             * @details Calls every onDisable() method of the components when the entity is disabled
             */
            void onDisable();

            /**
             * @details Calls every onDisable() method of the components when the entity is disabled
             */
            void onDisableChildren();
            
            /**
             * @details Event called on all components when a new scene is loaded
             */
            void onSceneLoaded(std::shared_ptr<engine::Scene> scene);

            /**
             * @details Event called on all components when a new scene is loaded
             */
            void onSceneLoadingChildren(std::shared_ptr<engine::Scene> scene);
            
            /**
             * @details Event called on all components when a scene is unloaded
             */
            void onSceneUnloaded(std::shared_ptr<engine::Scene> scene);

            /**
             * @details Event called on all components when a scene is unloaded
             */
            void onSceneUnloadingChildren(std::shared_ptr<engine::Scene> scene);




            /**
             * @details Saves the entity to a file
             * @param saveAllComponentsFirst: whether or not to save all components first
             * @param filePath: the path to the file (if empty, the entity will be saved in the same file it was loaded from)
             */
            void save(bool saveAllComponentsFirst = false, std::string filePath = "");
            

            /**
             * @details Get a child entity by its name
             * @param nameToFind The name of the child
             * @return The child entity
             */
            GameObject find(const std::string &nameToFind) const;

            /**
             * @details Get a child entity by its prefab id
             * @param prefabId The prefab id of the child
             * @return The child entity
             */
            GameObject findByPrefabId(const std::string &prefabId, bool _firstCall = true) const;

            /**
             * @details Get a child entity by its index
             * @param idx The idx of the wanted child
             * @return The child entity
             */
            GameObject childAt(std::size_t idx);



            /**
             * @brief Add a component to the entity
             * @param component The type of component to add
             * @param config The config of the component
             * @param gameObject
             */
            void addComponent(std::string &component, std::shared_ptr<myxmlpp::Node> &config);

            /**
             * @brief build the transform component with its configuration
             */
            void initTransform();

            /**
             * @details Looks for a component by type
             * @tparam T: The type of the component to look for.
             * @warning The type 'T' must inherit from the AComponent class to be fetched
             * @returns A safe pointer to the component
             */
            template<typename T>
            safe_ptr<T> getComponent();

            /**
             * @details Looks for a component by type
             * @param type: The type of the component to look for.
             * @returns A safe pointer to the component
             */
            safe_ptr<AComponent> getComponent(const std::string &type);

            /**
             * @details Looks for all components of type T
             * @tparam T: The 'T' type of the components to look for.
             * @warning The type 'T' must inherit from the AComponent class to be fetched
             * @returns A vector of safe pointer to the components of type 'T'
             */
            template<typename T>
            std::vector<safe_ptr<T>> getComponents();

            /**
             * @details Adds a component to the entity
             * @tparam T: The 'T' type of the component to add.
             * @warning Does nothing if the component is already added
             * @warning The type 'T' must be listed in the component factory to be added this way
             * @warning The type 'T' must inherit from the AComponent class to be added
             * @returns A safe pointer to the added component 'T'
             */
            template<typename T>
            safe_ptr<T> addComponent();

            /**
             * @details Checks if a component of type 'T' exist in the entity
             * @tparam T: The 'T' type of the component to check for.
             * @warning The type 'T' must inherit from the AComponent class to be checked
             * @returns True if the component exist
             */
            template<typename T>
            bool componentExist();

            /**
             * @details Deletes the component of type 'T' from the entity
             * @tparam T: The 'T' type of the component to delete.
             * @warning The type 'T' must inherit from the AComponent class to be deleted
             * @returns True if the component existed and was deleted successfully
             */
            template<typename T>
            bool deleteComponent();

            /**
             * @details A getter to fetch the entity's name
             * @returns An std::string of the entity's name
             */
            std::string getName() const noexcept;

            /**
             * @details A getter to fetch the entity's unique id
             * @returns An std::string of the entity's unique id
             */
            std::string getId() const noexcept;

            /**
             * @details A getter to fetch the entity's prefab id
             * @returns An std::string of the entity's prefab id
             */
            std::string getPrefabId() const noexcept;

            /**
             * @details A setter for the entity's unique id
             * @param An std::string of the entity's unique id
             */
            void setId(const std::string &id) noexcept;

            /**
             * @details A setter for the entity's prefab id
             * @param An std::string of the entity's prefab id
             */
            void setPrefabId(const std::string &id) noexcept;

            /**
             * @details A getter to fetch the XmlEntity associated with the entity
             * @returns The associated XmlEntity
             */
            std::shared_ptr<config::XmlEntity> getXmlConfig() const noexcept;

            /**
             * @details Comparator operator that compares 2 entities based on unique id.
             * @param entity: the entity to compare with.
             * @returns True if the entities are the same otherwise false.
             */
            bool operator==(Entity &entity) const noexcept;

            /**
             * @details Comparator operator that compares 2 entities based on unique id.
             * @param entity: the entity to compare with.
             * @returns False if the entities are the same otherwise True.
             */
            bool operator!=(Entity &entity) const noexcept;

            /**
             * @details Comparator operator that compares an entity and an id based on
             *          the entity's unique id.
             * @param id: the id to compare with.
             * @returns True if the entity's id is the same as the id passed
             *          the same otherwise False.
             */
            bool operator==(const std::string &id) const noexcept;

            /**
             * @details Comparator operator that compares an entity and an id based on
             *          the entity's unique id.
             * @param id: the id to compare with.
             * @returns False if the entity's id is the same as the id passed
             *          the same otherwise True.
             */
            bool operator!=(const std::string &id) const noexcept;

        private:

            /**
             * @details Check if component exist in the list of components composing the entity
             * @returns False if the component don't exist or True if it does
             */
            bool componentExist(std::string &type) const noexcept;
            
        public:
            void _createComponents();
        private:
            void _createComponent(std::shared_ptr<myxmlpp::Node> component);
            GameObject _getByPrefabId(std::string id);
//////////////////////--------------------------/////////////////////////

    };
}
