/*****************************************************************
Implementazione di un motore grafico 3D con OpenGL per Win32
Code by Leonardo Berti (c) 2008
******************************************************************/

#ifndef RENDERLST_H_INCLUDED
#define RENDERLST_H_INCLUDED

#include "lwtk/libhead.h"
#include "gl/gl.h"
#include "3dengine/3dengine.h"
#include "video/video.h"

#ifdef _USEVIDEONAMESPACE_
namespace video
{
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif

/**una render list è costituita da un array di elementi (coordinate di texture,vertici ecc, e alcune informazioni
che identificano come processarli.La struttura è pensata per essere usata con glDrawElements*/
class DLL_EXPORT GLRenderList:public Renderable
{
    private:

    bool visible;

    public:

    size_t vertices_count;
    float *vertices; //coordinate dei vertici (raggruppate tre a tre)
    double *dvertices; //usato quando le coordinate sono double

    size_t normals_count;
    float *normals; //normali per ogni vertice

    size_t colors_count;
    float *colors; //colori dei vertici

    size_t texture_coords_count;
    float *texture_coords; //coordinate delle texture per ogni vertice

    size_t vertices_indexes_count;
    unsigned int *vertices_indexes; //indici dei vertici

    GLenum mode; //specifica il tipo di rendering (GL_TRIANGLES,GL_QUADS ecc...)

    GLRenderList();
    virtual ~GLRenderList();

    //dealloca la render list NB: i puntatori potrebbero non essere deallocabili, usare con attenzione
    //oppure potrebbero puntare ad un vettore comune con altri oggetti (ad es. il vettore dei vertici)

    void release();
    //interfaccia Renderable
    virtual bool render();
    virtual int last_error();
    virtual bool is_visible();
    virtual void set_visible(bool b);
    virtual bool operator== (const Renderable& val);
    virtual void notify_add(); //notifica all'oggetto che viene aggiunto al renderer
    virtual void notify_remove(); //notifica all'oggetto che viene rimosso
};

#ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // RENDERLST_H_INCLUDED
