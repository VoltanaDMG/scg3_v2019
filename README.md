<p align="center">
  <a href="https://vahlers.github.io/scg3">
    <img
      alt="scg3"
      src="scg3/doc/hsh-logo-2013-small.png"
      width="auto"
    />
  </a>
</p>

An extensible OpenGL 3 / C++11 scene graph library for teaching computer graphics along the programmable pipeline.
**This project is bound by a [Code of Conduct][].**

_(C) 2014-2019 Volker Ahlers_

<br>

## Table of Contents

* [Prerequisites](#prerequisites)<br>
* [Environment set up](#environment-set-up)<br>
* [Building scg3](#building-scg3)
  * [Projects](#projects)
  * [Building using CMake on Linux](#building-using-cmake-on-linux)
  * [Building using Visual Studio on Windows](#building-using-visual-studio-on-windows)
* [Release types](#release-types)

<br>

## __Prerequisites__

Before we can set up our development environment, the following software must be downloaded and installed.

```
* C++11 compiler, e.g., GCC 4.6, LLVM/Clang 3.1, Visual C++ 11.0/Visual Studio 2012 (or higher)
* OpenGL 3.2 graphics driver (or higher)
* GLFW 3.2.0 (or higher), cf. http://www.glfw.org/
```

<br>

## __Environment set up__

You can check the Git repository at https://github.com/vahlers/scg3 up. Before you can use the `scg3` library, you need to compile it yourself. Just execute the following command in a folder of your choice.

```bash
$ git clone https://github.com/vahlers/scg3.git
```

<br>

## __Building scg3__

To compile `scg3` or `scg3_v2019` use Eclipse or Visual Studio, cf. documentation in [scg3/scg3.h](https://github.com/vahlers/scg3/blob/master/scg3/scg3.h). In our development team we are working with Visual Studio 2019 to allow parallelized compiles of the library.

#### Projects:

* `scg3`: scene graph library (static library)
* `scg3_example`: example application

#### Building using CMake on Linux

This project contains CMake files to build the project from the command line or import it into IDEs like CLion. (Only tested on Linux)

After navigating to the root directory of the project, you can build the library and example code using these commands:

```bash
$ mkdir build
$ cd build
$ cmake -DCMAKE_INSTALL_PREFIX=../build-output ..
$ make install -j8   # replace 8 with CPU core count
```

In case you want to install the `scg3` library globally into your system, use `cmake -DCMAKE_INSTALL_PREFIX=/usr ..` and `sudo make install -jX` instead.
Uninstallation can be done using `sudo make uninstall`.

#### Building using Visual Studio on Windows

This project contains Visual Studio project files to build the project from the command line with `msbuild` or import it into IDEs like Visual Studio.

To build this library successfully the Windows 10 SDK and at least the MSBuild Tools (or Visual Studio) need to be installed. This project also requires the library GLFW3 and its header files.

<br>

## Release Types

* **Current**: Under active development. Code for the Current release is in the
  branch for its major version number (for example,
  [v2019.x](https://github.com/VoltanaDMG/scg3_v2019/tree/v2019.x)). Node.js releases a new
  major version every 6 months, allowing for breaking changes. This happens in
  April and October every year. Releases appearing each October have a support
  life of 8 months. Releases appearing each April convert to LTS (see below)
  each October.
* **LTS**: Releases that receive Long-term Support, with a focus on stability
  and security. Every even-numbered major version will become an LTS release.
  LTS releases receive 18 months of _Active LTS_ support and a further 12 months
  of _Maintenance_. LTS release lines have alphabetically-ordered codenames,
  beginning with `v2019.x-alpha`. There are no breaking changes or feature additions,
  except in some special circumstances.
* **Nightly**: Code from the Current branch built every 24-hours when there are
  changes. Use with caution.

Current, LTS and Nightly releases follow the syntax `v[YYYY].[Version Nr]-[Channel/Type].(Patch Nr)`


[Code of Conduct]: https://github.com/VoltanaDMG/scg3_v2019/blob/master/CODE_OF_CONDUCT.md
