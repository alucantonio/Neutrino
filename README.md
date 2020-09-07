<p align="center">
<img src="./Logos/neutrino_logo.png" width="200" height="200" />
</p>

*A fast and light library for GPU-based computation and interactive data visualization.*

[www.neutrino.codes](https://www.neutrino.codes)

Overview
----
Neutrino is a C++ library that facilitates writing parallel code running on GPU hardware combining the power of the OpenCL computational framework with the OpenGL graphics language (see https://www.neutrino.codes).



Hardware requirements
----
- OpenCL-compatible GPU.

For interactive visualization, it is better if the _OpenCL-OpenGL interoperability_ mode is supported. Using the tool  `clinfo` (https://github.com/Oblomov/clinfo) check for the `cl_APPLE_gl_sharing` extension under MacOS, while under Linux or Windows check for the
`cl_khr_gl_sharing` extension.

Software requirements
---

- OpenCL (runtime/loader + headers)
- OpenGL (library + headers)
- Git (https://git-scm.com)
- GLAD (https://glad.dav1d.de/) *
- GLFW (https://www.glfw.org/)
- GCC (https://gcc.gnu.org)
- CMake (https://cmake.org)
- Make (**Linux/MacOS only**)
- Visual Studio 2019 (https://visualstudio.microsoft.com/) with "Desktop development
with C++ --> C++ CMake tools for Windows" workload (**Windows only**).
- GraphViz (https://graphviz.org/) **
- Doxygen v1.8.15 (http://www.doxygen.nl/) **

Under _Linux_, it should be possible to install most of the packages via the system's package manager.

\* The GLAD loader should be generated from its webpage using the following settings:
- Language = C/C++
- gl = Version 4.6
- Profile = Core

Download the zip file containing the code and extract it in a custom directory.

\** On _MacOS_ they can be installed using the `brew` package manager (https://brew.sh/).

Installation instructions
----
Neutrino can be installed and used on [Linux](./Installation/installation_linux.md), [Mac](./Installation/installation_mac.md) and [Windows](./Installation/installation_windows.md).

Examples
---
In order to test the installation of Neutrino and to start experimenting with it, please refer to the [Examples](https://github.com/NeutrinoCodes/Examples) repository.

© Alessandro LUCANTONIO, Erik ZORZIN - 2018-2020
