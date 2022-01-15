#include <iostream>
#include <string.h>
#include <unistd.h>
#include <SFML/Graphics.hpp>

//That's a simple functon that converts a char array into a string
std::string conv_str(char* arr, int length)
{
    std::string str = "";
    for (int i = 0; i < length; i++) str = str + arr[i];
    return str;
}

int main(int argc, char* argv[])
{
    //Creating some important values
    //The reason cells_height is 3/4 of the height, is because I want the cells to occupy 3/4 of the screen
    int height = sf::VideoMode::getDesktopMode().height, width = sf::VideoMode::getDesktopMode().width, cells_height = height*3/4, n, curr_cell = 0;

    bool left_held, right_held, up_held, down_held;

    //By default, the amount of cells will be 4, but if a second argument is given, the amount of cells will be set to that
    if(argc < 2)
    {
        std::cout << "No amount of cells given! Defaulting to 4." << std::endl;
        n = 4;
    }
    else n = stoi(conv_str(argv[1], sizeof(argv[1])));

    //This line simply creates the array of the size defined earlier
    bool cells[n] = {};

    //SFML stuff begins

    //Free anti-aliasing lol
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //Creates the actual window
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Turing Machine", sf::Style::Fullscreen, settings);

    //Despite a lot of rectangles being visible on the screen, we can just make one object and then draw it many times, which takes less memory
    //The 50.0f, 50.0f doesn't actually matter, these are random default values I put there
    sf::RectangleShape cell(sf::Vector2f(50.0f, 50.0f));

    //Loads the arial font from arial.ttf, if the loading did not end successfully, it displays an error and returns -1
    sf::Font arial;
    if(!arial.loadFromFile("arial.ttf"))
    {
        std::cout << "Font not found! Make sure arial.ttf is in the same folder as the executable file." << std::endl;
        return -1;
    }

    //This line creates the text value we will use for holding the current value of the text
    //Akin to the RectangleShape, we only need one Text, as we can use re-use it
    sf::Text cell_value;

    cell_value.setFont(arial); //Arial is the font I want to use
    cell_value.setString("0"); //By default, the value is set to 0
    cell_value.setCharacterSize(width/sizeof(cells)); //This makes the font size appropriate (regarding the amount of cells)
    cell_value.setFillColor(sf::Color(0x787878FF)); //This sets the color of the text
    cell_value.setStyle(sf::Text::Bold); //In my opinion, GUI-wise, bold text looks way better
    cell_value.setOrigin(sf::Vector2f(0, cells_height)); //Sets the origin position of the cell_value text

    //Creates the pointer object
    sf::CircleShape pointer(32, 3);
    //This sets the color
    pointer.setFillColor(sf::Color(0x787878FF));
    //Sets the default position
    pointer.setPosition(sf::Vector2f(width/sizeof(cells), 250.0f));
    //This flips the triangle
    pointer.setRotation(180);
    //This makes the scale of the pointer appropriate to the amount of cells
    pointer.setScale(sf::Vector2f(32.0f/sizeof(cells), 5.0f));

    //Here I create the text for the TRUE in the "check" mechanic
    sf::Text true_val;

    true_val.setFont(arial);
    true_val.setString("TRUE");
    true_val.setCharacterSize(200);
    //GREEN
    true_val.setFillColor(sf::Color(0x4EF542FF));
    true_val.setStyle(sf::Text::Bold);
    true_val.setPosition(sf::Vector2f(600.0f, 0.0f));

    //Here I create the text for the FALSE in the "check" mechanic
    sf::Text false_val;

    false_val.setFont(arial);
    false_val.setString("FALSE");
    false_val.setCharacterSize(200);
    //RED
    false_val.setFillColor(sf::Color(0xF54242FF));
    false_val.setStyle(sf::Text::Bold);
    false_val.setPosition(sf::Vector2f(600.0f, 0.0f));

    while (window.isOpen())
    {
        //In short: if closing is requested, close
        //Deleting this causes the app to be uncloseable, highly disrecommended...
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Clears the window with one of the 50 shades of grey
        window.clear(sf::Color(0x181A1BFF));

        //This sets up the cell color, outline, origin position and the fill color (which is actually just transparency)
        cell.setOrigin(sf::Vector2f(0, cells_height));
        cell.setFillColor(sf::Color::Transparent);
        cell.setOutlineColor(sf::Color(0x787878FF));
        cell.setOutlineThickness(3);

        //This is the drawing of the first cell, which is slightly repositioned, thus, out of the main cell-drawing for loop
        //That's why the main cell-drawing loop starts with "1" instead of "0"
        cell.setSize(sf::Vector2f(width/sizeof(cells)-3, cells_height));
        cell.setPosition(sf::Vector2f(3, height-3));
        window.draw(cell);

        //The follow line sets the correct size
        cell.setSize(sf::Vector2f(width/sizeof(cells), cells_height));
        //This is the main loop for displaying all of the cells
        //It's fairly simple, it draws a cell for every point in the array
        //The starting x position is determined by a simple formula I came up with: starting x position = current cell number/amount of cells
        for(int i = 1; i < sizeof(cells)-1; i++)
        {
            //The formula is visible in this line
            cell.setPosition(sf::Vector2f((width*i/sizeof(cells)), height-3));
            window.draw(cell);
        }

        //There was a reason the previous loop had "i < sizeof(cells)-1"
        //The reason for the -1 is that the last cell is also slightly repositioned to not go out of the screen, just like the first one

        cell.setSize(sf::Vector2f(width/sizeof(cells)-3, cells_height));
        //This line uses a slightly different formula
        //First of all, since this is the last cell, we know the cell number is sizeof(cells)-1
        //We would end up with something like: width*(sizeof(cells)-1)/sizeof(cells)
        //But this can be easily simplified with algebra to: width - width/sizeof(cells)
        cell.setPosition(sf::Vector2f(width - width/sizeof(cells), height-3));
        window.draw(cell);

        //The following loop prints all of the cell values similar to the cells
        for(int i = 0; i < sizeof(cells); i++)
        {
            //This if-else statement sets the cell_value to the actual value in the cell
            if(!cells[i]) cell_value.setString("0");
            else cell_value.setString("1");

            //The if-else statement here adjusts the height depending on the amount of cells
            //The rest over here should be understandable, as its similar to displaying the cells
            if(sizeof(cells) == 1)
            {
                //The only difference is this statement which simply returns -1 if we try to create a one-cell machine
                std::cout << "One cell not allowed!" << std::endl;
                return -1;
            }
            else if(sizeof(cells) < 3)
            {
                cell_value.setPosition(sf::Vector2f((width*i/sizeof(cells))+width/sizeof(cells)/sizeof(cells), height-200));
                window.draw(cell_value);
            }
            else if(sizeof(cells) < 5)
            {
                cell_value.setPosition(sf::Vector2f((width*i/sizeof(cells))+width/sizeof(cells)/sizeof(cells), height+75));
                window.draw(cell_value);
            }
            else if(sizeof(cells) < 9)
            {
                cell_value.setPosition(sf::Vector2f((width*i/sizeof(cells))+width/sizeof(cells)/sizeof(cells), height+250));
                window.draw(cell_value);
            }
            else
            {
                cell_value.setPosition(sf::Vector2f((width*i/sizeof(cells))+width/sizeof(cells)/sizeof(cells), height+300));
                window.draw(cell_value);
            }
        }


        //Pretty simple, decreases the curr_cell when the left arrow key is pressed
        //It also has a simple holding system, so it doesn't decrease the cell every frame, but rather, every time the user starts holding the button
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            if(!left_held)
            {
                //If the current cell is 0, it doesn't do anything, that's because we don't want to go off-screen
                if(!(curr_cell == 0)) curr_cell--;
                left_held = true;
            }
        }
        else
        {
            left_held = false;
        }

        //This is pretty similar to the previous statement
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            if(!right_held)
            {
                //We don't want to get off-screen here either, so it checks if the current cell is sizeof(cells)-1, and it if is, it won't do anything
                if(!(curr_cell == sizeof(cells)-1)) curr_cell++;
                right_held = true;
            }
        }
        else
        {
            right_held = false;
        }

        //Simple mechanisms that change the current cell to true or false depending on what is pressed
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            if(!up_held)
            {
                cells[curr_cell] = true;
                up_held = true;
            }
        }
        else
        {
            up_held = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            if(!down_held)
            {
                cells[curr_cell] = false;
                down_held = true;
            }
        }
        else
        {
            down_held = false;
        }

        pointer.setPosition(sf::Vector2f((width/sizeof(cells))*(curr_cell+1), 250.0f)); //this makes the pointer's position accurate to the current cell chosen
        window.draw(pointer); //This simply draws the virtual pointing device onto the screen

        //NULL CHECK
        //This shows "true" if the current cell value is 0, and "false" if it's 1
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        {
            if(cells[curr_cell] == false) window.draw(true_val);
            else window.draw(false_val);
        }

        //The following statement does pretty much the opposite of what was described about the previous one
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
        {
            if(cells[curr_cell] == true) window.draw(true_val);
            else window.draw(false_val);
        }

        //The reason for this line is SFML's double-buffering
        //You can search up on what is double-buffering if you don't know what it is
        window.display();
    }

    return 0;
}