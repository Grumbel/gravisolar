//  Gravitation - A simple gravitation toy app
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
#include <stdlib.h>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

#include <glm/vec2.hpp>

#include "system.hpp"
#include "world.hpp"
#include "game_session.hpp"

int main(int argc, char** argv)
{
  try 
  {
    int object_count = 100;
    if (argc >= 2)
    {
      object_count = atoi(argv[1]);
    }

    System system;
    system.create_window(800, 600, false);

    World world;
    world.add_random_objects(object_count);
    
    GameSession game_session(system, world);
    game_session.run();
  }
  catch(const std::exception& err)
  {
    std::cerr << "Exception: " << err.what() << std::endl;
  }

  return 0;
}

/* EOF */
