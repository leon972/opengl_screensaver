#ifndef LWTKWIN32_H_INCLUDED
#define LWTKWIN32_H_INCLUDED

#define WIN32_LEAN_AND_MEAN


#include "lwtk/lwtk.h"
#include "windows.h"
#include "wkeyinfo.h"
#include "wmouse.h"
#include <list>
#include <vector>
#include <string> //per test combo box
#include <map>

//nota:la definizione DEBUG_MODE puo' essere inserita automaticamente solo per//il build di debug
//da Projects/BuildOptions/define per la configurazione di debug

#ifdef DEBUG_MODE
#include "filelogger/filelogger.h"
#endif

using namespace util;

namespace lwtk {

    using namespace std;

    //stringa unicode
    typedef std::basic_string<TCHAR> ustring;



    class Win32Window;
    class Win32Graphics;
    class Win32Widget;
    class Win32GroupBox;
    class Win32Panel;
    // class Win32Border;
    class Win32Button;
    class Win32Label;
    class Win32TextField;
    class Win32MenuItem;
    class Win32Menu;
    class Win32MenuSeparator;
    class Win32MenuBar;
    class Win32RadioButton;
    class Win32CheckBox;
    class Win32List;
    class Win32ScrollBar;
    class Win32ComboBox;
    class Win32InputMask;
    class Win32KeyInfo;

#define FONT_NAME_SIZE 64

class DLL_EXPORT Win32Font:public video::Font {

        friend class Win32Application;
        friend class Win32Graphics;
        friend class Win32Widget;

protected:

       
       // static const size_t FONT_NAME_SIZE=64;

        static HFONT CreateFont(HDC hdc,const TCHAR* szFaceName,int iPointSizeH,int iPointSizeW,int attr);

        static int TranslateSysFont(LWTK_FONTS font_id);

        TCHAR font_name[FONT_NAME_SIZE];
        LWTK_FONTS system_font; //id del font di sistema (se � un font di sistema)
        bool is_sys_font;
        int font_attrs;
        int font_size;
        Win32Font(const TCHAR* szName,int size,bool bold,bool italic,bool underline,bool strikeout,LWTK_FONTS sys_font_id=FONT_NONE);


public:

        

        virtual ~Win32Font();
        const TCHAR* GetFontName();
        /**Restituisce la dimensione in punti del font*/
        int GetSize();
        bool IsBold();
        bool IsItalic();
        bool IsUnderline();
        bool IsStrikeout();
        int GetAttributes();
    };

class DLL_EXPORT Win32System:public System {

        friend class Win32Application;

protected:

        Win32System();
        virtual ~Win32System();
        static const size_t BUFF_SIZE=64;
        const TCHAR* os_name;
        const TCHAR* os_version;
        const TCHAR* dec_point;
        const TCHAR* path_separator;
        const TCHAR* username;
        const TCHAR* machine_name;
        const TCHAR* user_lang; //ISO code
        const TCHAR* user_country; //ISO code
        const TCHAR* th_sep; //separatore delle migliaia
        const TCHAR* currency_symbol;
        const TCHAR* currency_decsep;
        const TCHAR* short_dtformat;
        int res;

public:

        virtual const TCHAR* GetOSName();
        virtual const TCHAR* GetOSVersion();
        virtual const TCHAR* GetDecimalPoint();
        virtual const TCHAR* GetPathSeparator();
        virtual const TCHAR* GetUsername();
        virtual const TCHAR* GetMachineName();
        virtual const TCHAR* GetUserLanguage();
        virtual const TCHAR* GetUserCountry();
        virtual Locale GetLocale();
        virtual void Refresh();

    };

class DLL_EXPORT Win32Application:public Application {

        friend class Win32Window;
        // friend class Win32Dialog;
        friend class Win32Widget;
        friend class Win32Panel;
        friend class Win32MenuItem;

private:

        static bool is_executing;

        static bool exit_loop;
        /**contatore usato per generazione di id automatici*/
        static unsigned int res_id;

        static Win32Application* instance;
        /**nome globale dell'applicazione*/
        static const TCHAR* szAppName;
        /**classe delle finestre standard*/
        WNDCLASS wndclass;

        static HINSTANCE hInstance;

        static Win32System win32_system;

        /**mappa delle finestre create*/
        static map<HWND,Win32Window*> winmap;
        /**mappa degli handle delle finestre secondarie di controllo*/
        static map<HWND,Win32Widget*> hwndctrlmap;
        /**mappa che associa gli id univoci dei menu*/
        static map<int,Win32MenuItem*> menumap;

        /**lista dei controlli con bordo*/
        //static list<Win32Widget*> borded_ctrl;

        /**window proc*/
        static LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam);


        /**dialog proc*/
        static BOOL CALLBACK DlgProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam);

        /**window modal corrente*/
        //static HWND cur_modal_hwnd;

        Win32Application(const TCHAR* app_name);

        virtual ~Win32Application();

        list<Win32Window*> window_list;
        list<Win32Button*> button_list;
        list<Win32Label*> label_list;
        list<Win32TextField*> text_list;
        //list<Win32Border*> border_list;
        list<Win32MenuItem*> menu_item_list;
        list<Win32Menu*> menu_list;
        list<Win32MenuBar*> menu_bar_list;
        list<Win32RadioButton*> radio_list;
        list<Win32CheckBox*> check_list;
        list<Win32List*> listbox_list;
        list<Win32ScrollBar*>scrollbar_list;
        list<Win32GroupBox*>group_list;
        list<Win32ComboBox*>combo_list;
        list<Win32InputMask*>imask_list;
        list<Win32Panel*>panel_list;
        list<Win32Font*>font_list;

