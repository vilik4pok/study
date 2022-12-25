#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#define DEFAULTWIDTH 500
#define DEFAULTHEIGHT 500
#define ANGLE1 5*M_PI/3
#define ANGLE2 M_PI/6
#include <vector>

static SDL_Renderer* renderer;

/*����� �����*/
class Line
{
public:
    /*���������� ������*/
    int x1, x2, y1, y2;
    double angle;
    Line()
    {
        x1=x2=y1=y2=angle=0;
    }
    /*��������� ���������*/
    void setPos(int pos1, int pos2, int pos3, int pos4)
    {
        x1 = pos1;
        x2 = pos2;
        y1 = pos3;
        y2 = pos4;
    }
    /*���������*/
    void draw()
    {
        SDL_RenderDrawLine(renderer, x1, x2, y1, y2);
    }
    /*��� �������*/
    virtual int getType(){return -1;};
};

/*�������������� �����*/
class HortisontalLine : public Line
{
public:
    /*��� �������*/
    int getType(){return 0;}
};

/*������������ �����*/
class VerticalLine : public Line
{
public:
    /*��� �������*/
    int getType(){return 1;}
};

/*��������� �����*/
class ObliqueLine : public Line
{
public:
    /*��� �������*/
    int getType(){return 2;}
};

/*�������� ����� � �����*/
bool lineCircle(double x1, double y1, double x2, double y2, double cx, double cy, double r);
/*�������� ����� � �����*/
bool pointCircle(double px, double py, double cx, double cy, double r);
/*�������� ����� � �����*/
bool linePoint(double x1, double y1, double x2, double y2, double px, double py);
/*���������� ����� �������*/
double dist(double x1,double y1, double x2, double y2);

/*����� ����*/
class Circle
{
public:
    /*angle - ����, ��� ������� �������� ����*/
    double x, y, radius, angle;
    /*lines - ��������� �� ����� ��� �������� ��������*/
    std::vector<Line*> lines;
    Circle(int r, std::vector<Line*> l)
    {
        radius = r;
        angle = 0;
        lines = l;
    }
    /*��������� ��������� �����*/
    void setPos(double posx, double posy)
    {
        x=posx;
        y=posy;
    }
    /*�������� �����*/
    void move()
    {
        x+=cos(angle);
        y-=sin(angle);
        if(angle >= 2*M_PI)
            angle-=2*M_PI;
        if(angle <= -2*M_PI)
            angle+=2*M_PI;
        int count = 0, index, size = lines.size();
        /*������� ���-�� ��������*/
        for(int i=0; i<size; i++)
        {
            if(lineCircle(lines[i]->x1, lines[i]->x2, lines[i]->y1, lines[i]->y2, x, y, radius))
            {
                index = i;
                count++;
            }
        }
        /*���� �������� � ����� ��������, ������ ���� �������� � ����������� �� ���� �����*/
        if(count == 1)
        {
            /*���� �������� � �������������� ������*/
            if(lines[index]->getType()==0)
                angle= -angle + 2*M_PI;
            /*���� �������� � ������������ ������*/
            if(lines[index]->getType()==1)
                angle= -angle + 3*M_PI;
            /*���� �������� � ��������� ������*/
            if(lines[index]->getType()==2)
                angle= -angle + 2*M_PI - 2*lines[index]->angle;
        }
        else if(count>1) /*���� � �����, ������ ���� ����� ��������*/
            angle= angle + M_PI;
    };
    /*��������� ����� �� ������*/
    int draw()
    {
        int offsetx, offsety, d;
        int status;

        offsetx = 0;
        offsety = radius;
        d = radius -1;
        status = 0;

        while (offsety >= offsetx) {
            status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
            status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
            status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
            status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
            status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
            status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
            status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
            status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

            if (status < 0) {
                status = -1;
                break;
            }
            if (d >= 2*offsetx) {
                d -= 2*offsetx + 1;
                offsetx +=1;
            }
            else if (d < 2 * (radius - offsety)) {
                d += 2 * offsety - 1;
                offsety -= 1;
            }
            else {
                d += 2 * (offsety - offsetx - 1);
                offsety -= 1;
                offsetx += 1;
            }
        }
        return status;
    }
};

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_DisplayMode displayMode;
    if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0)
    {
        SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
        return 1;
    }
    int windowPosX = displayMode.w/2-DEFAULTWIDTH/2,windowPosY = displayMode.h/2-DEFAULTHEIGHT/2;
    SDL_Window* window = SDL_CreateWindow("Pr. 5",   windowPosX, windowPosY, DEFAULTWIDTH, DEFAULTWIDTH, 0);
    if (window == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Event windowEvent;

    /*������� ����� ��� �������������*/
    std::vector<Line*> lines;
    lines.push_back(new HortisontalLine());
    lines.push_back(new VerticalLine());
    lines.push_back(new ObliqueLine());
    lines.push_back(new HortisontalLine());
    lines.push_back(new VerticalLine());

    int offsetX = DEFAULTWIDTH*0.1, offsetY = DEFAULTHEIGHT*0.1;
    lines[0]->setPos(offsetX, DEFAULTHEIGHT-offsetY, DEFAULTWIDTH-offsetX, DEFAULTHEIGHT-offsetY);
    lines[1]->setPos(offsetX, offsetY, offsetX, DEFAULTHEIGHT-offsetY);
    lines[2]->setPos(offsetX, offsetY, DEFAULTWIDTH-offsetX, DEFAULTHEIGHT-offsetY);
    /*���� ��������� ������ ��� ���������*/
    lines[2]->angle = M_PI/4;
    lines[3]->setPos(offsetX, offsetY, DEFAULTWIDTH-offsetX, offsetY);
    lines[4]->setPos(DEFAULTWIDTH-offsetX, offsetY, DEFAULTWIDTH-offsetX, DEFAULTHEIGHT-offsetY);
    /*������ �������� ������*/
    Circle c(DEFAULTWIDTH*0.04, lines);
    Circle c2(DEFAULTWIDTH*0.04, lines);
    c.angle = ANGLE1;
    c.setPos(DEFAULTWIDTH-2*offsetX, 2*offsetY);
    c2.angle = ANGLE2;
    c2.setPos(2*offsetX, DEFAULTHEIGHT-2*offsetY);
    int size = lines.size();
    while (true)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for(int i=0; i<size; i++)
            lines[i]->draw();
        c.move();
        c.draw();
        c2.move();
        c2.draw();
        SDL_RenderPresent(renderer);

        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.key.keysym.sym==SDLK_ESCAPE)
                break;
            if (windowEvent.type == SDL_QUIT)
                break;
        }
        SDL_Delay(1);
    }
    for(int i = 0; i<size; i++)
        delete lines[i];
    lines.clear();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}

