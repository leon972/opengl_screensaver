/********************************
 Utilità usate per la localizzazione dei formati numerici
Code by L.Berti 2009
 *********************************/

#ifndef LOCALEDEF_H_INCLUDED
#define LOCALEDEF_H_INCLUDED

#include <tchar.h>

#ifndef TEXT
#ifdef UNICODE
/*
 * __TEXT is a private macro whose specific use is to force the expansion of a
 * macro passed as an argument to the macro TEXT.  DO NOT use this
 * macro within your programs.  It's name and function could change without
 * notice.
 */
#define __TEXT(q) L##q
#else
#define __TEXT(q) q
#endif
/*
 * UNICODE a constant string when UNICODE is defined, else returns the string
 * unmodified.
 * The corresponding macros  _TEXT() and _T() for mapping _UNICODE strings
 * passed to C runtime functions are defined in mingw/tchar.h
 */
#define TEXT(q) __TEXT(q)
#endif

namespace util {

    /**
     *Locale non valido o non definito
     */
    class LocaleNotFoundException {
    };

    /**
     *Definisce il separatore decimale e quello per le migliaia e altri simboli
     *in base alla localizzazione
     */
    class Locale {
    private:

        /**
         *
         * dec_point separatore decimale
         * th_sep simbolo separatore delle migliaia
         * currency_symbol simbolo della valuta
         * currency_dec_sep separatore decimale nelle valute
         * country nazione
         * language lingua
         * dt_fmt formato data
         */
        const TCHAR *dec_point, *th_sep, *currency_symbol, *currency_dec_sep, *country, *language;
        int dt_fmt;

    public:

        Locale(const TCHAR* dec_point,
                const TCHAR* th_sep,
                const TCHAR* currency_symbol,
                const TCHAR* currency_dec_sep,
                const TCHAR* country,
                const TCHAR* language,
                int dt_fmt);

        Locale();


        //id formato data
        static const int DT_M_D_Y = 0; //mese giorno anno
        static const int DT_D_M_Y = 1; //giorno mese anno
        static const int DT_Y_M_D = 2; //anno mese giorno

        //costanti utili dei paesi
        static const int US = 0x2;
        static const int UK = 0x3;
        static const int ITALY = 0x4;
        static const int FRANCE = 0x5;
        static const int GERMANY = 0x6;
        static const int CHINA = 0x7;
        static const int JAPAN = 0x8;
        static const int CANADA = 0x9;
        static const int CANADA_FRENCH = 0xA;
        static const int KOREA = 0xB;
        static const int TAIWAN = 0xC;
        //costanti utili delle lingue
        static const int ENGLISH = 0x101;
        static const int FRENCH = 0x102;
        static const int ITALIAN = 0x103;
        static const int GERMAN = 0x104;
        static const int CHINESE = 0x105;
        static const int JAPANESE = 0x106;

        //acquisisce un locale in base ad una delle costanti
        //� usata per costruire uno dei locale di default (sono presenti le costanti di quelli piu' usati)
        static Locale GetLocale(int country) throw (LocaleNotFoundException);

        /**carattere usato come separatore decimale*/
        const TCHAR* GetDecimalPoint() const;
        /**carattere usato come separatore delle migliaia*/
        const TCHAR* GetThousandsSep() const;
        /**carattere usato come simbolo della valuta*/
        const TCHAR* GetCurrencySymbol() const;
        /**carattere usato come punto decimale nella valuta*/
        const TCHAR* GetCurrencyDecSep() const;
        /**Restituisce l'id del paese (ISO 3166 2-letter code)*/
        const TCHAR* GetCountry() const;
        /**Restituisce la lingua (ISO 639 code)*/
        const TCHAR* GetLanguage() const;
        /**Restituisce il formato data*/
        int GetDateFormatType() const;

    };
};

#endif // LOCALE_H_INCLUDED
