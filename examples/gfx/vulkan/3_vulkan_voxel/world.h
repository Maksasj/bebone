#ifndef WORLD_H
#define WORLD_H

#include "camera.h"
#include "chunk.h"

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
 
        if (hash1 != hash2) {
            return hash1 ^ hash2;             
        }
         
        return hash1;
    }
};

class World {
    private:
        std::unordered_map<std::pair<int, int>, std::unique_ptr<Chunk>, hash_pair> chunks;
    
        int renderDistance = 8;
        std::unique_ptr<ArenaContainer> chunkRenderingQueue;
    public:
        World() {
            chunkRenderingQueue = std::make_unique<ArenaContainer>(_BEBONE_MEMORY_BYTES_8KB_);
        }

        void update(VulkanRenderer& renderer, GPUResourceManager& resourceManager, GPUResourceSet& resourceSet, const Camera& camera) {
            Vec3f camPos = camera.get_pos();
            Vec2i camChunkPos = Vec2i((camPos.x / 16), (camPos.z / 16));

            for(int x = -renderDistance; x < renderDistance; ++x) {
                for(int y = -renderDistance; y < renderDistance; ++y) {
                    std::pair<int, int> chunkPos = std::make_pair(camChunkPos.x + x, camChunkPos.y + y);

                    if(chunks.find(chunkPos) == chunks.end()) {
                        chunks[chunkPos] = std::make_unique<Chunk>(resourceManager, resourceSet, Vec3f(16.0f * chunkPos.first, 0.0f, 16.0f * chunkPos.second));
                        chunks[chunkPos]->generate(renderer);
                    } else {
                        Chunk** target = static_cast<Chunk**>(chunkRenderingQueue->alloc(sizeof(void*)));
                        *target = chunks[chunkPos].get();
                    }
                }
            }
        }

        void render(VulkanFrame& frame, VulkanPipelineLayoutImpl& pipelineLayout) {
            const size_t& size = chunkRenderingQueue->size();

            for(size_t i = 0; i < size; ++i) {
                Chunk** chunk = static_cast<Chunk**>(chunkRenderingQueue->at(i));
                (*chunk)->render(frame, pipelineLayout);
            }

            chunkRenderingQueue->clear();
        }
};

#endif
