#pragma	once
#include <entities/trigger.h>

class WarpPoint : public Trigger {
    public:
    WarpPoint(const char* nm) { newmap = nm; }
    const char* GetNewMap() { return newmap; }

    ~WarpPoint() {}

    private:
    const char* newmap;
};
