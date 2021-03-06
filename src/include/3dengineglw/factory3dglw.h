#ifndef FACTORY3DGLW_H_INCLUDED
#define FACTORY3DGLW_H_INCLUDED

#include "lwtk/libhead.h"
#include "3dengine/factory3d.h"

namespace renderer3d
{
    class DLL_EXPORT Factory3DGlw:public Factory3D
    {
        private:

        list<L3DEngine*> render3d_insts;
        list<Model3D*> model_insts;
        list<FPSCamera*> fpscam_insts;
        list<Camera*> camera_insts;
        list<Light*> light_insts;
        list<SceneNode*> node_insts;

        static Factory3DGlw* instance;

        protected:

        bool auto_gc;
        Factory3DGlw();

        public:

        static Factory3D* GetInstance(bool auto_gc);

        static Factory3D* GetInstance();

        virtual ~Factory3DGlw();

        bool SetAutoGC(bool auto_gc);
        bool GetAutoGC();

        /**Restituisce una nuova istanza del renderer 3d*/
        virtual L3DEngine* GetNewL3DEngine();

        virtual Model3D* GetNewModel3D();

        virtual FPSCamera* GetNewFPSCamera();

        virtual Camera* GetNewCamera();

        virtual Light* GetNewLight();
        virtual Light* GetNewLight(real x,real y,real z);

        virtual DirectionalLight* GetNewDirectionalLight();
        virtual DirectionalLight* GetNewDirectionalLight(real cx,real cy,real cz);
        virtual DirectionalLight* GetNewDirectionalLight(const CHVector3<real> direction);

        virtual SpotLight* GetNewSpotLight();
        virtual SpotLight* GetNewSpotLight(real posx,real posy,real posz,real dirx,real diry,real dirz);

        virtual SceneNode* GetNewSceneNode();

        //esegue la deallocazione di tutti gli oggetti creati
        //dopo questa chiamata i puntatori agli oggetti non sono piu' validi
        virtual void FreeMemory();

    };
};

#endif // FACTORY3DGLW_H_INCLUDED
