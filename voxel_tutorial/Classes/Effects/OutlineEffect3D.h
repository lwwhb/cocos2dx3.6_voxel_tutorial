//
//  OutlineEffect3D.h
//  Voxel_Tutorial
//
//  Created by wang haibo on 15/9/13.
//
//

#ifndef __Voxel_Tutorial__OutlineEffect3D__
#define __Voxel_Tutorial__OutlineEffect3D__

#include "BaseEffect3D.h"

class OutlineEffect3D : public BaseEffect3D
{
    OutlineEffect3D();
    virtual ~OutlineEffect3D();
public:
    CREATE_FUNC(OutlineEffect3D);
    virtual bool init();
    virtual void drawWithSprite3D(EffectSprite3D* sprite, const cocos2d::Mat4 &transform);
    
    void setOutlineColor(const cocos2d::Vec3& color);
    void setOutlineWidth(float width);
private:
    cocos2d::Vec3   m_OutlineColor;
    float           m_fOutlineWidth;
};

#endif /* defined(__Voxel_Tutorial__OutlineEffect3D__) */
