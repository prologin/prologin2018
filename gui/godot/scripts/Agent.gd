extends KinematicBody2D

var modulate_color = Color(1, 1, 1, 1)
var moving = false
var _moving_to = Vector2()
var _dash = false

const SPEED = 100

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

func move_to(to, dash):
	assert not moving
	_moving_to = to
	_dash = dash
	moving = true
	var anim = "slide" if _dash else "walk"
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
		else:
			var speed = SPEED * 2.5 if _dash else SPEED
			if diff.length() > speed * delta:
				move_and_slide(diff.normalized() * speed)
			else:
				move_and_slide(diff / delta)