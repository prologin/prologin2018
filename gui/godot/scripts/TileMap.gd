# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright 2018 Sacha Delanoue

extends TileMap

const SIZE = 31
const NB_AGENTS = 4

var walls = []
var agents = []
var agents_pos = []

var moving_agent = -1
var moving_dir = Vector2()
var dash = false
const SPEED = 100

const Util = preload("res://scripts/MapReader.gd")

onready var character_scene = preload("res://scenes/Agent.tscn")

func world_position(x, y):
	return map_to_world(Vector2(x, y)) + get_cell_size() / 2

func get_tile(x, y):
	var tile = "Wall" if walls[x][y] else "BG"
	return get_tileset().find_tile_by_name(tile)

func spawn_agent(i):
	var character = character_scene.instance()
	character.position = world_position(agents_pos[i].x, agents_pos[i].y)
	if (i < NB_AGENTS):
		character.set_modulate(Color(0, 0.5, 1, 1))
	else:
		character.set_modulate(Color(1, 0.5, 0, 1))
	add_child(character)
	agents.append(character)

func spawn_agents():
	agents = []
	for i in range(2 * NB_AGENTS):
		spawn_agent(i)

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

func move_agent(i, dir):
	var dest = agents_pos[i] + dir
	if not is_cell_free(dest):
		return false
	dash = false
	if Input.is_action_pressed("ui_shift"):
		dash = true
		while is_cell_free(dest + dir):
			dest += dir
	moving_agent = i
	moving_dir = dest
	var anim = "slide" if dash else "walk"
	var animated_sprite = agents[moving_agent].get_node("AnimatedSprite")
	animated_sprite.play(anim)
	var dx = dest.x - agents_pos[i].x
	if dx > 0:
		animated_sprite.flip_h = false
	elif dx < 0:
		animated_sprite.flip_h = true
	return true

func _ready():
	var map = Util.parse_map("res://../../maps/test_map")
	walls = map.walls
	agents_pos = map.agents
	set_map()
	spawn_agents()

func _process(delta):
	if moving_agent == -1:
		if Input.is_action_just_pressed("ui_up"):
			move_agent(1, Vector2(0, -1))
		elif Input.is_action_just_pressed("ui_down"):
			move_agent(1, Vector2(0, 1))
		elif Input.is_action_just_pressed("ui_right"):
			move_agent(1, Vector2(1, 0))
		elif Input.is_action_just_pressed("ui_left"):
			move_agent(1, Vector2(-1, 0))
	if moving_agent != -1:
		var diff = world_position(moving_dir.x, moving_dir.y) - agents[moving_agent].position
		if diff == Vector2():
			agents[moving_agent].get_node("AnimatedSprite").play("idle")
			agents_pos[moving_agent] = moving_dir
			moving_agent = -1
		else:
			var speed = SPEED * 2.5 if dash else SPEED
			if diff.length() > speed * delta:
				agents[moving_agent].move_and_slide(diff.normalized() * speed)
			else:
				agents[moving_agent].move_and_slide(diff / delta)
