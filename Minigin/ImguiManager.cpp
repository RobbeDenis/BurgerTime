#include "RodEnginePCH.h"
#include "ImguiManager.h"
#include "..\3rdParty\imgui-1.87\backends\imgui_impl_opengl2.h"
#include "..\3rdParty\imgui-1.87\backends\imgui_impl_sdl.h"
#include <chrono>

void dae::ImguiManager::Init(SDL_Window* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
    ImGui_ImplOpenGL2_Init();
}

void dae::ImguiManager::ProcessInput(const SDL_Event* e)
{
    ImGui_ImplSDL2_ProcessEvent(e);
}

void dae::ImguiManager::Render()
{
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame(m_Window);
    ImGui::NewFrame();

    UpdateTrashTheCashWindow();

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void dae::ImguiManager::Destroy()
{
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}


#pragma region TrashTheCash

void dae::ImguiManager::UpdateTrashTheCashWindow()
{
    // Data int
    ImGui::Begin("Trash the cache exercise 1");

    ImGui::InputInt("# samples", &m_SamplesInt, 1, 100);
    if (ImGui::Button("Calculate for int"))
        TrashCashInt(m_SamplesInt);
    ImGui::PlotLines("Time it takes to acces ints \nin microseconds depending on steps", m_GraphDataInt.data(), int(m_GraphDataInt.size()), 0, nullptr, FLT_MAX, FLT_MAX, { 260, 120 });

    ImGui::End();

    // Data obj
    ImGui::Begin("Trash the cache exercise 2");
    ImGui::InputInt("# samples", &m_SamplesObj, 1, 100);

    // Normal
    if (ImGui::Button("Calculate for obj"))
        TrashCashObject(m_SamplesObj);
    ImGui::PlotLines("Time it takes to acces obj\nin microseconds depending on steps", m_GraphDataObj.data(), int(m_GraphDataObj.size()), 0, nullptr, FLT_MAX, FLT_MAX, { 260, 120 });

    // Alt
    if (ImGui::Button("Calculate for obj_alt"))
        TrashCashObjectAlt(m_SamplesObj);
    ImGui::PlotLines("Time it takes to acces obj_alt\nin microseconds depending on steps", m_GraphDataObjAlt.data(), int(m_GraphDataObjAlt.size()), 0, nullptr, FLT_MAX, FLT_MAX, { 260, 120 });

    ImGui::End();
}

#pragma warning(push)
#pragma warning(disable:6001) // Disable warning of unitialized memory in arr
void dae::ImguiManager::TrashCashInt(int samples)
{
    m_GraphDataInt.erase(begin(m_GraphDataInt), end(m_GraphDataInt));

    std::cout << "\nImguiManager is calculating TrashCashInt" << std::endl;

    std::vector<int> averages{};
    averages.resize(11);

    for (int i = 0; i < samples; i++)
    {
        int* arr = new int[33'554'32];
        int step = 1;

        for (int averageIndex = 0; step <= 1024; averageIndex++)
        {
            const auto start = std::chrono::high_resolution_clock::now();

            for (int idx = 0; idx < 33'554'32; idx += step)
                arr[idx] *= 2;

            const auto end = std::chrono::high_resolution_clock::now();
            const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            averages[averageIndex] += int(total);

            step *= 2;
        }

        delete[] arr;
    }

    for (int average : averages)
    {
        m_GraphDataInt.push_back(float(average) / samples);
    }

    std::cout << "ImguiManager has calculated TrashCashInt" << std::endl;
}
#pragma warning(pop)

void dae::ImguiManager::TrashCashObject(int samples)
{
    m_GraphDataObj.erase(begin(m_GraphDataObj), end(m_GraphDataObj));

    std::cout << "\nImguiManager is calculating TrashCashObject" << std::endl;

    std::vector<int> averages{};
    averages.resize(11);

    for (int i = 0; i < samples; i++)
    {
        std::vector<GameObject3D>* objects = new std::vector<GameObject3D>();
        objects->resize(33'554'32);
        int step = 1;

        for (int averageIndex = 0; step <= 1024; averageIndex++)
        {
            const auto start = std::chrono::high_resolution_clock::now();

            for (int idx = 0; idx < 33'554'32; idx += step)
                objects->at(idx).ID *= 2;

            const auto end = std::chrono::high_resolution_clock::now();
            const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            averages[averageIndex] += int(total);

            step *= 2;
        }

        delete objects;
    }

    for (int average : averages)
    {
        m_GraphDataObj.push_back(float(average / samples));
    }

    std::cout << "ImguiManager has calculated TrashCashObject" << std::endl;
}

void dae::ImguiManager::TrashCashObjectAlt(int samples)
{
    m_GraphDataObjAlt.erase(begin(m_GraphDataObjAlt), end(m_GraphDataObjAlt));

    std::cout << "\nImguiManager is calculating TrashCashObjectAlt" << std::endl;

    std::vector<int> averages{};
    averages.resize(11);

    for (int i = 0; i < samples; i++)
    {
        std::vector<GameObject3DAlt>* objects = new std::vector<GameObject3DAlt>();
        objects->resize(33'554'32);
        int step = 1;

        for (int averageIndex = 0; step <= 1024; averageIndex++)
        {
            const auto start = std::chrono::high_resolution_clock::now();

            for (int idx = 0; idx < 33'554'32; idx += step)
                objects->at(idx).ID *= 2;

            const auto end = std::chrono::high_resolution_clock::now();
            const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            averages[averageIndex] += int(total);

            step *= 2;
        }

        delete objects;
    }

    for (int average : averages)
    {
        m_GraphDataObjAlt.push_back(float(average / samples));
    }

    std::cout << "ImguiManager has calculated TrashCashObjectAlt" << std::endl;
}

#pragma endregion
