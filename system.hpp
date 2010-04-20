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

#ifndef HEADER_GRAVISOLAR_SYSTEM_HPP
#define HEADER_GRAVISOLAR_SYSTEM_HPP

#include <SDL.h>

class System
{
private:
  SDL_Surface* m_screen;

public:
  System();
  ~System();

  void create_window(int width, int height, bool fullscreen);
  void swap_buffers();
};

#endif

/* EOF */
