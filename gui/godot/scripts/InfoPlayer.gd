# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright 2018 Sacha Delanoue

extends Node2D

class Player:
	var name = ""
	var score = 0
	var action_points = 0

var players = [Player.new(), Player.new()]

func _ready():
	$Player1.set("custom_colors/font_color", Color(0, 0.5, 1, 1))
	$Player2.set("custom_colors/font_color", Color(1, 0.5, 0, 1))
	redraw()

func _redraw_player(id, label):
	label.text = players[id].name + "\nScore: " + str(players[id].score) + "\nPoints: " + str(players[id].action_points)

func redraw():
	_redraw_player(0, $Player1)
	_redraw_player(1, $Player2)