public:

        static Application* GetInstance(const TCHAR* app_name);

        static Application* GetInstance();

        static const TCHAR* GetAppName();

        #ifdef DEBUG_MODE
        //logger per debug
        static FileLogger m_log;
        #endif

        System* GetSystemInstance();
        /**Crea una nuova finestra*/
        Window* GetNewWindow();
        Window* GetNewWindow(const TCHAR* title);
        Window* GetNewWindow(const TCHAR* title,bool resizable,bool iconifiable,bool maximizable);
        // Dialog* GetNewDialog(const TCHAR* title,bool resizable,bool iconifiable,bool maximizable);

        /**Crea un nuovo pulsante*/
        Button* GetNewButton(const TCHAR* text);
        Button* GetNewButton(const TCHAR* text,const TCHAR* command);
        Button* GetNewButton(const TCHAR* text,const TCHAR* command,int width,int height);
        Button* GetNewDefaultButton(const TCHAR* text);
        /**label (testo statico)*/
        Label* GetNewLabel(const TCHAR* text);
        Label* GetNewLabel(const TCHAR* text,TEXT_ALIGN align);
        Label* GetNewLabel(const TCHAR* text,BORDER_TYPE border);
        Label* GetNewLabel(const TCHAR* text,TEXT_ALIGN align,BORDER_TYPE border);

        /**Restituisce un filtro per l'input dei widget TextField*/
        InputMask* GetNewInputMask(const TCHAR* mask,bool exclude);
        /**Campo input testo*/
        TextField* GetNewTextField();
        TextField* GetNewTextField(int max_length);
        TextField* GetNewTextField(int max_length,BORDER_TYPE border);
        TextField* GetNewTextField(int max_length,TEXT_FIELD_TYPE type);
        TextField* GetNewTextField(int max_length,TEXT_FIELD_TYPE type,BORDER_TYPE border);
        TextField* GetNewTextArea(int max_length,int nlines,int width,TEXT_FIELD_TYPE type,bool hscroll,bool vscroll);

        /**CheckBox*/
        CheckBox* GetNewCheckBox(const TCHAR* text);
        CheckBox* GetNewCheckBox(const TCHAR* text,bool selected);
        /**Radio Button*/
        RadioButton* GetNewRadioButton(const TCHAR* text);
        RadioButton* GetNewRadioButton(const TCHAR* text,bool selected);
        /**List*/
        List* GetNewList();
        List* GetNewList(LIST_SELECTION_MODE selmode);
        List* GetNewList(LIST_SELECTION_MODE selmode,BORDER_TYPE border);
        List* GetNewList(const TCHAR** items,int size,LIST_SELECTION_MODE selmode,bool sorted);
        List* GetNewList(const TCHAR** items,int size,LIST_SELECTION_MODE selmode,bool sorted,BORDER_TYPE border);


        /**ComboBox*/
        ComboBox* GetNewComboBox();
        ComboBox* GetNewComboBox(COMBOBOX_STYLE style);
        ComboBox* GetNewComboBox(const TCHAR** items,int num_items,COMBOBOX_STYLE style,bool sorted);
        /**Scroll Bar*/
        ScrollBar* GetNewVScrollBar();
        ScrollBar* GetNewHScrollBar();
        ScrollBar* GetNewScrollBar(SCROLL_BAR_TYPE type,int minimum,int maximum);
        /**Crea un nuovo bordo*/
        //Border* GetNewBorder(BORDER_TYPE type);
        //Border* GetNewBorder(BORDER_TYPE type,COLOR color,int width);
        /**Crea un nuovo elemento di menu*/
        MenuItem* GetNewMenuItem();
        MenuItem* GetNewMenuItem(TCHAR* text,TCHAR* action=0);
        /**Crea un menu*/
        Menu* GetNewMenu(TCHAR* text=0);
        /**Crea una barra dei menu*/
        MenuBar* GetNewMenuBar();
        /**Pannello*/
        GroupBox* GetNewGroupBox();
        GroupBox* GetNewGroupBox(int width,int height);
        GroupBox* GetNewGroupBox(int width,int height,TCHAR* text);
        /**Crea un pannello contenitore*/
        Panel* GetNewPanel();
        Panel* GetNewPanel(int width,int height);
        Panel* GetNewPanel(int width,int height,BORDER_TYPE border);
        /**Fonts*/
        Font* GetNewFont(const TCHAR* font_name,int font_size,bool bold,bool italic,bool underline=false,bool strikeout=false);
        /**Ottiene un font di sistema*/
        Font* GetSysFont(LWTK_FONTS font_id);

        /**rilascia tutti gli oggetti allocati*/
        void Release();

        virtual void Quit(int return_value);
        virtual void Quit();

        /*-------- metodici specifici per questa implementazione*/
        /**trasformazione formato colori*/
        static COLOR ToColor(COLORREF c);
        static COLORREF ToColorref(COLOR c);
        /**gestione ciclo messaggi delle finestre*/
        static void DoMessagePump();
        /**genera un identificativo univoco di risorsa*/
        static unsigned int GetNewId();
        /**restituisce l'handle dell'istanza*/
        static HINSTANCE GetHInstance();
        /**Restituisce il widget collegato all'hwnd*/
        static Win32Widget* GetWidget(HWND hwnd);
        /**Restituisce l'istanza di system*/
        static Win32System* GetWin32SystemInstance();

    };

class DLL_EXPORT Win32Window: public Window {

        friend class Win32Application;

private:

        Win32KeyInfo ki_up,ki_down,ki_pressed;

protected:

        virtual void init(bool,bool,bool);
        Win32Panel* content_panel;
        Win32Graphics* graphics;
        const TCHAR* title;
        COLORREF back_color;
        COLORREF fore_color;
        int countdown;
        bool is_visible;
        WINDOW_SHOW_MODE show_mode;
        HWND hwnd;
        HWND hwnd_parent_window;
        HDC hdc;
        /**textmetric per il device context corrente*/
        TEXTMETRIC textmetrics;
        list<WindowEvents*> *window_events;
        list<PaintEvent*>* paint_events;
        list<FocusEvents*>* focus_events;
        list<KeyEvents*>* key_events;

        void UpdateTextMetrics();
        /**invia il messaggio generato dal sistema operativo alla finestra*/
        virtual LRESULT HandleWin32Msg(HWND h,UINT message,WPARAM wParam,LPARAM lParam,bool* handled);
        /**disegno personalizzato*/
        virtual LRESULT Paint(HDC hdc);
        Win32Window(const TCHAR* title,bool resizable,bool iconifiable,bool maximizable);
        Win32Window(const TCHAR* title);
        Win32Window();

public:

        virtual ~Win32Window();

        //--- interfaccia Window ---
        virtual const TCHAR* GetTitle();
        virtual void SetTitle(const TCHAR* title);
        virtual const TCHAR* GetText();
        virtual void SetText(const TCHAR* text);
        virtual void SetForeground(COLOR c);
        virtual COLOR GetForeground();
        virtual void SetBackground(COLOR c);
        virtual COLOR GetBackground();
        virtual void Resize(int w,int h);
        virtual void Move(int x,int y);
        virtual int GetWidth();
        virtual int GetHeight();
        virtual int GetLeft();
        virtual int GetTop();
        virtual int SetLeft(int x);
        virtual int SetTop(int y);
        virtual int SetWidth(int w);
        virtual int SetHeight(int h);
        virtual void SetPositionRelativeTo(Window* ref);
        virtual void SetPositionRelativeTo(Window* ref,WIDGET_POS position);
        virtual void SetVisible(bool visible);
        virtual bool IsVisible();
        virtual void Show();
        virtual void Show(WINDOW_SHOW_MODE show_mode);
        virtual void Close();
        virtual void Iconify();
        virtual void Maximize();
        virtual void Activate();
        virtual bool IsIconified();
        virtual bool IsMaximized();
        virtual MSG_BOX_RESULT MsgBox(const TCHAR* szTitle,int type,TCHAR* szFormat, ...);
        virtual Graphics* GetGraphics();
        virtual void SetMenuBar(MenuBar* menu_bar);
        //------------- interfaccia container
        virtual const Widget* Add(Widget* widget);
        virtual bool Remove(Widget* widget);
        /**Aggiunge un gestore degli eventi della finestra*/
        virtual WindowEvents* AddWindowEvents(WindowEvents* evt);
        /**Rimuove un gestore degli eventi della finestra*/
        virtual bool RemoveWindowEvents(WindowEvents* evt);
        virtual PaintEvent* AddPaintEvent(PaintEvent* evt);
        virtual bool RemovePaintEvent(PaintEvent* evt);
        /**Eventi focus*/
        virtual FocusEvents* AddFocusEvents(FocusEvents* evt);
        virtual bool RemoveFocusEvents(FocusEvents* evt);
        /**Eventi tastiera*/
        virtual KeyEvents* AddKeyEvents(KeyEvents* e);
        virtual bool RemoveKeyEvents(KeyEvents* e);
        /**Eventi mouse*/
        virtual MouseEvents* AddMouseEvents(MouseEvents* e);
        virtual bool RemoveMouseEvents(MouseEvents* e);
        /**Eventi movimento del mouse*/
        virtual MouseMoveEvents* AddMouseMoveEvents(MouseMoveEvents* e);
        virtual bool RemoveMouseMoveEvents(MouseMoveEvents* e);

