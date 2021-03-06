#ifndef RENDERABLE_H_INCLUDED
#define RENDERABLE_H_INCLUDED

#ifdef _USEVIDEONAMESPACE_
namespace video {
    #endif

/**Interfaccia per un oggetto renderizzabile*/
    class Renderable {
public:
        virtual ~Renderable() {}
        virtual bool render()=0;    
        virtual bool is_visible()=0;     
    };

#
};
#


#endif // RENDERABLE_H_INCLUDED
