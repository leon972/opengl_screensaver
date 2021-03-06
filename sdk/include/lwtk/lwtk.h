/*************************************************************
 Abstract GUI toolkit
 Copyright by L.Berti (c) 2007
 *************************************************************/

#ifndef LWTK_H_INCLUDED
#define LWTK_H_INCLUDED

#include <tchar.h>
#include "libhead.h"
#include "lwtkdefs.h"
#include "video/font.h"
#include "util/localedef.h"
#include "mouse.h"
#include "keys.h"
#include "window.h"
#include "control.h"
#include "menu.h"


#ifdef _USEVIDEONAMESPACE_
using namespace video;
#endif

using namespace util;

namespace lwtk {

    //fwd decl.
    class Window;
    class ActionEvent;
    class PaintEvent;
    class MouseEvents;
    class MouseMoveEvents;
    class FocusEvents;
    class KeyEvents;
    class ComboBox;
    class Container;
    class Widget;





    /**Evento che viene generato quando l'utente cambia il contenuto di un Widget*/
    class DLL_EXPORT ChangeEvents {
public:
        virtual ~ChangeEvents() {
        }
        virtual void ContentChanged(Widget* src)=0;
    };




    /**Bottone*/
class Button:public virtual Widget {
public:

        virtual ~Button() {
        }

    };

class Label:public Widget {
public:
        virtual ~Label() {
        }
        virtual void SetTextAlign(TEXT_ALIGN align)=0;
        virtual TEXT_ALIGN GetTextAlign()=0;
    };

    class InputMask {
public:
        virtual ~InputMask() {
        }
        /**restituisce i caratteri che compongono la maschera*/
        virtual const TCHAR* GetMask()=0;
        /**Rende true se i caratteri della maschera sono esclusi dal filtro*/
        virtual bool Exclude()=0;
        /**Rende true se il carattere � valido*/
        virtual bool IsValid(TCHAR ch)=0;
    };

class TextField:public Widget {
public:
        virtual ~TextField() {
        }
        virtual void SetMaxLength(int len)=0;
        virtual int GetMaxLength()=0;
        virtual void SetMask(const InputMask* mask)=0;
        virtual const InputMask* GetMask()=0;
    };

class ToggleButton:public virtual Widget {
public:
        virtual ~ToggleButton() {
        }
        virtual void SetSelected(bool selected)=0;
        virtual bool IsSelected()=0;
    };

class CheckBox:public virtual ToggleButton {

public:

        virtual ~CheckBox() {
        }
    };

class RadioButton:public ToggleButton {

public:
        virtual ~RadioButton() {}
    };

    class ListModel {
public:
        virtual ~ListModel() {
        }
        virtual int AddElement(const TCHAR* text)=0;
        virtual const TCHAR* GetElement(int index)=0;
        virtual void RemoveElement(int index)=0;
        virtual int GetSelectedIndex()=0;
        virtual void SetSelectedIndex(int index)=0;
        virtual void SetElementData(int data,int index)=0;
        virtual int GetElementData(int index)=0;
        virtual int GetSize()=0;
        virtual void Clear()=0;
    };

class List:public Widget,public ListModel {
public:
        virtual ~List() {
        }
        virtual LIST_SELECTION_MODE GetSelectionMode()=0;
        virtual bool IsSorted()=0;

    };

    class ComboBoxEvents {
public:
        virtual ~ComboBoxEvents() {
        }
        /**doppio click su un elemento della lista*/
        virtual void ComboListDblClick(ComboBox* src)=0;
        /**La lista viene visualizzata*/
        virtual void ListDropDown(ComboBox* src)=0;
        /**Viene selezionato un elemento della lista*/
        virtual void ItemSelected(ComboBox* src)=0;

    };

class ComboBox:public Widget,public ListModel {
public:
        virtual ~ComboBox() {}
        virtual COMBOBOX_STYLE GetStyle()=0;
        virtual bool IsSorted()=0;
        /**apre la lista drop down del combo box*/
        virtual void ShowDropDownList()=0;
        virtual void HideDropDownList()=0;
        virtual void AddComboBoxEvents(ComboBoxEvents* evt)=0;

    };

class ScrollBar:public Widget {
public:
        virtual ~ScrollBar() {}
        /**Restituisce il valore massimo del range*/
        virtual int GetMaximum()=0;
        /**Restituisce il valore minimo*/
        virtual int GetMinimum()=0;
        /**Imposta il valore massimo del range*/
        virtual int SetMaximum(int val)=0;
        /**Imposta il valore minimo*/
        virtual int SetMinimum(int val)=0;
        /**Restituisce il valore corrente*/
        virtual int GetValue()=0;
        /**Imposta il valore corrente*/
        virtual int SetValue(int value)=0;
        /**Imposta il valore di incremento per spostamento pagina*/
        virtual int SetBlockIncrement(int value)=0;
        /**Imposta il valore di incremento unitario*/
        virtual int SetUnitIncrement(int value)=0;
        /**Restituisce l'incremento per spostamento pagina
        block increment � minore del range maximum-minimum
        e rappresenta l dimensione di una pagina rispetto al range
        */
        virtual int GetBlockIncrement()=0;
        /**Restituisce l'incremento unitario*/
        virtual int GetUnitIncrement()=0;
    };



class GroupBox:public Panel {
public:

        virtual ~GroupBox() {}

    };


    /**Informazioni sul sistema*/
    class System {

public:
        virtual ~System() {}
        virtual const TCHAR* GetOSName()=0;
        virtual const TCHAR* GetOSVersion()=0;
        virtual const TCHAR* GetDecimalPoint()=0;
        virtual const TCHAR* GetPathSeparator()=0;
        virtual const TCHAR* GetUsername()=0;
        virtual const TCHAR* GetMachineName()=0;
        virtual const TCHAR* GetUserLanguage()=0;
        virtual const TCHAR* GetUserCountry()=0;
        virtual Locale GetLocale()=0;
        /**Aggiorna le propriet�*/
        virtual void Refresh()=0;
    };

