# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright 2018 Sacha Delanoue

extends Node2D

var color = Color(1, 1, 1, 1)
var player_name = ""
var score = 0
var action_points = 0

func _ready():
	redraw()

func set_player(name, id):
	player_name = name
	if id == 0:
		color = Color(0, 0.5, 1, 1)
	else:
		color = Color(1, 0.5, 0, 1)
	redraw()
	
func redraw():
	$Players.text = player_name + "\nScore: " + str(score) + "\nPoints: " + str(action_points)
	$Players.set("custom_colors/font_color", color)