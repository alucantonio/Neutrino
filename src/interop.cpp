#include "interop.hpp"

void push_float4_data(data_float4* data)
{
  int err;
  unsigned int i;
  GLfloat* unfolded_data;

  printf("Action: pushing argument #%d to GPU... ", (int)kernel_arg);

  unfolded_data = new GLfloat[4*data->size];

  for (i = 0; i < data->size; i++)
  {
    unfolded_data[4*i]     = data->x[i];
    unfolded_data[4*i + 1] = data->y[i];
    unfolded_data[4*i + 2] = data->z[i];
    unfolded_data[4*i + 3] = data->w[i];
  }

  glGenVertexArrays(1, &data->vao);
  glBindVertexArray(data->vao);

  glGenBuffers(1, &data->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, data->vbo);
  glBufferData(GL_ARRAY_BUFFER, 4*sizeof(GLfloat)*(data->size), unfolded_data, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  data->buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, data->vbo, &err);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, kernel_arg, sizeof(cl_mem), &data->buffer);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  kernel_arg++;

  printf("DONE!\n");
}

void push_float4_size(data_float4* data)
{
  int err;

  printf("Action: pushing argument #%d to GPU... ", (int)kernel_arg);

  err = clSetKernelArg(kernel, kernel_arg, sizeof(unsigned int), &data->size);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  kernel_arg++;

  printf("DONE!\n");
}

void push_float4_points(data_float4* points)
{
  int err;
  unsigned int i;
  GLfloat* unfolded_data;

  printf("Action: pushing argument #%d to GPU... ", (int)kernel_arg);

  unfolded_data = new GLfloat[4*points->size];

  for (i = 0; i < points->size; i++)
  {
    unfolded_data[4*i]     = points->x[i];
    unfolded_data[4*i + 1] = points->y[i];
    unfolded_data[4*i + 2] = points->z[i];
    unfolded_data[4*i + 3] = points->w[i];
  }

  glGenVertexArrays(1, &points->vao);
  glBindVertexArray(points->vao);

  glGenBuffers(1, &points->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, points->vbo);
  glBufferData(GL_ARRAY_BUFFER, 4*sizeof(GLfloat)*(points->size), unfolded_data, GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(0);                                                 // Matches "layout = 0" variable in vertex shader.
  glBindBuffer(GL_ARRAY_BUFFER, points->vbo);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);                        // Matches "layout = 0" variable in vertex shader.


  points->buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, points->vbo, &err);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, kernel_arg, sizeof(cl_mem), &points->buffer);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  kernel_arg++;

  printf("DONE!\n");
}

void push_float4_colors(data_float4* colors)
{
  int err;
  unsigned int i;
  GLfloat* unfolded_data;

  printf("Action: pushing argument #%d to GPU... ", (int)kernel_arg);

  unfolded_data = new GLfloat[4*colors->size];

  for (i = 0; i < colors->size; i++)
  {
    unfolded_data[4*i]     = colors->x[i];
    unfolded_data[4*i + 1] = colors->y[i];
    unfolded_data[4*i + 2] = colors->z[i];
    unfolded_data[4*i + 3] = colors->w[i];
  }

  glGenVertexArrays(1, &colors->vao);
  glBindVertexArray(colors->vao);

  glGenBuffers(1, &colors->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, colors->vbo);
  glBufferData(GL_ARRAY_BUFFER, 4*sizeof(GLfloat)*(colors->size), unfolded_data, GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(1);                                                 // Matches "layout = 1" variable in vertex shader.
  glBindBuffer(GL_ARRAY_BUFFER, colors->vbo);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);                        // Matches "layout = 1" variable in vertex shader.

  colors->buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, colors->vbo, &err);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, kernel_arg, sizeof(cl_mem), &colors->buffer);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  kernel_arg++;

  printf("DONE!\n");
}

void push_float_data(data_float* data)
{
  int err;
  unsigned int i;
  GLfloat* unfolded_data;

  printf("Action: pushing argument #%d to GPU... ", (int)kernel_arg);

  unfolded_data = new GLfloat[data->size];

  for (i = 0; i < data->size; i++)
  {
    unfolded_data[i] = data->x[i];
  }

  glGenVertexArrays(1, &data->vao);
  glBindVertexArray(data->vao);
  glGenBuffers(1, &data->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, data->vbo);
  glBufferData(GL_ARRAY_BUFFER, data->size*sizeof(GLfloat), unfolded_data, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  data->buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, data->vbo, &err);
  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, kernel_arg, sizeof(cl_mem), &data->buffer);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  kernel_arg++;

  printf("DONE!\n");
}

void push_float_size(data_float* data)
{
  int err;

  printf("Action: pushing argument #%d to GPU... ", (int)kernel_arg);

  err = clSetKernelArg(kernel, kernel_arg, sizeof(unsigned int), &data->size);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  kernel_arg++;

  printf("DONE!\n");
}

void push_int4_data(data_int4* data)
{
  int err;
  unsigned int i;
  GLint* unfolded_data;

  printf("Action: pushing argument #%d to GPU... ", (int)kernel_arg);

  unfolded_data = new GLint[4*data->size];

  kernel_arg++;

  for (i = 0; i < data->size; i++)
  {
    unfolded_data[4*i]     = data->x[i];
    unfolded_data[4*i + 1] = data->y[i];
    unfolded_data[4*i + 2] = data->z[i];
    unfolded_data[4*i + 3] = data->w[i];
  }

  glGenVertexArrays(1, &data->vao);
  glBindVertexArray(data->vao);
  glGenBuffers(1, &data->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, data->vbo);
  glBufferData(GL_ARRAY_BUFFER, 4*data->size*sizeof(GLint), unfolded_data, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 4, GL_INT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  data->buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, data->vbo, &err);
  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, kernel_arg, sizeof(cl_mem), &data->buffer);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  kernel_arg++;

  printf("DONE!\n");
}

void push_int4_size(data_int4* data)
{
  int err;

  printf("Action: pushing argument #%d to GPU... ", (int)kernel_arg);

  err = clSetKernelArg(kernel, kernel_arg, sizeof(unsigned int), &data->size);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  kernel_arg++;

  printf("DONE!\n");
}

void push_int_data(data_int* data)
{
  int err;
  unsigned int i;
  GLint* unfolded_data;

  printf("Action: pushing argument #%d to GPU... ", (int)kernel_arg);

  unfolded_data = new GLint[data->size];

  kernel_arg++;

  for (i = 0; i < data->size; i++)
  {
    unfolded_data[i] = data->x[i];
  }

  glGenVertexArrays(1, &data->vao);
  glBindVertexArray(data->vao);
  glGenBuffers(1, &data->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, data->vbo);
  glBufferData(GL_ARRAY_BUFFER, data->size*sizeof(GLint), unfolded_data, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 1, GL_INT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  data->buffer = clCreateFromGLBuffer(context, CL_MEM_READ_WRITE, data->vbo, &err);
  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &data->buffer);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  kernel_arg++;

  printf("DONE!\n");
}

void push_int_size(data_int* data)
{
  int err;

  printf("Action: pushing argument #%d to GPU... ", (int)kernel_arg);

  err = clSetKernelArg(kernel, kernel_arg, sizeof(unsigned int), &data->size);

  if(err < 0)
  {
    printf("\nError:  %s\n", get_error(err));
    exit(EXIT_FAILURE);
  }

  kernel_arg++;

  printf("DONE!\n");
}
