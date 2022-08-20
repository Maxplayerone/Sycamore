#pragma once
#include"../smpch.h"

namespace SM_Profiler {

    struct ProfileResult {
        const char* name;
        float time;
    };

    extern std::vector<ProfileResult> m_profileResults;

    class Timer
    {
    public:
        Timer(const char* name)
            : m_name(name), m_Stopped(false)
        {
            m_StartTimepoint = std::chrono::high_resolution_clock::now();
        }

        ~Timer()
        {
            if (!m_Stopped)
                Stop();
        }

        void Stop()
        {
            auto endTimepoint = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

            m_Stopped = true;

            float duration = (end - start) * 0.001f;
            m_profileResults.push_back({ m_name, duration });
        }
    private:
        const char* m_name;
        std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
        bool m_Stopped;
    };

    void ImGuiRender();
    void DoNothing();
    
    #define PROFILE_LEVEL 2

    #if PROFILE_LEVEL == 0
        #define MAIN(name) DoNothing()
        #define SUB(name) DoNothing()
    #elif PROFILE_LEVEL == 1
        #define MAIN(name) Timer timer(name)
        #define SUB(name) DoNothing()
    #elif PROFILE_LEVEL == 2
        #define MAIN(name) Timer timer(name)
        #define SUB(name) Timer timer(name)
    #endif
}