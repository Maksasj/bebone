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
};
