/**************************************************************
Analizzatore lessicale e sintattico e interprete
di espressioni matematiche.
Code by Leonardo Berti (c) 2009

****************************************************************/

#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <list>

/**grammar:
(grammatica usata dal parser di espressioni)

program:
  END
  expr_list END
expr_list:
  expression PRINT
  expression PRINT expr_list
expression:
  expression SUM term
  expression SUB term
  term
term:
  term DIV primary
  term MUL primary
  primary
primary:
  NUMBER
  VAR_NAME
  VAR_NAME=expression
  string
  function
  -primary
  (expression)
function:
  FUNCTION_NAME(arg_list)
arg_list:
  expression
  expression COMMA arg_list
  string
  string COMMA arg_list
string:
  QUOT char_seq QUOT
  QUOT QUOT
char_seq:
  char
  char char_seq

PRINT=;
SUM=+
SUB=-
MUL=*
DIV=/
COMMA=,
NUMBER=floating point number ('.'=decimal point)
VAR_NAME=nome variabile (stringa)
FUNCTION_NAME=nome funzione (stringa)
QUOT="

END=end of input

*/

using namespace std;

namespace calculator {

    class OutputStream;
    class Calculator;
    class UserInput;

    //tipi di funzioni gestititi dalll'interprete:

    /**
     *Funzione matematica con 1 solo argomento
     */
    typedef double (*SINGLE_ARG_FUNC)(double);

    /**
     *Funzione matematica con 2 argomenti
     */
    typedef double (*DOUBLE_ARG_FUNC) (double,double);

    /**
     *Funzione con argomento stringa, l'output viene inviato su out
     */
    typedef string (*STR_FUNC)(const string&,const OutputStream* out);

    /**
     *Funzione con argomento double e risultato stringa
     */
    typedef string (*VAL_FUNC)(double v);

    /**
     *Comando (funzione senza argomenti che non restituisce risultati
     */
    typedef void (*CMD_FUNC) (const OutputStream* out,Calculator& c);

    /**
     * Token usati dal parser di espressioni
     */
    enum Token {

        NAME,
        NUMBER,
        END,
        PLUS='+',
        MINUS='-',
        MUL='*',
        DIV='/',
        END_OF_STATEMENT=';',    //fine statement
        ASSIGN='=',
        LP='(',
        RP=')',
        FUNCTION_NAME,          //nome di una funzione (funzione built-in es. cos e sin o funzione definita dall'utente)
        COMMA=',',
        QUOT='"',

    };

    /**
     *Simbolo composto da un token e relativo valore
     * (il valore puo' essere stringa o numerico)
     */
    struct Symbol
    {
        Token token;
        double number_value;
        string string_value;
    };

    //eccezioni generate dal parser:

    /**
     * Fine dell'input
     * @param message
     * @return
     */
    class EndOfInput {};

    /**
     * Divisione per zero
     * @param message
     * @return
     */
    class DivideByZeroException {};

    /**
     *Simbolo non definito
     */
    class SymbolNotFound {};

    /**
     * Eccezione generata quando viene trovato un nome di variabile
     * o di funzione che coincide con un nome riservato
     * @return
     */
    class ReservedNameException {};

    /**
     * Ecezione generata dal parser in seguito ad un errore di sintassi nell'espresione
     */
    class ParseException
    {
        private:

        string msg;

        public:

        ParseException(string s)
        {
            msg=s;
        }

        string GetErrorMessage()
        {
            return msg;
        }
    };

    /**Interfaccia acquisizione input utente
     è usata per la funzione speciale denominata "input" che chiede all'utente di inserire un numero
     */
    class UserInput
    {
        public:
        virtual double GetDouble(const string& message) const=0;
    };

    /**Interfaccia per l'acquisizione dell'input (flusso di caratteri che contiene il programma)*/
    class InputStream {
public:
        virtual ~InputStream() {
        }
        virtual char GetNextChar() throw (EndOfInput)=0;
        virtual void PutBack()=0;
    };

    /**Stream di output del risultato di elaborazione di un programma*/
    class OutputStream
    {
        public:

        virtual ~OutputStream() {
        }

        virtual void print(const string& s) const=0;
        virtual void println(const string& s) const=0;
    };

    /**Implementazione dell'input stream basato su cin*/
    class StringInputStream:public InputStream
    {
        private:

        string program;
        int cur_pos;
        int llen;

        public:

        StringInputStream(const string& str_prog);
        virtual char GetNextChar() throw (EndOfInput);
        virtual void PutBack();
    };

