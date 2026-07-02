#pragma once

#include <SDL2/SDL.h>

struct MobileResolution {
    int height = 0;
    int width = 0;
};

class MobileDisplay {
public:
    static inline int GetScreenHeight()
    {
        auto dm = GetDM();
        return dm.height;
    }
    static inline int GetScreenWidth()
    {
        auto dm = GetDM();
        return dm.width;
    }
    static inline int GetDrawHeight()
    {
        return GetScreenHeight() / GetRecommendedScale();
    }
    static inline int GetDrawWidth()
    {
        return GetScreenWidth() / GetRecommendedScale();
    }
    static inline int GetRecommendedScale()
    {
        auto dm = GetDM();

        int s = 1;
        int w = dm.width;
        int h = dm.height;

        while ((w > 480) || (h > 272)) {
            w /= 2;
            h /= 2;
            s++;
        }
        return s;
    }

private:
    static inline MobileResolution GetDM()
    {
        MobileResolution mr;
        SDL_DisplayMode dm;
        if (SDL_GetCurrentDisplayMode(0, &dm) == 0)
        {
            mr.height = dm.h;
            mr.width = dm.w;
        } else {
            mr.height = 600;
            mr.width = 800;
        }
        return mr;
    }


};
