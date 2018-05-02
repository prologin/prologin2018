# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright 2018 Sacha Delanoue

extends Node

const DIR = [Vector2(-1, 0), Vector2(0, 1), Vector2(1, 0), Vector2(0, -1)]
const NB_AGENTS = 4

const COST_MOVE = 1
const COST_SLIDE = 3
const COST_PUSH = 4

var selected_tile = null

func agent_id_to_internal(agent_id, player_id):
	return agent_id + NB_AGENTS * player_id

func internal_to_agent_id(internal):
	return internal % NB_AGENTS

func move(agent_id, direction, player_id):
	var internal = agent_id_to_internal(agent_id, player_id)
	var destination = $TileMap.agents_pos[internal] + DIR[direction]
	if not $TileMap.is_cell_free(destination):
		return false
	$TileMap.move_agent(internal, destination, false, false)
	$Info.players[player_id].action_points -= COST_MOVE
	$Info.redraw()
	return true

func slide(agent_id, dir, player_id, pushed = false):
	var internal = agent_id_to_internal(agent_id, player_id)
	var dest = $TileMap.agents_pos[internal]
	while $TileMap.is_cell_free(dest + DIR[dir]):
		dest += DIR[dir]
	$TileMap.move_agent(internal, dest, true, pushed)
	if not pushed:
		$Info.players[player_id].action_points -= COST_SLIDE
		$Info.redraw()
	return true

func push(agent_id, dir, player_id):
	var internal = agent_id_to_internal(agent_id, player_id)
	var destination = $TileMap.agents_pos[internal] + DIR[dir]
	var agent = $TileMap.agents_pos.find(destination)
	if agent == -1:
		return false
	slide(internal_to_agent_id(agent), dir, agent / NB_AGENTS, true)
	$Info.players[player_id].action_points -= COST_PUSH
	$Info.redraw()
	return true

func init(walls, agents):
	$TileMap.init(walls, agents)
	$Info.position.y = $TileMap.walls.size() * $TileMap.cell_size.y * $TileMap.scale.y

func set_turn(turn_index):
	var type = turn_index % 3
	var real_turn = (turn_index - type) / 3
	$TileMap.update_aliens(real_turn)
	$Info.set_turn(real_turn, type)
	_update_tile_info()

func storm(dir):
	var positions = $TileMap.agents_pos
	var map_size = $TileMap.walls.size()
	var vector_dir = DIR[dir]
	var moving = 0
	for i in range(NB_AGENTS * 2):
		var pos = positions[i]
		var cross_agents = 0
		var candidate = pos + vector_dir
		while candidate.x < map_size and candidate.x >= 0 and candidate.y < map_size and candidate.y >= 0 and not $TileMap.walls[candidate.x][candidate.y]:
			if not $TileMap.agents_pos.has(candidate):
				pos += vector_dir
			candidate += vector_dir
		if positions[i] != pos:
			$TileMap.move_agent(i, pos, true, true)
			moving += 1
	return moving

func _update_tile_info():
	if not selected_tile:
		$Info/Tile.text = ""
		$TileMap/Select.visible = false
		return
	$TileMap/Select.visible = true
	$TileMap/Select.rect_position = $TileMap.map_to_world(selected_tile)
	var alien = null
	if $TileMap.get_cellv(selected_tile) == $TileMap.get_tileset().find_tile_by_name("Alien"):
		for a in $TileMap.aliens:
			if a.pos == selected_tile:
				alien = a
				break
	$Info.set_tile(selected_tile, $TileMap.walls[selected_tile.x][selected_tile.y], alien)

func _input(event):
	if event is InputEventMouseButton and event.button_index == BUTTON_LEFT and event.pressed:
		var pos = $TileMap.world_to_map(event.position)
		if pos.x >= 0 and pos.y >= 0 and pos.x < $TileMap.walls.size() and pos.y < $TileMap.walls.size():
			if selected_tile == pos:
				selected_tile = null
			else:
				selected_tile = pos
			_update_tile_info()