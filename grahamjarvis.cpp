#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

struct Point
{
    double x, y;
};

Point p0;

double distSq(Point a, Point b)
{
    return (a.x - b.x) * (a.x - b.x) +
           (a.y - b.y) * (a.y - b.y);
}

// 0 = kolinearni
// 1 = clockwise
// 2 = counterclockwise
int orientation(Point a, Point b, Point c)
{
    double val = (b.y - a.y) * (c.x - b.x) -
                 (b.x - a.x) * (c.y - b.y);

    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// GRAHAM SCAN

bool comparePoints(Point a, Point b)
{
    int o = orientation(p0, a, b);

    if (o == 0)
        return distSq(p0, a) < distSq(p0, b);

    return (o == 2);
}

vector<Point> grahamScan(vector<Point> points)
{
    int n = points.size();

    if (n < 3) return {};

    // Najdolna tocka
    int ymin = 0;

    for (int i = 1; i < n; i++)
    {
        if (points[i].y < points[ymin].y ||
           (points[i].y == points[ymin].y &&
            points[i].x < points[ymin].x))
        {
            ymin = i;
        }
    }

    swap(points[0], points[ymin]);
    p0 = points[0];

    sort(points.begin() + 1, points.end(), comparePoints);

    stack<Point> st;

    st.push(points[0]);
    st.push(points[1]);
    st.push(points[2]);

    for (int i = 3; i < n; i++)
    {
        while (st.size() > 1)
        {
            Point top = st.top();
            st.pop();

            Point next = st.top();

            if (orientation(next, top, points[i]) != 1)
            {
                st.push(top);
                break;
            }
        }

        st.push(points[i]);
    }

    vector<Point> hull;

    while (!st.empty())
    {
        hull.push_back(st.top());
        st.pop();
    }

    return hull;
}

// JARVIS MARCH

vector<Point> jarvisMarch(vector<Point> points)
{
    int n = points.size();

    if (n < 3) return {};

    vector<Point> hull;

    int leftMost = 0;

    for (int i = 1; i < n; i++)
    {
        if (points[i].x < points[leftMost].x)
            leftMost = i;
    }

    int p = leftMost, q;

    do
    {
        hull.push_back(points[p]);

        q = (p + 1) % n;

        for (int i = 0; i < n; i++)
        {
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        }

        p = q;

    } while (p != leftMost);

    return hull;
}

int main()
{
    srand(time(0));

    vector<Point> points;

    int N = 500000;

    // Generiranje 500000 tocki
    for (int i = 0; i < N; i++)
    {
        Point p;
        p.x = rand() % 1000000;
        p.y = rand() % 1000000;

        points.push_back(p);
    }

    cout << "Generirani " << N << " tocki.\n\n";


    // Graham Scan

    auto start1 = high_resolution_clock::now();

    vector<Point> hull1 = grahamScan(points);

    auto end1 = high_resolution_clock::now();

    auto time1 =
        duration_cast<milliseconds>(end1 - start1);


    // Jarvis March

    auto start2 = high_resolution_clock::now();

    vector<Point> hull2 = jarvisMarch(points);

    auto end2 = high_resolution_clock::now();

    auto time2 =
        duration_cast<milliseconds>(end2 - start2);

    // Rezultati

    cout << "GRAHAM SCAN:\n";
    cout << "Vreme: " << time1.count() << " ms\n";
    cout << "Hull points: " << hull1.size() << "\n\n";

    cout << "JARVIS MARCH:\n";
    cout << "Vreme: " << time2.count() << " ms\n";
    cout << "Hull points: " << hull2.size() << "\n\n";

    if (time1 < time2)
        cout << "Pobrzo raboti Graham Scan.\n";
    else
        cout << "Pobrzo raboti Jarvis March.\n";

    return 0;
}