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
#include <iostream>

#include "game_session.hpp"
#include "world.hpp"
#include "system.hpp"

GameSession::GameSession(System& system, World& world) :
  m_system(system),
  m_world(world),
  m_quit(false)
{
}

void
GameSession::run()
{
  while(!m_quit)
  {
    process_input();
    m_world.update(0.05f);
    m_world.draw();
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
          }
        }
        break;
    }
  }
}

/* EOF */
