/*
** ${PROJECT}, 2022
** AComponent.hpp by 0xMemoryGrinder
** File description:
** AComponent.hpp
*/


#pragma once

#include "polymorph/types/safe/safe_ptr.hpp"
#include "myxmlpp/Node.hpp"

namespace polymorph::engine
{
    class TransformComponent;

    using Transform = safe_ptr<TransformComponent>;

    class Entity;

    using GameObject = safe_ptr<Entity>;

    class Engine;

    class Scene;

    namespace api
    {
        class PluginManager;
        class SceneManager;
        class AssetManager;
        class ScriptingApi;
    }

    namespace config {
        class XmlComponent;
    }

    namespace debug { class Logger; }

    namespace time { class Time; }

    class AComponent
    {

////////////////////// CONSTRUCTORS/DESTRUCTORS /////////////////////////

        public:
            /**
             * @brief Created a new component from a game object
             * @param data the type of the component
             * @param game_object the game oejct that the component will be attached to
             */
            AComponent(std::shared_ptr<myxmlpp::Node> data, GameObject gameObject);

            virtual ~AComponent() = default;


//////////////////////--------------------------/////////////////////////



///////////////////////////// PROPERTIES ////////////////////////////////
        public:
            /**
             * @property A reference to the unique transform component of the entity
             */
            Transform transform = Transform(nullptr);

            /**
             * @property A reference to the entity which the component is part of.
             */
            GameObject gameObject = GameObject(nullptr);

            /**
             * @property The state of the component which defines if the component is updated or not.
             */
            bool enabled = true;

            /**
             * @property Plugin manager to search for symbols and serializable classes in self and other loaded plugins
             */
            api::PluginManager &Plugin;

            /**
             * @property Scene Manager to access to all scene operations
             */
            static api::SceneManager &Scene;

            /**
             * @property Asset Manager to search for asset path by their filename
             */
            api::AssetManager &Asset;

            /**
             * @property Scripting API to access to factories
             */
            api::ScriptingApi &Factory;

            /**
             * @property Logger to log any message/event needed
             */
            debug::Logger &Debug;

            /**
             * @property Time to delta time of the current frame
             */
            time::Time &time;

            /**
             * @property A reference to the engine
             */
            Engine &Game;

        private:
            /**
             * @property name name of the component
             */
            std::string _name;

            /**
             * @property _type type of the component
             */
            std::string _type;

            /**
             * @property _data the data of the component
             */
            std::shared_ptr<myxmlpp::Node> _data;

            /**
             * @property _xmlConfig the config of the component
             */
             std::shared_ptr<config::XmlComponent> _xmlConfig;

            /**
             * @property awaked know if the component needs to be updated or not
             */
            bool _awoken = false;

            /**
             * @property started know if the component  has been started or not yet
             */
            bool _started = false;

//////////////////////--------------------------/////////////////////////



/////////////////////////////// METHODS /////////////////////////////////
        public:

            /**
             * @brief Called before all components are awoken
             * @details This method has to be implemented to initialize the component properties
             */
            virtual void build() = 0;

            /**
             * @brief Called when the entity is saved
             * @details This method has to be implemented to save the component properties
             */
            virtual void saveAll() = 0;

            /**
             * @details An overridable method that's called once per frame in the game loop.
             */
            virtual void update();

            /**
             * @details An overridable method that's called once per frame in the game loop (after all updates).
             */
            virtual void lateUpdate();

            /**
             * @details An overridable method that's called when a scene is loaded.
             */
            virtual void onSceneLoaded(std::shared_ptr<engine::Scene> scene);

            /**
             * @details An overridable method that's called when a scene is loaded.
             */
            virtual void onSceneUnloaded(std::shared_ptr<engine::Scene> scene);

            /**
             * @details An overridable method that's called once in the lifetime of the component.
             *          It is called before the games start (or upon component creation at runtime).
             * @warning Is called even if the enable state of the component is set to false on creation.
             */
            virtual void onAwake();

            /**
             * @details An overridable method that's called once in the lifetime of the component,
             *          It is called before the update method (or upon component creation at runtime).
             * @warning Is called ONLY when the enabled state of the component is passed to true.
             */
            virtual void start();