    /**Implementazione dell'input utente da console*/
    class ConsoleUserInput:public UserInput
    {
        public:
        virtual double GetDouble(const string& message) const;
    };

    /**Implementazione dell'output stream basato su cout*/
    class StdOutput:public OutputStream
    {
        public:

        void print(const string& s) const
        {
            cout<<s;
        };

        void println(const string& s) const
        {
            cout<<s<<endl;
        };
    };

    /**
     *Interprete di espressioni
     *Il calcolatore riceve in input un programma che è costituito da una serie di "statement"
     *separate da ; lo elabora e invia il risultato sullo stream di output.
     *Per eseguire un programma utilizzare il metodo Run fornendo l'input, l'output e l'interfaccia
     * necessaria ad acquisire l'input da parte dell'utente durante l'esecuzione.
     *Per valutare una singola espressione matematica utilizzare il metodo Evaluate.
     *Per settare delle costanti da poter usare nelle espressioni matematiche usare il
     * metodo SetVar.Per settare delle funzioni definite dall'utente usare SetFunction
     */
    class Calculator {

protected:

        //variabili
        map<string,double> vars;
        //ultima variabile settata
        double* last_var;

        //funzioni di una sola variabile
        map<string,SINGLE_ARG_FUNC> sing_var_functions;
        //funzioni di due variabili
        map<string,DOUBLE_ARG_FUNC> double_var_functions;
        //funzioni con argomento stringa e risultato stringa
        map<string,STR_FUNC> str_str_functions;
        //funzioni con argomento double e risultato stringa
        map<string,VAL_FUNC> val_functions;
        //comandi (funzioni senza argomenti)
        map<string,CMD_FUNC> cmd_functions;
        //nomi di simboli riservati
        vector<string> reserved_words;
        //char stream di input del codice da eseguire
        InputStream* input_stream;
        //output stream (risultati del programma)
        OutputStream* output_stream;
        //user input (input di dati a run time da parte dell'utente)
        UserInput* user_input;
        Symbol cur_sym;

        /**
         * Acquisisce il token successivo
         * (metodo usato internamente dal parser di espressioni)
         * @param next_token
         * @return
         */
        void GetToken() throw (ParseException);

        /**
         * Acquisisce una espressione primaria (primary)
         * esempio:un numero,un nome di variabile,una espressione
         * (metodo usato internamente dal parser di espressioni)
         */
        double GetPrimary(bool next_token) throw (ParseException);

        /**
         * Acquisisce un termine (di una espressione tipo term+/-term
         * (metodo usato internamente dal parser di espressioni)
         * @param f
         * @return 
         */
        double GetTerm(bool next_token) throw (ParseException,DivideByZeroException);

        /**
         * Valuta una espressione numerica e ne restituisce il valore
         * (metodo usato internamente dal parser di espressioni)
         * @return risultato dell'espressione
         */
        double EvalExpr(bool next_token) throw (ParseException,DivideByZeroException);
        
        /**
         * Valuta una funzione con un solo argomento numerico
         * @param f
         * @return
         */
        double EvalFunc(SINGLE_ARG_FUNC f) throw (ParseException,DivideByZeroException);
        
        /**
         * Valuta una funzione con due argomenti numerici
         * @param f
         * @return
         */
        double EvalFunc(DOUBLE_ARG_FUNC f) throw (ParseException,DivideByZeroException);

        /**
         * Valuta una funzione con argomento stringa
         * @return
         */
        double EvalFunc(STR_FUNC f) throw (ParseException);
        /*
         *Esegue un comando
         */
        void EvalFunc(CMD_FUNC f) throw (ParseException);
        
        /**
         * acquisisce una stringa dallo stream di input
         * @return
         */
        string GetString() throw (ParseException);

        /**
         * inizializza
         */
        void Init();

        /**
         * controlla se il simbolo è una parola riservata
         */
        void CheckSymbol(const string& name) throw (ReservedNameException);

        /**
         * acquisizione dell'input da parte dell'utente
         */
        double GetUserInput() throw (ParseException);

        /**
         * funzioni usata internamente per l'output
         */
        static string print(const string& e,const OutputStream* out);
        /**
         * funzioni usata internamente per l'output         *
         */
        static string println(const string& e,const OutputStream* out);

        /**built in functions*/
        /**
         * funzioni polinomiali
         */
        static double p2(double x); //x*x (l'argomento x viene elevato alla seconda potenza) seconda
        static double p3(double x); //x*x*x (..... terza potenza)
        static double p4(double x);
        static double p5(double x);
        static double p6(double x);
        static double p7(double x);
        static double p8(double x);
        static double p9(double x);
        static double p10(double x);

