#include <bits/stdc++.h>
#include <graphics.h>
using namespace std;

int gd = DETECT, gm;
char data[] = "C:\\MinGW\\lib\\libbgi.a";

class line_
{
public:
    int x1, y1, c1, x2, y2, c2;
    line_(int a, int b, int c, int d)
    {
        x1 = a;
        y1 = b;
        c1 = 0;
        x2 = c;
        y2 = d;
        c2 = 0;
    }
};

vector<line_> take_input()
{
    int n;
    cout << "ENTER NO OF LINES: ";
    cin >> n;

    vector<line_> v;
    int a, b, c, d;
    while (n--)
    {
        cout << "Enter the four coordinates: ";
        cin >> a >> b >> c >> d;
        line_ l1(a, b, c, d);
        v.push_back(l1);
    }
    return v;
}

void Sahil_D(int &x1, int &y1, int &x2, int &y2, int xmin, int ymin, int xmax, int ymax)
{
    int code1 = 0, code2 = 0, codeOut;
    bool accept = false, done = false;

    while (!done)
    {
        code1 = 0;
        code2 = 0;

        if (x1 < xmin)
            code1 |= 1;
        if (x1 > xmax)
            code1 |= 2;
        if (y1 < ymin)
            code1 |= 4;
        if (y1 > ymax)
            code1 |= 8;

        if (x2 < xmin)
            code2 |= 1;
        if (x2 > xmax)
            code2 |= 2;
        if (y2 < ymin)
            code2 |= 4;
        if (y2 > ymax)
            code2 |= 8;

        if ((code1 == 0) && (code2 == 0))
        {
            accept = true;
            done = true;
        }
        else if (code1 & code2)
            done = true;

        else
        {
            codeOut = code1 ? code1 : code2;

            double x, y;

            if (codeOut & 8)
            {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            }
            else if (codeOut & 4)
            {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            }
            else if (codeOut & 2)
            {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            }
            else if (codeOut & 1)
            {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (codeOut == code1)
            {
                x1 = x;
                y1 = y;
                code1 = 0;
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = 0;
            }
        }
    }

    if (accept)
        line(x1, y1, x2, y2);
}

void draw_poly(vector<line_> v, int xmin = 0, int ymin = 0, int xmax = 640, int ymax = 480)
{
    for (int i = 0; i < v.size(); i++)
    {
        int x1 = v[i].x1;
        int y1 = v[i].y1;
        int x2 = v[i].x2;
        int y2 = v[i].y2;

        Sahil_D(x1, y1, x2, y2, xmin, ymin, xmax, ymax);
    }
}

int main()
{
    int n;
    vector<line_> v1;
    v1 = take_input();
    initgraph(&gd, &gm, data);
    draw_poly(v1);
    getch();
    closegraph();

    cout << "Now for clipping window: ";
    vector<line_> v2;
    v2 = take_input();
    initgraph(&gd, &gm, data);
    draw_poly(v2);
    draw_poly(v1, v2[0].x1, v2[0].y1, v2[1].x2, v2[1].y2);
    getch();
    closegraph();

    return 0;
}
