# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright 2018 Sacha Delanoue

extends Node

const DIR = [Vector2(-1, 0), Vector2(0, 1), Vector2(1, 0), Vector2(0, -1)]
const DIR_DIC = {'OUEST': 0, 'SUD': 1, 'EST': 2, 'NORD': 3}

var selected_tile = null
var _turn = 0

func agent_id_to_internal(agent_id, player_id):
	return agent_id + constants.NB_AGENTS * player_id

func internal_to_agent_id(internal):
	return internal % constants.NB_AGENTS

func move(agent_id, direction, player_id):
	var internal = agent_id_to_internal(agent_id, player_id)
	var destination = $TileMap.agents_pos[internal] + DIR[direction]
	if not $TileMap.is_cell_free(destination):
		return false
	$TileMap.move_agent(internal, destination, false, false)
	$Info.players[player_id].action_points[agent_id] -= constants.COUT_DEPLACEMENT
	$Info.redraw()
	return true

func slide(agent_id, dir, player_id, pushed = false):
	var internal = agent_id_to_internal(agent_id, player_id)
	var dest = $TileMap.agents_pos[internal]
	while $TileMap.is_cell_free(dest + DIR[dir]):
		dest += DIR[dir]
	$TileMap.move_agent(internal, dest, true, pushed)
	if not pushed:
		$Info.players[player_id].action_points[agent_id] -= constants.COUT_GLISSADE
		$Info.redraw()
	return true

func push(agent_id, dir, player_id):
	var internal = agent_id_to_internal(agent_id, player_id)
	var destination = $TileMap.agents_pos[internal] + DIR[dir]
	var agent = $TileMap.agents_pos.find(destination)
	if agent == -1:
		return false
	slide(internal_to_agent_id(agent), dir, agent / constants.NB_AGENTS, true)
	$Info.players[player_id].action_points[agent_id] -= constants.COUT_POUSSER
	$Info.redraw()
	return true

func init(walls, agents):
	$TileMap.init(walls, agents)
	$Info.position.y = $TileMap.walls.size() * $TileMap.cell_size.y * $TileMap.scale.y

func set_turn(turn_index):
	var type = turn_index % 3
	_turn = (turn_index - type) / 3
	$TileMap.update_aliens(_turn)
	$Info.set_turn(_turn, type)
	_update_tile_info()

func _update_tile_info():
	if selected_tile == null:
		$Info/Tile.text = ""
		$TileMap/Select.visible = false
		return
	$TileMap/Select.visible = true
	$TileMap/Select.rect_position = $TileMap.map_to_world(selected_tile)
	var alien = null
	if $TileMap.get_cellv(selected_tile) == $TileMap.get_tileset().find_tile_by_name("Alien"):
		for a in $TileMap.aliens:
			if a.pos == selected_tile:
				if _turn >= a.first_turn and _turn < a.first_turn + a.duration \
						and a.capture < constants.NB_TOURS_CAPTURE:
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

func replay_action(action, player_id):
	if action['type'] == 'ID_ACTION_DEPLACER':
		return move(int(action['id_agent']), DIR_DIC[action['dir']], player_id)
	elif action['type'] == 'ID_ACTION_POUSSER':
		return push(int(action['id_agent']), DIR_DIC[action['dir']], player_id)
	elif action['type'] == 'ID_ACTION_GLISSER':
		return slide(int(action['id_agent']), DIR_DIC[action['dir']], player_id)
	elif action['type'] == 'ID_ACTION_DEBUG_AFFICHER_DRAPEAU':
		$TileMap.set_flag(player_id, Vector2(action['pos']['c'], action['pos']['r']), action['drapeau'])
	else:
		print("Unknown action ", action['type'])
	return false


func _no_flags():
	$TileMap.flagNodes[0].set_visible(false)
	$TileMap.flagNodes[1].set_visible(false)

func _flags_j1():
	$TileMap.flagNodes[0].set_visible(true)
	$TileMap.flagNodes[1].set_visible(false)

func _flags_j2():
	$TileMap.flagNodes[0].set_visible(false)
	$TileMap.flagNodes[1].set_visible(true)

func _ready():
	$Info/FlagsNo.connect("pressed", self, "_no_flags")
	$Info/FlagsP1.connect("pressed", self, "_flags_j1")
	$Info/FlagsP2.connect("pressed", self, "_flags_j2")