        virtual Panel* GetContentPanel();
        virtual void Refresh();
        virtual void Refresh(int left,int top,int right,int bottom);
        virtual int GetTextWidth(const TCHAR* text);
        virtual int GetTextHeight(const TCHAR* text);


        //------------- metodi specifici dell'implementazione -------

        HWND GetHWND();
        HWND GetParentHWND();
        HDC GetHDC();
        static int TextWidth(HWND hwnd,const TCHAR* text);
        static int TextHeight(HWND hwnd,const TCHAR* text);

    };


class DLL_EXPORT Win32Widget:public Widget {

        friend class Win32Application;
        friend class Win32Panel;
        friend class Win32GroupBox;
        friend class Win32Window;

protected:

        TCHAR* text;
        const TCHAR* action;
        HFONT custom_font;
        Font* current_font;
        bool mouse_over; //usato per gestione rollover
        Container* parent_container;
        //dimensioni di default dei widget
        static const int defaultHeight=25;
        static const int defaultWidth=32;
        static int ctrl_id_counter; //generatore id univoci dei controlli
        static int GenId();//genera un id univoco per i controlli
        static Win32KeyInfo ki_up,ki_down,ki_pressed;
        list<ActionEvent*>* action_events;
        list<PaintEvent*>* paint_events;
        list<MouseEvents*>* mouse_events;
        list<MouseMoveEvents*>* mouse_move_events;
        list<MouseRolloverEvents*>* mouse_rollover_events;
        list<FocusEvents*>* focus_events;
        list<KeyEvents*>* key_events;
        UINT id; //id risorsa
        bool is_visible;
        bool is_enabled;
        void RegisterHWND();
        /**registra l'id del widget nella mappa degli id*/
        void Register();
        void init();
        //restituisce l'altezza del testo in pixel sulla finestra hwnd
        //static int GetTextHeight(HWND hwnd);
        /**restituisce il flag win32 corrispondente al tipo di bordo*/
        static UINT GetBorderStyle(BORDER_TYPE type);
        static UINT GetBorderStyleEx(BORDER_TYPE type);
        int width,height,x,y; //dimensioni e posizione
        COLOR foreground,background;
        COLORREF cref_foreground,cref_background;
        COLORREF cref_default_background; //colore di default per il background
        HBRUSH hbrBackground; //pennello di default per il background
        bool custom_foreground; //flag che indica che il widget ha un colore di primo piano impostato dall'utente
        bool custom_background; //flag che indica che il widget ha un colore di sfondo impostato dall'utente

        HWND parent_hwnd;
        BORDER_TYPE border;
        /**Crea il widget sulla finestra di destinazione*/
        virtual void Create(HWND dest)=0;
        /**invia il messaggio generato dal sistema operativo al widget*/
        virtual LRESULT HandleWin32Msg(HWND hwnd_parent,UINT message,WPARAM wParam,LPARAM lParam,bool* handled);
        /**disegno personalizzato*/
        virtual LRESULT Paint(HDC hdc);
        /**ridimensiona il controllo in base al testo*/
        void ResizeToDefault(int insetx,int insety);
        /**imposta le dimensioni iniziali*/
        void SetInitialSize(int insetx,int insety);
        /**Dopo la creazione del controllo, inizializza le propriet� standard (dimensioni,colori ecc...)*/
        virtual void PostCreateInit();
        /**Invoca gli action events*/
        virtual void DoActions();

public:

        HWND hwnd; //hwnd del widget
        virtual ~Win32Widget();
        //interfaccia Control
        virtual const TCHAR* GetText();
        virtual void SetText(const TCHAR* text);
        virtual void SetForeground(COLOR c);
        virtual COLOR GetForeground();
        virtual void SetBackground(COLOR c);
        virtual COLOR GetBackground();
        virtual int GetWidth();
        virtual int GetHeight();
        virtual void Resize(int w,int h);
        virtual void Move(int x,int y);
        virtual int GetLeft();
        virtual int GetTop();
        virtual int SetWidth(int w);
        virtual int SetHeight(int h);
        virtual int SetLeft(int x);
        virtual int SetTop(int y);
        virtual void SetEnabled(bool enabled);
        virtual bool IsEnabled();
        virtual void SetVisible(bool visible);
        virtual bool IsVisible();
        /**Imposta il font corrente per la finestra*/
        virtual void SetFont(Font* font);
        /**Ottiene il font corrente*/
        virtual Font* GetFont();
        virtual Container* GetParent();
        virtual BORDER_TYPE GetBorder()=0;
        //interfaccia Widget
        virtual void AddActionEvent(ActionEvent* e);
        virtual bool RemoveActionEvent(ActionEvent* e);
        virtual void AddMouseEvents(MouseEvents* e);
        virtual void RemoveMouseEvents(MouseEvents* e);
        virtual void AddMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddMouseRolloverEvents(MouseRolloverEvents* e);
        virtual void RemoveMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddFocusEvents(FocusEvents* e);
        virtual void RemoveFocusEvents(FocusEvents* e);
        virtual void AddKeyEvents(KeyEvents* e);
        virtual void RemoveKeyEvents(KeyEvents* e);
        virtual void SetAction(const TCHAR* action);
        virtual void SetZOrder(ZORDER_POS pos);
        virtual void SetZOrder(Widget* ins_after);
        virtual void ResizeToDefault();
        virtual const TCHAR* GetAction();

        //------------- metodi specifici dell'implementazione -------
        UINT GetId();
        HWND GetHWND();
    };

//nota bene:deve ereditare public da Win32Widget altrimenti non funziona il metodo add (perch� il dynamic cast rende null)
class DLL_EXPORT Win32Panel:public Panel,public Win32Widget {

        friend class Win32Window;
        //friend class Win32Dialog;
        friend class Win32Application;

protected:

        list<Win32Widget*>* widgets;
        virtual void Create(HWND dest);
        /**Costruttore speciale usato per creare un content panel*/
        Win32Panel(HWND hwnd);
        /**Costruttore standard*/
        Win32Panel();
        Win32Panel(BORDER_TYPE b);
        Win32Graphics* graphics;
        /**classe della finestra child usata per costruire il pannello*/
        static WNDCLASS wnd_panel_class;
        /**flag che indica se la classe del pannello � stata inizializzata*/
        static int wnd_panel_class_counter;
        static const char* CreatePanelClass();
        static char szCurClassName[64];
        virtual LRESULT HandleWin32Msg(HWND hwnd_parent,UINT message,WPARAM wParam,LPARAM lParam,bool* handled);

public:

        virtual ~Win32Panel();
        virtual const Widget* Add(Widget* widget);
        virtual bool Remove(Widget* widget);

        //interfaccia Widget

