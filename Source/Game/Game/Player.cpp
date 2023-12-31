#include "Player.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Weapon.h"

void Player::Update(float dt)
{
    // movement
    float rotate = 0;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
    m_transform.rotation += rotate * m_turnRate * kiko::g_time.getDeltaTime();

    float thrust = 0;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
    
    m_transform.position += forward * m_speed * thrust * kiko::g_time.getDeltaTime();

    m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
    m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

    // fire weapon
    if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
    {
        // create weapon
        kiko::Transform transform{ m_transform.position, m_transform.rotation, 1};
        std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>( 400.0f, transform, m_model );
        m_scene->Add(std::move(weapon));
    }
}