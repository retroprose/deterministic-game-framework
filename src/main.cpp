



#include <SFML/Graphics.hpp>


#include <everything.hpp>






int main() {

    experiment();

    auto const width = 1920, height = 1080;
    sf::RenderWindow window(sf::VideoMode(width, height), "Transformation");
    window.setFramerateLimit(30);

    sf::View view(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));

    sf::Texture texture;
    texture.loadFromFile("D:\\Programming\\C++\\projects\\deterministic-game-framework\\assets\\textures\\invaders.png");

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(100.f, 100.f);
    
    // create the composed transform object
    const sf::Transform transform = [height]{
        sf::Transformable transformation;
        transformation.setOrigin(0, height); // 1st transform
        transformation.setScale(1.f, -1.f);  // 2nd transform
        return transformation.getTransform();
    }();

    sf::RectangleShape rect({15*2, 10*2});
    rect.setOrigin(15, 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();


        sf::Vector2f move(0.0f, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))    {move.y = -1.0f;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))    {move.y =  1.0f;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))    {move.x = -1.0f;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))    {move.x =  1.0f;}
        //position += move;
        view.move(move);
        //view.setCenter(position);

        // update rectangle's position
        //rect.move(0, 1);
        sprite.move(0, 1);

        window.setView(view);

        window.clear();

        rect.setFillColor(sf::Color::Blue);
        rect.setPosition(sprite.getPosition());
        window.draw(rect, transform); 

        //x 173
        //y 219 -> 293
        //w 15
        //h 10

        //sprite.setTextureRect(sf::IntRect(0, 0, sprite.getLocalBounds().getSize().x, sprite.getLocalBounds().getSize().y));
        sprite.setTextureRect(sf::IntRect(173, 293 - 10, 15, 10));
        sprite.setOrigin(15.0f / 2.0f, 10.0f / 2.0f);
        sprite.setScale(2.f, 2.f);
        window.draw(sprite); // no transformation applied

        rect.setFillColor(sf::Color::Red);
        //window.draw(rect, transform); // transformation applied

        //sprite.setTextureRect(sf::IntRect(0, sprite.getLocalBounds().getSize().y, sprite.getLocalBounds().getSize().x, -sprite.getLocalBounds().getSize().y));
        sprite.setTextureRect(sf::IntRect(173, 293 /*- 10*/, 15, -10));
        sprite.setOrigin(15.0f / 2.0f, 10.0f / 2.0f);
        sprite.setScale(2.f, 2.f);
        window.draw(sprite, transform); // transformation applied

        window.display();
    }
}