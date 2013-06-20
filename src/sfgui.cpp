#include "sfgui.h"

void Clicky::run()
{

    if (state == "menu")
        menu();
    else if (state == "join")
        join();

    renwin.resetGLStates();
    while (renwin.isOpen())
    {
        while (renwin.pollEvent(event))
        {
            desktop.HandleEvent(event);
            if (event.type == sf::Event::Closed)
            {   
                renwin.close();
            }   
        }

        desktop.Update(clock.restart().asSeconds());

        renwin.clear();
        sfgui.Display(renwin);
        renwin.display();
    } 
}
    
void Clicky::menu()
{
    joinButt(sfg::Widget::OnLeftClick).Connect(&Clicky::onJoinButtClick, this);
    hostButt(sfg::Widget::OnLeftClick).Connect(&Clicky::onHostButtClick, this);
    instructButt(sfg::Widget::OnLeftClick).Connect(&Clicky::onInstructButtClick, this);
    optionsButt(sfg::Widget::OnLeftClick).Connect(&Clicky::onOptionsButtClick, this);

    menuBox->Pack(joinButt, false);
    menuBox->Pack(hostButt, false);
    menuBox->Pack(instructButt, false);
    menuBox->Pack(optionsButt, false);
    desktop.Add(menuBox);
}

void Clicky::join()
{}

//menu
void Clicky::onJoinButtClick()
{
    state = "join";
}

void Clicky::onHostButtClick()
{
    state = "host";
}

/* void onInstructButtClick();
{
    state = "instructions";
}

void onOptionsButtClick();
{
    state = "options";
}   */
