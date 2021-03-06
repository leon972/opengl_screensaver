/* 
 * File:   ColorRamp.cpp
 * Author: Leonardo Berti
 * Rampa colore
 * Created on 1 novembre 2010, 17.10
 */

#include "ColorRamp.h"

ColorRamp::ColorRamp() {

    setFirstColor(CL_BLACK);
    setSecondColor(CL_WHITE);
}


ColorRamp::~ColorRamp() {
}



ColorRamp::ColorRamp(COLOR firstColor,COLOR secondColor) {

    setFirstColor(firstColor);
    setSecondColor(secondColor);
}

void ColorRamp::calcDelta() {

    delta[0]=second[0]-first[0];
    delta[1]=second[1]-first[1];
    delta[2]=second[2]-first[2];
    delta[3]=second[3]-first[3];

}

void ColorRamp::setFirstColor(COLOR c) {

    Video::toRGBAFloat(&first[0],&first[1],&first[2],&first[3],c);
    calcDelta();

}

void ColorRamp::setFirstColor(float clampRed,float clampGreen,float clampBlue) {
    setFirstColor(clampRed,clampGreen,clampBlue,1.0);
}

void ColorRamp::setFirstColor(float clampRed,float clampGreen,float clampBlue,float clampAlpha) {

    clampRed=clampF(clampRed);
    clampGreen=clampF(clampGreen);
    clampBlue=clampF(clampBlue);
    clampAlpha=clampF(clampAlpha);
    first[0]=clampRed;
    first[1]=clampGreen;
    first[2]=clampBlue;
    first[3]=clampAlpha;
    calcDelta();
}

void ColorRamp::setSecondColor(COLOR c) {

     Video::toRGBAFloat(&second[0],&second[1],&second[2],&second[3],c);
     calcDelta();
}

void ColorRamp::setSecondColor(float clampRed,float clampGreen,float clampBlue) {
    setSecondColor(clampRed,clampGreen,clampBlue,1.0);
}

void ColorRamp::setSecondColor(float clampRed,float clampGreen,float clampBlue,float clampAlpha) {

    clampRed=clampF(clampRed);
    clampGreen=clampF(clampGreen);
    clampBlue=clampF(clampBlue);
    clampAlpha=clampF(clampAlpha);
    second[0]=clampRed;
    second[1]=clampGreen;
    second[2]=clampBlue;
    second[3]=clampAlpha;
    calcDelta();

}

COLOR ColorRamp::getFirstColor() const {
    return Video::getRGBAColorFloat(first[0],first[1],first[2],first[3]);
}

COLOR ColorRamp::getSecondColor() const {
    return Video::getRGBAColorFloat(second[0],second[1],second[2],second[3]);
}

void ColorRamp::getColor(float* r,float* g,float* b,const float clampPerc) const {

    *r=delta[0]*clampPerc+first[0];
    *g=delta[1]*clampPerc+first[1];
    *b=delta[2]*clampPerc+first[2];

}

void ColorRamp::getColor(float* r,float* g,float* b,float* a,const float clampPerc) const {

    *r=delta[0]*clampPerc+first[0];
    *g=delta[1]*clampPerc+first[1];
    *b=delta[2]*clampPerc+first[2];
    *a=delta[3]*clampPerc+first[3];

}

COLOR ColorRamp::getColor(float clampPerc) const {

    float r=delta[0]*clampPerc+first[0];
    float g=delta[1]*clampPerc+first[1];
    float b=delta[2]*clampPerc+first[2];
    float a=delta[3]*clampPerc+first[3];

    return Video::getRGBAColorFloat(r,g,b,a);

}



