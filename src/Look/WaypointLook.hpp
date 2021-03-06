/*
Copyright_License {

  Top Hat Soaring Glide Computer - http://www.tophatsoaring.org/
  Copyright (C) 2000-2016 The Top Hat Soaring Project
  A detailed list of copyright holders can be found in the file "AUTHORS".

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#ifndef WAYPOINT_LOOK_HPP
#define WAYPOINT_LOOK_HPP

#include "Screen/Icon.hpp"
#include "Screen/Brush.hpp"
#include "Screen/Font.hpp"

class Font;
struct WaypointRendererSettings;

struct WaypointLook {
  MaskedIcon small_icon, turn_point_icon, task_turn_point_icon;
  MaskedIcon mountain_pass_icon;
  MaskedIcon mountain_top_icon, bridge_icon, obstacle_icon;
  MaskedIcon tower_icon, power_plant_icon, tunnel_icon, thermal_hotspot_icon;
  MaskedIcon marker_icon;
  MaskedIcon airport_reachable_icon, airport_unreachable_icon;
  MaskedIcon airport_marginal_icon;
  MaskedIcon field_marginal_icon, field_reachable_icon, field_unreachable_icon;
  MaskedIcon teammate_icon;

  Brush reachable_brush, terrain_unreachable_brush, unreachable_brush;

  Brush white_brush, light_gray_brush, magenta_brush, orange_brush;

  // pointers to the instances, to avoid refactoring all references to these
  const Font *font, *bold_font;
  Font font_instance, bold_font_instance;

  void Initialise(const WaypointRendererSettings &settings,
                  unsigned font_scale_map_waypoint_name);

  void Reinitialise(const WaypointRendererSettings &settings,
                    unsigned font_scale_map_waypoint_name);
};

#endif
