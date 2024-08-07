#include "game.h"
#include "texture_loader.h"
#include "entity_component_system/components/sprite_renderer.h"
#include "entity_component_system/game_object.h"

#include "rng.h"

namespace game::core {
    using namespace bebone::gfx;
    using namespace std;
    using namespace ecs;
    using namespace fsm;

    vector<shared_ptr<GameObject>> Game::game_objects = vector<shared_ptr<GameObject>>();

    Game::Game(const unsigned int& width, const unsigned int& height, const shared_ptr<Input>& input) : input(input) {
        const auto aspect = static_cast<f32>(width) / static_cast<f32>(height);

        camera = make_shared<OrthographicCamera>(aspect * -7.0f, aspect * 7.0f, 7.0, -7.0, -7.0f, 7.0f);
 
        const auto shader_flags = EnableUniforms;

        auto vertex_shader = GLShaderFactory::create_shader("assets/vertex.glsl", ShaderTypes::vertex_shader, shader_flags);
        auto fragment_shader = GLShaderFactory::create_shader("assets/fragment.glsl", ShaderTypes::fragment_shader, shader_flags);
        auto shader_program = make_shared<GLShaderProgram>(vertex_shader, fragment_shader);

        TextureLoader::load_textures("assets/gfx");
        
        batch = make_shared<Batch>(shader_program, camera, 1024);

        auto bg = instantiate("Background", Vec3f(0.0f, 0.0f, 3.0f));
        add_renderer_component(bg, "bg", 32);
        bg->get_transform()->set_scale(0.6f);
        batch->add(bg);

        auto flappy_bird = instantiate("Flappy Bird");
        add_renderer_component(flappy_bird, "flappy_bird", 32);
        batch->add(flappy_bird);
        
        auto ground1 = instantiate("Ground1", Vec3f(0, -7.0f, 1.0f));
        auto ground1_transform = ground1->get_transform();
        add_renderer_component(ground1, "ground", 32);
        batch->add(ground1);
        ground1_transform->set_scale(0.5f);

        auto ground_sprite = ground1->get_component<SpriteRenderer>()->get_sprite();

        Vec3f ground2_position = ground1_transform->get_position();
        ground2_position.x = ground_sprite->get_unit_width();

        auto ground2 = instantiate("Ground2", ground2_position);
        add_renderer_component(ground2, "ground", 32);
        batch->add(ground2);
        ground2->get_transform()->set_scale(0.5f);

        auto pipe1 = instantiate("Pipe1");
        add_renderer_component(pipe1, "pipes", 32);
        batch->add(pipe1);
        pipe1->get_transform()->set_scale(0.5f);

        auto pipe2 = instantiate("Pipe2");
        add_renderer_component(pipe2, "pipes", 32);
        batch->add(pipe2);
        pipe2->get_transform()->set_scale(0.5f);

        main_menu_state = make_shared<MainMenuState>(flappy_bird, input);
        game_state = make_shared<GameState>(flappy_bird, input);
        end_game_state = make_shared<EndGameState>(flappy_bird, input);
        
        main_menu_state->set_game_state(game_state);
        game_state->set_end_game_state(end_game_state);
        end_game_state->set_menu_state(main_menu_state);

        StateMachine::set_state(main_menu_state);
    }

    shared_ptr<GameObject> Game::instantiate(const string& game_object_name, const Vec3f& position) {
        auto game_object = make_shared<GameObject>(game_object_name, position);
        game_objects.push_back(game_object);

        return game_object;
    }

    void Game::add_renderer_component(shared_ptr<GameObject>& game_object, const string& texture_name, const unsigned int& pixels_per_unit) {
        auto sprite = make_shared<Sprite>(texture_name, pixels_per_unit);
        game_object->add_component<SpriteRenderer>(sprite);
    }

    void Game::update() {
        StateMachine::update_current_state();
        update_game_objects();

        batch->render();
    }

    void Game::update_game_objects() {
        for (auto it = game_objects.begin(); it != game_objects.end(); ++it) {
            (*it)->update();
        }
    }

    shared_ptr<GameObject> Game::find_game_object_by_name(const string& game_object_name) {
        for (auto it = game_objects.begin(); it != game_objects.end(); ++it) {
            auto game_object = *it;

            if (game_object->get_name() == game_object_name) {
                return game_object;
            }
        }
        
        return nullptr;
    }
}