        /**
         * Valore assoluto
         * @param var_name
         */
        static double abs(double x);

        /**
         * funzione segno
         * @return segno 1 se x>0 -1 se x<0 0 se x=0
        *
        *
        */
        static double sgn(double x); 

        /**
         * Esegue il dump delle variabili e costanti
         * (visualizza sullo stream di output out lo stato interno dell'interprete
         */
        static void dump(const OutputStream* out,Calculator& c);

public:

        /**
         * Crea una istanza dell'interprete di espressioni
         * @param f_name
         */
        Calculator();
        virtual ~Calculator();
        /**
         * Imposta il valore di una variabile definita dall'utente
         * @param var_name nome della varibili
         * @param value valore
         * @throw ReservedNameException se il nome var_name è un nome riservato
         */
        double SetVar(const string& var_name,double value) throw (ReservedNameException);
        /**
         * Imposta l'ultima variabile settata (metodo veloce)
         * @param value valore
         */
        double SetLastVar(double value);
        /**
         * Acquisisce il valore di una variabile
         * @param var_name nome della variabile
         * @throw SymbolNotFound se il nome della varibile non è definito
         */
        double GetVar(const string& var_name) throw (SymbolNotFound);
        
        /**
         * Rimuove una variabile
         * @throw SymbolNotFound se il nome della varibile non è definito
         * @throw ReservedNameException se il nome è riservato
         *
         */
        void RemoveVar(const string& var_name) throw (SymbolNotFound,ReservedNameException);

        /**
         * Aggiunge una funzione definita dall'utente
         * @param name nome della funzione usata dal parser di espressioni
         * @param f puntatore alla funzione matematica con singolo argomento
         * @throw SymbolNotFound se il nome non è definito
         * @throw ReservedNameException se il nome è riservato
         */
        void SetFunction(const string& f_name,SINGLE_ARG_FUNC f) throw (ReservedNameException);
        
        /**
         * Rimuove una funzione
         * @throw SymbolNotFound se il nome non è definito
         * @throw ReservedNameException se il nome è riservato
         */
        void RemoveFunction(const string& f_name) throw (ReservedNameException,SymbolNotFound);

        /**
         * Aggiunge una funzione definita dall'utente con argomento stringa
         * @throw ReservedNameException se il nome è riservato
         */
        void SetFunction(const string& f_name,STR_FUNC f) throw (ReservedNameException);

        /**
         *Rimuove una funzione stringa
         * @throw SymbolNotFound se il nome non è definito
         * @throw ReservedNameException se il nome è riservato                     
         */
        void RemoveStrFunction(const string& f_name) throw (ReservedNameException,SymbolNotFound);
        
        /**
         * Imposta lo stream di output
         * @param o stream di output del programma
         */
        void SetOutput(OutputStream* o);

        /**
         * Valuta direttamente una espressione matematica e restituisce il risultato
         * @param expr espressione matematica che può fare riferimento a varibili e/o funzioni
         * definite dall'utente e built in
         * esempio: "cos(x)+(exp(x*x)/8.5)"
         */
        double Evaluate(const string& expr) throw (ParseException,DivideByZeroException);

        /**
         * Esegue un programma (sequenza di espressioni matematiche separate da ;)
         * Il risultato del programma viene ottenuto interrogando la tabella delle variabili
         * L'eventuale output del programma viene inviato sullo stream di output ostr
         * @param istr input stream dal quale viene letto il programma
         * @param uinput interfaccia da usare per acquisire l'input da parte dell'utente (se viene usata la funzione innput nel programma)
         * @param trace se settato esegue il tracing dell'elaborazione
         */
        void Run(InputStream* istr,OutputStream* ostr,UserInput* uinput,bool trace) throw (ParseException,DivideByZeroException);

        /**
         * Ottiene la lista di tutte le variabili definite
         */
        void ListVars(map<string,double>& mvar_list);

        /**
         * Ottiene la lista delle funzioni con singolo parametro
         */
        void ListSingleArgFunctions(list<string>& func_list);

        /**
         * Ottiene la lista della funzioni con due parametri
         */
        void ListDoubleArgFunctions(list<string>& funct_list);

        /**
         * Ottiene la lista dei comandi
         */
        void ListCmdFunctions(list<string>& funct_list);
   };
};

#endif // CALCULATOR_H_INCLUDED
