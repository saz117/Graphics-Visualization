#include <Geometry/Plane.h>

Plane::Plane()//: Object(6)
{
    qDebug() << "Estic en el constructor del cub\n";
    // Cub centrat al 0,0,0 amb dimensió 1 a totes les seves arestes
    xorig = -0.5; yorig = -0.50; zorig = -0.5;
    a = 1.0;
    h = 1.0;
    p = 0.0; //profundidad 0 porque es una sola cara

    // Vertices of a unit cube centered at origin, sides aligned with axes
    //4 vertices porque es una sola cara
    vertices[0] = point4( -0.5, -0.5,  0.5, 1.0 );
    vertices[1] = point4( -0.5,  0.5,  0.5, 1.0 );
    vertices[2] = point4(  0.5,  0.5,  0.5, 1.0 );
    vertices[3] = point4(  0.5, -0.5,  0.5, 1.0 );

    // RGBA colors
    vertex_colors[0] =    color4( 0.0, 0.0, 0.0, 1.0 );  // black
    vertex_colors[1] =    color4( 1.0, 0.0, 0.0, 1.0 );  // red
    vertex_colors[2] =    color4( 1.0, 1.0, 0.0, 1.0 );  // yellow
    vertex_colors[3] =    color4( 0.0, 1.0, 0.0, 1.0 );  // green

    //Calculem la normal:
    vec3 a = vec3(vertices[0].x-vertices[1].x,vertices[0].y-vertices[1].y,vertices[0].z-vertices[1].z);
    vec3 b = vec3(vertices[3].x-vertices[1].x,vertices[3].y-vertices[1].y,vertices[3].z-vertices[1].z);
    normal = normalize(vec4(cross(a,b),0.0f));

}

// Constructora amb tots els parametres
Plane::Plane(int an, int al, int profu, const GLfloat x0, GLfloat y0, GLfloat z0)//: Object(6)
{
    qDebug() << "Estic en el constructor parametritzat del cub\n";
    a = an;
    h = al;
    p = profu;
    xorig = x0;
    yorig = y0;
    zorig = z0;
}

// Destructora
Plane::~Plane()
{
}

// quad generates two triangles for each face and assigns colors
//    to the vertices

//todo esto para una cara
void Plane::quad( int a, int b, int c, int d )
{
    //Como la normal es la misma para todos los puntos, pasamos la misma al array normals
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a];
    vertexsTextura[Index] = vec2(0.0, 0.0); normals[Index] = normal; Index++;
    colors[Index] = vertex_colors[b]; points[Index] = vertices[b];
    vertexsTextura[Index] = vec2(1.0, 0.0); normals[Index] = normal; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c];
    vertexsTextura[Index] = vec2(1.0, 1.0); normals[Index] = normal; Index++;
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a];
    vertexsTextura[Index] = vec2(0.0, 0.0); normals[Index] = normal; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c];
    vertexsTextura[Index] = vec2(1.0, 1.0); normals[Index] = normal; Index++;
    colors[Index] = vertex_colors[d]; points[Index] = vertices[d];
    vertexsTextura[Index] = vec2(0.0, 1.0); normals[Index] = normal; Index++;
}


// Realitzacio de la geometria del cub en el vertex array
void Plane::make()
{
    qDebug() << "Estic en el make del cub\n";
    // generacio de la geometria dels triangles per a visualitzar-lo
    Index = 0;
    quad( 1, 0, 3, 2 ); //llamamos solo a una cara
    initTextura();
}

void Plane::initTextura()
 {
     qDebug() << "Initializing textures...\n";


     // Carregar la textura
     glActiveTexture(GL_TEXTURE0);
     texture = make_shared<QOpenGLTexture>(QImage("://resources/earth1.png"));
     texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
     texture->setMagnificationFilter(QOpenGLTexture::Linear);

     texture->bind(0);

 }

// Carrega del cub a la GPU
void Plane::toGPU(QGLShaderProgram *program){

    qDebug() << "Passo les dades del plane a la GPU\n";

    // S'activa la textura i es passa a la GPU
    texture->bind(0);
    program->setUniformValue("texMap", 0);

    // Creació d'un vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Creacio i inicialitzacio d'un buffer object

    glGenBuffers( 1, &buffer );

    // Activació a GL del Vertex Buffer Object
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    //Transferencia
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors) + sizeof(normals) + sizeof(vertexsTextura),NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points)+sizeof(colors), sizeof(normals), normals );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points)+sizeof(colors)+sizeof(normals), sizeof(vertexsTextura), vertexsTextura );


    // set up vertex arrays

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,  0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(points)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(points)+sizeof(colors)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(points)+sizeof(colors)+sizeof(normals)));
    glEnableVertexAttribArray(3);


    glEnable( GL_DEPTH_TEST );
    glEnable(GL_TEXTURE_2D);

}

// Pintat dels arrays definits del cub: activació del pipeline de GL
void Plane::draw()
{
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glDrawArrays( GL_TRIANGLES, 0, NumVertices );
}

void Plane::aplicaTG(mat4 m)
{
    point4  transformed_points[NumVertices];

    for ( int i = 0; i < NumVertices; ++i ) {
        transformed_points[i] = m * points[i];
    }

    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    // Actualitzacio del vertex array per a preparar per pintar
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(transformed_points),
                     transformed_points );
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}
