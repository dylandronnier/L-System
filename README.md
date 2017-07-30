# L-System
Print the most famous L-Systems in 2D (Imagine++) and 3D (OpenGL).

## Presentation
L-Systems are mathematical objects introduced by Aristid Lindenmayer in 1968. They can describe the behaviour of plant cells and to model the growth processes of plant development. L-systems are also used to generate fractals. For more information, check out the [Wikipedia page](https://en.wikipedia.org/wiki/L-system).

This project aims to print different L-Systems in 2D and 3D. The two parts are independant.

## 2D


### Installation
First install the [Imagine++ librairies](http://imagine.enpc.fr/~monasse/Imagine++/). Don't forget to set `Imagine_DIR` environment variable. Then you can use cmake and make to install the 2D part of the project:

```sh
$ cd 2D/
$ mkdir build && cd build/
$ cmake .. -DCMAKE_INSTALL_PREFIX=..
$ make
$ make install
```

The two executables are located in 2D/bin/ directory. `cs.out` print a vraiation of L-systems using [context-sensitive grammar](https://en.wikipedia.org/wiki/L-system#Context_sensitive_grammars) and `sto.out`, another variation using [stochastic grammar](https://en.wikipedia.org/wiki/L-system#Stochastic_grammars).

### Examples
![Example 1](/Screenshots/Tree.png)

![Example 2](/Screenshots/Dragon_Curve.png)

## 3D
In 3D, we print only classic L-systems
### Installation
You need to install the following OpenGL libraries: freeGLUT, GLEW, SOIL and GLM. Then you can install the second part of the project.

```sh
$ cd 3D/
$ mkdir build && cd build/
$ cmake .. -DCMAKE_INSTALL_PREFIX=..
$ make
$ make install
```

The lines below should create 5 executables in `3D/bin/`:

* `hilbert.out` prints the 3D Hilbert curve
* `koch.out` prints the Koch snowflake in 3D
* `menger.out` prints the Menger sponge
* `pyramid.out` prints a pyramid fracal
* `sier.out` prints the Sierpinski tetrix
