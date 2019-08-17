/// @file

// MESH:
 #define XMIN          -1.0                                                                         // XMIN spatial boundary [m].
 #define XMAX          +1.0                                                                         // XMAX spatial boundary [m].
 #define YMIN          -1.0                                                                         // YMIN spatial boundary [m].
 #define YMAX          +1.0                                                                         // YMAX spatial boundary [m].
 #define NODES_X       100                                                                          // Number of nodes in "X" direction [#].
 #define NODES_Y       100                                                                          // Number of nodes in "Y" direction [#].
 #define NODES         NODES_X* NODES_Y                                                             // Total number of nodes [#].
 #define DX            (float)((XMAX - XMIN)/(NODES_X - 1))                                         // DX mesh spatial size [m].
 #define DY            (float)((YMAX - YMIN)/(NODES_Y - 1))                                         // DY mesh spatial size [m].

// OPENGL:
 #define INTEROP       true                                                                         // "true" = use OpenGL-OpenCL interoperability.
 #define GUI_SIZE_X    800                                                                          // Window x-size [px].
 #define GUI_SIZE_Y    600                                                                          // Window y-size [px].
 #define GUI_NAME      "neutrino 3.0"                                                               // Window name.

 #ifdef __linux__
   #define SHADER_HOME "/run/media/ezor/LINUX/BookhouseBoys/ezor/Neutrino/Code/shader"              // Linux OpenGL shaders directory.
   #define KERNEL_HOME "/run/media/ezor/LINUX/BookhouseBoys/ezor/Neutrino/Code/kernel"              // Linux OpenCL kernels directory.
 #endif

 #ifdef __APPLE__
   #define SHADER_HOME "/Users/Erik/Documents/PROJECTS/BookhouseBoys/ezor/Neutrino/Code/shader"     // Mac OpenGL shaders directory.
   #define KERNEL_HOME "/Users/Erik/Documents/PROJECTS/BookhouseBoys/ezor/Neutrino/Code/kernel"     // Mac OpenCL kernels directory.
 #endif

 #ifdef WIN32
   #define SHADER_HOME "F:\\BookHouseBoys\\ezor\\neutrino\\Code\\shader"                            // Windows OpenGL shaders directory.
   #define KERNEL_HOME "F:\\BookHouseBoys\\ezor\\neutrino\\Code\\kernel"                            // Windows OpenCL kernels directory.
 #endif

 #define SHADER_VERT   "voxel_vertex.vert"                                                          // OpenGL vertex shader.
 #define SHADER_GEOM   "voxel_geometry.geom"                                                        // OpenGL geometry shader.
 #define SHADER_FRAG   "voxel_fragment.frag"                                                        // OpenGL fragment shader.

// OPENCL:
 #define QUEUE_NUM     1                                                                            // # of OpenCL queues [#].
 #define KERNEL_NUM    1                                                                            // # of OpenCL kernel [#].
 #define KERNEL_SX     NODES                                                                        // Dimension of OpenCL kernel (i-index).
 #define KERNEL_SY     0                                                                            // Dimension of OpenCL kernel (j-index).
 #define KERNEL_SZ     0                                                                            // Dimension of OpenCL kernel (k-index).
 #define KERNEL_FILE   "sine_kernel.cl"                                                             // OpenCL kernel.

// INCLUDES:
#include "opengl.hpp"
#include "opencl.hpp"

