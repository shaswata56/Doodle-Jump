#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <time.h>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}
using namespace sf;

struct point
{
    int x,y;
};

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 533), "Doodle Game!");
    app.setFramerateLimit(90);
    int score=0;
    Texture t1,t2,t3,t4;
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/platform.png");
    t3.loadFromFile("images/doodle.png");
    t4.loadFromFile("images/over.png");

    Sprite sBackground(t1), sPlat(t2), sPers(t3), sOver(t4);

    point plat[20];

    for (int i=0;i<10;i++)
      {
       plat[i].x=rand()%400;
       plat[i].y=rand()%533;
      }

	int x=100,y=100,h=200;
    float dy=0;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

    if (Keyboard::isKeyPressed(Keyboard::Right)) x+=3;
    if (Keyboard::isKeyPressed(Keyboard::Left)) x-=3;

    dy+=0.2;
    y+=dy;
    if (y>500)
    {
        //app.draw(sOver);
        Text text;
        Font font;
        font.loadFromFile("arial.ttf");
        text.setFont(font);
        text.setString("\n            GAME OVER!!!\n           Press R to Restart\n         Press ENTER to Close\n");
        text.setCharacterSize(25);
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold);
        app.draw(text);
        if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Space)) app.close();
        else if(Keyboard::isKeyPressed(Keyboard::R))
        {
            app.close();
            main();
        }
    }
	if (y<h)
    for (int i=0;i<10;i++)
    {
      y=h;
      plat[i].y = plat[i].y - dy;
      if (plat[i].y>533) {plat[i].y=0; plat[i].x=rand()%400;}
    }

	for (int i=0;i<10;i++)
    if ((x+50>plat[i].x) && (x+20<plat[i].x+68) && (y+70>plat[i].y) && (y+70<plat[i].y+14) && (dy>0))
    {
        score++;
        dy=-10;
    }
    Text text;
        Font font;
        font.loadFromFile("arial.ttf");
        text.setFont(font);
        std::string str_score = "SCORE:" + patch::to_string(score);
        text.setString(str_score);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        text.setStyle(sf::Text::Bold);
        app.draw(text);
	sPers.setPosition(x,y);
    app.draw(sBackground);
    app.draw(sPers);
    for (int i=0;i<10;i++)
    {
    sPlat.setPosition(plat[i].x,plat[i].y);
    app.draw(sPlat);
    }
    app.display();
}

    return 0;
}