/*�������� ����� � �����*/
bool lineCircle(double x1, double y1, double x2, double y2, double cx, double cy, double r)
{

    /*���� ����� ����� � ���������� ����, �� ���� �����������*/
    bool inside1 = pointCircle(x1,y1, cx,cy,r);
    bool inside2 = pointCircle(x2,y2, cx,cy,r);
    if (inside1 || inside2) return true;

    /*����� �����*/
    double len = dist(x1, y1, x2, y2);

    double dot = ( ((cx-x1)*(x2-x1)) + ((cy-y1)*(y2-y1)) ) / pow(len,2);

    /*��������� �����*/
    double closestX = x1 + (dot * (x2-x1));
    double closestY = y1 + (dot * (y2-y1));

    /*��������� �� ��������� ����� �� �����*/
    bool onSegment = linePoint(x1,y1,x2,y2, closestX,closestY);
    if (!onSegment) return false;

    /*���� ���������� �� ��������� ����� <= �������, �� ���� �����������*/
    if (dist(closestX, closestY, cx, cy) <= r)
        return true;

    return false;
}

/*�������� ����� � �����*/
bool pointCircle(double px, double py, double cx, double cy, double r)
{
  /*���� ���������� ����� ������ � ������� ����� <= �������, �� ����� ������ �����*/
    if (dist(px, py, cx, cy) <= r)
        return true;
    return false;
}

/*�������� ����� � �����*/
bool linePoint(double x1, double y1, double x2, double y2, double px, double py)
{
    /*���������� �� ����� �� ������ �����*/
    double d1 = dist(px,py, x1,y1);
    double d2 = dist(px,py, x2,y2);
    /*����� �����*/
    double lineLen = dist(x1,y1, x2,y2);
    /*��������� ����, � ������� ����� �����������*/
    double buffer = 0.1;
    /*���� ����� ���������� �������� ��������� � ������ �����, �� ���� �����������*/
    if (d1+d2 >= lineLen - buffer && d1+d2 <= lineLen+buffer)
        return true;
    return false;
}

/*���������� ����� �������*/
double dist(double x1,double y1, double x2, double y2)
{
    double distX = x1 - x2;
    double distY = y1 - y2;
    return sqrt( (distX*distX) + (distY*distY) );
}
