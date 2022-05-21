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

#ifndef HEADER_GRAVISOLAR_GAME_SESSION_HPP
#define HEADER_GRAVISOLAR_GAME_SESSION_HPP

#include "math/vector2f.hpp"

class World;
class System;

class GameSession
{
private:
  System& m_system;
  World& m_world;
  bool m_quit;
  bool m_pause;
  bool m_single_step;
  bool m_forward;

  Vector2f m_camera_pos;
  Vector2f m_camera_stick;

  float m_camera_zoom;
  float m_camera_zoom_stick;

  Vector2f m_ship_stick;

public:
  GameSession(System& system, World& world);

  void run();
  void process_input();
  
private:
  GameSession(const GameSession&);
  GameSession& operator=(const GameSession&);
};

#endif

/* EOF */
