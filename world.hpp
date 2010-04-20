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

#ifndef HEADER_GRAVISOLAR_WORLD_HPP
#define HEADER_GRAVISOLAR_WORLD_HPP

#include <vector>

#include "object.hpp"

class World
{
private:
  std::vector<Object> m_objects;

public:
  World();

  void draw();
  void update(float delta);

  void add_random_objects(int object_count);

private:
  World(const World&);
  World& operator=(const World&);
};

#endif

/* EOF */
