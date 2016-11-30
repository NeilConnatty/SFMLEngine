//
// Created by Neil Connatty on 2016-11-27.
//

#include "application.h"
#include "states/state.h"

sf::Time application::TIME_PER_FRAME = sf::seconds(1.f/60.f);

application::application () :
        m_window(sf::VideoMode(640, 480), "SFML Application"),
        m_player(),
        m_fonts(),
        m_textures(),
        m_context(m_window, m_textures, m_fonts, m_player),
        m_stack(m_context),
        m_statisticsText(),
        m_statisticsTimeUpdate(),
        m_statisticsNumFrames(0)
{
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
            if (!m_isPaused)
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
    m_stack.register_state(states::TITLE);
    m_stack.register_state(states::MENU);
    m_stack.register_state(states::GAME);
    m_stack.register_state(states::PAUSE);
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
}

void application::process_input ()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        m_stack.handle_event(event);

        switch (event.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::GainedFocus:
                m_isPaused = false;
                break;
            case sf::Event::LostFocus:
                m_isPaused = true;
                break;
        }
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