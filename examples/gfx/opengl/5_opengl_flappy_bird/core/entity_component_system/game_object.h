#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <string>
#include <memory>
#include <typeindex>

#include "transform.h"

namespace game::core::ecs {
    using namespace std;

    class Component;

    class GameObject : private bebone::core::NonCopyable {
        private:
            string name;
            shared_ptr<Transform> transform;

            map<type_index, vector<shared_ptr<Component>>> components;

            type_index get_type(shared_ptr<Component> component);
            vector<shared_ptr<Component>>& get_component_vector(const type_index& type);

        public:
            explicit GameObject(const string& name);
            GameObject(const string& name, const Vec3f& position);

            shared_ptr<Transform>& get_transform();
            [[nodiscard]] string get_name() const;
            
            void update();

            void remove_component(shared_ptr<Component> component);

            template <typename T, typename... Args>
            shared_ptr<T> add_component(Args&&... args) {
                static_assert(std::is_base_of<Component, T>::value, "T must be a Component");

                auto component = std::make_shared<T>(std::forward<Args>(args)...);
                component->set_transform(transform);
                component->enabled = true;

                type_index type = get_type(component);
                components[type].push_back(component);

                return component;
            }

            template <typename T>
            shared_ptr<T> get_component() {
                auto v = components[typeid(T)];
                
                if (!v.empty()) {
                    return dynamic_pointer_cast<T>(v[0]);
                }
                
                return nullptr;
            }

            template <typename T>
            vector<shared_ptr<T>> get_components() {
                auto v = components[typeid(T)];
                auto v_out = vector<shared_ptr<T>>();
                
                for (auto & it : v) {
                    v_out.push_back(dynamic_pointer_cast<T>(it));
                }

                return v_out;
            }
    };

    class Component : private bebone::core::NonCopyable {
        friend class GameObject;
        private:
            shared_ptr<Transform> transform;
            bool enabled;

            void set_transform(shared_ptr<Transform> transform);

        public:
            virtual ~Component() = default;
            virtual void update() = 0;

            shared_ptr<Transform>& get_transform();

            virtual void disable();
            virtual void enable();

            bool is_enabled();


    };
}

#endif
