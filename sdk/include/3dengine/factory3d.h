/**************************
classe factory per il renderer 3D
6-8-2009
***************************/
#ifndef FACTORY3D_H_INCLUDED
#define FACTORY3D_H_INCLUDED

#include "video/video_exception.h"
#include "3dengine/3dengine.h"
#include "3dengine/fpscamera.h"
#include "3dengine/camera.h"
#include "3dengine/light.h"

namespace renderer3d
{
    class Factory3D
    {
        public:

        virtual ~Factory3D() {
        }

        /**Restituisce una nuova istanza del renderer 3d*/
        virtual L3DEngine* GetNewL3DEngine()=0;

        virtual Model3D* GetNewModel3D()=0;

        virtual FPSCamera* GetNewFPSCamera()=0;

        virtual Camera* GetNewCamera()=0;

        virtual Light* GetNewLight()=0;
        virtual Light* GetNewLight(real x,real y,real z)=0;

        virtual DirectionalLight* GetNewDirectionalLight()=0;
        virtual DirectionalLight* GetNewDirectionalLight(real cx,real cy,real cz)=0;
        virtual DirectionalLight* GetNewDirectionalLight(const CHVector3<real> direction)=0;

        virtual SpotLight* GetNewSpotLight()=0;
        virtual SpotLight* GetNewSpotLight(real posx,real posy,real posz,real dirx,real diry,real dirz)=0;

        virtual SceneNode* GetNewSceneNode()=0;

        //esegue la deallocazione di tutti gli oggetti creati
        //dopo questa chiamata i puntatori agli oggetti non sono piu' validi
        virtual void FreeMemory()=0;
    };
};

#endif // FACTORY3D_H_INCLUDED
