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

#include "system.hpp"

#include <SDL_opengl.h>
#include <assert.h>
#include <stdexcept>
#include <sstream>

System::System() :
  m_screen(0)
{
  srand(time(0));

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::stringstream msg;
    msg << "Couldn't initialize SDL: " << SDL_GetError();
    throw std::runtime_error(msg.str());
  }
  else
  {
    atexit(SDL_Quit);
    SDL_EnableUNICODE(1);
  }
}

System::~System()
{
}

void
System::create_window(int width, int height, bool fullscreen)
{
  assert(!m_screen);

  Uint32 flags = SDL_OPENGL;
  if (fullscreen)
    flags |= SDL_FULLSCREEN;

  m_screen = SDL_SetVideoMode(width, height, 0, flags);

  glOrtho(-width*10, width*10, height*10, -height*10, 1000.0, -1000.0);
}

void
System::swap_buffers()
{
  SDL_GL_SwapBuffers();
}

/* EOF */