        virtual Container* GetParent();
        virtual const TCHAR* GetText();
        virtual void SetText(const TCHAR* text);
        virtual void SetAction(const TCHAR* action);
        virtual const TCHAR* GetAction();
        virtual void SetForeground(COLOR c);
        virtual COLOR GetForeground();
        virtual void SetBackground(COLOR c);
        virtual COLOR GetBackground();
        virtual void AddActionEvent(ActionEvent* e);
        virtual bool RemoveActionEvent(ActionEvent* e);
        virtual PaintEvent* AddPaintEvent(PaintEvent* evt);
        virtual bool RemovePaintEvent(PaintEvent* evt);
        virtual void AddMouseEvents(MouseEvents* e);
        virtual void RemoveMouseEvents(MouseEvents* e);
        virtual void AddMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddMouseRolloverEvents(MouseRolloverEvents* e);
        virtual void RemoveMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddFocusEvents(FocusEvents* e);
        virtual void RemoveFocusEvents(FocusEvents* e);
        virtual void AddKeyEvents(KeyEvents* e);
        virtual void RemoveKeyEvents(KeyEvents* e);
        virtual int GetWidth();
        virtual int GetHeight();
        virtual int SetWidth(int w);
        virtual int SetHeight(int h);
        virtual int SetLeft(int x);
        virtual int SetTop(int y);
        virtual void Resize(int w,int h);
        virtual void Move(int x,int y);
        virtual void SetZOrder(ZORDER_POS pos);
        virtual void SetZOrder(Widget* ins_after);
        virtual int GetLeft();
        virtual int GetTop();
        virtual void SetEnabled(bool enabled);
        virtual bool IsEnabled();
        virtual void SetVisible(bool visible);
        virtual bool IsVisible();
        virtual void ResizeToDefault();
        virtual void SetFont(Font* font);
        virtual Font* GetFont();
        // virtual void SetBorder(Border* border);
        virtual BORDER_TYPE GetBorder();
        //-----
        /**disegno personalizzato*/
        virtual LRESULT Paint(HDC hdc);
        virtual void Refresh();
        list<Win32Widget*>* GetWidgets();
    };


class DLL_EXPORT Win32GroupBox:public GroupBox,public Win32Panel {

        friend class Win32Window;
        friend class Win32Application;

protected:

        void Create(HWND dest);
        Win32GroupBox();

public:

        virtual ~Win32GroupBox();
        virtual const Widget* Add(Widget* widget);
        virtual bool Remove(Widget* widget);

        //interfaccia Widget
        virtual const TCHAR* GetText();
        virtual void SetText(const TCHAR* text);
        virtual void SetAction(const TCHAR* action);
        virtual const TCHAR* GetAction();
        virtual void SetForeground(COLOR c);
        virtual COLOR GetForeground();
        virtual void SetBackground(COLOR c);
        virtual COLOR GetBackground();
        virtual Container* GetParent();
        virtual void AddActionEvent(ActionEvent* e);
        virtual bool RemoveActionEvent(ActionEvent* e);
        virtual PaintEvent* AddPaintEvent(PaintEvent* evt);
        virtual bool RemovePaintEvent(PaintEvent* evt);
        virtual void AddMouseEvents(MouseEvents* e);
        virtual void RemoveMouseEvents(MouseEvents* e);
        virtual void AddMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddMouseRolloverEvents(MouseRolloverEvents* e);
        virtual void RemoveMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddFocusEvents(FocusEvents* e);
        virtual void RemoveFocusEvents(FocusEvents* e);
        virtual void AddKeyEvents(KeyEvents* e);
        virtual void RemoveKeyEvents(KeyEvents* e);
        virtual int GetWidth();
        virtual int GetHeight();
        virtual int SetWidth(int w);
        virtual int SetHeight(int h);
        virtual int SetLeft(int x);
        virtual int SetTop(int y);
        virtual void SetZOrder(ZORDER_POS pos);
        virtual void SetZOrder(Widget* ins_after);
        virtual void Resize(int w,int h);
        virtual void Move(int x,int y);
        virtual int GetLeft();
        virtual int GetTop();
        virtual void SetEnabled(bool enabled);
        virtual bool IsEnabled();
        virtual void SetVisible(bool visible);
        virtual bool IsVisible();
        virtual void ResizeToDefault();
        virtual void SetFont(Font* font);
        virtual Font* GetFont();
        //  virtual void SetBorder(Border* border);
        virtual BORDER_TYPE GetBorder();
        virtual void Refresh();

    };

class DLL_EXPORT Win32MenuItem:public MenuItem,public Win32Widget {

        friend class Win32Menu;
        friend class Win32Application;

protected:

        HMENU hmenu; //handle del menu genitore
        bool is_checked;
        bool is_separator;
        void Create(HWND dest);
        Win32MenuItem();

public:

        virtual ~Win32MenuItem();
        virtual bool IsChecked();
        virtual void SetChecked(bool checked);
        virtual Container* GetParent();
        virtual void SetForeground(COLOR c);
        virtual COLOR GetForeground();
        virtual void SetBackground(COLOR c);
        virtual COLOR GetBackground();
        virtual void Resize(int w,int h);
        virtual void Move(int x,int y);
        virtual int GetWidth();
        virtual int GetHeight();
        virtual int GetLeft();
        virtual int GetTop();
        virtual int SetWidth(int w);
        virtual int SetHeight(int h);
        virtual int SetLeft(int x);
        virtual int SetTop(int y);
        virtual void SetZOrder(ZORDER_POS pos);
        virtual void SetZOrder(Widget* ins_after);
        virtual void SetEnabled(bool enabled);
        virtual bool IsEnabled();
        virtual void SetVisible(bool visible);
        virtual bool IsVisible();
        virtual void ResizeToDefault();
        virtual bool IsSeparator();
        virtual const TCHAR* GetText();
        virtual void SetText(const TCHAR* text);
        virtual void SetAction(const TCHAR* action);
        virtual const TCHAR* GetAction();
        virtual void SetFont(Font* font);
        virtual Font* GetFont();
        virtual void AddActionEvent(ActionEvent* e);
        virtual bool RemoveActionEvent(ActionEvent* e);
        virtual void AddMouseEvents(MouseEvents* e);
        virtual void RemoveMouseEvents(MouseEvents* e);
        virtual void AddMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddMouseRolloverEvents(MouseRolloverEvents* e);
        virtual void RemoveMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddFocusEvents(FocusEvents* e);
        virtual void RemoveFocusEvents(FocusEvents* e);
        virtual void AddKeyEvents(KeyEvents* e);
        virtual void RemoveKeyEvents(KeyEvents* e);
        //virtual void SetBorder(Border* border);
        virtual BORDER_TYPE GetBorder();
    };


class DLL_EXPORT Win32Menu:private Win32MenuItem,public virtual Menu {

        friend class Win32MenuBar;
        friend class Win32Application;

protected:
        HMENU parent_menu; //handle del menu genitore
        Win32Menu();
public:

        virtual ~Win32Menu();
        virtual void AddItem(MenuItem* m);
        virtual bool RemoveItem(MenuItem* m);
        virtual void AddSubMenu(Menu* m);
        virtual bool RemoveSubMenu(Menu* m);
        virtual void AddSeparator();
        virtual void SetForeground(COLOR c);
        virtual COLOR GetForeground();
        virtual void SetBackground(COLOR c);
        virtual COLOR GetBackground();
        virtual void Resize(int w,int h);
        virtual void Move(int x,int y);
        virtual int GetWidth();
        virtual int GetHeight();
        virtual int GetLeft();
        virtual int GetTop();
        virtual const TCHAR* GetText();
        virtual void SetText(const TCHAR* text);
        virtual void SetEnabled(bool enabled);
        virtual bool IsEnabled();
        virtual void SetVisible(bool visible);
        virtual bool IsVisible();
        virtual void ResizeToDefault();
        virtual void SetAction(const TCHAR* action);
        virtual const TCHAR* GetAction();
        virtual void SetFont(Font* font);
        virtual Font* GetFont();
        virtual void AddActionEvent(ActionEvent* e);
        virtual bool RemoveActionEvent(ActionEvent* e);
        virtual void AddMouseEvents(MouseEvents* e);
        virtual void RemoveMouseEvents(MouseEvents* e);
        virtual void AddMouseMoveEvents(MouseMoveEvents* e);
        virtual void RemoveMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddFocusEvents(FocusEvents* e);
        virtual void RemoveFocusEvents(FocusEvents* e);
        virtual bool IsChecked();
        virtual void SetChecked(bool checked);
    };