            /**
             * @brief Set the component as started after calling start()
             */
            virtual void setAsStarted() noexcept final;

            /**
             * @brief Set the component as awoken to update it
             */
            virtual void setAsAwoken() noexcept final;

            /**
             * @brief Get the status of the component
             * @return true if the component is awoken
             */
            virtual bool isAwoken() const noexcept final;

            /**
             * @brief Get the status of the component
             * @return true if the component is started
             */
            virtual bool isStarted() const noexcept final;

            /**
             * @details Getter that return's the type of the component.
             * @return the type of the component as std::string.
             */
            virtual std::string getType() const noexcept final;

            /**
             * @details Looks for a component by type
             * @tparam T: The 'T' type of the component to look for.
             * @warning The type 'T' must inherit from the AComponent class to be fetched
             * @returns A safe pointer to the component 'T'
             */
            template<typename T>
            safe_ptr<T> getComponent();

            /**
             * @details Looks for a component by type in parent's
             * @tparam T: The 'T' type of the component to look for.
             * @warning The type 'T' must inherit from the Component class to be fetched
             * @returns A safe pointer to the component 'T'
             */
            template<typename T>
            safe_ptr<T> getComponentInParent();

            /**
             * @details Looks for a component by type in children
             * @tparam T: The 'T' type of the component to look for.
             * @warning Using depth first search !
             * @warning The type 'T' must inherit from the Component class to be fetched
             * @returns A safe pointer to the component 'T'
             */
            template<typename T>
            safe_ptr<T> getComponentInChildren();

            /**
             * @details Adds a component to the entity
             * @tparam T: The 'T' type of the component to add.
             * @warning Does nothing if the component is already added
             * @warning The type 'T' must have an initializer in the component factory to be added this way
             * @warning The type 'T' must inherit from the Component class to be added
             * @returns A safe pointer to the component 'T'
             */
            template<typename T>
            safe_ptr<T> addComponent();

            /**
             * @details Checks if a component of type 'T' exist in the entity
             * @tparam T: The 'T' type of the component to check for.
             * @warning The type 'T' must inherit from the Component class to be checked
             * @returns True if the component exist
             */
            template<typename T>
            bool componentExist();

            /**
             * @details Deletes the component of type 'T' from the entity
             * @tparam T: The 'T' type of the component to delete.
             * @warning The type 'T' must inherit from the Component class to be deleted
             * @returns True if the component existed and was deleted successfully
             */
            template<typename T>
            bool deleteComponent();

            /**
             * @brief Saves a property in the Xml data by its name
             * @param name The name of the property
             * @tparam T The type of the property
             * @param value The value of the property
             */

            template<typename T>
            void saveProperty(std::string propertyName, T &toSave);


            /**
             * @brief Saves a property in the Xml data by its name
             * @param name The name of the property
             * @tparam T The type of the property
             * @param value The value of the property
             */
            template<typename T>
            void saveProperty(std::string propertyName, std::shared_ptr<T> &toSave);

            /**
             * @brief Saves a property in the Xml data by its name
             * @param name The name of the property
             * @tparam T The type of the property
             * @param value The value of the property
             */
            template<typename T>
            void saveProperty(std::string propertyName, safe_ptr<T> &toSave);

        protected:
            /**
             * @brief Sets a property from the Xml data by its name
             * @param name The name of the property
             * @tparam T The type of the property
             * @param value The property to set
             */
            template<typename T>
            void _setProperty(const std::string &propertyName, std::shared_ptr<T> &toSet, debug::Logger::severity level = debug::Logger::DEBUG);

            /**
             * @brief Sets a property from the Xml data by its name
             * @param name The name of the property
             * @tparam T The type of the property
             * @param value The property to set
             */
            template<typename T>
            void _setProperty(const std::string &propertyName, safe_ptr<T> &toSet, debug::Logger::severity level = debug::Logger::DEBUG);

            /**
             * @brief Sets a property from the Xml data by its name
             * @param name The name of the property
             * @tparam T The type of the property
             * @param value The property to set
             */
            template<typename T>
            void _setProperty(const std::string &propertyName, T &toSet, debug::Logger::severity level = debug::Logger::DEBUG);

            template<class T>
            safe_ptr<T> _self();

//////////////////////--------------------------/////////////////////////

    };
}