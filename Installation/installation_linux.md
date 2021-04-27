# Linux installation

Neutrino can be compiled and installed on Linux manually using the CMake/Make toolchain or using the **VScode** editor. In the latter case, please follow the instructions (https://code.visualstudio.com/docs/cpp/config-linux) and verify the installation of GCC, as well as the instructions (https://code.visualstudio.com/docs/cpp/cmake-linux) to verify the installation of CMake and to install the CMake Tools extension for VSCode.

In the following, we assume that software and hardware [requirements](../README.md) are satisfied.

Manual compilation from sources using CMake/Make toolchain
----
1. From the command shell, navigate into your favorite directory and clone the Neutrino project using the command `git clone https://github.com/NeutrinoCodes/neutrino.git`.

2. Into the Neutrino's project directory, create a configuration script file called `configure` and edit it by adding the following command lines:

  `cmake -B"./cmake" -H"./" \`\
  `-DGLAD_PATH=your_path_to_glad \`\
  `-DGLFW_PATH=your_path_to_glfw \`\
  `-DGMSH_PATH=your_path_to_gmsh \`\
  `-DNEUTRINO_PATH=your_path_to_neutrino`

  and specify the paths accordingly, where:
  - *GLAD_PATH* is the path of the root directory of the GLAD library: it contains the subdirectories src and include;
  - *GLFW_PATH* is the path where glfw3.h is located;
  - *GMSH_PATH* is the path where the header files of Gmsh are located;
  - *NEUTRINO_PATH* is the path of Neutrino's project folder (root).

3. Make the configuration script executable (`chmod a+x configure`) and launch it by typing `./configure` at the command prompt. The CMake configuration files will be generated.

4. Enter the `cmake` directory and type `make install`. The library binary and headers will be generated and copied in the `NEUTRINO_PATH/lib` subdirectory.

Compilation using VScode toolchain
---
1. From the command shell (either VScode's or system's), navigate into *NeutrinoCodes* and create a `libnu` directory using the command:\
`mkdir libnu`\
\
This will create the `libnu` directory.

2. From the command shell (either VScode's or system's), navigate into *NeutrinoCodes* and clone the Neutrino project using the command:\
  `git clone https://github.com/NeutrinoCodes/neutrino.git` 

  This will create the `neutrino` directory.

3. Go to the `neutrino` directory and create a `.vscode` hidden directory:
`mkdir .vscode`
and create a new file `settings.json` in it, then fill it with the following information:\
`{`\
&nbsp;&nbsp;`"C_Cpp.default.configurationProvider": "vector-of-bool.cmake-tools",`\
&nbsp;&nbsp;`"cmake.configureArgs" : [   `\
&nbsp;&nbsp;&nbsp;&nbsp;`"-DGLAD_PATH=your_path_to_NeutrinoCodes/glad,`\
&nbsp;&nbsp;&nbsp;&nbsp;`"-DGLFW_PATH=your_path_to_NeutrinoCodes/glfw",`\
&nbsp;&nbsp;&nbsp;&nbsp;`"-DGMSH_PATH=your_path_to_NeutrinoCodes/gmsh",`\
&nbsp;&nbsp;&nbsp;&nbsp;`"-DNEUTRINO_PATH=your_path_to_NeutrinoCodes/libnu"`\
&nbsp;&nbsp;`]`\
`}`\
\
and save it.

4. In VScode, go to the left bar and locate the **CMake** button (it comes after the installation of the CMake Tools extension for VScode) and push it: a CMake panel will open, push the **Configure All Projects** button on it.

5. Check that the **Target** button in the bottom toolbar has been selected to **[install]**.

6. Push the **Build** button in the bottom toolbar to build the Neutrino library.

7. (*Optional*) We provide an **Uncrustify** configuration file specific for Neutrino. Add the following lines to either the *global* or *project* **settings.json** file:
`"uncrustify.executablePath.linux": "your_path_to_uncrustify",`\
`"editor.defaultFormatter": "LaurentTreguier.uncrustify",`\
`"editor.formatOnSave": true`\
\
To edit the *global* settings, on VScode go to the left bar: push the **Extensions** button and select the Uncrustify extension. Then go to **Manage --> Extension Settings** (gear-like icon) and edit the `settings.json` file by clicking one of the links in that section.
\
To edit the *project* settings, open `settings.json` file in the `.vscode` you created for Neutrino (the hidden directory inside the `Neutrino` directory) and put the same lines in it.