class DLL_EXPORT Win32MenuBar:public MenuBar {

        friend class Win32Window;
        friend class Win32Application;

protected:

        HMENU hmenu; //handle del menu della menu bar
        Win32Window* parent;
        Win32MenuBar();

public:

        virtual ~Win32MenuBar();
        virtual void SetEnabled(bool enabled);
        virtual bool IsEnabled();
        virtual void SetVisible(bool visible);
        virtual bool IsVisible();
        virtual void AddMenu(Menu* m);
        virtual bool RemoveMenu(Menu* m);
    };




class DLL_EXPORT Win32Graphics:public Graphics {
private:

        HDC hdc;
        COLORREF cur_color; //colore disegno
        COLORREF cur_fill_color; //colore riempimento
        COLORREF cur_clear_color; //colore sfondo area disegno
        COLORREF cur_text_color; //colore ouput del testo
        int width,height;
        int line_width;//larghezza in pixel della linea del disegno
        HPEN draw_pen; //penne per il disegno e per il testo
        HBRUSH draw_brush; //pennello per riempimento
        bool bk_transparent; //flag che indica se attualemente � impostato bk mode transparent
        bool tx_metric_init; //flag che indica che la struttura textmetric � aggiornata
        TEXTMETRIC textmetric;
        HFONT custom_font;
        Font* current_font;

        void SetBkTransparent(bool value);
        void InitTextMetric();
        static const float ANGLE_CONV=0.0174532925f;

public:
        Win32Graphics();
        virtual ~Win32Graphics();

        //cancella l'area grafica
        virtual void Cls(void);
        virtual void Cls(COLOR c);
        virtual void SetClearScreenColor(COLOR color);
        //imposta un pixel dell'area grafica
        virtual void SetPixel(int x,int y);
        //traccia una linea con il colore di disegno corrente
        virtual void DrawLine(int x1,int y1,int x2,int y2);
        //disegna un rettangolo
        virtual void DrawRect(int x1,int y1,int x2,int y2);
        //riempie un rettangolo
        virtual void FillRect(int x1,int y1,int x2,int y2);
        //rettangolo stondato
        virtual void RoundRect(int x1,int y1,int x2,int y2,int radius,bool filled);
        //disegna un cerchio
        virtual void DrawCircle(int cx,int cy,float radius);
        //disegna un arco
        virtual void DrawArc(int cx,int cy,float radiusx,float radiusy,float deg_ang_start,float deg_ang_finish);
        //disegna un settore riempito con il colore di riempimento corrente
        virtual void FillArc(int cx,int cy,float radiusx,float radiusy,float deg_ang_start,float deg_ang_finish);
        //riempie un cerchio
        virtual void FillCircle(int cx,int cy,float radius);
        //riempie un'ellisse
        virtual void FillEllipse(int cx,int cy,float radiusx,float radiusy);
        //disegna un'ellisse
        virtual void DrawEllipse(int cx,int cy,float radiusx,float radiusy);
        //larghezza linea disegno
        virtual void SetLineWidth(int width);
        virtual int GetLineWidth();
        //imposta il colore trasparente il blitting
        virtual void SetTransparentBlitColor(COLOR color);
        //acquisisce il colore trasparente per il blitting
        virtual COLOR GetTransparentBlitcolor(void);
        //crea il colore a partire dai valori RGB
        //imposta il colore per il disegno
        virtual void SetDrawColor(COLOR color);
        virtual void SetDrawColor(unsigned char red,unsigned char green,unsigned char blue);
        virtual void SetDrawColor(unsigned char red,unsigned char green,unsigned char blue,unsigned char alpha);
        //imposta il colore di riempimento
        virtual void SetFillColor(COLOR color);
        virtual void SetFillColor(unsigned char red,unsigned char green,unsigned char blue);
        virtual void SetFillColor(unsigned char red,unsigned char green,unsigned char blue,unsigned char alpha);
        //imposta il colore di output per il testo
        virtual void SetTextColor(COLOR color);
        virtual void SetTextColor(unsigned char red,unsigned char green,unsigned char blue);
        virtual void SetTextColor(unsigned char red,unsigned char green,unsigned char blue,unsigned char alpha);
        //output di testo alle coordinate x,y
        virtual void WriteText(int x,int y,const TCHAR* formatText ...);
        //restituisce la larghezza del font corrente
        virtual int GetFontWidth(void);
        //restituisce l'altezza del font corrente
        virtual int GetFontHeight(void);
        //ottiene il colore per il disegno
        virtual COLOR GetDrawColor(void);
        //ottiene il colore corrente per il riempimento
        virtual COLOR GetFillColor(void);
        //ottiene il colore di output per il testo corrente
        virtual COLOR GetTextColor(void);
        virtual COLOR GetPixel(int x,int y);

        /**Imposta il font corrente per la finestra*/
        virtual void SetFont(Font* font);
        /**Ottiene il font corrente*/
        virtual Font* GetFont();

        virtual OriginPos GetOriginPos(void);

        //restituisce la direzione dell'asse verticale
        virtual VAxisDir GetVerticalAxisDir(void);

        //restituisce la direzione dell'asse orizzontale
        virtual HAxisDir GetHorizontalAxisDir(void);

        //ottiene la larghezza in pixel dell'area grafica
        int GetScreenWidth(void);
        //ottiene l'altezza in pixel dell'area grafica
        int GetScreenHeight(void);
        //ottiene il numero di bit per pixel
        int GetScreenBpp(void);
        //rende true se � in modalit� color palette
        bool IsPaletteColorMode(void);
        bool IsFullScreen(void);
         /**applica un rettangolo di clipping*/
        void SetClippingArea(int x,int y,int x1,int y1);
        /**rimuove il rettangolo di clipping*/
        void RemoveClippingArea();


        //------------- metodi specifici Win32
        void SetDC(HDC hdc);
        HDC GetDC();
        void SetInvalidRect(const RECT& rect);
    };

class DLL_EXPORT Win32Button:public Button,public Win32Widget {

        friend class Win32Application;

protected:

        void Create(HWND dest);
        Win32Button(const TCHAR* text,bool is_default);
        bool is_default; //bottone di default
        bool m_owner_draw;
        virtual LRESULT HandleWin32Msg(HWND hwnd_parent,UINT message,WPARAM wParam,LPARAM lParam,bool* handled);

        //dimensioni di default
        static const int WIDTH=64;
        static const int HEIGHT=32;

public:

        virtual ~Win32Button();
        Container* GetParent();
        virtual void SetForeground(COLOR c);
        virtual COLOR GetForeground();
        virtual void SetBackground(COLOR c);
        virtual COLOR GetBackground();
        virtual void Resize(int w,int h);
        virtual void Move(int x,int y);
        virtual int GetWidth();
        virtual int GetHeight();
        virtual int GetLeft();
        virtual int GetTop();
        virtual int SetWidth(int w);
        virtual int SetHeight(int h);
        virtual int SetLeft(int x);
        virtual int SetTop(int y);
        virtual void SetZOrder(ZORDER_POS pos);
        virtual void SetZOrder(Widget* ins_after);
        virtual void SetEnabled(bool enabled);
        virtual bool IsEnabled();
        virtual void SetVisible(bool visible);
        virtual bool IsVisible();
        virtual void ResizeToDefault();
        virtual const TCHAR* GetText();
        virtual void SetText(const TCHAR* text);
        virtual void SetAction(const TCHAR* action);
        virtual const TCHAR* GetAction();
        virtual void SetFont(Font* font);
        virtual Font* GetFont();
        virtual void AddActionEvent(ActionEvent* e);
        virtual bool RemoveActionEvent(ActionEvent* e);
        virtual void AddMouseEvents(MouseEvents* e);
        virtual void AddMouseRolloverEvents(MouseRolloverEvents* e);
        virtual void RemoveMouseEvents(MouseEvents* e);
        virtual void AddMouseMoveEvents(MouseMoveEvents* e);
        virtual void RemoveMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddFocusEvents(FocusEvents* e);
        virtual void RemoveFocusEvents(FocusEvents* e);
        virtual void AddKeyEvents(KeyEvents* e);
        virtual void RemoveKeyEvents(KeyEvents* e);
        //virtual void SetBorder(Border* border);
        virtual BORDER_TYPE GetBorder();
    };

class DLL_EXPORT Win32Label:public Label,public Win32Widget {

        friend class Win32Application;

protected:

        void Create(HWND dest);
        //i costruttori sono invocati dalla classe factory
        Win32Label(const TCHAR* text);
        Win32Label(const TCHAR* text,TEXT_ALIGN align,BORDER_TYPE b);
        TEXT_ALIGN text_align;
        void init(const TCHAR* text);
public:

        static const int HEIGHT=24;
        static const int WIDTH=64;
        static const int MAX_DEFAULT_WIDTH=300;

        virtual Container* GetParent();
        virtual void SetForeground(COLOR c);
        virtual COLOR GetForeground();
        virtual void SetBackground(COLOR c);
        virtual COLOR GetBackground();
        virtual void Resize(int w,int h);
        virtual void Move(int x,int y);
        virtual int GetWidth();
        virtual int GetHeight();
        virtual int GetLeft();
        virtual int GetTop();
        virtual int SetWidth(int w);
        virtual int SetHeight(int h);
        virtual int SetLeft(int x);
        virtual int SetTop(int y);
        virtual void SetZOrder(ZORDER_POS pos);
        virtual void SetZOrder(Widget* ins_after);
        virtual void SetEnabled(bool enabled);
        virtual bool IsEnabled();
        virtual void SetVisible(bool visible);
        virtual bool IsVisible();
        virtual void ResizeToDefault();
        virtual const TCHAR* GetText();
        virtual void SetText(const TCHAR* text);
        //interfaccia Label
        void SetTextAlign(TEXT_ALIGN align);
        TEXT_ALIGN GetTextAlign();

        virtual void SetAction(const TCHAR* action);
        virtual const TCHAR* GetAction();
        virtual void SetFont(Font* font);
        virtual Font* GetFont();
        virtual void AddActionEvent(ActionEvent* e);
        virtual bool RemoveActionEvent(ActionEvent* e);
        virtual void AddMouseEvents(MouseEvents* e);
        virtual void AddMouseRolloverEvents(MouseRolloverEvents* e);
        virtual void RemoveMouseEvents(MouseEvents* e);
        virtual void AddMouseMoveEvents(MouseMoveEvents* e);
        virtual void RemoveMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddFocusEvents(FocusEvents* e);
        virtual void RemoveFocusEvents(FocusEvents* e);
        virtual void AddKeyEvents(KeyEvents* e);
        virtual void RemoveKeyEvents(KeyEvents* e);
        //virtual void SetBorder(Border* border);
        virtual BORDER_TYPE GetBorder();

        //  virtual void SetAction(const TCHAR* action);
        //  virtual const TCHAR* GetAction();
        // virtual void AddActionEvent(ActionEvent* e);
        // virtual bool RemoveActionEvent(ActionEvent* e);
    };

class DLL_EXPORT Win32InputMask:public InputMask {

        friend class Win32Application;
        friend class Win32TextField;

private:

        static const size_t MAX_CHARS=256;
        bool bmask[MAX_CHARS];
        const TCHAR* cur_mask;
        bool exclude;
        Win32InputMask(const TCHAR* mask,bool exclude);

public:

        /**restituisce i caratteri che compongono la maschera*/
        const TCHAR* GetMask();
        /**Rende true se i caratteri della maschera sono esclusi dal filtro*/
        bool Exclude();
        /**Rende true se il carattere � valido*/
        bool IsValid(TCHAR ch);
    };


class DLL_EXPORT Win32TextField:public TextField,public Win32Widget {

        friend class Win32Application;

protected:

        //dimensioni default
        static const int WIDTH=64;
        static const int HEIGHT=24;
        //massima larghezza di default
        static const int MAX_DEFAULT_WIDTH=300;
        static int dec_sep; //separatore decimale
        static Win32InputMask integer_mask;
        static Win32InputMask float_mask;
        //usate per la verifica dell'input
        static bool ParseInt(const TCHAR* text,TCHAR next_char,bool is_signed);
        static bool ParseFloat(const TCHAR* text,TCHAR next_char);
        //subclassing della wndproc del text field (usata per gestire maschere e max length)
        static LRESULT CALLBACK TextFieldProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        //memorizza la wnd proc originale
        static WNDPROC oldwndproc;

        const InputMask* input_mask;
        int max_length;
        int type;
        int style;
        void init(int max_length,TEXT_FIELD_TYPE type,BORDER_TYPE b);
        void Create(HWND dest);
        Win32TextField();
        Win32TextField(int max_length);
        Win32TextField(int max_length,TEXT_FIELD_TYPE type,BORDER_TYPE b);
        Win32TextField(int max_length,int nlines,int width,TEXT_FIELD_TYPE type,bool hscroll,bool vscroll,BORDER_TYPE b);


public:

        //interfaccia Widget
        virtual Container* GetParent();
        virtual void SetForeground(COLOR c);
        virtual COLOR GetForeground();
        virtual void SetBackground(COLOR c);
        virtual COLOR GetBackground();
        virtual void Resize(int w,int h);
        virtual void Move(int x,int y);
        virtual int GetWidth();
        virtual int GetHeight();
        virtual int GetLeft();
        virtual int GetTop();
        virtual int SetWidth(int w);
        virtual int SetHeight(int h);
        virtual int SetLeft(int x);
        virtual int SetTop(int y);
        virtual void SetZOrder(ZORDER_POS pos);
        virtual void SetZOrder(Widget* ins_after);
        virtual void SetEnabled(bool enabled);
        virtual bool IsEnabled();
        virtual void SetVisible(bool visible);
        virtual bool IsVisible();
        virtual void ResizeToDefault();
        virtual const TCHAR* GetText();
        virtual void SetText(const TCHAR* text);
        //interfaccia text field
        virtual void SetMaxLength(int len);
        virtual int GetMaxLength();
        virtual void SetMask(const InputMask* mask);
        virtual const InputMask* GetMask();
        virtual void SetAction(const TCHAR* action);
        virtual const TCHAR* GetAction();
        virtual void SetFont(Font* font);
        virtual Font* GetFont();
        virtual void AddActionEvent(ActionEvent* e);
        virtual bool RemoveActionEvent(ActionEvent* e);
        virtual void AddMouseEvents(MouseEvents* e);
        virtual void RemoveMouseEvents(MouseEvents* e);
        virtual void AddMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddMouseRolloverEvents(MouseRolloverEvents* e);
        virtual void RemoveMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddFocusEvents(FocusEvents* e);
        virtual void RemoveFocusEvents(FocusEvents* e);
        virtual void AddKeyEvents(KeyEvents* e);
        virtual void RemoveKeyEvents(KeyEvents* e);
        //virtual void SetBorder(Border* border);
        virtual BORDER_TYPE GetBorder();
    };

    /**classe base toggle button*/
