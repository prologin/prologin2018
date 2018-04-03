# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright 2018 Sacha Delanoue

extends TileMap

const SIZE = 31
const NB_AGENTS = 4

var walls = []
var agents = []
var agents_pos = []

const Util = preload("res://scripts/MapReader.gd")

onready var character_scene = preload("res://scenes/Agent.tscn")

func world_position(x, y):
	return map_to_world(Vector2(x, y)) + get_cell_size() / 2

func get_tile(x, y):
	var tile = "Wall" if walls[x][y] else "BG"
	return get_tileset().find_tile_by_name(tile)

func spawn_agents():
	agents = []
	for i in range(2 * NB_AGENTS):
		var character = character_scene.instance()
		character.position = world_position(agents_pos[i].x, agents_pos[i].y)
		character.set_team(i < NB_AGENTS)
		add_child(character)
		agents.append(character)

func set_map():
	clear()
	for x in range(SIZE):
		for y in range(SIZE):
			set_cell(x, y, get_tile(x, y))

func is_cell_free(pos):
	if pos.x < 0 or pos.y < 0 or pos.x >= SIZE or pos.y >= SIZE:
		return false
	if walls[pos.x][pos.y] or agents_pos.has(pos):
		return false
	return true

func move_agent(i, dest, dash):
	agents[i].move_to(world_position(dest.x, dest.y), dash)
	agents_pos[i] = dest
	return true

func _ready():
	var map = Util.parse_map("res://../../maps/test_map")
	walls = map.walls
	agents_pos = map.agents
	set_map()
	spawn_agents()