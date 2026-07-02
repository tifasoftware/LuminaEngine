#pragma once

class MobileDisplay {
public:
    static inline int GetScreenHeight()
    {
        return 600;
    }
    static inline int GetScreenWidth()
    {
        return 800;
    }
    static inline int GetDrawHeight()
    {
        return GetScreenHeight();
    }
    static inline int GetDrawWidth()
    {
        return GetScreenWidth();
    }
    static inline int GetRecommendedScale()
    {
        return 1;
    }
};
