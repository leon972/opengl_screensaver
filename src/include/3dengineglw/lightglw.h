/*****************************************************************
L3DEngine - lighting
Code by Leonardo Berti (c) 2008
******************************************************************/

#ifndef LIGHTGLW_H_INCLUDED
#define LIGHTGLW_H_INCLUDED

#include "lwtk/libhead.h"
#include "math/vectors3.h"    //vettori a 2,3 e 3 dim in coord. omogenee
#include "math/matrix2.h"     //matrici 2x2,3x3 e 3x3 in coord. omogenee
#include "math/quat2.h"       //quaternions
#include "video/video.h"      //interfaccia video 2D
#include "videoglw/videoglw.h"
#include "3dengineglw.h"
#include "3dengine/3dengine.h"
#include "3dengine/light.h"            //interfaccia per il lighting
#include <vector>

//nota : queste istruzioni del preprocessore servono ad esclude i namespace
//per rendere i file compatibili con alcuni vecchi compilatori
#ifdef _USENAMESPACE_
using namespace mathengine; //namespace usato dai moduli matematici
#endif

#ifdef _USEVIDEONAMESPACE_
namespace video {
    #endif
///////////////////////////////// LightGlWin32 /////////////////////////////////

class DLL_EXPORT LightGlWin32:public Light {

        friend class L3DEngineGlWin32;
        friend class CameraGlWin32;
        friend class SceneNodeGlw;

private:

        static int m_ogl_light_counter; //id open GL della luce
        static std::vector<LightGlWin32*> lights_list; //lista di tutte le luci abilitate
        static const int sym_side=5;

protected:


        static int GetOGLLightId(LightGlWin32* light);
        //restituisce la lista delle luci abilitate
        static std::vector<LightGlWin32*>* GetLightList();
        virtual void init(real x,real y,real z);
        //colori della luce (ambient,diffuse e specular) per default sono tutti bianchi
        COLOR ambient_col,diffuse_col,specular_col;
        CHVector3<real> position;
        bool switched_on; //indica se la luce è accesa o spenta
        float Kc,Kl,Kq;
        int light_id;
        bool draw_symbol;

        virtual void Refresh(bool update_pos);
        virtual void Refresh();

public:

        LightGlWin32();
        LightGlWin32(real x,real y,real z);
        virtual ~LightGlWin32();

        //interfaccia Light
        /**imposta tutti i colori per la luce (ambient,diffuse,specular)*/
        virtual void SetColor(COLOR c);
        virtual COLOR GetColor();
        virtual void SetAmbientColor(COLOR c);
        virtual COLOR GetAmbientColor();
        virtual void SetDiffuseColor(COLOR c);
        virtual COLOR GetDiffuseColor();
        virtual void SetSpecularColor(COLOR c);
        virtual COLOR GetSpecularColor();
        virtual void SetPosition(const CHVector3<real>& pos);
        virtual CHVector3<real> GetPosition();
        /**imposta l'attenuazione della luce secondo la formula 1/(Kc+Kl*d+Kq*d*d)
        dove Kc è il termine costante, Kl è il termine lineare e Kq il quadratico
        impostando Kc=1 e Kl=Kq=0 la luce non viene attenuata in base alla distanza d*/
        virtual void SetAttenuation(float Kc,float Kl,float Kq);
        virtual void GetAttenuation(float* Kc,float* Kl,float* Kq);
        virtual void SetEnabled(bool enabled);
        /**restituisce true se la luce è abilitata*/
        virtual bool IsEnabled();
        /**attiva/disattiva il disegno del simbolo della luce (per scopo di debug)*/
        virtual void SetLightSymbolEnabled(bool enabled);
        /**restituisce true se il disegno del simbolo della luce è abilitato*/
        virtual bool IsLightSymbolEnabled();
        //interfaccia Renderable
        virtual bool render();
        virtual int last_error();
        virtual bool is_visible();
        virtual void set_visible(bool b);
        virtual void notify_add();
        virtual void notify_remove();
        virtual bool operator== (const Renderable& val);
        //----


    };

//////////////////////////////////// DirectionalLightGlWin32 ///////////////////////////

class DirectionalLightGlWin32:public DirectionalLight,public LightGlWin32 {

protected:

