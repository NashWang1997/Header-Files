#ifndef _Ball_h
#define _Ball_h

class IllegalRadius{};
class Ball {
private:
    double radius;
public:
    Ball() {radius = 0;}
    Ball(double r);
    ~Ball() {}
    double area() {return 12.5663704 * radius;}
    double volume() {return 4.18879013 * radius * radius * radius;}
    void set_r(double r);
};
#endif // _Ball_h

Ball::Ball(double r)
{
    if (r < 0) throw IllegalRadius();
    else radius = r;
}
void Ball::set_r(double r)
{
    if (r < 0) throw IllegalRadius();
    else radius = r;
}
