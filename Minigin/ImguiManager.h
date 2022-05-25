#pragma once
#include "Singleton.h"

struct Transform
{
    float matrix[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 };
};

class GameObject3D
{
public:
    Transform transform;
    int ID;
};

class GameObject3DAlt
{
public:
    Transform* transform;
    int ID;
};

namespace dae
{
	class ImguiManager final : public Singleton<ImguiManager>
	{
    public:
        void Init(SDL_Window* window);
        void ProcessInput(const SDL_Event* e);
		void Render();
        void Destroy();

    private:
        void TrashCashInt(int samples);
        void TrashCashObject(int samples);
        void TrashCashObjectAlt(int samples);

        void UpdateTrashTheCashWindow();

        std::vector<float> m_GraphDataInt;
        std::vector<float> m_GraphDataObj;
        std::vector<float> m_GraphDataObjAlt;
        SDL_Window* m_Window;
        int m_SamplesInt = 10;
        int m_SamplesObj = 10;
        bool m_ShowGraphWindow = true;
	};
}


