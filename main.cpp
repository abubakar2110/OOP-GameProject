#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

class Platform
{
public:
    int x, y;
    Sprite sprite;

    Platform(Texture& t)
    {
        sprite.setTexture(t);
        x = rand() % 400;
        y = rand() % 533;
        sprite.setPosition(x, y);
    }

    void update(float dy)
    {
        y -= dy;
        if (y > 533)
        {
            y = 0;
            x = rand() % 400;
        }
        sprite.setPosition(x, y);
    }
};

class Player
{
public:
    int x, y, h;
    float dx, dy;
    Sprite sprite;

    Player(Texture& t)
    {
        sprite.setTexture(t);
        x = 100;
        y = 100;
        h = 200;
        dx = 0;
        dy = 0;
        sprite.setPosition(x, y);
    }

    void update()
    {
        dy += 0.2;
        y += dy;
        if (y > 500) dy = -10;
        if (Keyboard::isKeyPressed(Keyboard::Right)) x += 3;
        if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 3;

        if (x > 400) x = 0;
        if (x < 0) x = 400;

        sprite.setPosition(x, y);
    }

    void checkCollision(Platform* plat)
    {
        for (int i = 0; i < 10; i++)
            if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
                && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0)) dy = -10;
    }
};

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 533), "Doodle Game!");
    app.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/platform.png");
    t3.loadFromFile("images/doodle.png");

    Sprite sBackground(t1);
    Platform platforms[10] = { t2, t2, t2, t2, t2, t2, t2, t2, t2, t2 };
    Player player(t3);

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

        player.update();
        player.checkCollision(platforms);

        if (player.y < player.h)
        {
            for (int i = 0; i < 10; i++)
            {
                player.y = player.h;
                platforms[i].update(player.dy);
            }
        }

        app.clear();
        app.draw(sBackground);
        app.draw(player.sprite);
        for (int i = 0; i < 10; i++)
        {
            app.draw(platforms[i].sprite);
        }
        app.display();
    }

    return 0;
}
