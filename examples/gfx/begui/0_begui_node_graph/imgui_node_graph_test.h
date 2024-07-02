#include <math.h>

#define BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
#define BEBONE_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

void ShowExampleAppCustomNodeGraph(bool* opened) {
    ImGui::SetNextWindowSize(ImVec2(700, 600), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Example: Custom Node Graph", opened)) {
        ImGui::End();
        return;
    }

    struct Node {
        int     id;
        std::string name;
        ImVec2  pos, size;
        float   value;
        ImVec4  color;
        int     inputs_count, outputs_count;

        Node(int id, std::string name, const ImVec2& pos, float value, const ImVec4& color, int inputs_count, int outputs_count) {
            this->id = id;
            this->name = name;
            this->pos = pos;
            this->value = value;
            this->color = color;
            this->inputs_count = inputs_count;
            this->outputs_count = outputs_count;
        }

        ImVec2 get_input_slot_pos(int slot_no) const { return ImVec2(pos.x, pos.y + size.y * ((float)slot_no + 1) / ((float)inputs_count + 1)); }
        ImVec2 get_output_slot_pos(int slot_no) const { return ImVec2(pos.x + size.x, pos.y + size.y * ((float)slot_no + 1) / ((float)outputs_count + 1)); }
    };
    struct NodeLink {
        int input_idx;
        int input_slot;
        int output_idx;
        int output_slot;

        NodeLink(int input_idx, int input_slot, int output_idx, int output_slot) {
            this->input_idx = input_idx;
            this->input_slot = input_slot;
            this->output_idx = output_idx;
            this->output_slot = output_slot;
        }
    };

    static ImVector<Node> nodes;
    static ImVector<NodeLink> links;
    static ImVec2 scrolling = ImVec2(0.0f, 0.0f);
    static bool inited = false;
    static bool show_grid = true;
    static int node_selected = -1;

    // Initialization
    ImGuiIO& io = ImGui::GetIO();
    if (!inited) {
        nodes.push_back(Node(0, "MainTex", ImVec2(40, 50), 0.5f, ImColor(255, 100, 100), 1, 1));
        nodes.push_back(Node(1, "BumpMap", ImVec2(40, 150), 0.42f, ImColor(200, 100, 200), 1, 1));
        nodes.push_back(Node(2, "Combine", ImVec2(270, 80), 1.0f, ImColor(0, 200, 100), 2, 2));
        links.push_back(NodeLink(0, 0, 2, 0));
        links.push_back(NodeLink(1, 0, 2, 1));
        inited = true;
    }

    // Draw a list of nodes on the left side
    bool open_context_menu = false;
    int node_hovered_in_list = -1;
    int node_hovered_in_scene = -1;
    ImGui::BeginChild("node_list", ImVec2(100, 0));
    ImGui::Text("Nodes");
    ImGui::Separator();
    for (int node_idx = 0; node_idx < nodes.size(); node_idx++) {
        Node* node = &nodes[node_idx];
        ImGui::PushID(node->id);
        if (ImGui::Selectable(node->name.c_str(), node->id == node_selected))
            node_selected = node->id;
        if (ImGui::IsItemHovered()) {
            node_hovered_in_list = node->id;
            open_context_menu |= ImGui::IsMouseClicked(1);
        }
        ImGui::PopID();
    }
    ImGui::EndChild();

    ImGui::SameLine();
    ImGui::BeginGroup();

    const float node_slot_radius = 4.0f;
    const ImVec2 node_window_padding(8.0f, 8.0f);

    // Create our child canvas
    ImGui::Text("Hold middle mouse button to scroll (%.2f,%.2f)", scrolling.x, scrolling.y);
    ImGui::SameLine(ImGui::GetWindowWidth() - 100);
    ImGui::Checkbox("Show grid", &show_grid);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(60, 60, 70, 200));
    ImGui::BeginChild("scrolling_region", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
    ImGui::PopStyleVar(); // WindowPadding
    ImGui::PushItemWidth(120.0f);

    const ImVec2 offset = ImGui::GetCursorScreenPos() + scrolling;
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    if (show_grid) {
        ImU32 grid_color = IM_COL32(200, 200, 200, 40);
        float grid_size = 64.0f;
        ImVec2 win_pos = ImGui::GetCursorScreenPos();
        ImVec2 canvas_size = ImGui::GetWindowSize();
        for (float x = fmodf(scrolling.x, grid_size); x < canvas_size.x; x += grid_size)
            draw_list->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, canvas_size.y) + win_pos, grid_color);
        for (float y = fmodf(scrolling.y, grid_size); y < canvas_size.y; y += grid_size)
            draw_list->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(canvas_size.x, y) + win_pos, grid_color);
    }

    draw_list->ChannelsSplit(2);
    draw_list->ChannelsSetCurrent(0); // Background
    for (int link_idx = 0; link_idx < links.size(); link_idx++) {
        NodeLink* link = &links[link_idx];
        Node* node_inp = &nodes[link->input_idx];
        Node* node_out = &nodes[link->output_idx];
        ImVec2 p1 = offset + node_inp->get_output_slot_pos(link->input_slot);
        ImVec2 p2 = offset + node_out->get_input_slot_pos(link->output_slot);

        draw_list->AddBezierCubic(p1, p1 + ImVec2(+50, 0), p2 + ImVec2(-50, 0), p2, IM_COL32(200, 200, 100, 255), 3.0f);
        // draw_list->AddLine(p1, p2, IM_COL32(200, 200, 100, 255), 3.0f);
    }

    for (int node_idx = 0; node_idx < nodes.size(); node_idx++) {
        Node* node = &nodes[node_idx];
        ImGui::PushID(node->id);
        ImVec2 node_rect_min = offset + node->pos;

        // Display node contents first
        draw_list->ChannelsSetCurrent(1); // Foreground
        bool old_any_active = ImGui::IsAnyItemActive();
        ImGui::SetCursorScreenPos(node_rect_min + node_window_padding);
        ImGui::BeginGroup(); // Lock horizontal position
        ImGui::Text("%s", node->name.c_str());
        ImGui::SliderFloat("##value", &node->value, 0.0f, 1.0f, "Alpha %.2f");
        ImGui::ColorEdit3("##color", &node->color.x);
        ImGui::EndGroup();

        // Save the size of what we have emitted and whether any of the widgets are being used
        bool node_widgets_active = (!old_any_active && ImGui::IsAnyItemActive());
        node->size = ImGui::GetItemRectSize() + node_window_padding + node_window_padding;
        ImVec2 node_rect_max = node_rect_min + node->size;

        // Display node box
        draw_list->ChannelsSetCurrent(0); // Background
        ImGui::SetCursorScreenPos(node_rect_min);
        ImGui::InvisibleButton("node", node->size);
        if (ImGui::IsItemHovered()) {
            node_hovered_in_scene = node->id;
            open_context_menu |= ImGui::IsMouseClicked(1);
        }
        bool node_moving_active = ImGui::IsItemActive();
        if (node_widgets_active || node_moving_active)
            node_selected = node->id;
        if (node_moving_active && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
            node->pos = node->pos + io.MouseDelta;

        ImU32 node_bg_color = (node_hovered_in_list == node->id || node_hovered_in_scene == node->id || (node_hovered_in_list == -1 && node_selected == node->id)) ? IM_COL32(75, 75, 75, 255) : IM_COL32(60, 60, 60, 255);
        draw_list->AddRectFilled(node_rect_min, node_rect_max, node_bg_color, 4.0f);
        draw_list->AddRect(node_rect_min, node_rect_max, IM_COL32(100, 100, 100, 255), 4.0f);
        for (int slot_idx = 0; slot_idx < node->inputs_count; slot_idx++)
            draw_list->AddCircleFilled(offset + node->get_input_slot_pos(slot_idx), node_slot_radius, IM_COL32(150, 150, 150, 150));
        for (int slot_idx = 0; slot_idx < node->outputs_count; slot_idx++)
            draw_list->AddCircleFilled(offset + node->get_output_slot_pos(slot_idx), node_slot_radius, IM_COL32(150, 150, 150, 150));

        ImGui::PopID();
    }
    draw_list->ChannelsMerge();

    // Open context menu
    if (ImGui::IsMouseReleased(ImGuiMouseButton_Right))
        if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup) || !ImGui::IsAnyItemHovered()) {
            node_selected = node_hovered_in_list = node_hovered_in_scene = -1;
            open_context_menu = true;
        }
    if (open_context_menu) {
        ImGui::OpenPopup("context_menu");
        if (node_hovered_in_list != -1)
            node_selected = node_hovered_in_list;
        if (node_hovered_in_scene != -1)
            node_selected = node_hovered_in_scene;
    }

    // Draw context menu
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));
    if (ImGui::BeginPopup("context_menu"))
    {
        Node* node = node_selected != -1 ? &nodes[node_selected] : NULL;
        ImVec2 scene_pos = ImGui::GetMousePosOnOpeningCurrentPopup() - offset;

        if (node) {
            ImGui::Text("Node '%s'", node->name.c_str());
            ImGui::Separator();
            if (ImGui::MenuItem("Rename..", NULL, false, false)) {}
            if (ImGui::MenuItem("Delete", NULL, false, false)) {}
            if (ImGui::MenuItem("Copy", NULL, false, false)) {}
        } else {
            if (ImGui::MenuItem("Add")) { nodes.push_back(Node(nodes.size(), "New node", scene_pos, 0.5f, ImColor(100, 100, 200), 2, 2)); }
            if (ImGui::MenuItem("Paste", NULL, false, false)) {}
        }
        ImGui::EndPopup();
    }
    ImGui::PopStyleVar();

    if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 0.0f))
        scrolling = scrolling + io.MouseDelta;

    ImGui::PopItemWidth();
    ImGui::EndChild();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    ImGui::EndGroup();

    ImGui::End();
}
