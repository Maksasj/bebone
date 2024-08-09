#ifndef _BEBONE_RENDERER_H_
#define _BEBONE_RENDERER_H_

#include "irenderer.h"
#include "renderer_factory.h"

#include "irender_graph_impl.h"

#include "ipass_impl.h"
#include "ipass.h"

#include "mesh/imesh.h"
#include "mesh/imesh_builder.h"
#include "mesh/imesh_generator.h"
#include "mesh/imesh_loader.h"

#include "mesh/quad_mesh_generator.h"
#include "mesh/cube_mesh_generator.h"
#include "mesh/uv_sphere_mesh_generator.h"
#include "mesh/obj_mesh_loader.h"

#include "vulkan/vulkan_renderer.h"

// Utils
#include "mesh/opengl_triangle_mesh.h"
#include "mesh/opengl_triangle_mesh_builder.h"

#endif
