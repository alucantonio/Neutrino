<p align="center">
<img src="./Logos/neutrino_logo.png" width="200" height="200" />
</p>

*A fast and light library for GPU-based computation and interactive data visualization.*


Overview
----
[Neutrino](https://www.neutrino.codes) is a C++ library that facilitates writing parallel code running on GPU hardware combining the power of the OpenCL computational framework with the OpenGL graphics language.


Hardware requirements
----
- OpenCL-compatible GPU

For interactive visualization, it is better if the _OpenCL-OpenGL interoperability_ mode is supported. Using the tool  `clinfo` (https://github.com/Oblomov/clinfo) check for the `cl_APPLE_gl_sharing` extension under MacOS, while under Linux or Windows check for the
`cl_khr_gl_sharing` extension.

Software requirements
---

- OpenCL (runtime/loader + headers)
- OpenGL (library + headers)
- Git (https://git-scm.com)
- GLAD (https://glad.dav1d.de/) *
- GLFW (https://www.glfw.org/)
- GMSH ()
- GCC (https://gcc.gnu.org)
- CMake (https://cmake.org)
- Make (https://www.gnu.org/software/make/) **
- VSCode (https://code.visualstudio.com/) **
- GraphViz (https://graphviz.org/)
- Doxygen v1.8.15 (http://www.doxygen.nl/)
- Uncrustify (https://github.com/uncrustify/uncrustify) ***

#### Notes
\* The GLAD loader should be generated from its webpage using the following settings:
- Language = C/C++
- gl = Version 4.6
- Profile = Core

Download the zip file containing the code and extract it in a custom directory.

\** Under **Windows** we provide compilation instructions only for the *VSCode toolchain*, so the VSCode editor is required, while Make is not. Under **Linux/MacOS** we also provide instructions for compilation using the *CMake/Make toolchain*, which requires the installation of the tool Make (VSCode is not needed).

\*** In order to use it, please first install Uncrustify according to your operating system (e.g. use the Linux's package manager, or Homebrew under Mac or use these binaries: https://sourceforge.net/projects/uncrustify/ under Windows), then install the VScode's *Uncrustify extension* (https://marketplace.visualstudio.com/items?itemName=LaurentTreguier.uncrustify)

Installation instructions
----
Neutrino can be installed and used on [Linux](./Installation/installation_linux.md), [Mac](./Installation/installation_mac.md) and [Windows](./Installation/installation_windows.md).

Examples
---
In order to test the installation of Neutrino and to start experimenting with it, please refer to the [Examples](https://github.com/NeutrinoCodes/Examples) repository.

© Alessandro LUCANTONIO, Erik ZORZIN - 2018-2020 - [www.neutrino.codes](https://www.neutrino.codes)
