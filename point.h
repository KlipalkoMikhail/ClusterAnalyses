#ifndef POINT_H
#define POINT_H
class Point
{
    private:
        double x;
        double y;
        int NP;
        int colour;

    public:
        Point();
        Point(const Point& point);
        Point(double x, double y);
        void setx(double x1);
        void sety(double x2);
        void setnp(int np);
        void setc(int c);
        double getx() const;
        double gety() const;
        int getNP() const;
        int getColour() const;
        const Point & operator=(const Point & point);
        ~Point();
};
#endif
