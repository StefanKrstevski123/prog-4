#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

void multiplyMatrix(double M[3][3], double v[3], double result[3])
{
    for(int i=0;i<3;i++)
    {
        result[i] = 0;
        for(int j=0;j<3;j++)
        {
            result[i] += M[i][j] * v[j];
        }
    }
}

int main()
{
    ifstream in("monkey.obj");
    ofstream out("rotated_monkey.obj");//nejke da mi go kreira fajlot inace raboti

    double angleX = 30 * M_PI/180.0;
    double angleY = 30 * M_PI/180.0;
    double angleZ = 30 * M_PI/180.0;

    double Rx[3][3] =
    {
        {1,0,0},
        {0,cos(angleX),-sin(angleX)},
        {0,sin(angleX),cos(angleX)}
    };

    double Ry[3][3] =
    {
        {cos(angleY),0,sin(angleY)},
        {0,1,0},
        {-sin(angleY),0,cos(angleY)}
    };

    double Rz[3][3] =
    {
        {cos(angleZ),-sin(angleZ),0},
        {sin(angleZ),cos(angleZ),0},
        {0,0,1}
    };

    string line;

    while(getline(in,line))
    {
        if(line.rfind("v ",0)==0)
        {
            stringstream ss(line);
            char c;
            double x,y,z;

            ss >> c >> x >> y >> z;

            double v[3] = {x,y,z};
            double temp[3];

            multiplyMatrix(Rx,v,temp);
            multiplyMatrix(Ry,temp,v);
            multiplyMatrix(Rz,v,temp);

            out << "v " << temp[0] << " " << temp[1] << " " << temp[2] << endl;
        }
        else
        {
            out << line << endl;
        }
    }

    cout<<"Rotation complete"<<endl;
}