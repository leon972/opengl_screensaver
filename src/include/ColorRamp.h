/* 
 * File:   ColorRamp.h
 * Author: Proprietario
 *
 * Created on 1 novembre 2010, 17.10
 */

#ifndef COLORRAMP_H
#define	COLORRAMP_H

#include "video/video.h"

using namespace video;

class DLL_EXPORT ColorRamp {
private:
    
    float first[4];
    float second[4];
    float delta[4];

    void calcDelta();

public:

    static float clampF(float f)
    {
        if (f<0.0) return 0.0;
        else if (f>1.0) return 1.0;
        return f;
    }

    ColorRamp();

    ColorRamp(COLOR firstColor,COLOR secondColor);

    void setFirstColor(COLOR c);
    void setFirstColor(float clampRed,float clampGreen,float clampBlue);
    void setFirstColor(float clampRed,float clampGreen,float clampBlue,float clampAlpha);

    void setSecondColor(COLOR c);
    void setSecondColor(float clampRed,float clampGreen,float clampBlue);
    void setSecondColor(float clampRed,float clampGreen,float clampBlue,float clampAlpha);

    COLOR getFirstColor() const;
    COLOR getSecondColor() const;

    void getColor(float* r,float* g,float* b,const float clampPerc) const;
    void getColor(float* r,float* g,float* b,float* a,const float clampPerc) const;
    COLOR getColor(float clampPerc) const;

    virtual ~ColorRamp();

};

#endif	/* COLORRAMP_H */

