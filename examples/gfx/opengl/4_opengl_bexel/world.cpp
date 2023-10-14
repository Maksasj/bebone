#include "world.h"

namespace bexel {
    World::World() : m_worldGenerator(nullptr) {
        m_worldGenerator = make_unique<WorldGenerator>(123);
    }

    void World::update() {

    }

    void World::render(unique_ptr<GLShaderProgram>& shader) {

    };
}
