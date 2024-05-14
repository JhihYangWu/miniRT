#include "octree.hpp"
#include <queue>

Octree::Octree(BBox bbox, std::vector<Triangle*> trigs, int maxDepth, int approxTrigPerBBox) {
    this->bbox = bbox;
    if (trigs.size() <= approxTrigPerBBox || maxDepth == 0) {
        isLeaf = true;
        for (int i = 0; i < 8; i++) children[i] = nullptr;
        this->trigs = trigs;
    } else {
        isLeaf = false;
        // subdivide bbox into 8 regions
        int i = 0;
        for (int x = 0; x < 2; x++) {
            for (int y = 0; y < 2; y++) {
                for (int z = 0; z < 2; z++) {
                    Vector3 minPt;
                    Vector3 maxPt;
                    if (x == 0) {
                        minPt.x = bbox.minPt.x;
                        maxPt.x = (bbox.minPt.x + bbox.maxPt.x) / 2.0f;
                    } else {
                        minPt.x = (bbox.minPt.x + bbox.maxPt.x) / 2.0f;
                        maxPt.x = bbox.maxPt.x;
                    }
                    if (y == 0) {
                        minPt.y = bbox.minPt.y;
                        maxPt.y = (bbox.minPt.y + bbox.maxPt.y) / 2.0f;
                    } else {
                        minPt.y = (bbox.minPt.y + bbox.maxPt.y) / 2.0f;
                        maxPt.y = bbox.maxPt.y;
                    }
                    if (z == 0) {
                        minPt.z = bbox.minPt.z;
                        maxPt.z = (bbox.minPt.z + bbox.maxPt.z) / 2.0f;
                    } else {
                        minPt.z = (bbox.minPt.z + bbox.maxPt.z) / 2.0f;
                        maxPt.z = bbox.maxPt.z;
                    }
                    BBox subBBox(minPt, maxPt);
                    // new Octree node
                    // constructed using all triangles that has a part inside this bbox
                    std::vector<Triangle*> subTrigs;
                    for (Triangle* t : trigs) {
                        if (subBBox.isInBox(t->A) || subBBox.isInBox(t->B) || subBBox.isInBox(t->C)) {
                            subTrigs.push_back(t);
                        }
                    }
                    children[i] = new Octree(subBBox, subTrigs, maxDepth - 1, approxTrigPerBBox);
                    i++;
                }
            }
        }
    }
}

Octree::~Octree() {
    if (!isLeaf) {
        for (int i = 0; i < 8; i++) {
            delete children[i];
        }
    }
}

float Octree::intersect(Ray r, Triangle** hitTrig) {
    float tmin = -1.0f;

    // perform BFS
    std::queue<Octree*> queue;
    queue.push(this);

    while (!queue.empty()) {
        // pop element in the front of the queue
        Octree* o = queue.front();
        queue.pop();
        // check if ray intersects this node and is closer to tmin
        float t1 = o->bbox.intersect(r);
        if (t1 != -1.0f && (tmin == -1.0f || t1 < tmin)) {
            // ray intersects this node and is possibly closer
            if (o->isLeaf) {
                // if leaf, intersect with triangles
                for (Triangle* trig : o->trigs) {
                    float t2 = trig->intersect(r);
                    if (t2 != -1.0f && (tmin == -1.0f || t2 < tmin)) {
                        *hitTrig = trig;
                        tmin = t2;
                    }
                }
            } else {
                // add children nodes
                for (int i = 0; i < 8; i++) queue.push(o->children[i]);
            }
        }
    }

    return tmin;
}
