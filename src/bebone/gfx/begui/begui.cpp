#include "begui.h"

namespace bebone::gfx {
    void BeGUI::init(const std::shared_ptr<Window>& window) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_None;

        ImGui::CreateContext();

        //ImGui::StyleColorsDark();
        apply_default_bebone_theme();

        ImGui_ImplGlfw_InitForOpenGL(window->get_backend(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void BeGUI::begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void BeGUI::end() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void BeGUI::profiler_trace_profiles(Profile* profile) {
        const auto& childs = profile->get_childs();

        for(const auto& profile : childs) {
            if (ImGui::TreeNode(profile->label)) {
                const f64 totalExecutionTime = profile->totalExecutionTime / 1000000.0;

                const f64 maxExecutionTime = profile->maxExecutionTime / 1000000.0;
                const f64 minExecutionTime = profile->minExecutionTime / 1000000.0;
                const f64 avgExecutionTime = totalExecutionTime / profile->executionCount;

                ImGui::Text("executed %llu times, total execution time %f ms", profile->executionCount, totalExecutionTime);

                ImGui::Text("Max execution time %f ms", maxExecutionTime);
                ImGui::Text("Min execution time %f ms", minExecutionTime);
                ImGui::Text("Avg execution time %f ms", avgExecutionTime);

                profiler_trace_profiles(profile);

                ImGui::TreePop();
            }
        }
    }

    void BeGUI::show_profiler() {
        ImGui::Begin("Bebone profiler");

        for(const auto& profile : Profiler::get_instance().entryPoints) {
            if (ImGui::TreeNode(profile->label)) {
                profiler_trace_profiles(profile);

                ImGui::TreePop();
            }
        }

        ImGui::End();
    }
};
