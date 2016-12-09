//
// Created by Neil Connatty on 2016-11-27.
//

#include <states/title_state.h>
#include <states/menu_state.h>
#include <states/game_state.h>
#include <states/pause_state.h>
#include <states/loading_state.h>
#include <states/settings_state.h>
#include "application.h"
#include "states/state.h"
#include "state_stack.h"

sf::Time application::TIME_PER_FRAME = sf::seconds(1.f/60.f);

application::application () :
        m_window(sf::VideoMode(640, 480), "SFML Application"),
        m_player(),
        m_fonts(),
        m_textures(),
        m_stack(state::context(m_window, m_textures, m_fonts, m_player)),
        m_statisticsText(),
        m_statisticsTimeUpdate(),
        m_statisticsNumFrames(0)
{
    m_window.setKeyRepeatEnabled(false);

    load_textures();
    load_fonts();

    m_statisticsText.setFont(m_fonts.get(fonts::DEFAULT));
    m_statisticsText.setPosition(5.f, 5.f);
    m_statisticsText.setCharacterSize(10u);

    register_states();
    m_stack.push_state(states::TITLE);
}

void application::run ()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (m_window.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= TIME_PER_FRAME;

            process_input();
            update(TIME_PER_FRAME);

            if (m_stack.is_empty())
                m_window.close();
        }

        update_statistics(elapsedTime);
        render();
    }
}

void application::register_states ()
{
    m_stack.register_state<title_state>(states::TITLE);
    m_stack.register_state<menu_state>(states::MENU);
    m_stack.register_state<game_state>(states::GAME);
    m_stack.register_state<pause_state>(states::PAUSE);
    m_stack.register_state<loading_state>(states::LOADING);
    m_stack.register_state<settings_state>(states::SETTINGS);
}

void application::load_textures ()
{
    std::string path(PATH_TO_PROJECT_ROOT);
    m_textures.load(textures::EAGLE, path.append("assets/textures/Eagle.png"));
    path.assign(PATH_TO_PROJECT_ROOT);
    m_textures.load(textures::RAPTOR, path.append("assets/textures/Raptor.png"));
    path.assign(PATH_TO_PROJECT_ROOT);
    m_textures.load(textures::DESERT, path.append("assets/textures/Desert.png"));
    path.assign(PATH_TO_PROJECT_ROOT);
    m_textures.load(textures::TITLE_SCREEN, path.append("assets/textures/TitleScreen.png"));
    path.assign(PATH_TO_PROJECT_ROOT);
    m_textures.load(textures::BUTTON_NORMAL, path.append("assets/textures/ButtonNormal.png"));
    path.assign(PATH_TO_PROJECT_ROOT);
    m_textures.load(textures::BUTTON_PRESSED, path.append("assets/textures/ButtonPressed.png"));
    path.assign(PATH_TO_PROJECT_ROOT);
    m_textures.load(textures::BUTTON_SELECTED, path.append("assets/textures/ButtonSelected.png"));
}

void application::load_fonts ()
{
    std::string path(PATH_TO_PROJECT_ROOT);
    m_fonts.load(fonts::DEFAULT, path.append("assets/Sansation.ttf"));
}

void application::process_input ()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        m_stack.handle_event(event);

        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}

void application::update (sf::Time dt)
{
    m_stack.update(dt);
}

void application::render ()
{
    m_window.clear();

    m_stack.draw();

    m_window.setView(m_window.getDefaultView());
    m_window.draw(m_statisticsText);

    m_window.display();
}

void application::update_statistics(sf::Time deltaTime)
{
    m_statisticsTimeUpdate += deltaTime;
    m_statisticsNumFrames += 1;

    if (m_statisticsTimeUpdate >= sf::seconds(1.f))
    {
        m_statisticsText.setString("FPS: " + std::to_string(m_statisticsNumFrames));

        m_statisticsTimeUpdate -= sf::seconds(1.f);
        m_statisticsNumFrames = 0;
    }
}