# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright 2018 Sacha Delanoue

extends Node

const DIR = {'OUEST': 0, 'SUD': 1, 'EST': 2, 'NORD': 3}
const MAX_ROUNDS = 100

const DumpReader = preload("res://scripts/DumpReader.gd")

var dump = null
var turn_index = 0
var actions_playing = []
var animating = false
var playing = false

func get_json_path():
	for arg in OS.get_cmdline_args():
		if arg.begins_with("-json="):
			return arg.right(6)
	return "res://../../test_dumper.json"

func _ready():
	var json = get_json_path()
	print("Read dump ", json)
	dump = DumpReader.parse_dump(json)
	var init = DumpReader.parse_turn(dump[0])
	$GameState.init(init.walls, init.players[0].agents + init.players[1].agents)
	for agent in $GameState/TileMap.agents:
		 agent.connect("finished_moving", self, "_finish_animating")
	$GameState/Info.players[0].name = init.players[0].name
	$GameState/Info.players[1].name = init.players[1].name
	for alien_input in init.aliens:
		var alien = $GameState/TileMap.Alien.new()
		alien.pos = alien_input.pos
		alien.points = alien_input.points
		alien.first_turn = alien_input.first_turn
		alien.duration = alien_input.duration
		alien.capture = alien_input.capture
		$GameState/TileMap.aliens.append(alien)
	$GameState.set_turn(0)
	$GameState/Info.add_turn_slider().connect("value_changed", self, "_turn_slider")

func _turn_slider(value):
	if int(value) != (turn_index - turn_index % 3) / 3:
		_jump(int(value) * 3)

func _finish_animating():
	animating = false

func _dump_index():
	return (turn_index - turn_index % 3) / 3 * 2 + turn_index % 3

func _finish_last_turn(warn_teleport = true):
	"""The actions for a turn have been processed; now prepare next"""
	actions_playing = []
	var state = DumpReader.parse_turn(dump[_dump_index()])
	$GameState/Info.players[0].score = state.players[0].score
	$GameState/Info.players[1].score = state.players[1].score
	var size = state.players[0].agents.size()
	for agent_id in range(size):
		for player_id in range(2):
			var pos = state.players[player_id].agents[agent_id]
			if $GameState/TileMap.teleport_agent(agent_id + player_id * size, pos):
				if warn_teleport:
					print("Had to fix inconsistency in dump agent position")

func _jump(index):
	turn_index = max(index - 1, 0)
	_finish_last_turn(false)
	turn_index = index
	$GameState.set_turn(turn_index)
	playing = false
	get_tree().paused = false

func _continue():
	_finish_last_turn()
	if turn_index + 1 == MAX_ROUNDS * 3:
		return
	turn_index += 1
	if turn_index % 3:
		var state = DumpReader.parse_turn(dump[_dump_index()])
		# We duplicate the array here in case we read it again
		actions_playing = state.players[turn_index % 3 - 1].history.duplicate()
	$GameState.set_turn(turn_index)

func _process(delta):
	if Input.is_action_just_pressed("ui_select"):
		playing = !playing
		get_tree().paused = not playing
	if not animating:
		if actions_playing:
			var action = actions_playing.pop_front()
			var player_id = turn_index % 3 - 1
			if action['type'] == 'ID_ACTION_DEPLACER':
				animating = $GameState.move(int(action['id_agent']), DIR[action['dir']], player_id)
			elif action['type'] == 'ID_ACTION_POUSSER':
				animating = $GameState.push(int(action['id_agent']), DIR[action['dir']], player_id)
			elif action['type'] == 'ID_ACTION_GLISSER':
				animating = $GameState.slide(int(action['id_agent']), DIR[action['dir']], player_id)
			else:
				print("Unknown action ", action['type'])
		else:
			if playing:
				_continue()
			elif Input.is_action_just_pressed("ui_right") and turn_index < MAX_ROUNDS * 3:
				_jump(turn_index + 1)
			elif Input.is_action_just_pressed("ui_left") and turn_index > 0:
				_jump(turn_index - 1)
