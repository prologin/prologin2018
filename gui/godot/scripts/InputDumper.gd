# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright 2018 Sacha Delanoue

extends Node

const DIR = {'OUEST': 0, 'SUD': 1, 'EST': 2, 'NORD': 3}

const DumpReader = preload("res://scripts/DumpReader.gd")

var dump = null
var turn_index = 0
var actions_playing = []
var animating = false

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
	$GameState/Info.redraw()

func _finish_animating():
	animating = false

func _dump_index():
	return (turn_index - turn_index % 3) / 3 * 2 + turn_index % 3

func _jump(index):
	turn_index = index
	var state = DumpReader.parse_turn(dump[_dump_index()])
	var size = state.players[0].agents.size()
	for i in range(size):
		$GameState/TileMap.teleport_agent(i, state.players[0].agents[i])
		$GameState/TileMap.teleport_agent(i + size, state.players[1].agents[i])
	$GameState/Info.players[0].score = state.players[0].score
	$GameState/Info.players[1].score = state.players[1].score
	$GameState.set_turn(turn_index)

func _continue():
	turn_index += 1
	var state = DumpReader.parse_turn(dump[_dump_index()])
	$GameState/Info.players[0].score = state.players[0].score
	$GameState/Info.players[1].score = state.players[1].score
	actions_playing = []
	if turn_index % 3:
		var player_id = turn_index % 3 - 1
		actions_playing = state.players[player_id].history
	$GameState.set_turn(turn_index)

func _process(delta):
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
			if Input.is_action_just_pressed("ui_right"):
				_jump(turn_index + 1)
			elif Input.is_action_just_pressed("ui_left") and turn_index > 0:
				_jump(turn_index - 1)
			if Input.is_action_just_pressed("ui_select"):
				_continue()
