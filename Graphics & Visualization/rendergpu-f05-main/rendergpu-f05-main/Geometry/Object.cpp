#include "Geometry/Object.h"



/**
 * @brief Object::Object
 * @param npoints
 * @param parent
 */
Object::Object(int npoints, QObject *parent) : QObject(parent){
    numPoints = npoints;
    points = new point4[numPoints];
    normals= new point4[numPoints];
    colors = new point4[numPoints];
    textures = new vec2[numPoints];
    material = make_shared<Material>(vec3(0.2, 0.2, 0.2),vec3(0.8, 0.5, 0.5),vec3(1.0, 1.0, 1.0),vec3(1.0,1.0,1.0),20);
    //material = make_shared<Material>(vec3(0.2, 0.2, 0.2),vec3(0.5, 1.0, 0.2),vec3(1.0, 1.0, 1.0),vec3(1.0,1.0,1.0),20);

 }

//Constructor con textura
/**
 * @brief Object::Object
 * @param npoints
 * @param t
 * @param parent
 */
Object::Object(int npoints, shared_ptr<QOpenGLTexture> t, QObject *parent) : QObject(parent){
    numPoints = npoints;
    points = new point4[numPoints];
    normals= new point4[numPoints];
    colors = new point4[numPoints];
    textures = new vec2[numPoints];
    material = make_shared<Material>(vec3(0.2, 0.2, 0.2),vec3(0.8, 0.5, 0.5),vec3(1.0, 1.0, 1.0),vec3(1.0,1.0,1.0),20);
    //material = make_shared<Material>(vec3(0.2, 0.2, 0.2),vec3(0.5, 1.0, 0.2),vec3(1.0, 1.0, 1.0),vec3(1.0,1.0,1.0),20);
    texture = t;
 }




/**
 * @brief Object::Object
 * @param npoints
 * @param n
 */
Object::Object(int npoints, QString n) : numPoints(npoints){
    points = new point4[numPoints];
    normals= new point4[numPoints];
    colors = new point4[numPoints];
    textures = new vec2[numPoints];
    material = make_shared<Material>(vec3(0.2, 0.2, 0.2),vec3(0.8, 0.5, 0.5),vec3(1.0, 1.0, 1.0),vec3(1.0,1.0,1.0),20);
    //material = make_shared<Material>(vec3(0.2, 0.2, 0.2),vec3(0.5, 1.0, 0.2),vec3(1.0, 1.0, 1.0),vec3(1.0,1.0,1.0),20);

    parseObjFile(n);
    make();
}

/**
 * @brief Object::Object
 * @param npoints
 * @param t
 * @param n
 */
Object::Object(int npoints, shared_ptr<QOpenGLTexture> t, QString n) : numPoints(npoints){
    points = new point4[numPoints];
    normals= new point4[numPoints];
    colors = new point4[numPoints];
    textures = new vec2[numPoints];
    material = make_shared<Material>(vec3(0.2, 0.2, 0.2),vec3(0.8, 0.5, 0.5),vec3(1.0, 1.0, 1.0),vec3(1.0,1.0,1.0),20);
    //material = make_shared<Material>(vec3(0.2, 0.2, 0.2),vec3(0.5, 1.0, 0.2),vec3(1.0, 1.0, 1.0),vec3(1.0,1.0,1.0),20);
    texture = t;

    parseObjFile(n);
    make();
}


/**
 * @brief Object::~Object
 */
Object::~Object(){
    delete points;
    delete normals;
    delete colors;
    delete textures;
}

/**
 * @brief Object::toGPU
 * @param pr
 */
