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

#include "vector2f.hpp"

class Object
{
public:
  Vector2f vel;
  Vector2f pos;
  float    mass;
  Vector2f force;
  bool remove;

  static bool removable(const Object& obj) { return obj.remove; }
};

int main(int argc, char** argv)
{
  int object_count = 100;
  if (argc >= 2)
  {
    object_count = atoi(argv[1]);
  }

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

  SDL_Surface* screen = SDL_SetVideoMode(800, 800, 0, SDL_OPENGL);

  glOrtho(-10000, 10000, 10000, -10000, 1000.0, -1000.0);

  std::vector<Object> objects;

  if (false)
  for(int i = 0; i < object_count; ++i)
  {
    Object obj;
    obj.pos.x = rand() % 10000 - 5000;
    obj.pos.y = rand() % 10000 - 5000;
    obj.vel.x = (rand() % 20 - 10);
    obj.vel.y = (rand() % 20 - 10);
    obj.mass  = (rand() % 50 + 50) * 100.0f;
    obj.remove = false;
    objects.push_back(obj);
  }

  bool quit = false;
  while(!quit)
  {
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        case SDL_QUIT:
          // FIXME: This should be a bit more gentle, but will do for now
          std::cout << "Ctrl-c or Window-close pressed, game is going to quit" << std::endl;
          quit = true;
          break;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
          if (event.key.state)
          {    
            switch (event.key.keysym.sym)
            {
              case SDLK_ESCAPE:
                quit = true;
                break;

              case SDLK_SPACE:
                for(int i = 0; i < object_count; ++i)
                {
                  Object obj;
                  obj.pos.x = rand() % 10000 - 5000;
                  obj.pos.y = rand() % 10000 - 5000;
                  obj.vel.x = (rand() % 200 - 100);
                  obj.vel.y = (rand() % 200 - 100);
                  obj.mass  = (rand() % 50 + 50) * 100.0f;
                  obj.remove = false;
                  objects.push_back(obj);
                }
                break;
            }
          }
      }
    }
    
    for(int it = 0; it < 15; ++it)
    {
      // Clear all forces
      for(std::vector<Object>::iterator i = objects.begin(); i != objects.end(); ++i)
      {
        i->force = Vector2f();
      }

      // Calculate all forces
      for(std::vector<Object>::iterator i = objects.begin(); i != objects.end(); ++i)
      {
        for(std::vector<Object>::iterator j = objects.begin(); j != objects.end(); ++j)
        {
          if (i != j && !i->remove && !j->remove)
          {
            float G = 15.0f;
            Vector2f dir = i->pos - j->pos;
            float dist = dir.length();
            float force = G * (i->mass * j->mass) / (dist*dist);

            if (force < 10000000.0f)
            {
              dir.normalize();
          
              i->force += -dir * force;
              j->force +=  dir * force;
            }
            else // collision
            {
              i->vel  = (i->mass * i->vel + j->mass * j->vel) / (i->mass + j->mass);
              i->pos  = (i->pos + j->pos)/2.0f;
              i->mass = i->mass + j->mass;
              i->force = Vector2f();
              j->remove = true;
            }
          }
        }

        // remove stuff
        
        objects.erase(std::remove_if(objects.begin(), objects.end(), Object::removable),
                      objects.end());
      }
    
      // Apply all forces
      for(std::vector<Object>::iterator i = objects.begin(); i != objects.end(); ++i)
      {
        float delta = 0.05f;
        i->vel += (i->force / i->mass) * delta;
        i->pos += (i->vel) * delta;

        //i->pos.x = fmodf(i->pos.x, 1280);
        //i->pos.y = fmodf(i->pos.y, 1280);
      }
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    for(std::vector<Object>::iterator i = objects.begin(); i != objects.end(); ++i)
    {
      if (false)
      {
        glVertex2f(i->pos.x, i->pos.y);
        glVertex2f(i->pos.x, i->pos.y);

        glVertex2f(i->pos.x+1, i->pos.y);
        glVertex2f(i->pos.x, i->pos.y);
        glVertex2f(i->pos.x, i->pos.y+1);
        glVertex2f(i->pos.x, i->pos.y-1);
      }
      else
      {
        float d = std::max(sqrtf(i->mass)/5.0f, 1.5f);
        
        glVertex2f(i->pos.x + d, i->pos.y);
        glVertex2f(i->pos.x, i->pos.y - d);

        glVertex2f(i->pos.x - d, i->pos.y);
        glVertex2f(i->pos.x, i->pos.y - d);

        glVertex2f(i->pos.x + d, i->pos.y);
        glVertex2f(i->pos.x, i->pos.y + d);

        glVertex2f(i->pos.x - d, i->pos.y);
        glVertex2f(i->pos.x, i->pos.y + d);
      }
    }
    glEnd();

    SDL_GL_SwapBuffers();
  }

  return 0;
}

/* EOF */
