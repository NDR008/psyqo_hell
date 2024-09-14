#include "main.hh"
#include "common/syscalls/syscalls.h"

//namespace {

// A PSYQo software needs to declare one \`Application\` object.
// This is the one we're going to do for our hello world.
App g_app;
AScene scene;

int main() { return g_app.run(); }

void App::prepare() {
    psyqo::GPU::Configuration config;
    config.set(psyqo::GPU::Resolution::W320)
        .set(psyqo::GPU::VideoMode::AUTO)
        .set(psyqo::GPU::ColorMode::C15BITS)
        .set(psyqo::GPU::Interlace::PROGRESSIVE);
    gpu().initialize(config);

    // All of the music is done here, really.
    // This may change later, as the mod player is still a piece of C code
    // that needs to be updated.

    // First, initialize the mod player.
//     MOD_Load(&_binary_musix_oh_amiga_with_effects_hit_start);
//     // Then, create a timer that will play the music.
//     // The internals of the MOD player will give us the number of hblanks
//     // to wait, so we need to convert that to microseconds.
//     m_musicTimer = gpu().armPeriodicTimer(MOD_hblanks * psyqo::GPU::US_PER_HBLANK, [this](uint32_t) {
//         MOD_Poll();
//         // There is no downside in changing the timer every time, in case the
//         // mod player wants to change the timing.
//         gpu().changeTimerPeriod(m_musicTimer, MOD_hblanks * psyqo::GPU::US_PER_HBLANK);
//     });
}

void App::createScene() {
    if (!m_initialized) {
        m_font.uploadSystemFont(gpu());
        m_input.initialize();
        m_initialized = true;
    }
    pushScene(&scene);
    // Our root scene is the splash screen. We'll push it
    // unconditionally.
    // pushScene(&m_splash);
}

void AScene::frame() {
    g_app.gpu().clear();
    // auto& font = g_app.m_font;
    g_app.c = {{.r = 255, .g = 0, .b = 0}};
    g_app.m_input.setOnEvent([this](const psyqo::SimplePad::Event& event) {
        if (event.pad != psyqo::SimplePad::Pad::Pad1) return;
        if (event.type == psyqo::SimplePad::Event::ButtonReleased) {
            switch (event.button) {
                case psyqo::SimplePad::Button::Left:
                    g_app.c = {{.r = 255, .g = 255, .b = 0}};
                case psyqo::SimplePad::Button::Right:
                    g_app.c = {{.r = 255, .g = 0, .b = 255}};
            }
        }
    });

    g_app.m_font.print(g_app.gpu(), "Hello World!", {{.x = 16, .y = 32}}, g_app.c);
    ramsyscall_printf("what");
}