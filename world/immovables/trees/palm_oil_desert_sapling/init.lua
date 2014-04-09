dirname = path.dirname(__file__)

world:new_immovable_type{
   name = "palm_oil_desert_sapling",
   descname = _ "Oil Palm (Sapling)",
   size = "small",
   attributes = { "seed" },
   programs = {
      program = {
         "animate=idle 42000",
         "remove=32",
         "grow=palm_oil_desert_pole",
      },
   },
   animations = {
      idle = {
         pictures = path.glob(dirname, "idle_\\d+.png"),
         player_color_masks = {},
         hotspot = { 5, 12 },
         fps = 8,
         sfx = {},
      },
   },
}