class DLL_EXPORT Win32ToggleButton:public Win32Widget {
protected:

        bool is_selected;
        void init(const TCHAR* text,bool selected);

public:

        //interfaccia ToggleButton
        void SetSelected(bool selected);
        bool IsSelected();
    };

    /**check box*/
class DLL_EXPORT Win32CheckBox:public CheckBox,public Win32ToggleButton {

        friend class Win32Application;

protected:

        void Create(HWND dest);
        Win32CheckBox(const TCHAR* text,bool selected);
        Win32CheckBox(const TCHAR* text);

public:
        //interfaccia Widget
        Container* GetParent();
        virtual void SetForeground(COLOR c);
        virtual COLOR GetForeground();
        virtual void SetBackground(COLOR c);
        virtual COLOR GetBackground();
        virtual void Resize(int w,int h);
        virtual void Move(int x,int y);
        virtual int GetWidth();
        virtual int GetHeight();
        virtual int GetLeft();
        virtual int GetTop();
        virtual int SetWidth(int w);
        virtual int SetHeight(int h);
        virtual int SetLeft(int x);
        virtual int SetTop(int y);
        virtual void SetZOrder(ZORDER_POS pos);
        virtual void SetZOrder(Widget* ins_after);
        virtual void SetEnabled(bool enabled);
        virtual bool IsEnabled();
        virtual void SetVisible(bool visible);
        virtual bool IsVisible();
        virtual void ResizeToDefault();
        virtual const TCHAR* GetText();
        virtual void SetText(const TCHAR* text);
        virtual void SetAction(const TCHAR* action);
        virtual const TCHAR* GetAction();
        /**Imposta il font corrente per la finestra*/
        virtual void SetFont(Font* font);
        /**Ottiene il font corrente*/
        virtual Font* GetFont();
        virtual void AddActionEvent(ActionEvent* e);
        virtual bool RemoveActionEvent(ActionEvent* e);
        virtual void AddMouseEvents(MouseEvents* e);
        virtual void AddMouseRolloverEvents(MouseRolloverEvents* e);
        virtual void RemoveMouseEvents(MouseEvents* e);
        virtual void AddMouseMoveEvents(MouseMoveEvents* e);
        virtual void RemoveMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddFocusEvents(FocusEvents* e);
        virtual void RemoveFocusEvents(FocusEvents* e);
        virtual void AddKeyEvents(KeyEvents* e);
        virtual void RemoveKeyEvents(KeyEvents* e);

        //virtual void SetBorder(Border* border);
        virtual BORDER_TYPE GetBorder();
        //interfaccia ToggleButton
        virtual void SetSelected(bool selected);
        virtual bool IsSelected();
    };

class DLL_EXPORT Win32RadioButton:public RadioButton,public Win32ToggleButton {
        friend class Win32Application;
protected:

        void Create(HWND dest);
        Win32RadioButton(const TCHAR* text,bool selected);
        Win32RadioButton(const TCHAR* text);

public:
        //interfaccia Widget
        virtual Container* GetParent();
        virtual void SetForeground(COLOR c);
        virtual COLOR GetForeground();
        virtual void SetBackground(COLOR c);
        virtual COLOR GetBackground();
        virtual void Resize(int w,int h);
        virtual void Move(int x,int y);
        virtual int GetWidth();
        virtual int GetHeight();
        virtual int GetLeft();
        virtual int GetTop();
        virtual int SetWidth(int w);
        virtual int SetHeight(int h);
        virtual int SetLeft(int x);
        virtual int SetTop(int y);
        virtual void SetZOrder(ZORDER_POS pos);
        virtual void SetZOrder(Widget* ins_after);
        virtual void SetEnabled(bool enabled);
        virtual bool IsEnabled();
        virtual void SetVisible(bool visible);
        virtual bool IsVisible();
        virtual void ResizeToDefault();
        virtual const TCHAR* GetText();
        virtual void SetText(const TCHAR* text);
        virtual void SetAction(const TCHAR* action);
        virtual const TCHAR* GetAction();
        /**Imposta il font corrente per la finestra*/
        virtual void SetFont(Font* font);
        /**Ottiene il font corrente*/
        virtual Font* GetFont();
        virtual void AddActionEvent(ActionEvent* e);
        virtual bool RemoveActionEvent(ActionEvent* e);
        virtual void AddMouseEvents(MouseEvents* e);
        virtual void RemoveMouseEvents(MouseEvents* e);
        virtual void AddMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddMouseRolloverEvents(MouseRolloverEvents* e);
        virtual void RemoveMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddFocusEvents(FocusEvents* e);
        virtual void RemoveFocusEvents(FocusEvents* e);
        virtual void AddKeyEvents(KeyEvents* e);
        virtual void RemoveKeyEvents(KeyEvents* e);
        // virtual void SetBorder(Border* border);
        virtual BORDER_TYPE GetBorder();
        //interfaccia ToggleButton
        virtual void SetSelected(bool selected);
        virtual bool IsSelected();
    };

class Win32ComboBox:public ComboBox,public Win32Widget {

        friend class Win32Application;

protected:

        static const int init_w=128;
        static const int init_h=32;
        void Create(HWND dest);
        bool sorted;
        int selected_index;
        COMBOBOX_STYLE style;
        Win32ComboBox(const TCHAR* text[],int size,COMBOBOX_STYLE style,bool sorted);
        std::vector<const TCHAR*> elements;
        std::list<ComboBoxEvents*>* combo_events;
        void Refresh();
        /**gestisce messaggi di notifica speciali per il combo box*/
        virtual LRESULT HandleWin32Msg(HWND hwnd_parent,UINT message,WPARAM wParam,LPARAM lParam,bool* handled);

public:

        static UINT AddString(const HWND,const ustring&);

        static HWND CreateCombobox(const HWND hParent,const HINSTANCE hInst,DWORD dwStyle,const RECT& rc,const int id,const ustring& caption);

