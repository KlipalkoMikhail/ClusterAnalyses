#ifndef POINT_H
#define POINT_H
class Point
{
    double x;
    double y;
    int NP;
    int colour;

    public:

    Point();
    Point(double x1, double y1, int NP1, int colour1);
    void setx(double x1);
    void sety(double x2);
    void setnp(int np);
    void setc(int c);
    double getx() const;
    double gety() const;
    int getNP() const;
    int getcolour() const;
    const Point & operator=(const Point & point);
    ~Point();
};
#endif
