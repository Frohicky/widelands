/*
 * Copyright (C) 2002-2019 by the Widelands Development Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef WL_LOGIC_MAP_OBJECTS_TRIBES_TRIBE_DESCR_H
#define WL_LOGIC_MAP_OBJECTS_TRIBES_TRIBE_DESCR_H

#include <map>
#include <memory>
#include <vector>

#include "base/macros.h"
#include "graphic/animation/animation.h"
#include "graphic/toolbar_imageset.h"
#include "logic/map_objects/immovable.h"
#include "logic/map_objects/tribes/building.h"
#include "logic/map_objects/tribes/road_textures.h"
#include "logic/map_objects/tribes/ship.h"
#include "logic/map_objects/tribes/tribe_basic_info.h"
#include "logic/map_objects/tribes/tribes.h"
#include "logic/map_objects/tribes/ware_descr.h"
#include "logic/map_objects/tribes/worker.h"
#include "logic/widelands.h"

namespace Widelands {

class ResourceDescription;
class WareDescr;
class Warehouse;
class WorkerDescr;
class World;
class BuildingDescr;
struct Event;

/*
 * Resource indicators:
 * A ResourceIndicatorSet maps the resource name to a ResourceIndicatorList.
 * A ResourceIndicatorList maps resource amounts to the DescriptionIndex of an immovable this player
 * uses.
 * Special case: The ResourceIndicatorList mapped to "" contains resis that will be used in
 * locations
 * without resources. If it has several entries, result is arbitrary.
 */
using ResourceIndicatorList = std::map<uint32_t, DescriptionIndex>;
using ResourceIndicatorSet = std::map<std::string, ResourceIndicatorList>;

/*
Tribes
------

Every player chooses a tribe. A tribe has distinct properties such as the
buildings it can build and the associated graphics.
Two players can choose the same tribe.
*/
class TribeDescr {
public:
	TribeDescr(const LuaTable& table,
	           const Widelands::TribeBasicInfo& info,
	           const Tribes& init_tribes);

	const std::string& name() const;
	const std::string& descname() const;

	size_t get_nrwares() const;
	size_t get_nrworkers() const;

	const std::vector<DescriptionIndex>& buildings() const;
	const std::set<DescriptionIndex>& wares() const;
	const std::set<DescriptionIndex>& workers() const;
	const std::set<DescriptionIndex>& immovables() const;
	const ResourceIndicatorSet& resource_indicators() const;

	bool has_building(const DescriptionIndex& index) const;
	bool has_ware(const DescriptionIndex& index) const;
	bool has_worker(const DescriptionIndex& index) const;
	bool has_immovable(const DescriptionIndex& index) const;

	// A ware is a construction material if it appears in a building's buildcost or enhancement cost
	bool is_construction_material(const DescriptionIndex& ware_index) const;

	DescriptionIndex building_index(const std::string& buildingname) const;
	DescriptionIndex immovable_index(const std::string& immovablename) const;
	DescriptionIndex ware_index(const std::string& warename) const;
	DescriptionIndex worker_index(const std::string& workername) const;

	/// Return the given building or die trying
	DescriptionIndex safe_building_index(const std::string& buildingname) const;
	/// Return the given ware or die trying
	DescriptionIndex safe_ware_index(const std::string& warename) const;
	/// Return the given worker or die trying
	DescriptionIndex safe_worker_index(const std::string& workername) const;

	BuildingDescr const* get_building_descr(const DescriptionIndex& index) const;
	ImmovableDescr const* get_immovable_descr(const DescriptionIndex& index) const;
	WareDescr const* get_ware_descr(const DescriptionIndex& index) const;
	WorkerDescr const* get_worker_descr(const DescriptionIndex& index) const;

	DescriptionIndex builder() const;
	DescriptionIndex carrier() const;
	DescriptionIndex carrier2() const;
	DescriptionIndex geologist() const;
	DescriptionIndex soldier() const;
	DescriptionIndex ship() const;
	DescriptionIndex port() const;
	DescriptionIndex ironore() const;
	DescriptionIndex rawlog() const;
	DescriptionIndex refinedlog() const;
	DescriptionIndex granite() const;

	const std::vector<DescriptionIndex>& trainingsites() const;
	const std::vector<DescriptionIndex>& worker_types_without_cost() const;

