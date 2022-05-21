//  Gravisolar
//  Copyright (C) 2010 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>

#include "game_session.hpp"
#include "world.hpp"
#include "system.hpp"

GameSession::GameSession(System& system, World& world) :
  m_system(system),
  m_world(world),
  m_quit(false),
  m_pause(false),
  m_single_step(false),
  m_forward(true),
  m_camera_pos(0.0f, 0.0f),
  m_camera_stick(0.0f, 0.0f),
  m_camera_zoom(1.0f),
  m_camera_zoom_stick(0.0f),
  m_ship_stick(0.0f, 0.0f)
{
}

void
GameSession::run()
{
  while(!m_quit)
  {
    float delta = 0.05f;
  
    process_input();

    m_camera_pos += 5000.0f * m_camera_stick * (1.0f/m_camera_zoom) * delta;

    if (m_camera_zoom_stick > 0.0f)
      m_camera_zoom *= 1.0f / (1.0f + 0.5f * delta);
    else if (m_camera_zoom_stick < 0.0f)
      m_camera_zoom *= 1.0f + 0.5f * delta;

    if (!m_pause || m_single_step)
    {
      if (m_forward)
        m_world.update(delta);
      else
        m_world.update(-delta);

      m_single_step = false;
    }

    glPushMatrix();
    glScalef(m_camera_zoom, m_camera_zoom, 0.0f);
    glTranslatef(m_camera_pos.x, m_camera_pos.y, 0.0f);
    m_world.draw();
    glPopMatrix();

    m_system.swap_buffers();
  }
}

void
GameSession::process_input()
{
  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_QUIT:
        // FIXME: This should be a bit more gentle, but will do for now
        std::cout << "Ctrl-c or Window-close pressed, game is going to quit" << std::endl;
        m_quit = true;
        break;

      case SDL_KEYDOWN:
      case SDL_KEYUP:
        if (event.key.state)
        {    
          switch (event.key.keysym.sym)
          {
            case SDLK_ESCAPE:
              m_quit = true;
              break;

            case SDLK_SPACE:
              m_world.add_random_objects(100);
              break;

            case SDLK_KP5:
              m_camera_pos  = glm::vec2(0.0f, 0.0f);
              m_camera_zoom = 1.0f;
              break;

            case SDLK_p:
              m_pause = !m_pause;
              break;

            case SDLK_i:
              if (!m_pause) 
                m_pause = true;
              m_single_step = true;
              break;

            case SDLK_f:
              m_forward = !m_forward;
              break;

            default:
              break;
          }
        }
        break;
    }
  }
  
  Uint8* keystate = SDL_GetKeyState(NULL);

  m_camera_stick = glm::vec2(0.0f, 0.0f);

  if (keystate[SDLK_KP4] && !keystate[SDLK_KP6])
    m_camera_stick.x = 1.0f;

  if (keystate[SDLK_KP6] && !keystate[SDLK_KP4])
    m_camera_stick.x = -1.0f;

  if (keystate[SDLK_KP2] && !keystate[SDLK_KP8])  
    m_camera_stick.y = -1.0f;

  if (keystate[SDLK_KP8] && !keystate[SDLK_KP2])  
    m_camera_stick.y = 1.0f;

  m_camera_zoom_stick = 0.0f;
  if (keystate[SDLK_KP_PLUS] && !keystate[SDLK_KP_MINUS])
    m_camera_zoom_stick = -1.0f;

  if (keystate[SDLK_KP_MINUS] && !keystate[SDLK_KP_PLUS])
    m_camera_zoom_stick = 1.0f;


  m_ship_stick = glm::vec2(0.0f, 0.0f);
  if (keystate[SDLK_LEFT] && !keystate[SDLK_RIGHT])
    m_ship_stick.x = 1.0f;

  if (keystate[SDLK_RIGHT] && !keystate[SDLK_LEFT])
    m_ship_stick.x = -1.0f;

  if (keystate[SDLK_UP] && !keystate[SDLK_DOWN])
    m_ship_stick.y = -1.0f;

  if (keystate[SDLK_DOWN] && !keystate[SDLK_UP])
    m_ship_stick.y = 1.0f;
}

/* EOF */