    //classe factory per i widget
    class Application {

public:

        virtual ~Application() {}
        virtual System* GetSystemInstance()=0;
        virtual Window* GetNewWindow()=0;
        virtual Window* GetNewWindow(const TCHAR* title)=0;
        virtual Window* GetNewWindow(const TCHAR* title,bool resizable,bool iconifiable,bool maximizable)=0;
        //  virtual Dialog* GetNewDialog(const TCHAR* title,bool resizable,bool iconifiable,bool maximizable)=0;
        /**Crea un nuovo pulsante*/
        virtual Button* GetNewButton(const TCHAR* text)=0;
        virtual Button* GetNewButton(const TCHAR* text,const TCHAR* command)=0;
        virtual Button* GetNewButton(const TCHAR* text,const TCHAR* command,int width,int height)=0;
        virtual Button* GetNewDefaultButton(const TCHAR* text)=0;
        /**Crea una nuova label*/
        virtual Label* GetNewLabel(const TCHAR* text)=0;
        virtual Label* GetNewLabel(const TCHAR* text,TEXT_ALIGN align)=0;
        virtual Label* GetNewLabel(const TCHAR* text,BORDER_TYPE border)=0;
        virtual Label* GetNewLabel(const TCHAR* text,TEXT_ALIGN align,BORDER_TYPE border)=0;
        /**Restituisce una maschera di input*/
        virtual InputMask* GetNewInputMask(const TCHAR* mask,bool exclude)=0;
        /**Crea un campo di input testo*/
        virtual TextField* GetNewTextField()=0;
        virtual TextField* GetNewTextField(int max_length)=0;
        virtual TextField* GetNewTextField(int max_length,BORDER_TYPE border)=0;
        virtual TextField* GetNewTextField(int max_length,TEXT_FIELD_TYPE type)=0;
        virtual TextField* GetNewTextField(int max_length,TEXT_FIELD_TYPE type,BORDER_TYPE border)=0;
        virtual TextField* GetNewTextArea(int max_length,int nlines,int width,TEXT_FIELD_TYPE type,bool hscroll,bool vscroll)=0;
        /**CheckBox*/
        virtual CheckBox* GetNewCheckBox(const TCHAR* text)=0;
        virtual CheckBox* GetNewCheckBox(const TCHAR* text,bool selected)=0;
        /**Radio Button*/
        virtual RadioButton* GetNewRadioButton(const TCHAR* text)=0;
        virtual RadioButton* GetNewRadioButton(const TCHAR* text,bool selected)=0;
        /**List*/
        virtual List* GetNewList()=0;
        virtual List* GetNewList(LIST_SELECTION_MODE selmode)=0;
        virtual List* GetNewList(LIST_SELECTION_MODE selmode,BORDER_TYPE border)=0;
        virtual List* GetNewList(const TCHAR** items,int size,LIST_SELECTION_MODE selmode,bool sorted)=0;
        virtual List* GetNewList(const TCHAR** items,int size,LIST_SELECTION_MODE selmode,bool sorted,BORDER_TYPE border)=0;
        /**Combo box*/
        virtual ComboBox* GetNewComboBox()=0;
        virtual ComboBox* GetNewComboBox(COMBOBOX_STYLE style)=0;
        virtual ComboBox* GetNewComboBox(const TCHAR** items,int num_items,COMBOBOX_STYLE style,bool sorted)=0;

        /**Scroll Bar*/
        virtual ScrollBar* GetNewVScrollBar()=0;
        virtual ScrollBar* GetNewHScrollBar()=0;
        virtual ScrollBar* GetNewScrollBar(SCROLL_BAR_TYPE type,int minimum,int maximum)=0;

        /**Crea un bordo*/
        // virtual Border* GetNewBorder(BORDER_TYPE type)=0;
        // virtual Border* GetNewBorder(BORDER_TYPE type,COLOR color,int width)=0;
        /**Crea un lemento di un menu*/
        virtual MenuItem* GetNewMenuItem()=0;
        virtual MenuItem* GetNewMenuItem(TCHAR* text,TCHAR* action=0)=0;
        /**Crea un menu*/
        virtual Menu* GetNewMenu(TCHAR* text=0)=0;
        /**Crea una menu bar*/
        virtual MenuBar* GetNewMenuBar()=0;
        /**Crea un contenitore di controlli con titolo (group box)*/
        virtual GroupBox* GetNewGroupBox()=0;
        virtual GroupBox* GetNewGroupBox(int width,int height)=0;
        virtual GroupBox* GetNewGroupBox(int width,int height,TCHAR* text)=0;
        /**Crea un pannello contenitore*/
        virtual Panel* GetNewPanel()=0;
        virtual Panel* GetNewPanel(int width,int height)=0;
        virtual Panel* GetNewPanel(int width,int height,BORDER_TYPE border)=0;
        /**Crea un font*/
        virtual Font* GetNewFont(const TCHAR* font_name,int font_size,bool bold,bool italic,bool underline=false,bool strikeout=false)=0;
        /**Ottiene un font di sistema*/
        virtual Font* GetSysFont(LWTK_FONTS font_id)=0;

        /**Termina l'applicazione*/
        virtual void Quit(int return_value)=0;
        virtual void Quit()=0;

        /**rilascia tutti gli oggetti allocati*/
        virtual void Release()=0;
    };
};

#endif // LWTK_H_INCLUDED
