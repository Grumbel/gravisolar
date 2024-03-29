# Gravisolar
# Copyright (C) 2010-2022 Ingo Ruhnke <grumbel@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.14)
project(gravisolar)

include(GNUInstallDirs)

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)

file(GLOB GRAVISOLAR_SOURCES_CXX
  src/*.cpp)

add_executable(gravisolar ${GRAVISOLAR_SOURCES_CXX})
target_link_libraries(gravisolar PRIVATE
  SDL::SDL
  OpenGL::OpenGL)

install(TARGETS gravisolar RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# EOF #
