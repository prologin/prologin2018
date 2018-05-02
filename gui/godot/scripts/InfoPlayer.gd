# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright 2018 Sacha Delanoue

extends Node2D

class Player:
	var name = ""
	var score = 0
	var action_points = 0

var players = [Player.new(), Player.new()]
var _turn = 0
var _type = 0
var _turn_slider = null

func _ready():
	$Player1.set("custom_colors/font_color", Color(0, 0.5, 1, 1))
	$Player2.set("custom_colors/font_color", Color(1, 0.5, 0, 1))
	$Speed.text = "Vitesse : " + str(global.speed_factor)
	$SpeedSlider.connect("value_changed", self, "_speed_slider")
	redraw()

func _redraw_player(id, label):
	label.text = players[id].name + "\nScore : " + str(players[id].score) + "\nPoints : " + str(players[id].action_points)

func redraw():
	_redraw_player(0, $Player1)
	_redraw_player(1, $Player2)
	$Turn.text = "Tour : " + str(_turn) + "\n" + ["Env", "P1", "P2"][_type]

func set_turn(turn, type):
	_turn = turn
	_type = type
	players[0].action_points = 0
	players[1].action_points = 0
	if type != 0:
		players[type - 1].action_points = 10
	if _turn_slider:
		_turn_slider.value = turn
	redraw()

func _speed_slider(value):
	var v = 1 << int(value)
	global.speed_factor = v
	$Speed.text = "Vitesse : " + str(v)

func add_turn_slider():
	_turn_slider = HSlider.new()
	_turn_slider.margin_left = 200
	_turn_slider.margin_right = 280
	_turn_slider.margin_top = 32
	_turn_slider.step = 1
	_turn_slider.min_value = 1
	_turn_slider.max_value = 100
	add_child(_turn_slider)
	return _turn_slider