# Rendering panorama maps in the "atelier Novat" style



This code was writen for the research project "Rendering panorama maps in the "atelier Novat" style. Performed at Inria Grenoble Rhône-Alpes, Maverick Team. Univ.Grenoble Alpes, LJK, INRIA. Under the supervision of : Joelle THOLLOT and Romain VERGNE.

-----------------------------------------
## Installing
To build from source , first clone the repository
```bash
git clone TODO
```



In order to compile the project, the following tools and libraries are required:
* OpenGL 4.5
* C++14-enabled compiler (GCC 5 or Clang 3.4)
* CMake 3.1
* QT 5.6
* Glew
* GLM 0.9
* GLFW3
* pkg-config

```bash
#Install all libraries on debian/Ubuntu
apt-get install qt5-default qt5-qmake qtdeclarative5-dev libglew-dev libglm-dev libglfw3-dev pkg-config

#Configure
mkdir -p build && cd build
cmake ..

#Compile
make
```
-----------------------------------------
## Usage

Read the [controls](documentations/controls.md)
-----------------------------------------
## Documentation
+ Read the [report](documentations/report/Rapport/M2Report_Jonathan_Granier.pdf) (In french)
+ Read the [code abstract]()

Show the complete code documentation :
```bash
firefox documentations/code_documentation/html/index.html
```
-----------------------------------------
## Copyright
Jonathan GRANIER <jonathan.granier@wanadoo.fr>
```
License: MLP
This Source Code Form is subject to the terms of the Mozilla Public License,
v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at https://mozilla.org/MPL/2.0/.
```
