#include"Profiler.h"

#include"imgui/imgui.h"

std::vector<SM_Profiler::ProfileResult> SM_Profiler::m_profileResults;

void SM_Profiler::ImGuiRender()
{
    ImGui::Begin("Settings");

    for (auto& result : m_profileResults)
    {
        char label[50];
        strcpy(label, "%.3fms ");
        strcat(label, result.name);
        ImGui::Text(label, result.time);
    }
    m_profileResults.clear();

    ImGui::End();
}

void SM_Profiler::DoNothing() {

}