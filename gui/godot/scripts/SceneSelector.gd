extends Node

func _ready():
	for arg in OS.get_cmdline_args():
		if arg.begins_with("-json="):
			get_tree().change_scene("res://scenes/Replay.tscn")
			return
	get_tree().quit()