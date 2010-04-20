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

#include "world.hpp"

#include <SDL_opengl.h>
#include <stdexcept>
#include <algorithm>
#include <math.h>

World::World()
{
}

void
World::update(float delta)
{  
  for(int it = 0; it < 15; ++it)
  {
    // Clear all forces
    for(std::vector<Object>::iterator i = m_objects.begin(); i != m_objects.end(); ++i)
    {
      i->force = Vector2f();
    }

    // Calculate all forces
    for(std::vector<Object>::iterator i = m_objects.begin(); i != m_objects.end(); ++i)
    {
      for(std::vector<Object>::iterator j = m_objects.begin(); j != m_objects.end(); ++j)
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
        
      m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(), Object::removable),
                      m_objects.end());
    }
    
    // Apply all forces
    for(std::vector<Object>::iterator i = m_objects.begin(); i != m_objects.end(); ++i)
    {
      i->vel += (i->force / i->mass) * delta;
      i->pos += (i->vel) * delta;

      //i->pos.x = fmodf(i->pos.x, 1280);
      //i->pos.y = fmodf(i->pos.y, 1280);
    }
  }
}

void
World::draw()
{
  glClear(GL_COLOR_BUFFER_BIT);

  for(std::vector<Object>::iterator i = m_objects.begin(); i != m_objects.end(); ++i)
  {
    float d = std::max(sqrtf(i->mass)/5.0f, 1.5f);

    glBegin(GL_LINE_LOOP);        
    glVertex2f(i->pos.x + d, i->pos.y);
    glVertex2f(i->pos.x, i->pos.y - d);
    glVertex2f(i->pos.x - d, i->pos.y);
    glVertex2f(i->pos.x, i->pos.y + d);
    glEnd();
  }
}

void
World::add_random_objects(int object_count)
{
  for(int i = 0; i < object_count; ++i)
  {
    Object obj;
    obj.pos.x = rand() % 10000 - 5000;
    obj.pos.y = rand() % 10000 - 5000;
    obj.vel.x = (rand() % 200 - 100);
    obj.vel.y = (rand() % 200 - 100);
    obj.mass  = (rand() % 50 + 50) * 100.0f;
    obj.remove = false;
    m_objects.push_back(obj);
  }
}

/* EOF */