void Object::toGPU(shared_ptr<QGLShaderProgram> pr) {
    // TO  DO: A modificar a la fase 1 de la practica 2

    qDebug() << "Obj to GPU.....";

    program = pr;
    // Creació d'un vertex array object
    material->toGPU(pr);

    glGenVertexArrays( 1, &vao );

    // Creacio i inicialitzacio d'un vertex buffer object (VBO)
    glGenBuffers( 1, &buffer );

    // Aqui s'ha de fer el pas de dades a la GPU per si hi ha més d'un objecte
    // Activació a GL del Vertex Buffer Object
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // TO  DO: A modificar a la fase 1 de la practica 2
    // Cal passar les normals a la GPU


    //glBufferData( GL_ARRAY_BUFFER, sizeof(point4)*Index + sizeof(point4)*Index, NULL, GL_STATIC_DRAW );
    glBufferData( GL_ARRAY_BUFFER, sizeof(point4)*Index*3 + sizeof(vec2)*Index, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*Index, points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index, sizeof(point4)*Index, colors );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index*2, sizeof(point4)*Index, normals); //pasar las normales
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index*3, sizeof(vec2)*Index, textures); //pasar las texCoord

    // set up vertex arrays
    glBindVertexArray( vao );
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,  0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(point4)*Index));
    glEnableVertexAttribArray(1);

    //set up de las normales en loc=2
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(point4)*Index*2));
    glEnableVertexAttribArray(2);

    //set up de las texturas en loc=3
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(point4)*Index*3));
    glEnableVertexAttribArray(3);

    if(textVertexs.size() > 0){
        toGPUTexture(pr);
    }
}


/**
 * Pintat en la GPU.
 * @brief Object::draw
 */
void Object::draw(){

    // Aqui s'ha de fer el pas de dades a la GPU per si hi ha més d'un objecte
    // Activació a GL del Vertex Buffer Object

    glBindVertexArray( vao );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays( GL_TRIANGLES, 0, Index );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);

}

/**
 * @brief Object::make
 */
void Object::make(){

    // TO  DO: A modificar a la fase 1 de la practica 2
    // Cal calcular la normal a cada vertex a la CPU

    //el cuarto color solo se usa si en lugar de triangulos los objetos están compuestos por cuadrados
    static vec3  base_colors[] = {
        vec3( 1.0, 0.0, 0.0 ),
        vec3( 0.0, 1.0, 0.0 ),
        vec3( 0.0, 0.0, 1.0 ),
        vec3( 1.0, 1.0, 0.0 )
    };

    Index = 0;
    for(unsigned int i=0; i<cares.size(); i++){
        for(unsigned int j=0; j<cares[i].idxVertices.size(); j++){
            points[Index] = vertexs[cares[i].idxVertices[j]];
            colors[Index] = vec4(base_colors[j%4], 1.0);
            normals[Index] = normalsVertexs[cares[i].idxNormals[j]];
            if(textVertexs.size() > 0){//El .obj tiene textura
                textures[Index] = textVertexs[cares[i].idxTextures[j]];
            }else{//El .obj no tiene textura, asignamos valor por defecto (-1,-1)
                textures[Index] = vec2(-1.0,-1.0);
            }
            Index++;
        }
    }

    if(textVertexs.size() > 0){
        initTexture();
    }
}


/**
 * @brief Object::toGPUTexture
 * @param pr
 */
