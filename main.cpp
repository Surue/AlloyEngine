
#include <SFML/Graphics.hpp>
#include <vector.h>

#include <log.h>

int main() {

    alloy::fvec2 v1;

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    using namespace alloy;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        std::string s = "Salut";
    	debug::Log("ICI" + std::to_string(3) + " voilà ça marche");
        debug::LogWarning("Warning");
        debug::LogError("Error");
    	debug::Log(s);

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
