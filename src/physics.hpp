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

#ifndef HEADER_GRAVISOLAR__HOME_INGO_PROJECTS_GRAVISOLAR_GRAVISOLAR_GIT_PHYSICS_HPP
#define HEADER_GRAVISOLAR__HOME_INGO_PROJECTS_GRAVISOLAR_GRAVISOLAR_GIT_PHYSICS_HPP

#include <vector>

#include <glm/vec2.hpp>

#include "object.hpp"

typedef Object PhysicsObject;
typedef PhysicsObject* PhysicsObjectPtr;

class Physics
{
private:
  std::vector<PhysicsObject*> m_objects;
  std::vector<PhysicsObject*> m_active_objects;
  float m_G;

public:
  Physics();

  PhysicsObjectPtr create_object(const glm::vec2& pos,
                                 const glm::vec2& vel,
                                 float mass,
                                 bool active);
  void remove_object(PhysicsObjectPtr obj);

  void update(float delta);
  glm::vec2 calc_force(const glm::vec2& pos, float mass);

private:
  void update_clear_forces(float delta);
  void update_calc_forces(float delta);
  void update_apply_forces(float delta);
  void update_removes(float delta);

private:
  Physics(const Physics&);
  Physics& operator=(const Physics&);
};

#endif

/* EOF */