        //interfaccia Widget
        virtual ~Win32ComboBox();
        virtual Container* GetParent();
        virtual void SetForeground(COLOR c);
        virtual COLOR GetForeground();
        virtual void SetBackground(COLOR c);
        virtual COLOR GetBackground();
        virtual void Resize(int w,int h);
        virtual void Move(int x,int y);
        virtual int GetWidth();
        virtual int GetHeight();
        virtual int GetLeft();
        virtual int GetTop();
        virtual int SetWidth(int w);
        virtual int SetHeight(int h);
        virtual int SetLeft(int x);
        virtual int SetTop(int y);
        virtual void SetZOrder(ZORDER_POS pos);
        virtual void SetZOrder(Widget* ins_after);
        virtual void SetEnabled(bool enabled);
        virtual bool IsEnabled();
        virtual void SetVisible(bool visible);
        virtual bool IsVisible();
        virtual void ResizeToDefault();
        virtual const TCHAR* GetText();
        virtual void SetText(const TCHAR* text);
        virtual void SetAction(const TCHAR* action);
        virtual const TCHAR* GetAction();
        virtual void SetFont(Font* font);
        virtual Font* GetFont();
        virtual void AddActionEvent(ActionEvent* e);
        virtual bool RemoveActionEvent(ActionEvent* e);
        virtual void AddMouseEvents(MouseEvents* e);
        virtual void AddMouseRolloverEvents(MouseRolloverEvents* e);
        virtual void RemoveMouseEvents(MouseEvents* e);
        virtual void AddMouseMoveEvents(MouseMoveEvents* e);
        virtual void RemoveMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddFocusEvents(FocusEvents* e);
        virtual void RemoveFocusEvents(FocusEvents* e);
        virtual void AddKeyEvents(KeyEvents* e);
        virtual void RemoveKeyEvents(KeyEvents* e);
        //virtual void SetBorder(Border* border);
        virtual BORDER_TYPE GetBorder();
        //interfaccia List
        virtual int AddElement(const TCHAR* text);
        virtual const TCHAR* GetElement(int index);
        virtual void RemoveElement(int index);
        virtual int GetSelectedIndex();
        virtual void SetSelectedIndex(int index);
        virtual void SetElementData(int data,int index);
        virtual int GetElementData(int index);
        virtual int GetSize();
        virtual void Clear();
        //-----------------------
        virtual COMBOBOX_STYLE GetStyle();
        virtual bool IsSorted();
        virtual void ShowDropDownList();
        virtual void HideDropDownList();
        virtual void AddComboBoxEvents(ComboBoxEvents* evt);

    };

class Win32List:public List,public Win32Widget {

        friend class Win32Application;


protected:

        static const int init_w=64;
        static const int init_h=32;
        void Create(HWND dest);
        bool sorted;
        LIST_SELECTION_MODE selmode;
        Win32List(const TCHAR* text[],int size,LIST_SELECTION_MODE sel_mode,bool sorted,BORDER_TYPE b);
        ~Win32List();
        std::vector<const TCHAR*> elements;
        void Refresh();

public:
        //interfaccia Widget
        virtual Container* GetParent();
        virtual void SetForeground(COLOR c);
        virtual COLOR GetForeground();
        virtual void SetBackground(COLOR c);
        virtual COLOR GetBackground();
        virtual void Resize(int w,int h);
        virtual void Move(int x,int y);
        virtual int GetWidth();
        virtual int GetHeight();
        virtual int GetLeft();
        virtual int GetTop();
        virtual int SetWidth(int w);
        virtual int SetHeight(int h);
        virtual int SetLeft(int x);
        virtual int SetTop(int y);
        virtual void SetZOrder(ZORDER_POS pos);
        virtual void SetZOrder(Widget* ins_after);
        virtual void SetEnabled(bool enabled);
        virtual bool IsEnabled();
        virtual void SetVisible(bool visible);
        virtual bool IsVisible();
        virtual void ResizeToDefault();
        virtual const TCHAR* GetText();
        virtual void SetText(const TCHAR* text);
        virtual void SetAction(const TCHAR* action);
        virtual const TCHAR* GetAction();
        virtual void SetFont(Font* font);
        virtual Font* GetFont();
        virtual void AddActionEvent(ActionEvent* e);
        virtual bool RemoveActionEvent(ActionEvent* e);
        virtual void AddMouseEvents(MouseEvents* e);
        virtual void AddMouseRolloverEvents(MouseRolloverEvents* e);
        virtual void RemoveMouseEvents(MouseEvents* e);
        virtual void AddMouseMoveEvents(MouseMoveEvents* e);
        virtual void RemoveMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddFocusEvents(FocusEvents* e);
        virtual void RemoveFocusEvents(FocusEvents* e);
        virtual void AddKeyEvents(KeyEvents* e);
        virtual void RemoveKeyEvents(KeyEvents* e);
        // virtual void SetBorder(Border* border);
        virtual BORDER_TYPE GetBorder();
        //interfaccia List
        virtual int AddElement(const TCHAR* text);
        virtual const TCHAR* GetElement(int index);
        virtual void RemoveElement(int index);
        virtual int GetSelectedIndex();
        virtual void SetSelectedIndex(int index);
        virtual void SetElementData(int data,int index);
        virtual int GetElementData(int index);
        virtual LIST_SELECTION_MODE GetSelectionMode();
        virtual int GetSize();
        virtual void Clear();
        virtual bool IsSorted();
    };

class Win32ScrollBar:public ScrollBar,public Win32Widget {
        friend class Win32Application;

protected:

        Win32ScrollBar(SCROLL_BAR_TYPE type,int min_val,int max_val);
        void Create(HWND dest);
        int maximum,minimum,value,block_increment,unit_increment;
        SCROLL_BAR_TYPE type;

public:
        //interfaccia scrollbar
        /**Restituisce il valore massimo del range*/
        virtual int GetMaximum();
        /**Restituisce il valore minimo*/
        virtual int GetMinimum();
        /**Imposta il valore massimo del range*/
        virtual int SetMaximum(int val);
        /**Imposta il valore minimo*/
        virtual int SetMinimum(int val);
        /**Restituisce il valore corrente*/
        virtual int GetValue();
        /**Imposta il valore corrente*/
        virtual int SetValue(int value);
        /**Imposta il valore di incremento per spostamento pagina*/
        virtual int SetBlockIncrement(int value);
        /**Imposta il valore di incremento unitario*/
        virtual int SetUnitIncrement(int value);
        /**Restituisce l'incremento per spostamento pagina*/
        virtual int GetBlockIncrement();
        /**Restituisce l'incremento unitario*/
        virtual int GetUnitIncrement();
        //interfaccia Widget
        virtual Container* GetParent();
        virtual void SetForeground(COLOR c);
        virtual COLOR GetForeground();
        virtual void SetBackground(COLOR c);
        virtual COLOR GetBackground();
        virtual void Resize(int w,int h);
        virtual void Move(int x,int y);
        virtual int GetWidth();
        virtual int GetHeight();
        virtual int GetLeft();
        virtual int GetTop();
        virtual int SetWidth(int w);
        virtual int SetHeight(int h);
        virtual int SetLeft(int x);
        virtual int SetTop(int y);
        virtual void SetZOrder(ZORDER_POS pos);
        virtual void SetZOrder(Widget* ins_after);
        virtual void SetEnabled(bool enabled);
        virtual bool IsEnabled();
        virtual void SetVisible(bool visible);
        virtual bool IsVisible();
        virtual void ResizeToDefault();
        virtual const TCHAR* GetText();
        virtual void SetText(const TCHAR* text);
        virtual void SetAction(const TCHAR* action);
        virtual const TCHAR* GetAction();
        virtual void SetFont(Font* font);
        virtual Font* GetFont();
        virtual void AddActionEvent(ActionEvent* e);
        virtual bool RemoveActionEvent(ActionEvent* e);
        virtual void AddMouseEvents(MouseEvents* e);
        virtual void RemoveMouseEvents(MouseEvents* e);
        virtual void AddMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddMouseRolloverEvents(MouseRolloverEvents* e);
        virtual void RemoveMouseMoveEvents(MouseMoveEvents* e);
        virtual void AddFocusEvents(FocusEvents* e);
        virtual void RemoveFocusEvents(FocusEvents* e);
        virtual void AddKeyEvents(KeyEvents* e);
        virtual void RemoveKeyEvents(KeyEvents* e);
        // virtual void SetBorder(Border* border);
        virtual BORDER_TYPE GetBorder();
        /**gestione personalizzata messaggi scrollbar*/
        virtual LRESULT HandleWin32Msg(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam,bool* handled);

    };
//fine namespace
}
;

#endif // LWTKWIN32_H_INCLUDED
