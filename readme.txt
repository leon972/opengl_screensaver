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
INSTALLATION
*********************************************************************

This is a screen saver for Windows O.S.
It requires OpenGL library installed on your system.

Use the installation package from the setup folder to install the screen saver
on the Windows directory.
To activate this screen saver, right-click on the Windows desktop
and choose parametric_surfaces in the screen savar tab of the 
display settings panel.
Click the configure button to configure the screen saver's parameters.

**********************************************************************
TESTING
**********************************************************************
The folder test_executalbe contains the screen saver compiled
as a normal application.Execute screensaver.exe to test the screen saver

**********************************************************************
How to compile:
**********************************************************************

The sorce code has been compiled with MinGW 4.5.0 under Windows.

You may use netbeans IDE to open the project ssaver.

To compile this code you need to add the reference to:

sdk/lib/LMath.dll
sdk/lib/lwtk.dll
sdk/lib/render2d.dll
sdk/lib/render3d.dll

Add additional include directories:

sdk/include
src/include

Add all cpp sources in src directory.

To debug the program #define APPLICATION_MODE in
ScreenSaverMain.h and undef it in deployment mode.
Running the screen saver with APPLICATION_MODE undefined
will bring up the configuration dialog.
