int main ()
{
  neutrino* bas             = new neutrino ();                                                      // Neutrino baseline.
  opengl*   gui             = new opengl ();                                                        // OpenGL context.
  opencl*   ctx             = new opencl ();                                                        // OpenCL context.
  shader*   S               = new shader ();                                                        // OpenGL shader program.
  float4G*  P               = new float4G ();                                                       // OpenGL float4G.
  float4G*  C               = new float4G ();                                                       // OpenGL float4G.
  float1*   t               = new float1 ();                                                        // Time [s].
  queue*    Q               = new queue ();                                                         // OpenCL queue.
  kernel*   K               = new kernel ();                                                        // OpenCL kernel array.
  size_t    i;                                                                                      // "x" direction index.
  size_t    j;                                                                                      // "y" direction index.

  float     orbit_x;                                                                                // x-axis orbit rotation.
  float     orbit_y;                                                                                // y-axis orbit rotation.
  float     orbit_decaytime = 1.25;                                                                 // Orbit LP filter decay time [s].
  float     orbit_deadzone  = 0.1;                                                                  // Orbit rotation deadzone [0...1].
  float     orbit_rate      = 1.0;                                                                  // Orbit rotation rate [rev/s].

  float     pan_x;                                                                                  // x-axis pan translation.
  float     pan_y;                                                                                  // y-axis pan translation.
  float     pan_z;                                                                                  // z-axis pan translation.
  float     pan_decaytime   = 1.25;                                                                 // Pan LP filter decay time [s].
  float     pan_deadzone    = 0.1;                                                                  // Pan rotation deadzone [0...1].
  float     pan_rate        = 1.0;                                                                  // Pan rotation rate [rev/s].

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////// INITIALIZATION ///////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  bas->init (QUEUE_NUM, KERNEL_NUM, INTEROP);                                                       // Initializing Neutrino baseline...
  gui->init (bas, GUI_SIZE_X, GUI_SIZE_Y, GUI_NAME);                                                // Initializing OpenGL context...
  ctx->init (bas, gui, NU_GPU);                                                                     // Initializing OpenCL context...
  S->init (bas, SHADER_HOME, SHADER_VERT, SHADER_GEOM, SHADER_FRAG);                                // Initializing OpenGL shader...
  P->init (NODES);                                                                                  // Initializing OpenGL point array...
  C->init (NODES);                                                                                  // Initializing OpenGL color array...
  t->init (NODES);                                                                                  // Initializing time...
  Q->init (bas);                                                                                    // Initializing OpenCL queue...
  K->init (bas, KERNEL_HOME, KERNEL_FILE, KERNEL_SX, KERNEL_SY, KERNEL_SZ);                         // Initializing OpenCL kernel...

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////// SETTING POINTS DATA /////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  P->name = "voxel_center";                                                                         // Setting variable name in OpenGL shader...
  C->name = "voxel_color";                                                                          // Setting variable name in OpenGL shader...

  for(j = 0; j < NODES_Y; j++)
  {
    for(i = 0; i < NODES_X; i++)
    {
      // Setting point coordinates:
      P->data[j*NODES_X + i].x = i*DX + XMIN;                                                       // Setting "x" point coordinate...
      P->data[j*NODES_X + i].y = j*DY + YMIN;                                                       // Setting "y" point coordinate...
      P->data[j*NODES_X + i].z = 0.0;                                                               // Setting "z" point coordinate...
      P->data[j*NODES_X + i].w = 1.0;                                                               // Setting "w" point coordinate...

      // Setting point colors:
      C->data[j*NODES_X + i].x = 0.01*(rand () % 100);                                              // Setting "r" color coordinate...
      C->data[j*NODES_X + i].y = 0.01*(rand () % 100);                                              // Setting "g" color coordinate...
      C->data[j*NODES_X + i].z = 0.01*(rand () % 100);                                              // Setting "b" color coordinate...
      C->data[j*NODES_X + i].w = 1.0;                                                               // Setting "a" color coordinate...

      // Setting time:
      t->data[j*NODES_X + i]   = 0.0;                                                               // Setting time...
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////// SETTING OPENCL KERNEL ARGUMENTS ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  K->setarg (P, 0);                                                                                 // Setting kernel argument "0"...
  K->setarg (C, 1);                                                                                 // Setting kernel argument "1"...
  K->setarg (t, 2);                                                                                 // Setting kernel argument "2"...

  ////////////////////////////////////////////////////////////////////////////////
  ////////////////////////// WRITING DATA ON OPENCL QUEUE ////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  Q->write (P, 0);                                                                                  // Uploading argument "0" on kernel...
  Q->write (C, 1);                                                                                  // Uploading argument "1" on kernel...
  Q->write (t, 2);                                                                                  // Uploading argument "2" on kernel...

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////// SETTING OPENGL SHADER ARGUMENTS ///////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  S->setarg (P, 0);                                                                                 // Setting shader argument "0"...
  S->setarg (C, 1);                                                                                 // Setting shader argument "1"...
  S->build ();                                                                                      // Building shader program...

  ////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////// APPLICATION LOOP //////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  while(!gui->closed ())                                                                            // Opening gui...
  {
    bas->get_tic ();                                                                                // Getting "tic" [us]...
    gui->clear ();                                                                                  // Clearing gui...
    gui->poll_events ();                                                                            // Polling gui events...

    Q->write (t, 2);

    Q->acquire (P, 0);                                                                              // Acquiring OpenGL/CL shared argument...
    Q->acquire (C, 1);                                                                              // Acquiring OpenGL/CL shared argument...
    ctx->execute (K, Q, NU_WAIT);                                                                   // Executing OpenCL kenrnel...
    Q->release (P, 0);                                                                              // Releasing OpenGL/CL shared argument...
    Q->release (C, 1);                                                                              // Releasing OpenGL/CL shared argument...

    orbit_x = gui->axis_LEFT_X;                                                                     // Setting "Near clipping-plane" x-coordinate...
    orbit_y = -gui->axis_LEFT_Y;                                                                    // Setting "Near clipping-plane" y-coordinate...

    gui->orbit (
                orbit_x,                                                                            // "Near clipping-plane" x-coordinate.
                orbit_y,                                                                            // "Near clipping-plane" y-coordinate.
                orbit_rate,                                                                         // Orbit angular rate coefficient [rev/s].
                orbit_deadzone,                                                                     // Orbit deadzone threshold coefficient.
                orbit_decaytime                                                                     // Orbit low pass decay time [s].
               );

    pan_x   = gui->axis_RIGHT_X;                                                                    // Setting world x-pan...
    pan_y   = -gui->axis_RIGHT_Y;                                                                   // Setting world y-pan...
    pan_z   = (gui->axis_RIGHT_TRIGGER + 1.0)/2.0 - (gui->axis_LEFT_TRIGGER + 1.0)/2.0;             // Setting world z-pan...

    gui->pan (
              pan_x,                                                                                // World x-pan.
              pan_y,                                                                                // World y-pan.
              pan_z,                                                                                // World z-pan.
              pan_rate,                                                                             // Pan rate [length/s].
              pan_deadzone,                                                                         // Pan deadzone threshold coefficient.
              pan_decaytime                                                                         // Pan low pass decay time [s].
             );

    gui->plot (S);                                                                                  // Plotting shared arguments...

    Q->read (t, 2);

    gui->refresh ();                                                                                // Refreshing gui...
    bas->get_toc ();                                                                                // Getting "toc" [us]...
  }

  ////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// CLEANUP //////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////
  delete bas;                                                                                       // Deleting Neutrino baseline...
  delete gui;                                                                                       // Deleting OpenGL gui ...
  delete ctx;                                                                                       // Deleting OpenCL context...
  delete S;                                                                                         // Deleting OpenGL shader...
  delete P;                                                                                         // Deleting OpenGL point...
  delete C;                                                                                         // Deleting OpenGL color...
  delete Q;                                                                                         // Deleting OpenCL queue...
  delete K;                                                                                         // Deleting OpenCL kernel...

  return 0;
}
