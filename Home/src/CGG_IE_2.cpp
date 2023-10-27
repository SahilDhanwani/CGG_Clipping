#include <bits/stdc++.h>
#include <graphics.h>
using namespace std;

char data[] = "C:\\MinGW\\lib\\libbgi.a";
int gd = DETECT, gm;

class line_
{
public:
    int x1, y1, c1, x2, y2, c2;
    void set(int a, int b, int c, int d)
    {
        x1 = a;
        y1 = b;
        c1 = 0;
        x2 = c;
        y2 = d;
        c2 = 0;
    }
};

vector<line_> take_input_object()
{
    vector<line_> v;
    
    line_ l1;

    // Part 3 :
    l1.set(140, 200, 200, 150); v.push_back(l1);
    l1.set(250, 200, 140, 200); v.push_back(l1);
    l1.set(200, 150, 250, 200); v.push_back(l1);

    // Part 1 :
    l1.set(140, 330, 140, 200); v.push_back(l1);
    l1.set(250, 200, 250, 330); v.push_back(l1);

    // Part 6 :
    l1.set(200, 150, 350, 150); v.push_back(l1);
    l1.set(350, 150, 400, 200); v.push_back(l1);
    l1.set(250, 200, 400, 200); v.push_back(l1);

    // Part 5 :
    l1.set(400, 200, 400, 330); v.push_back(l1);
    l1.set(140, 330, 400, 330); v.push_back(l1);

    // Part 2 :
    l1.set(170, 260, 170, 330); v.push_back(l1);
    l1.set(170, 260, 210, 260); v.push_back(l1);
    l1.set(210, 260, 210, 330); v.push_back(l1);

    // Part 7 :
    l1.set(300, 250, 350, 250); v.push_back(l1);
    l1.set(300, 280, 350, 280); v.push_back(l1);
    l1.set(300, 280, 300, 250); v.push_back(l1);
    l1.set(350, 280, 350, 250); v.push_back(l1);
    return v;
}

vector<line_> take_input_window()
{
    vector<line_> v;
    line_ l1;

    l1.set(100, 100, 100, 300); v.push_back(l1);
    l1.set(100, 300, 325, 300); v.push_back(l1);
    l1.set(325, 300, 325, 100); v.push_back(l1);
    l1.set(325, 100, 100, 100); v.push_back(l1);
    return v;
}

void clip_algo(int &x1, int &y1, int &x2, int &y2, int xmin, int ymin, int xmax, int ymax)
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

void flood_fill_algo(int x1, int y1, int color)
{
    if (getbkcolor() != getpixel(x1, y1)) return;
    putpixel(x1, y1, color);
    flood_fill_algo(x1 - 1, y1, color);
    flood_fill_algo(x1 + 1, y1, color);
    flood_fill_algo(x1, y1 - 1, color);
    flood_fill_algo(x1, y1 + 1, color);
}

void draw_poly(vector<line_> v,int time = 0, int xmin = 0, int ymin = 0, int xmax = 640, int ymax = 480)
{
    for (int i = 0; i < v.size(); i++)
    {
        int x1 = v[i].x1;
        int y1 = v[i].y1;
        int x2 = v[i].x2;
        int y2 = v[i].y2;

        delay(time);
        clip_algo(x1, y1, x2, y2, xmin, ymin, xmax, ymax);
    }
}

int main()
{
    vector<line_> v1;
    v1 = take_input_object();

    initgraph(&gd, &gm, data);
    draw_poly(v1,100);
    circle(196, 180, 15); //part 4

    flood_fill_algo(150,210,1);
    flood_fill_algo(180,270,2);
    flood_fill_algo(200,160,3);
    flood_fill_algo(196,180,4);
    flood_fill_algo(260,250,5);
    flood_fill_algo(320,175,6);
    flood_fill_algo(320,260,7);

    getch();

    vector<line_> v2;
    v2 = take_input_window();
    draw_poly(v2,100);

    getch();
    closegraph();

    initgraph(&gd, &gm, data);
    draw_poly(v1,100,v2[0].x1, v2[0].y1, v2[1].x2, v2[1].y2);
    circle(196, 180, 15); //part 4
    draw_poly(v2,100); 

    flood_fill_algo(150,210,1);
    flood_fill_algo(180,270,2);
    flood_fill_algo(200,160,3);
    flood_fill_algo(196,180,4);
    flood_fill_algo(260,250,5);
    flood_fill_algo(320,175,6);
    flood_fill_algo(320,260,7);
    
    getch();
    closegraph();
    return 0;
}