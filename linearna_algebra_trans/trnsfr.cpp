#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

using Vec3 = array<float, 3>;

struct Mat3 {
    float m[3][3];

    static Mat3 identity() {
        return {{
            {1,0,0},
            {0,1,0},
            {0,0,1}
        }};
    }

    static Mat3 rotation(float angle) {
        return {{
            {cos(angle), -sin(angle), 0},
            {sin(angle),  cos(angle), 0},
            {0,           0,          1}
        }};
    }

    static Mat3 translation(float tx, float ty) {
        return {{
            {1, 0, 0},
            {0, 1, 0},
            {tx, ty, 1}
        }};
    }

    static Mat3 scale(float s) {
        return {{
            {s, 0, 0},
            {0, s, 0},
            {0, 0, 1}
        }};
    }

    Mat3 operator*(const Mat3& other) const {
        Mat3 result = {};
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                for (int k = 0; k < 3; ++k)
                    result.m[i][j] += m[i][k] * other.m[k][j];
        return result;
    }

    Vec3 operator*(const Vec3& v) const {
        Vec3 result = {0,0,0};
        for (int j = 0; j < 3; ++j)
            for (int k = 0; k < 3; ++k)
                result[j] += v[k] * m[k][j];
        return result;
    }
};

vector<Vec3> loadOBJVertices(const string& filename) {
    vector<Vec3> vertices;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << filename << endl;
        return vertices;
    }

    string line;
    while (getline(file, line)) {
        if (line.rfind("v ", 0) == 0) {
            istringstream iss(line);
            char discard;
            float x, y, z;
            iss >> discard >> x >> y >> z;
            vertices.push_back({x, y, 1.0f});
        }
    }

    return vertices;
}

int main() {
    vector<Vec3> vertices = loadOBJVertices("square.obj");

    if (vertices.empty()) {
        cerr << "nema loadnato" << endl;
        return 1;
    }

    Mat3 transform =
        Mat3::rotation(M_PI / 4) *
        Mat3::translation(2.0f, 0.0f) *
        Mat3::scale(4.0f);

    for (const auto& v : vertices) {
        Vec3 result = transform * v;
        cout << result[0] << " "
             << result[1] << " "
             << result[2] << endl;
    }

    return 0;
}