/// @file   kernel.hpp
/// @author Erik ZORZIN
/// @date   24OCT2019
/// @brief  Declaration of an OpenCL "kernel" class.

#ifndef kernel_hpp
#define kernel_hpp

#include "neutrino.hpp"
#include "data_classes.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// "kernel" class ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class kernel
/// ### OpenCL kernel.
/// Declares an OpenCL kernel.
/// To be used to run OpenCL computation.
class kernel
{
private:
  neutrino*     baseline;                                                                           ///< @brief **Neutrino baseline.**
  cl_device_id* device_id;                                                                          ///< @brief **Device ID array.**

public:
  cl_kernel     kernel_id;                                                                          ///< @brief **Kernel id.**
  std::string   kernel_home;                                                                        ///< @brief **Kernel home directory [std::string].**
  std::string   kernel_file_name;                                                                   ///< @brief **Kernel file name [std::string].**
  std::string   compiler_options;                                                                   ///< @brief **OpenCL JIT complier options string [std::string].**
  std::string   compiler_log;                                                                       ///< @brief **OpenCL JIT compiler error log [std::string].**
  std::string   source;                                                                             ///< @brief **Kernel source [std::string].**
  size_t        source_size;                                                                        ///< @brief **Kernel source size [characters].
  cl_program    program;                                                                            ///< @brief **Kernel program.**
  size_t        size_i;                                                                             ///< @brief **Kernel size (i-index) [#].**
  size_t        size_j;                                                                             ///< @brief **Kernel size (j-index) [#].**
  size_t        size_k;                                                                             ///< @brief **Kernel size (k-index) [#].**
  cl_event      event;                                                                              ///< @brief **Kernel event.**

  /// @brief Class constructor.
  /// @details It resets the @link source @endlink, @link program @endlink, @link size_i @endlink,
  /// @link size_j @endlink, @link size_k @endlink, @link event @endlink and @link kernel_id
  /// @endlink default values.
  /// The initialization of the class must occur
  /// after the initialization of the @link opencl @endlink and the @link opengl @endlink object,
  /// therefore it must be done by invoking the @link kernel::init @endlink method.
  kernel();

  /// @brief Class initializer.
  /// @details Loads an OpenCL kernel source from its corresponding source file,
  /// creates an OpenCL program from that kernel source and builds it into an OpenCL program,
  /// creates an OpenCL kernel object from that program and initializes the kernel object.
  /// The values of the kernel dimensions @link size_i @endlink, @link size_j @endlink,
  /// and @link size_k @endlink variables are copied from the corresponding parameters the user
  /// must pass as input arguments to the @link kernel::init @method , according to the
  /// implementation of the algorithms in the kernel source code.
  void init (
             neutrino*   loc_baseline,                                                              ///< @brief **Neutrino baseline.
             std::string loc_kernel_home,                                                           ///< @brief **Kernel home directory.
             std::string loc_kernel_file_name,                                                      ///< @brief **OpenCL kernel file name.
             size_t      loc_kernel_size_i,                                                         ///< @brief **OpenCL kernel size (i-index).
             size_t      loc_kernel_size_j,                                                         ///< @brief **OpenCL kernel size (j-index).
             size_t      loc_kernel_size_k                                                          ///< @brief **OpenCL kernel size (k-index).
            );

  /// @brief
  /// @details My read.
  void setarg (
               float1* loc_data,                                                                    ///< @brief **float1 object.
               cl_uint loc_layout_index                                                             ///< @brief **Layout index.
              );

  /// @overload read(int1* loc_data, cl_uint loc_layout_index)
  /// Pippo.
  void setarg (
               int1*   loc_data,                                                                    ///< @brief **int1 object.
               cl_uint loc_layout_index                                                             ///< @brief **Layout index.
              );

  /// @overload read(int1* loc_data, cl_uint loc_layout_index)
  /// Pippo.
  void setarg (
               float4* loc_data,                                                                    ///< @brief **Float4 object.
               cl_uint loc_layout_index                                                             ///< @brief **Layout index.
              );

  /// @overload read(int1* loc_data, cl_uint loc_layout_index)
  /// Pippo.
  void setarg (
               int4*   loc_data,                                                                    ///< @brief **Int4 object.
               cl_uint loc_layout_index                                                             ///< @brief **Layout index.
              );

  /// @overload read(int1* loc_data, cl_uint loc_layout_index)
  /// Pippo.
  void setarg (
               float1G* loc_data,                                                                   ///< @brief **Point object.
               GLuint   loc_layout_index                                                            ///< @brief **Layout index.
              );

  /// @overload read(int1* loc_data, cl_uint loc_layout_index)
  /// Pippo.
  void setarg (
               float4G* loc_data,                                                                   ///< @brief **Point object.
               GLuint   loc_layout_index                                                            ///< @brief **Layout index.
              );

  ////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////// DESTRUCTOR /////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  ~kernel();
};

#endif
