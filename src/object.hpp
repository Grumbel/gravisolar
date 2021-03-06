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

#ifndef HEADER_GRAVISOLAR__HOME_INGO_PROJECTS_GRAVISOLAR_GRAVISOLAR_GIT_OBJECT_HPP
#define HEADER_GRAVISOLAR__HOME_INGO_PROJECTS_GRAVISOLAR_GRAVISOLAR_GIT_OBJECT_HPP

#include <glm/vec2.hpp>

class Object
{
public:
  glm::vec2 vel;
  glm::vec2 pos;
  float    mass;
  glm::vec2 force;
  bool remove;

  Object() :
    vel(0.0f, 0.0f),
    pos(0.0f, 0.0f),
    mass(0.0f),
    force(0.0f, 0.0f),
    remove(false)
  {}

  static bool removable(const Object& obj) { return obj.remove; }
  static bool removable_ptr(const Object* obj) { return obj->remove; }
};

#endif

/* EOF */
