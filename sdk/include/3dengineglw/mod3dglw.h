/*****************************************************************
Implementazione di un motore grafico 3D con OpenGL per Win32
Code by Leonardo Berti (c) 2007
******************************************************************/

#ifndef MOD3DGLW_H_INCLUDED
#define MOD3DGLW_H_INCLUDED

#include "lwtk/libhead.h"
#include "3dengineglw.h"
#include "renderlst.h"

using namespace std;

#ifdef _USEVIDEONAMESPACE_
namespace video
{
#endif

typedef struct GLVERTEX_TYP
{
    real v[3];

} GLVERTEX,*GL_VERTEX_PTR;

typedef struct GLMATERIAL_TYP
{
    //colore del materiale
    float ambient[4];
    float diffuse[4];
    //lucentezza
    float shininess; //da 0 a 128
    //colore emissivo (per default 0,0,0,1 non emissivo)
    float emissive[4];
    //specular color
    float specular[4];

} GLMATERIAL,*GLMATERIAL_PTR;

//un triangolo con la normale e le informazioni sul colore
typedef struct GLTRIANGLE_TYP
{
    unsigned int vertices[3];
    real normal[3];
    float color[4];

} GLTRIANGLE,*GLTRIANGLE_PTR;

//un quad con la normale e le informazioni sul colore
typedef struct GLQUAD_TYP
{
    unsigned int vertices[4];
    real normal[3];
    float color[4];

} GLQUAD,*GLQUAD_PTR;

typedef struct GLLINE_TYP
{
    unsigned int vertices[2];
    float color[4];

} GLLINE,*GLLINE_PTR;


//semplice modello 3D costituito da triangoli e quad implementato con OpenGL (usato per debug)
class DLL_EXPORT Model3DGlWin32:public Model3D
{
    friend class RenderListGlWin32;
    friend class L3DEngineGlWin32; //deve poter accedere alla lista dei vertici e delle primitive

    private:

        //colore di default per tutti gli elementi
        COLOR def_color;

        std::vector<GLTRIANGLE> triangle_list;
        std::vector<GLQUAD> quad_list;
        std::vector<GLVERTEX> vertex_list;
        std::vector<GLLINE> line_list;

        real* vertex_array; //array con tutti i vertici
        bool m_isCompiled;
        bool visible;
        bool Compile(void); //copia i vertici dalla lista nell'array dei vertici

    public:

        Model3DGlWin32();
        virtual ~Model3DGlWin32();

       //Aggiunge un vertice (usato per formare triangoli o quads)
        //restituisce l'indice del vertice
        virtual unsigned int AddVertex(real x,real y,real z);
        //imposta un triangolo del modello vi=indici dei vertici
        virtual unsigned int AddTriangle(unsigned int v1,unsigned int v2,unsigned int v3);
        //aggiunge un triangolo specificando il colore
        virtual unsigned int AddTriangle(unsigned int v1,unsigned int v2,unsigned int v3,COLOR color);
        //aggiunge un quad
        virtual unsigned int AddQuad(unsigned int v1,unsigned int v2,unsigned int v3,unsigned int v4);
        //aggiunge un quad specificando il colore
        virtual unsigned int AddQuad(unsigned int v1,unsigned int v2,unsigned int v3,unsigned int v4,COLOR color);
        //aggiunge una linea
        virtual unsigned int AddLine(unsigned int v1,unsigned int v2);
        //aggiunge una linea specificando il coolore
        virtual unsigned int AddLine(unsigned int v1,unsigned int v2,COLOR color);
        //imposta la normale di un triangolo (da usare per impostare manualmente la normale.Le funzioni Add... calcolano la normale automaticamente)
        virtual bool SetTriangleNormal(unsigned int tindex,real nx,real ny,real nz);
        //imposta la normale di un quad
        virtual bool SetQuadNormal(unsigned int qindex,real nx,real ny,real nz);

        virtual unsigned int GetVertexCount();

        virtual unsigned int GetTriangleCount();

        virtual unsigned int GetQuadCount();

        bool isCompiled(void);

        //interfaccia Renderable
        bool render();

        int last_error();

        bool is_visible();

        void set_visible(bool visible);

        void notify_add();

        void notify_remove();

        bool operator== (const Renderable& val);

        static CHVector3<real> ToVector(const GLVERTEX& vertex);

        static GLVERTEX ToVertex(const CHVector3<real>& vector);

};

#ifdef _USEVIDEONAMESPACE_
};
#endif


#endif // MOD3DGLW_H_INCLUDED
