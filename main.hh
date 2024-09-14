#pragma once

#include "psyqo/application.hh"
#include "psyqo/font.hh"
#include "psyqo/simplepad.hh"
#include "psyqo/scene.hh"

class App final : public psyqo::Application {
    // These two methods are called by the PSYQo framework.
    void prepare() override;
    void createScene() override;

    // We keep track of how many times we've been called to
    // avoid initializing the hardware multiple times.
    bool m_initialized = false;

  public:
    psyqo::Color getBlink(unsigned scale = 1);

    // We're going to use the SimplePad interface to handle the input.
    psyqo::SimplePad m_input;
    // The font renderer. We instantiate it with the defaut amount of
    // fragments, but we're not actually using that many.
    psyqo::Font<> m_font;

    psyqo::Color c;

  private:
    // The global timer used by the mod player.
    unsigned m_musicTimer;
};

// We're only going to use a single global to hold everything. It'll
// be defined in tetris.cpp, and this is its definition for all the
// other modules in this project.
extern App g_app;

class AScene final : public psyqo::Scene {
    void frame() override;

    // We'll have some simple animation going on, so we
    // need to keep track of our state here.
    uint8_t m_anim = 0;
    bool m_direction = true;
};

extern AScene g_scene;