class Point
{
public:
    int x;
    int y;

    Point();
    Point(int x_val, int y_val);

    void move(int dx, int dy);
    void print() const;
    double distance_to(const Point& other) const;
};