void Object::toGPUTexture(shared_ptr<QGLShaderProgram> pr) {
    program = pr;

// TO DO: Cal implementar en la fase 1 de la practica 2
// S'ha d'activar la textura i es passa a la GPU

    // S'activa la textura i es passa a la GPU

    program->setUniformValue("texMap", 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
}


/**
 * Pintat en la GPU.
 * @brief Object::drawTexture
 */
void Object::drawTexture(){

    // TO DO: Cal implementar en la fase 1 de la practica 2
    // S'ha d'activar la textura i es passa a la GPU

    /*if(texture!=NULL){
        texture->bind(0);
        program->setUniformValue("texMap",0);
    }

    glBindVertexArray( vao );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays( GL_TRIANGLES, 0, Index );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);*/

}

void Object::setTexture(shared_ptr<QOpenGLTexture> t){
   //texture = t;

   //Modificado fase1
    glActiveTexture(GL_TEXTURE_2D);
    texture = t;

    //Inicializamos de nuevo por si acaso
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    texture->bind(0);
}


/**
 * @brief Object::initTexture
 */
void Object::initTexture()
 {
    // TO DO: A implementar a la fase 1 de la practica 2
    // Cal inicialitzar la textura de l'objecte: veure l'exemple del CubGPUTextura
    qDebug() << "Initializing textures...";

    // Carregar la textura per defecte
    glActiveTexture(GL_TEXTURE0);
    texture = make_shared<QOpenGLTexture>(QImage("://resources/textures/head_diffuse.jpg").mirrored());//Mirrored para evitar fallos de que solo se texturice la mitad
    texture->setWrapMode(QOpenGLTexture::Repeat);
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->bind(0);
 }


void Object::parseObjFile(const QString &fileName)
{
    QFile file(fileName);
    if(file.exists()) {
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            QVector<QVector3D> v, vn;
            QVector<QVector2D> vt;

            while(!file.atEnd()) {
                QString line = file.readLine().trimmed();
                QStringList lineParts = line.split(QRegularExpression("\\s+"));
                if(lineParts.count() > 0) {
                    // if it’s a comment
                    if(lineParts.at(0).compare("#", Qt::CaseInsensitive) == 0)
                    {
                        qDebug() << line.remove(0, 1).trimmed();
                    }

                    // if it’s a vertex position (v)
                    else if(lineParts.at(0).compare("v", Qt::CaseInsensitive) == 0)
                    {
                        vertexs.push_back(point4(lineParts.at(1).toFloat(),
                                           lineParts.at(2).toFloat(),
                                           lineParts.at(3).toFloat(), 1.0f));
                    }

                    // if it’s a normal (vn)
                    else if(lineParts.at(0).compare("vn", Qt::CaseInsensitive) == 0)
                    {
                        normalsVertexs.push_back (point4(lineParts.at(1).toFloat(),
                                            lineParts.at(2).toFloat(),
                                            lineParts.at(3).toFloat(), 0.0f));
                    }

                    // if it’s a texture (vt)
                    else if(lineParts.at(0).compare("vt", Qt::CaseInsensitive) == 0)
                    {
                        textVertexs.push_back(vec2(lineParts.at(1).toFloat(),
                                            lineParts.at(2).toFloat()));
                    }

                    // if it’s face data (f)
                    // there’s an assumption here that faces are all triangles
                    else if(lineParts.at(0).compare("f", Qt::CaseInsensitive) == 0)
                    {
                        Cara *cara = new Cara();

                        // get points from v array
                        cara->idxVertices.push_back(lineParts.at(1).split("/").at(0).toInt() - 1);
                        cara->idxVertices.push_back(lineParts.at(2).split("/").at(0).toInt() - 1);
                        cara->idxVertices.push_back(lineParts.at(3).split("/").at(0).toInt() - 1);

                        if(textVertexs.size() > 0) // check if really there are any UV coords
                        {
                            cara->idxTextures.push_back( lineParts.at(1).split("/").at(1).toInt() - 1);
                            cara->idxTextures.push_back( lineParts.at(2).split("/").at(1).toInt() - 1);
                            cara->idxTextures.push_back( lineParts.at(3).split("/").at(1).toInt() - 1);
                        }

                        // get normals from vn array
                        cara->idxNormals.push_back( lineParts.at(1).split("/").at(2).toInt() - 1);
                        cara->idxNormals.push_back( lineParts.at(2).split("/").at(2).toInt() - 1);
                        cara->idxNormals.push_back( lineParts.at(3).split("/").at(2).toInt() - 1);


                        // cara->calculaNormal();
                        cares.push_back(*cara);
                    }

                }
            }
            file.close();
        }
    }
}

Capsa3D Object::calculCapsa3D()
{
    vec3    pmin, pmax;
    int     i;
    Capsa3D capsa;

    pmin.x = points[0].x;
    pmin.y = points[0].y;
    pmin.z = points[0].z;
    pmax = pmin;
    for(i=1; i<Index; i++) {
        if(points[i].x <pmin[0])
            pmin[0] = points[i].x;
        if(points[i].y <pmin[1])
            pmin[1] = points[i].y;
        if(points[i].z <pmin[2])
            pmin[2] = points[i].z;

        if(points[i].x >pmax[0])
            pmax[0] = points[i].x;
        if(points[i].y >pmax[1])
            pmax[1] = points[i].y;
        if(points[i].z >pmax[2])
            pmax[2] = points[i].z;
    }
    capsa.pmin = pmin;
    capsa.a = pmax[0]-pmin[0];
    capsa.h = pmax[1]-pmin[1];
    capsa.p = pmax[2]-pmin[2];
    return capsa;
}

void Object::aplicaTG(shared_ptr<TG> tg){
    //COMO EL CÓDIGO ES IGUAL PARA TRANSLACIONES Y ESCALADOS, NO HACE FALTA HACER CAST
    mat4 t = tg->getTG();
    for (int i = 0; i < vertexs.size(); i++) {
        vertexs[i] = t * vertexs[i];
    }

    make();
}

void Object::setMaterial(shared_ptr<Material> m){
    material = m;
}
