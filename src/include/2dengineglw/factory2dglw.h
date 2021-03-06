#ifndef FACTORY2DGLW_H_INCLUDED
#define FACTORY2DGLW_H_INCLUDED

#include <list>
#include "lwtk/libhead.h"
#include "2dengine/factory2d.h"

using namespace std;

namespace renderer2d
{
    class DLL_EXPORT Factory2DGlw:public Factory2D
    {
        private:

        static Factory2DGlw* instance;
        static Video* canvas;
        static ImageMgr* image_manager;
        static Fader* fader;

        list<Sprite*> sprite_insts;
        list<SpriteTree*> tsprite_insts;
        list<Image*> image_insts;

        protected:

         //automatic garbage collection
        bool auto_gc;
        Factory2DGlw();

        public:

        static Factory2D* GetInstance(bool auto_gc);

        static Factory2D* GetInstance();

        virtual ~Factory2DGlw();

        virtual bool SetAutoGC(bool auto_gc);
        virtual bool GetAutoGC();

        /**Restituisce una nuova istanza del video*/
        virtual Video* GetVideo();

        virtual ImageMgr* GetImageManager();

        virtual Fader* GetFader();

        virtual Sprite* GetNewSprite();

        virtual SpriteTree* GetNewSpriteTree();

        virtual Image* GetNewImage();

        //esegue la deallocazione di tutti gli oggetti creati
        //dopo questa chiamata i puntatori agli oggetti non sono piu' validi
        virtual void FreeMemory();

    };
};


#endif // FACTORY2DGLW_H_INCLUDED
