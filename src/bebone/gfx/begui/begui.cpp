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
                const f64 total_execution_time = profile->total_execution_time / 1000000.0;

                const f64 max_execution_time = profile->max_execution_time / 1000000.0;
                const f64 min_execution_time = profile->min_execution_time / 1000000.0;
                const f64 avg_execution_time = total_execution_time / profile->execution_count;

                f64 parent_ration_time = 100.0;
                if(parent != nullptr)
                    parent_ration_time = (profile->total_execution_time / parent->total_execution_time) * 100.0;

                ImGui::Text("executed %llu times, total execution time %f ms", profile->execution_count, total_execution_time);

                ImGui::Text("Max execution time %f ms", max_execution_time);
                ImGui::Text("Min execution time %f ms", min_execution_time);
                ImGui::Text("Avg execution time %f ms", avg_execution_time);
                ImGui::Text("Parent total time ratio %f %%", parent_ration_time);

                profiler_trace_profiles(profile);

                ImGui::TreePop();
            }
        }
    }

    void BeGUI::show_profiler() {
        ImGui::Begin("Bebone profiler");

        const auto& entry_points = Profiler::get_instance().get_entry_points();

        for(const auto& profile : entry_points) {
            if (ImGui::TreeNode(profile->label.c_str())) {
                ImGui::Text("Execution ratio %f %%", 100.0);

                profiler_trace_profiles(profile);

                ImGui::TreePop();
            }
        }

        ImGui::End();
    }
};