	uint32_t frontier_animation() const;
	uint32_t flag_animation() const;

	// A vector of all texture images that can be used for drawing a
	// (normal|busy) road. The images are guaranteed to exist.
	const std::vector<std::string>& normal_road_paths() const;
	const std::vector<std::string>& busy_road_paths() const;

	// Add the corresponding texture for roads.
	void add_normal_road_texture(const Image* texture);
	void add_busy_road_texture(const Image* texture);

	// The road textures used for drawing roads.
	const RoadTextures& road_textures() const;

	DescriptionIndex get_resource_indicator(const ResourceDescription* const res,
	                                        const ResourceAmount amount) const;

	// Returns the initalization at 'index' (which must not be out of bounds).
	const Widelands::TribeBasicInfo::Initialization& initialization(const uint8_t index) const {
		return initializations_.at(index);
	}

	using WaresOrder = std::vector<std::vector<Widelands::DescriptionIndex>>;
	const WaresOrder& wares_order() const {
		return wares_order_;
	}

	const WaresOrder& workers_order() const {
		return workers_order_;
	}

	const std::vector<std::string>& get_ship_names() const {
		return ship_names_;
	}

	/// Registers a building with the tribe
	void add_building(const std::string& buildingname);
	/// Registers a worker with the tribe and adds it to the bottom of the last worker column
	void add_worker(const std::string& workername);

	// The custom toolbar imageset if any. Can be nullptr.
	ToolbarImageset* toolbar_image_set() const;

private:
	/// Registers a worker with the tribe and adds it to the bottom of the given worker column
	void add_worker(const std::string& workername,
	                std::vector<DescriptionIndex>& workers_order_column);

	// Helper function for adding a special worker type (carriers etc.)
	DescriptionIndex add_special_worker(const std::string& workername);
	// Helper function for adding a special building type (port etc.)
	DescriptionIndex add_special_building(const std::string& buildingname);
	// Helper function to identify special wares across tribes (iron ore etc.)
	DescriptionIndex add_special_ware(const std::string& warename);

	const std::string name_;
	const std::string descname_;
	const Tribes& tribes_;

	uint32_t frontier_animation_id_;
	uint32_t flag_animation_id_;
	std::vector<std::string> normal_road_paths_;
	std::vector<std::string> busy_road_paths_;
	RoadTextures road_textures_;

	std::vector<DescriptionIndex> buildings_;
	std::set<DescriptionIndex> immovables_;  // The player immovables
	std::vector<std::string> ship_names_;
	std::set<DescriptionIndex> workers_;
	std::set<DescriptionIndex> wares_;
	ResourceIndicatorSet resource_indicators_;
	// The wares that are used by construction sites
	std::set<DescriptionIndex> construction_materials_;
	// Special units. Some of them are used by the engine, some are only used by the AI.
	DescriptionIndex builder_;     // The builder for this tribe
	DescriptionIndex carrier_;     // The basic carrier for this tribe
	DescriptionIndex carrier2_;    // Additional carrier for busy roads
	DescriptionIndex geologist_;   // This tribe's geologist worker
	DescriptionIndex soldier_;     // The soldier that this tribe uses
	DescriptionIndex ship_;        // The ship that this tribe uses
	DescriptionIndex port_;        // The port that this tribe uses
	DescriptionIndex ironore_;     // Iron ore
	DescriptionIndex rawlog_;      // Simple log
	DescriptionIndex refinedlog_;  // Refined log, e.g. wood or blackwood
	DescriptionIndex granite_;     // Granite
	std::vector<DescriptionIndex> worker_types_without_cost_;
	std::vector<DescriptionIndex> trainingsites_;
	// Order and positioning of wares in the warehouse display
	WaresOrder wares_order_;
	WaresOrder workers_order_;

	// An optional custom imageset for the in-game menu toolbar
	std::unique_ptr<ToolbarImageset> toolbar_image_set_;

	std::vector<Widelands::TribeBasicInfo::Initialization> initializations_;

	DISALLOW_COPY_AND_ASSIGN(TribeDescr);
};
}  // namespace Widelands

#endif  // end of include guard: WL_LOGIC_MAP_OBJECTS_TRIBES_TRIBE_DESCR_H
