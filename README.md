********************************************************************

Parametric surfaces Screen Saver
Copyright (c) 2010 by Leonardo Berti
leonardo.berti@tin.it

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

contact: leonardo.berti@tin.it  

*********************************************************************
INSTALLAZIONE
*********************************************************************

Questo screen saver richiede il sistema operativo Windows
con la libreria OpenGL preinstallata sul sistema.

Utilizzare il pacchetto di installazione nella cartella setup
per installare lo screen saver.
Per attivare lo screen saver fare click con il tasto destro
del mouse sul desktop e selezionare nel tab "screen saver"
parametric_surfaces.Premere il tasto "configura" per 
impostare i parametri di esecuzione.


**********************************************************************
ESEGUIRE LO SCREEN SAVER COME NORMALE APPLICAZIONE
**********************************************************************
Nella cartella test_executable è contenuto lo screen saver compilato
come normale applicazione.Fare doppio click sull'eseguibile per testare
il programma.

**********************************************************************
COMPILARE LO SCREEN SAVER USANDO I SORGENTI
**********************************************************************

Utilizzare il compilatore MinGW ver. 4.5 o successiva.

Se si utilizza NetBeans aprire il progetto selezionando direttamente
la cartella ScreenSaver.

Aggiungere nella sezione linker le seguenti dll che si trovano
nella cartella test_executable

LMath.dll
lwtk.dll
render2d.dll
render3d.dll

Aggiungere le seguenti cartelle nella sezione "include":

sdk/include
src/include

Aggiungere tutti i sorgenti (.cpp) presenti nella cartella src

Per eseguire il debug definire #define APPLICATION_MODE in
ScreenSaverMain.h.
Se si esegue lo screen saver con il parametro APPLICATION_MODE 
non definito causerà l'apertura della finestra di dialogo di configurazione.
















