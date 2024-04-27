#include "begui.h"

namespace bebone::gfx {
    void BeGUI::init(const std::shared_ptr<Window>& window) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_None;

        ImGui::CreateContext();

        //ImGui::StyleColorsDark();
        apply_default_bebone_imgui_theme();

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

    void BeGUI::profiler_trace_profiles(Profile* parent) {
        const auto& childs = parent->get_childs();

        for(const auto& profile : childs) {
            if (ImGui::TreeNode(profile->label.c_str())) {
                const f64 totalExecutionTime = profile->totalExecutionTime / 1000000.0;

                const f64 maxExecutionTime = profile->maxExecutionTime / 1000000.0;
                const f64 minExecutionTime = profile->minExecutionTime / 1000000.0;
                const f64 avgExecutionTime = totalExecutionTime / profile->executionCount;

                f64 parentRationTime = 100.0;
                if(parent != nullptr)
                    parentRationTime = (profile->totalExecutionTime / parent->totalExecutionTime) * 100.0;

                ImGui::Text("executed %lu times, total execution time %f ms", profile->executionCount, totalExecutionTime);

                ImGui::Text("Max execution time %f ms", maxExecutionTime);
                ImGui::Text("Min execution time %f ms", minExecutionTime);
                ImGui::Text("Avg execution time %f ms", avgExecutionTime);
                ImGui::Text("Parent total time ratio %f %%", parentRationTime);

                profiler_trace_profiles(profile);

                ImGui::TreePop();
            }
        }
    }

    void BeGUI::show_profiler() {
        ImGui::Begin("Bebone profiler");

        const auto& entryPoints = Profiler::get_instance().get_entry_points();

        for(const auto& profile : entryPoints) {
            if (ImGui::TreeNode(profile->label.c_str())) {
                ImGui::Text("Execution ratio %f %%", 100.0);

                profiler_trace_profiles(profile);

                ImGui::TreePop();
            }
        }

        ImGui::End();
    }
};
