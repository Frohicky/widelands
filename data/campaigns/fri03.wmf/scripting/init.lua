-- =======================================================================
--                         Frisian Campaign Mission 3
-- =======================================================================
set_textdomain("scenario_fri03.wmf")

include "scripting/coroutine.lua"
include "scripting/objective_utils.lua"
include "scripting/infrastructure.lua"
include "scripting/table.lua"
include "scripting/ui.lua"

map = wl.Game().map
p1 = wl.Game().players[1] -- Claus Lembeck     – Player's tribe
p2 = wl.Game().players[2] -- Waldemar Atterdag – Enemy, King of Denmark
p3 = wl.Game().players[3] -- Henneke Lembeck   – Claus's son and friend
p4 = wl.Game().players[4] -- Hans Ravenstrupp  – Enemy to Claus's other son

p3_start = {
   map:get_field(334, 206),
   map:get_field(334, 207),
   map:get_field(335, 208),
   map:get_field(335, 206),
   map:get_field(335, 207),
   map:get_field(335, 205),
   map:get_field(336, 206),
   map:get_field(336, 207),
   map:get_field(336, 205),
   map:get_field(337, 206),
   map:get_field(337, 204),
   map:get_field(337, 205),
   map:get_field(338, 204),
   map:get_field(338, 205),
}

include "map:scripting/texts.lua"
include "map:scripting/mission_thread.lua"
