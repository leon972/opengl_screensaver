/***********************************************
Classe factory per gli oggetti del 2DRenderer

*************************************************/

#ifndef FACTORY2D_H_INCLUDED
#define FACTORY2D_H_INCLUDED

#include "video/video_exception.h"
#include "video/video.h"
#include "video/fader.h"
#include "2dengine/sprite.h"
#include "2dengine/tsprite.h"
#include "image/imagemgr.h"

namespace renderer2d
{
    class Factory2D
    {
        public:

        virtual ~Factory2D() {
        }

        /**Restituisce l'istanza del video*/
        virtual Video* GetVideo()=0;

        virtual Sprite* GetNewSprite()=0;

        virtual SpriteTree* GetNewSpriteTree()=0;

        virtual Image* GetNewImage()=0;

        virtual ImageMgr* GetImageManager()=0;

        virtual Fader* GetFader()=0;

        //esegue la deallocazione di tutti gli oggetti creati
        //dopo questa chiamata i puntatori agli oggetti non sono piu' validi
        virtual void FreeMemory()=0;

    };
};

#endif // FACTORY2D_H_INCLUDED