        virtual void Refresh();
        virtual void Refresh(bool update_pos);
        virtual void init(real x,real y,real z);

public:
        DirectionalLightGlWin32();
        DirectionalLightGlWin32(const CHVector3<real> direction);
        DirectionalLightGlWin32(real cx,real cy,real cz);
        virtual ~DirectionalLightGlWin32();
        //interfaccia DirectionLight
        virtual void SetDirection(const CHVector3<real>& direction);
        virtual CHVector3<real> GetDirection();
        //interfaccia Light
        /**imposta tutti i colori per la luce (ambient,diffuse,specular)*/
        virtual void SetColor(COLOR c);
        virtual COLOR GetColor();
        virtual void SetAmbientColor(COLOR c);
        virtual COLOR GetAmbientColor();
        virtual void SetDiffuseColor(COLOR c);
        virtual COLOR GetDiffuseColor();
        virtual void SetSpecularColor(COLOR c);
        virtual COLOR GetSpecularColor();
        virtual void SetPosition(const CHVector3<real>& pos);
        virtual CHVector3<real> GetPosition();
        /**imposta l'attenuazione della luce secondo la formula 1/(Kc+Kl*d+Kq*d*d)
        dove Kc è il termine costante, Kl è il termine lineare e Kq il quadratico
        impostando Kc=1 e Kl=Kq=0 la luce non viene attenuata in base alla distanza d*/
        virtual void SetAttenuation(float Kc,float Kl,float Kq);
        virtual void GetAttenuation(float* Kc,float* Kl,float* Kq);
        virtual void SetEnabled(bool enabled);
        /**restituisce true se la luce è abilitata*/
        virtual bool IsEnabled();
        /**attiva/disattiva il disegno del simbolo della luce (per scopo di debug)*/
        virtual void SetLightSymbolEnabled(bool enabled);
        /**restituisce true se il disegno del simbolo della luce è abilitato*/
        virtual bool IsLightSymbolEnabled();
        //interfaccia Renderable
        virtual bool render();
        virtual int last_error();
        virtual bool is_visible();
        virtual void set_visible(bool b);
        virtual void notify_add();
        virtual void notify_remove();
        virtual bool operator== (const Renderable& val);

    };

/////////////////////////////////// SpotLightGlWin32 /////////////////////////////////

    /**luce tipo spot*/
class SpotLightGlWin32:public SpotLight,public LightGlWin32 {

private:

        float spot_angle; //angolo del cono di luce
        float spot_exponent;  //fattore di concentrazione della luce al centro del cono
        CHVector3<real> direction;

protected:

        virtual void Refresh();
        virtual void Refresh(bool update_pos);
        virtual void init(real px,real py,real pz,real dx,real dy,real dz);

public:

        SpotLightGlWin32();
        SpotLightGlWin32(real posx,real posy,real posz,real dirx,real diry,real dirz);

        //interfaccia Light
        /**imposta tutti i colori per la luce (ambient,diffuse,specular)*/
        virtual void SetColor(COLOR c);
        virtual COLOR GetColor();
        virtual void SetAmbientColor(COLOR c);
        virtual COLOR GetAmbientColor();
        virtual void SetDiffuseColor(COLOR c);
        virtual COLOR GetDiffuseColor();
        virtual void SetSpecularColor(COLOR c);
        virtual COLOR GetSpecularColor();
        virtual void SetPosition(const CHVector3<real>& pos);
        virtual CHVector3<real> GetPosition();
        /**imposta l'attenuazione della luce secondo la formula 1/(Kc+Kl*d+Kq*d*d)
        dove Kc è il termine costante, Kl è il termine lineare e Kq il quadratico
        impostando Kc=1 e Kl=Kq=0 la luce non viene attenuata in base alla distanza d*/
        virtual void SetAttenuation(float Kc,float Kl,float Kq);
        virtual void GetAttenuation(float* Kc,float* Kl,float* Kq);
        virtual void SetEnabled(bool enabled);
        /**restituisce true se la luce è abilitata*/
        virtual bool IsEnabled();
        /**attiva/disattiva il disegno del simbolo della luce (per scopo di debug)*/
        virtual void SetLightSymbolEnabled(bool enabled);
        /**restituisce true se il disegno del simbolo della luce è abilitato*/
        virtual bool IsLightSymbolEnabled();
        //interfaccia DirectionalLight
        virtual void SetDirection(const CHVector3<real>& direction);
        virtual CHVector3<real> GetDirection();
        //interfaccia Renderable
        virtual bool render();
        virtual int last_error();
        virtual bool is_visible();
        virtual void set_visible(bool b);
        virtual void notify_add();
        virtual void notify_remove();
        virtual bool operator== (const Renderable& val);
        //interfaccia SpotLight
        /**angolo del cono di luce*/
        virtual void SetSpotAngle(float deg);
        /**concentrazione della luce verso il centro del cono:è un valore compreso fra 0 e 1
        0 significa che non c'è attenuazione verso il bordo, 1 signific che la lkuce è concentrata tutta verso il centro del cono*/
        virtual void SetSpotExponent(float v);

    };

    #ifdef _USEVIDEONAMESPACE_
};
#endif

#endif // LIGHTGLW_H_INCLUDED
