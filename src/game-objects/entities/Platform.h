#include "../GameObject.h"

class Platform : public GameObject {
public:
    Platform(GameScene *parrent_scene, int x, int y, int width, int height, int animation_speed, int num_frames,
             std::string texture_ID);

    virtual void Update() override;

    virtual void Draw() override;

    virtual void Free() override;
};