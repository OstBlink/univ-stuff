#include <iostream>
#include <fstream>

struct rect
{
    std::string width, height, x, y, fill;
    rect(std::string width, std::string height, std::string x, std::string y, std::string fill) : width(width), height(height), x(x), y(y), fill(fill) {}
};

struct ellipse
{
    std::string cx, cy, rx, ry, transform, fill;
    ellipse(std::string cx, std::string cy, std::string rx, std::string ry, std::string transform, std::string fill) : cx(cx), cy(cy), rx(rx), ry(ry), transform(transform), fill(fill) {}
};

struct polygon
{
    std::string points, fill;
    polygon(std::string points, std::string fill) : points(points), fill(fill) {}
};

std::ostream& operator<<(std::ostream& os, const rect& obj) 
{ 
    return os << "<rect width=\"" << obj.width << "\" height=\"" << obj.height << "\" x=\"" << obj.x << "\" y=\"" << obj.y << "\" fill=\"" << obj.fill << "\" /> \n";
} 

std::ostream& operator<<(std::ostream& os, const ellipse& obj) 
{ 
    return os << "<ellipse cx=\"" << obj.cx << "\" cy=\"" << obj.cy << "\" rx=\"" << obj.rx << "\" ry=\"" << obj.ry << "\" transform=\"" << obj.transform << "\" fill=\"" << obj.fill << "\" /> \n";
} 

std::ostream& operator<<(std::ostream& os, const polygon& obj) 
{ 
    return os << "<polygon points=\"" << obj.points << "\" fill=\"" << obj.fill << "\" /> \n";
} 

int main()
{
    rect r1("100", "60", "0", "0", "#e64100");
    ellipse el1("88", "35", "2", "17", "rotate(-13 30 0)", "#3d1100"), el2("90", "21", "1", "1", "", "#3d1100");
    polygon p1("5,30 90,5 98,37 15,55 12,47 70,30 9,40", "#852600");
    
    std::ofstream fout("test.svg");

    fout << "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 100 100\"> \n";
    fout << r1 << p1 << el1 << el2;
    fout << "</svg>";

    fout.close();

    return 0;
}
