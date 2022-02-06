#ifndef BOUND_OBJECT_H
#define BOUND_OBJECT_H
#pragma once

#include <vector>
#include <string>

#include <QString>
#include <QFile>
#include <QRegularExpression>


#include <iostream>
#include <stdlib.h>
#include <cstring>

#include "Object.h"
#include "Cara.h"
#include "DataService/ReadObj.h"
#include "Triangle.h"

using namespace std;

class BoundaryObject : public Object {
public:
    BoundaryObject(string s, float data);
    BoundaryObject(const QString &fileName, float data);
    virtual bool hit(const Ray& r, float t_min, float t_max, HitInfo& info) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;
    virtual ~BoundaryObject() override;

private:

    string nom;
    vector<Cara> cares; // cares de l'objecte
    vector<vec4> vertexs; // vertexs de l'objecte sense repetits
    vector<Triangle*> triangles;

    void readObj(string filename);
    void construeix_cara ( char **words, int nwords, BoundaryObject *objActual, int vindexUlt);
    void clearVectors();
    void initTriangles(float data);
    const vector<Cara> &BoundaryObject::getCares() const;
    void BoundaryObject::setCares(const vector<Cara> &cares);
    const vector<vec4> &BoundaryObject::getVertexs() const;
    void BoundaryObject::setVertexs(const vector<vec4> &vertexs);
    vector<Triangle*> BoundaryObject::getTriangles() const;
    void BoundaryObject::setTriangles(const vector<Triangle*> triangles);

};

#endif
