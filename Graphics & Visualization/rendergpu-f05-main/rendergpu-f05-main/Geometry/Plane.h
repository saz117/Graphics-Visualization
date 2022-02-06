#pragma once

#include <library/Common.h>
#include <QGLShaderProgram>

#include <stdio.h>
#include "Object.h"

const int NumVertices = 6; //(1 faces)(2 triangles/face)(3 vertices/triangle)

typedef vec4  color4;
typedef vec4  point4;

class Plane//: public Object
{
  public:
      Plane();
      Plane(int an, int al, int profu, GLfloat x0, GLfloat y0, GLfloat z0);
      ~Plane();
      void make();
      void toGPU(QGLShaderProgram *program);
      void draw();
      void aplicaTG(mat4 m);

  private:

      void quad( int a, int b, int c, int d );
      void initTextura();

      int a; // amplada
      int h; // alcada
      int p; // profunditat
      GLdouble xorig, yorig, zorig;

      point4 vertices[4]; // 4 vertexs del cub
      color4 vertex_colors[4]; // 4 colors RGBA associats a cada vertex
      point4 normal;

      int Index;
      point4 points[NumVertices]; // 6 punts: cub triangulat
      color4 colors[NumVertices]; // colors en aquests punts
      point4 normals[NumVertices];//
      vec2 vertexsTextura[NumVertices]; // coordenades de textura associades a cada vertex

      shared_ptr<QOpenGLTexture> texture;

      GLuint buffer;
};

