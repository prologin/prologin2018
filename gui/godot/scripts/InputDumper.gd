# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright 2018 Sacha Delanoue

extends Node

const DIR = {'OUEST': 0, 'SUD': 1, 'EST': 2, 'NORD': 3}

const DumpReader = preload("res://scripts/DumpReader.gd")

var dump = null
var dump_index = 0
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
	var init = DumpReader.parse_turn(dump[dump_index])
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
	$GameState/TileMap.update_aliens(0)
	$GameState/Info.redraw()

func _finish_animating():
	animating = false

func _jump(index):
	var state = DumpReader.parse_turn(dump[index])
	var size = state.players[0].agents.size()
	for i in range(size):
		$GameState/TileMap.teleport_agent(i, state.players[0].agents[i])
		$GameState/TileMap.teleport_agent(i + size, state.players[1].agents[i])
	$GameState/Info.players[0].score = state.players[0].score
	$GameState/Info.players[1].score = state.players[1].score
	dump_index = index
	$GameState/Info.players[0].action_points = 0
	$GameState/Info.players[1].action_points = 0
	$GameState/Info.redraw()
	$GameState/TileMap.update_aliens(max(0, (dump_index - 1) / 2))

func _continue():
	dump_index += 1
	var state = DumpReader.parse_turn(dump[dump_index])
	var player_id = (dump_index + 1) % 2 
	actions_playing = state.players[player_id].history
	$GameState/Info.players[0].score = state.players[0].score
	$GameState/Info.players[1].score = state.players[1].score
	$GameState/Info.players[dump_index % 2].action_points = 0
	$GameState/Info.players[(dump_index + 1) % 2].action_points = 10
	$GameState/Info.redraw()
	$GameState/TileMap.update_aliens(max(0, (dump_index - 1) / 2))

func _process(delta):
	if not animating:
		if actions_playing:
			var action = actions_playing.pop_front()
			var player_id = (dump_index + 1) % 2
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
				_jump(dump_index + 1)
			if Input.is_action_just_pressed("ui_left"):
				_jump(dump_index - 1)
			if Input.is_action_just_pressed("ui_select"):
				_continue()
