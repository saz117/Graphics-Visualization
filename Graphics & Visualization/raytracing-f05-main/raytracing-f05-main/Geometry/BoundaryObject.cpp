
#include <QVector>
#include <QVector3D>

#include "BoundaryObject.h"

BoundaryObject::BoundaryObject(string s, float data) : Object(data){

    readObj(s);//Aqui es creem els objectes com a vertex i cares i a initTriangles es processa
    // TO DO: Cal fer un recorregut de totes les cares per a posar-les com Triangles
    // Cal recorrer l'estructura de l'objecte segons cara-vertexs que es carrega
    initTriangles(data);
}

void BoundaryObject::clearVectors() {
    this->vertexs.clear();
    this->cares.clear();
}

void BoundaryObject::initTriangles(float data) {
    vec3 vertex1, vertex2, vertex3;
    Triangle* triangle;

    for (auto cara : this->getCares()) {

        vertex1 = vec3(getVertexs()[cara.idxVertices[0]]);
        vertex2 = vec3(getVertexs()[cara.idxVertices[1]]);
        vertex3 = vec3(getVertexs()[cara.idxVertices[2]]);

        triangle = new Triangle(vertex1, vertex2, vertex3, data);

        triangles.push_back(triangle);
    }

    clearVectors();
}

BoundaryObject::~BoundaryObject() {
    for(auto triangle: this->triangles) {
        delete triangle;
    }

    delete this;
}

bool BoundaryObject::hit(const Ray& raig, float t_min, float t_max, HitInfo& info) const {

    // TO DO Fase 1: A implementar
    bool hit;
    bool thereIsHit;
    HitInfo closestHit;
    HitInfo hitAux;
    float minT = INFINITY;
    float maxT = INFINITY;

    thereIsHit = false;

    for (Triangle *triangle : triangles) {
        hit = triangle->hit(raig, minT, maxT, hitAux);

        if (hit) {
            if (minT == INFINITY) {
                minT = hitAux.t;
                maxT = minT;
                closestHit = hitAux;
                thereIsHit = true;
            } else if (hitAux.t < minT) {
                minT = hitAux.t;
                closestHit = hitAux;
            } else if (hitAux.t >= maxT) {
                maxT = hitAux.t;
            }
        }
    }

    if (thereIsHit) {
        info = closestHit;
        info.mat_ptr = material.get();
    }

    return thereIsHit;
}


void BoundaryObject::aplicaTG(shared_ptr<TG> t) {
    if(dynamic_pointer_cast<TranslateTG>(t)){
        for (Triangle *triangle : triangles) {
            triangle->aplicaTG(t);
        }
    }

}

BoundaryObject::BoundaryObject(const QString &fileName, float data): Object(data)
{
    QFile file(fileName);
    if(file.exists()) {
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            QVector<QVector3D> v;

            while(!file.atEnd()) {
                QString line = file.readLine().trimmed();
                QStringList lineParts = line.split(QRegularExpression("\\s+"));
                if(lineParts.count() > 0) {
                    // if it’s a comment
                    if(lineParts.at(0).compare("#", Qt::CaseInsensitive) == 0)
                    {
                       // qDebug() << line.remove(0, 1).trimmed();
                    }

                        // if it’s a vertex position (v)
                    else if(lineParts.at(0).compare("v", Qt::CaseInsensitive) == 0)
                    {
                        vertexs.push_back(vec4(lineParts.at(1).toFloat(),
                                                 lineParts.at(2).toFloat(),
                                                 lineParts.at(3).toFloat(), 1.0f));
                    }

                        // if it’s a normal (vn)
                    else if(lineParts.at(0).compare("vn", Qt::CaseInsensitive) == 0)
                    {

                    }
                    // if it’s a texture (vt)
                    else if(lineParts.at(0).compare("vt", Qt::CaseInsensitive) == 0)
                    {

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

                        cares.push_back(*cara);
                    }

                }
            }

            file.close();
        }
    initTriangles(data);
    }
}


