# Version 0.2.0v

- [ ] Make a game for GMTK 24 game jam

- [ ] Renderer
    - [ ] Interfaces
        - [ ] IProgram
        - [ ] IUniformBuffer
        - [ ] IVertexBuffer
        - [ ] IIndexBuffer
        - [ ] ITexture
        - [ ] IMesh
        - [ ] IMaterial
        - [ ] ISprite
        - [ ] IModel

    - [ ] Handles
        - [ ] ProgramHandle
        - [ ] UniformBufferHandle
        - [ ] VertexBufferHandle
        - [ ] IndexBufferHandle
        - [ ] TextureHandle
        - [ ] MeshHandle
        - [ ] MaterialHandle
        - [ ] SpriteHandle
        - [ ] ModelHandle

    - [ ] Helper classes
        - [ ] Vertex
        - [ ] Transform

- [ ] Assets 
    - [ ] Add Vec2i variants for ImagePainter methods

- [ ] GFX
    - [ ] Vulkan part
        - [ ] Vulkan pipeline manager
        - [ ] Vulkan textures
        - [ ] VulkanDevice manages all child vulkan objects
    - [ ] Refactor window api
        - [ ] Default values

- [ ] Sound system
    - [ ] SoundEngine class
    - [ ] Abstract sound fx interface
    - [ ] Sound class
    - [ ] Music class

- [x] Naming convention
    - [x] Scane case: methods, functions, variables
    - [x] Pascal case: Classes, Enums

- [ ] Core
    - [ ] Timers (delta time) 
    - [ ] Ray, Box, Sphere types, Intersection api
        - Maybe this will be base for our Physics module ?
    - [x] omni_types migrate into bebone

- [ ] Input system
    - [ ] Utility functions like 'GetKeyDown'
    - [ ] Singleton moment    