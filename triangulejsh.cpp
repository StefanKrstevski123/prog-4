#include <iostream>
#include <vector>
using namespace std;

struct Point {
    double x, y;
};

struct Triangle {
    Point a, b, c;
};

bool same(Point p, Point q) {
    return p.x == q.x && p.y == q.y;
}

bool sameEdge(Point a1, Point a2, Point b1, Point b2) {
    return (same(a1,b1) && same(a2,b2)) || (same(a1,b2) && same(a2,b1));
}

bool inCircle(Triangle t, Point p) {
    double ax = t.a.x - p.x, ay = t.a.y - p.y;
    double bx = t.b.x - p.x, by = t.b.y - p.y;
    double cx = t.c.x - p.x, cy = t.c.y - p.y;

    double det =
        (ax*ax + ay*ay)*(bx*cy - cx*by) -
        (bx*bx + by*by)*(ax*cy - cx*ay) +
        (cx*cx + cy*cy)*(ax*by - bx*ay);

    return det > 0;
}

int main() {
    vector<Point> pts = {{0,0},{2,0},{1,2},{1,1}};

    Point s1 = {-100,-100}, s2 = {100,-100}, s3 = {0,100};
    vector<Triangle> tris = {{s1,s2,s3}};

    for (Point p : pts) {
        vector<Triangle> newTris;
        vector<pair<Point,Point>> edges;

        for (auto &t : tris) {
            if (inCircle(t,p)) {
                edges.push_back({t.a,t.b});
                edges.push_back({t.b,t.c});
                edges.push_back({t.c,t.a});
            } else {
                newTris.push_back(t);
            }
        }

        vector<pair<Point,Point>> boundary;
        for (int i=0;i<edges.size();i++) {
            bool dup = false;
            for (int j=0;j<edges.size();j++) {
                if (i!=j && sameEdge(edges[i].first,edges[i].second,
                                     edges[j].first,edges[j].second)) {
                    dup = true;
                    break;
                }
            }
            if (!dup) boundary.push_back(edges[i]);
        }

        for (auto &e : boundary) {
            newTris.push_back({e.first, e.second, p});
        }

        tris = newTris;
    }

    vector<Triangle> result;
    for (auto &t : tris) {
        if (!same(t.a,s1)&&!same(t.a,s2)&&!same(t.a,s3)&&
            !same(t.b,s1)&&!same(t.b,s2)&&!same(t.b,s3)&&
            !same(t.c,s1)&&!same(t.c,s2)&&!same(t.c,s3)) {
            result.push_back(t);
        }
    }

    cout << "Triangulacija: " << result.size() << "\n";
    for (auto &t : result) {
        cout << "(" << t.a.x << "," << t.a.y << ") ";
        cout << "(" << t.b.x << "," << t.b.y << ") ";
        cout << "(" << t.c.x << "," << t.c.y << ")\n";
    }
}
