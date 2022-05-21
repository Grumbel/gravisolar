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

#include "physics.hpp"

#include <algorithm>

Physics::Physics() :
  m_objects(),
  m_active_objects(),
  m_G(15.0f)
{
}

PhysicsObjectPtr
Physics::create_object(const Vector2f& pos,
                       const Vector2f& vel,
                       float mass,
                       bool active)
{
  PhysicsObjectPtr obj = new PhysicsObject();

  return obj;
}

void
Physics::remove_object(PhysicsObjectPtr obj)
{

}

void
Physics::update(float delta)
{
  update_clear_forces(delta);
  update_calc_forces(delta);
  update_apply_forces(delta);
  update_removes(delta);
}

void
Physics::update_clear_forces(float delta)
{
  for(std::vector<PhysicsObjectPtr>::iterator i = m_objects.begin(); i != m_objects.end(); ++i)
  {
    (*i)->force = Vector2f(0.0f, 0.0f);
  }
}

void
Physics::update_calc_forces(float delta)
{
  // Calculate all forces
  for(std::vector<PhysicsObjectPtr>::iterator i = m_objects.begin(); i != m_objects.end(); ++i)
  {
    for(std::vector<PhysicsObjectPtr>::iterator j = m_active_objects.begin(); j != m_active_objects.end(); ++j)
    {
      if (*i != *j && !(*i)->remove && !(*j)->remove)
      {
        Vector2f dir = (*i)->pos - (*j)->pos;
        float dist = dir.length();
        float force = m_G * ((*i)->mass * (*j)->mass) / (dist*dist);

        if (force < 10000000.0f)
        {
          dir.normalize();
          
          (*i)->force += -dir * force;
          (*j)->force +=  dir * force;
        }
        else // collision
        {
          (*i)->vel  = ((*i)->mass * (*i)->vel + (*j)->mass * (*j)->vel) / ((*i)->mass + (*j)->mass);
          (*i)->pos  = ((*i)->mass * (*i)->pos + (*j)->mass * (*j)->pos) / ((*i)->mass + (*j)->mass);
          (*i)->mass = (*i)->mass + (*j)->mass;
          (*i)->force = Vector2f(0.0f, 0.0f);
          (*j)->remove = true;
        }
      }
    }
  }
}

void
Physics::update_apply_forces(float delta)
{
  Vector2f force(0.0f, 0.0f);

  for(std::vector<PhysicsObjectPtr>::iterator i = m_active_objects.begin(); i != m_active_objects.end(); ++i)
  {
    (*i)->vel += ((*i)->force / (*i)->mass) * delta;
    (*i)->pos += ((*i)->vel) * delta;
  }
}

void
Physics::update_removes(float delta)
{
  m_active_objects.erase(std::remove_if(m_active_objects.begin(), m_active_objects.end(), Object::removable_ptr),
                         m_active_objects.end());
}

Vector2f
Physics::calc_force(const Vector2f& pos, float mass)
{
  Vector2f total_force(0.0f, 0.0f);

  for(std::vector<PhysicsObjectPtr>::iterator i = m_active_objects.begin(); i != m_active_objects.end(); ++i)
  {
    Vector2f dir = pos - (*i)->pos;
    float dist = dir.length();
    float force = m_G * (mass * (*i)->mass) / (dist*dist);   

    dir.normalize();
          
    total_force += -dir * force;
  }

  return total_force;
}

/* EOF */
