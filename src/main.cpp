



#include <everything.hpp>




int main()
{

   

    std::cout << "blah ";


}



/*
#include <iostream>

#include <test.hpp>

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    window.setFramerateLimit(30);

    sf::View view(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
    view.setViewport(sf::FloatRect(0.f, 1.f, 1.f, -1.f));

    sf::VertexArray lines(sf::LinesStrip, 2);
    lines[0].position = sf::Vector2f(10, 10);
    lines[0].color = sf::Color::Red;
    lines[1].position = sf::Vector2f(100, 100);
    lines[1].color = sf::Color::Red;

    std::cout << "starting!";

    sf::Vector2f position(0.f, 0.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
 
        sf::Vector2f move(0.0f, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))    {move.y = -1.0f;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))    {move.y =  1.0f;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))    {move.x = -1.0f;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))    {move.x =  1.0f;}

        position += move;

        view.move(move);
        //view.setCenter(position);

        //lines[0].position = sf::Vector2f(position.x + 10, position.y + 10); 
        //lines[1].position = sf::Vector2f(position.x + 100, position.y + 100);
        
        window.clear();

        window.setView(view);

        window.draw(lines);
        window.display();
    }

    std::cout << "All done!";

    return 0;
}
*/