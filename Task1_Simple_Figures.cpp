#include <iostream>
#include <vector>
#include <cmath>

constexpr double PI{ 3.14159265359 };

enum class Angle {
	RADIAN,
	DEGREE
};

// Point class
class Point {
private:
	double pos_x;
	double pos_y;

public:
	Point(double x, double y) : pos_x{ x }, pos_y{ y }
	{
	}

	Point& Move(double horizontal, double vertical) {
		pos_x += horizontal;
		pos_y += vertical;

		return *this;
	}

	Point& Rotate(double angle, Angle angleType = Angle::RADIAN) {

		if (angleType == Angle::DEGREE) {
			angle = angle * PI / 180.0;
		}

		double newX = pos_x * cos(angle) - pos_y * sin(angle);
		double newY = pos_x * sin(angle) - pos_y * cos(angle);

		pos_x = newX;
		pos_y = newY;

		return *this;
	}

	void SetX(double x) {
		pos_x = x;
	}

	double GetX() {
		return pos_x;
	}

	void SetY(double y) {
		pos_y = y;
	}

	double GetY() {
		return pos_y;
	}

	void PrintPoint() {
		std::cout << "x: " << pos_x << " y: " << pos_y << std::endl;
	}
};

// Line class
class Line {
private:
	Point startPoint;
	Point endPoint;

public:
	Line(Point start, Point end) : startPoint{ start }, endPoint{ end } {
	}

	Line& Move(double horizontal, double vertical) {
		startPoint.Move(horizontal, vertical);
		endPoint.Move(horizontal, vertical);

		return *this;
	}

	Line& Rotate(double angle, Angle angleType = Angle::RADIAN) {
		startPoint.Rotate(angle, angleType);
		endPoint.Rotate(angle, angleType);

		return *this;
	}

	void PrintLine() {
		std::cout << "Starting Point:\n";
		startPoint.PrintPoint();
		std::cout << "End Point:\n";
		endPoint.PrintPoint();
	}
};

// Circle class
class Circle {
private:
	Point center;
	double radius;

public:
	Circle(Point ctr, double rad) : center{ ctr }, radius{ rad } {
	}

	Circle& Move(double horizontal, double vertical) {
		center.Move(horizontal, vertical);

		return *this;
	}

	Circle& Rotate(double angle, Angle angleType = Angle::RADIAN) {
		center.Rotate(angle, angleType);

		return *this;
	}

	void PrintCircle() {
		center.PrintPoint();
		std::cout << "radius: " << radius << std::endl;
	}
};

// Aggregation class
class Aggregation {
private:
	std::vector<Point> points;
	std::vector<Line> lines;
	std::vector<Circle> circles;

public:
	Aggregation() = default;

	Aggregation(std::vector<Point> pts, std::vector<Line> lns, std::vector<Circle> crs) 
		: points{ pts }, lines{ lns }, circles{ crs }
	{
	}

	Aggregation& AddPoint(Point point) {
		points.push_back(point);

		return *this;
	}
	
	Aggregation& AddLine(Line line) {
		lines.push_back(line);

		return *this;
	}
	
	Aggregation& AddCircle(Circle circle) {
		circles.push_back(circle);

		return *this;
	}

	Aggregation& Move(double horizontal, double vertical) {
		for (Point& point : points) {
			point.Move(horizontal, vertical);
		}

		for (Line& line : lines) {
			line.Move(horizontal, vertical);
		}

		for (int i{ 0 }; i < circles.size(); i++) {
			circles.at(i).Move(horizontal, vertical);
		}

		return *this;
	}

	Aggregation& Rotate(double angle, Angle angleType = Angle::RADIAN) {
		for (Point& point : points) {
			point.Rotate(angle, angleType);
		}

		for (Line& line : lines) {
			line.Rotate(angle, angleType);
		}

		for (Circle& circle : circles) {
			circle.Rotate(angle, angleType);
		}

		return *this;
	}

	void AggrInfo() {
		std::cout << "Aggregation\n" << "Points: " << points.size() << "\nLines: " << lines.size() << "\nCircles: " << circles.size() << "\n\n";
	}
};

int main() {
	// Usage example
	Point p1(1.0, 2.0);
	Line l1(Point(0.0, 0.0), Point(3.0, 4.0));
	Circle c1(Point(5.0, 5.0), 2.0);

	Aggregation aggr;
	aggr.AddPoint(p1)
		.AddPoint(Point(3.0, 5.0))
		.AddLine(l1)
		.AddCircle(c1)
		.AggrInfo();

	p1.Move(2, 2);
	p1.Rotate(180, Angle::DEGREE);
	p1.PrintPoint();

	std::cout << "\n\n";

	l1.Move(2, 2);
	l1.PrintLine();
	l1.Rotate(180, Angle::DEGREE);
	l1.PrintLine();

	std::cout << "\n\n";

	c1.Move(2, 2);
	c1.PrintCircle();
	c1.Rotate(180, Angle::DEGREE);
	c1.PrintCircle();

	return 0;
}