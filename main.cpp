//Created by Grecu Narcis

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define maxTries 50000

using namespace sf;
using namespace std;

RenderWindow window(VideoMode(800, 600), "Random Non Overlaping Circles!");


struct Circle {
	double x;
	double y;
	double r;
};


void setup() {
	window.clear(Color(112, 167, 255));
	window.setFramerateLimit(120);

	srand(time(0));
}


double distance(double x1, double y1, double x2, double y2) {
	return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
} //returns the distance between two points


bool doOverlap(Circle c, vector<Circle> circles) {
	for (int i = 0; i < circles.size(); i++) {
		if (distance(c.x, c.y, circles[i].x, circles[i].y) <= (c.r + circles[i].r)) {
			return 1;
		}
	}

	return 0;
} //checks if current circle overlap with previous generated circles


bool isInWindow(Circle circle) {
	int width = window.getSize().x;
	int height = window.getSize().y;

	if (circle.x - circle.r >= 0 && circle.x + circle.r < width && circle.y - circle.r >= 0 && circle.y + circle.r < height)
		return 1;

	return 0;
} //checks if current circles has every point of in inside the window


Circle generateCircle() {
	int width = window.getSize().x, height = window.getSize().y;
	Circle circle;
	circle.x = rand() % width;
	circle.y = rand() % height;
	circle.r = rand() % 25 + 15;

	return circle;
} //generate a random circle which has center at x (between 0, width-1) and y (between 0, height-1) and a radius between 15 and 24


void drawCircles(vector<Circle> circles) {
	CircleShape circle;
	circle.setFillColor(Color(255, 0, 251, 150));

	for (int i = 0; i < circles.size(); i++) {
		circle.setPosition(Vector2f(circles[i].x - circles[i].r, circles[i].y - circles[i].r));
		circle.setRadius(circles[i].r);
		window.draw(circle);
	}		
} //draw all the circles


int main() {
	setup();

	int protection = 0; //we use protection to know when to stop

	vector<Circle> circles;
	Circle circle;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		if (protection < maxTries) {
			circle = generateCircle();
			protection++;
		}

		if (doOverlap(circle, circles) == 0 && isInWindow(circle)) {
			circles.push_back(circle);
			drawCircles(circles);
			protection = 0;

			window.clear(Color(112, 167, 255));
			drawCircles(circles);
			window.display();
		}
		
		//if we generated 'maxTries' circles and no one is good then we should stop because is a small chance the 'maxTries + 1' circle to be good
		if (protection == maxTries) {
			cout << "Finished!";
			protection++;
		}
	}
	
	return 0;
}
