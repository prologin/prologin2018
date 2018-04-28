# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright 2018 Sacha Delanoue

extends KinematicBody2D

signal finished_moving

var modulate_color = Color(1, 1, 1, 1)
var moving = false
var _moving_to = Vector2()
var _dash = false

const SPEED = 50

func set_team(blue):
	if blue:
		modulate_color = Color(0, 0.5, 1, 1)
	else:
		modulate_color = Color(1, 0.5, 0, 1)
	set_modulate(modulate_color)

func focus():
	set_modulate(modulate_color.lightened(0.75))

func unfocus():
	set_modulate(modulate_color)

func move_to(to, dash, pushed):
	assert not moving
	assert not pushed or dash
	_moving_to = to
	_dash = dash
	moving = true
	var anim = "hurt" if pushed else ("slide" if dash else "walk")
	$AnimatedSprite.play(anim)
	var dx = to.x - position.x
	if dx > 0:
		$AnimatedSprite.flip_h = false
	elif dx < 0:
		$AnimatedSprite.flip_h = true

func _process(delta):
	if moving:
		var diff = _moving_to - position
		if diff == Vector2():
			$AnimatedSprite.play("idle")
			moving = false
			emit_signal("finished_moving")
		else:
			var speed = SPEED * 2.5 if _dash else SPEED
			if diff.length() > speed * delta:
				position += (diff.normalized() * speed * delta)
			else:
				position = _moving_to
				$AnimatedSprite.play("idle")
				moving = false
				emit_signal("finished_moving")