// Llegeix un fitxer .obj
//  Si el fitxer referencia fitxers de materials (.mtl), encara no es llegeixen
//  Tots els elements del fitxer es llegeixen com a un unic objecte.
void BoundaryObject::readObj(string filename){

    FILE *fp = fopen(filename.c_str(),"rb");
    if (!fp)
    {
        cout << "No puc obrir el fitxer " << endl;
    }
    else {

        while (true)
        {
            char *comment_ptr = ReadObj::fetch_line (fp);

            if (comment_ptr == (char *) -1)  //end-of-file
                break;

            //did we get a comment?
            if (comment_ptr) {
                //make_comment (comment_ptr);
                continue;
            }

            //if we get here, the line was not a comment
            int nwords = ReadObj::fetch_words();

            //skip empty lines
            if (nwords == 0)
                continue;

            char *first_word = ReadObj::words[0];

            if (!strcmp (first_word, "v"))
            {
                if (nwords < 4) {
                    fprintf (stderr, "Too few coordinates: '%s'", ReadObj::str_orig);
                    exit (-1);
                }

                string sx(ReadObj::words[1]);
                string sy(ReadObj::words[2]);
                string sz(ReadObj::words[3]);
                double x = atof(sx.c_str());
                double y = atof(sy.c_str());
                double z = atof(sz.c_str());

                if (nwords == 5) {
                    string sw(ReadObj::words[4]);
                    double w = atof(sw.c_str());
                    x/=w;
                    y/=w;
                    z/=w;
                }
                // S'afegeix el vertex a l'objecte
                vertexs.push_back(vec4(x, y, z, 1));

            }
            else if (!strcmp (first_word, "vn")) {
            }
            else if (!strcmp (first_word, "vt")) {
            }
            else if (!strcmp (first_word, "f")) {
                // S'afegeix la cara a l'objecte
                // A modificar si es vol carregar mes de un objecte
                construeix_cara (&ReadObj::words[1], nwords-1, this, 0);
            }
            // added
            else if (!strcmp (first_word, "mtllib")) {
                //read_mtllib (&words[1], nwords-1, matlib, filename);
            }
            else if (!strcmp (first_word, "usemtl")) {
                //int size = strlen(words[1])-1;
                //while (size && (words[1][size]=='\n' || words[1][size]=='\r') ) words[1][size--]=0;
                //currentMaterial = matlib.index(words[1]);
            }
            // fadded
            else {
                //fprintf (stderr, "Do not recognize: '%s'\n", str_orig);
            }
        }
    }
    fclose(fp);
}

/**
 * @brief BoundaryObject::construeix_cara
 * @param words
 * @param nwords
 * @param objActual
 * @param vindexUlt
 */


void BoundaryObject::construeix_cara ( char **words, int nwords, BoundaryObject *objActual, int vindexUlt) {
    Cara face;

    for (int i = 0; i < nwords; i++) {
        int vindex;
        int nindex;
        int tindex;

        if ((words[i][0]>='0')&&(words[i][0]<='9')) {
            ReadObj::get_indices (words[i], &vindex, &tindex, &nindex);

#if 0
            printf ("vtn: %d %d %d\n", vindex, tindex, nindex);
#endif

            // store the vertex index

            if (vindex > 0)       //indices are from one, not zero
                face.idxVertices.push_back(vindex - 1 - vindexUlt);
            else if (vindex < 0)  // negative indices mean count backwards
                face.idxVertices.push_back(objActual->vertexs.size() + vindex);
            else {
                fprintf (stderr, "Zero indices not allowed: '%s'\n", ReadObj::str_orig);
                exit (-1);
            }
        }
    }
    face.color = vec4(1.0, 0.0, 0.0, 1.0);
    objActual->cares.push_back(face);
}

const vector<Cara> &BoundaryObject::getCares() const {

  return cares;

}

void BoundaryObject::setCares(const vector<Cara> &cares) {

  BoundaryObject::cares = cares;

}

const vector<vec4> &BoundaryObject::getVertexs() const {

  return vertexs;

}

void BoundaryObject::setVertexs(const vector<vec4> &vertexs) {

  BoundaryObject::vertexs = vertexs;

}

vector<Triangle*> BoundaryObject::getTriangles() const{

  return triangles;

}

void BoundaryObject::setTriangles(const vector<Triangle*> triangles) {

  BoundaryObject::triangles = triangles;

}

