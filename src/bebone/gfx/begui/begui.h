#ifndef _BEBONE_BEGUI_BEGUI_H_
#define _BEBONE_BEGUI_BEGUI_H_

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "../window/window.h"
#include "../../core/core.h"

namespace bebone::gfx {
    class BeGUI {
        public:
            static void init(const std::shared_ptr<Window>& window) {
                IMGUI_CHECKVERSION();
                ImGui::CreateContext();

                ImGuiIO& io = ImGui::GetIO();
                io.ConfigFlags |= ImGuiConfigFlags_None;

                ImGui::CreateContext();
                ImGui::StyleColorsDark();
                ImGui_ImplGlfw_InitForOpenGL(window->get_backend(), true);
                ImGui_ImplOpenGL3_Init("#version 330");
            }

            static void begin() {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();
            }

            static void end() {
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }


        private:
            static void profiler_trace_profiles(Profile* profile) {
                auto childs = profile->get_childs();

                for(auto i = childs.first; i < childs.second; ++i) {
                    const auto& pp = *i;

                    if (ImGui::TreeNode(pp->label.c_str())) {
                        const f64 exceptionTime = pp->exceptionTime / 1000000.0;

                        ImGui::Text("executed %llu times, total execution time %f ms", pp->executionTimes, exceptionTime);

                        profiler_trace_profiles((*i));

                        ImGui::TreePop();
                    }
                }
            }

        public:
            static void show_profiler() {
                ImGui::Begin("Bebone profiler");

                for(auto profile : Profiler::entryPoints) {
                    if (ImGui::TreeNode(profile->label.c_str())) {
                        profiler_trace_profiles(profile);

                        ImGui::TreePop();
                    }
                }

                ImGui::End();
            }
    };
};

#endif
