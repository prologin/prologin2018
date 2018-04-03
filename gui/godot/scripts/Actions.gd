# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright 2018 Sacha Delanoue

extends Node

var team = 0
var agent_selected = 0
var animating = false

const DIR = [Vector2(-1, 0), Vector2(0, 1), Vector2(1, 0), Vector2(0, -1)]
const NB_AGENTS = 4

func agent_id_to_internal(agent_id, player_id):
	return agent_id + NB_AGENTS * player_id

func internal_to_agent_id(internal):
	return internal % NB_AGENTS

func move(agent_id, destination, player_id):
	if not $TileMap.is_cell_free(destination):
		return false
	var internal = agent_id_to_internal(agent_id, player_id)
	if $TileMap.agents_pos[internal].distance_squared_to(destination) != 1:
		return false
	$TileMap.move_agent(internal, destination, false, false)
	return true

func slide(agent_id, dir, player_id, pushed = false):
	var internal = agent_id_to_internal(agent_id, player_id)
	var dest = $TileMap.agents_pos[internal]
	while $TileMap.is_cell_free(dest + DIR[dir]):
		dest += DIR[dir]
	$TileMap.move_agent(internal, dest, true, pushed)
	return true

func push(agent_id, dir, player_id):
	var internal = agent_id_to_internal(agent_id, player_id)
	var destination = $TileMap.agents_pos[internal] + DIR[dir]
	var agent = $TileMap.agents_pos.find(destination)
	if agent == -1:
		return false
	slide(internal_to_agent_id(agent), dir, agent / NB_AGENTS, true)
	return true

func _ready():
	for agent in $TileMap.agents:
		 agent.connect("finished_moving", self, "_finish_animating")
	_select_agent(team * NB_AGENTS)

func _finish_animating():
	animating = false
	
func _input_move(dir):
	var dash = Input.is_action_pressed("ui_shift")
	var agent_id = internal_to_agent_id(agent_selected)
	var player = agent_selected / NB_AGENTS
	assert player == 0 or player == 1
	if Input.is_action_pressed("ui_ctrl"):
		animating = push(agent_id, dir, player)
	elif dash:
		slide(agent_id, dir, player)
		animating = true
	else:
		animating = move(agent_id, $TileMap.agents_pos[agent_selected] + DIR[dir], player)

func _select_agent(i):
	assert i >= 0 and i < 2 * NB_AGENTS
	$TileMap.agents[agent_selected].unfocus()
	$TileMap.agents[i].focus()
	agent_selected = i

func _process(delta):
	if not animating:
		if Input.is_action_just_pressed("ui_up"):
			_input_move(3)
		elif Input.is_action_just_pressed("ui_down"):
			_input_move(1)
		elif Input.is_action_just_pressed("ui_right"):
			_input_move(2)
		elif Input.is_action_just_pressed("ui_left"):
			_input_move(0)
		elif Input.is_action_just_pressed("ui_focus_next"):
			_select_agent((agent_selected + 1) % NB_AGENTS + NB_AGENTS * team)