extends Node

var team = 0
var agent_selected = 0
var animating = false

const MapReader = preload("res://scripts/MapReader.gd")

onready var DIR = $GameState.DIR
onready var NB_AGENTS = $GameState.NB_AGENTS


func _ready():
	var map = MapReader.parse_map("res://../../maps/test_map")
	$GameState/TileMap.init(map.walls, map.agents)
	for agent in $GameState/TileMap.agents:
		 agent.connect("finished_moving", self, "_finish_animating")
	_select_agent(team * NB_AGENTS)

func _finish_animating():
	animating = false
	
func _input_move(dir):
	var dash = Input.is_action_pressed("ui_shift")
	var agent_id = agent_selected % NB_AGENTS
	var player = agent_selected / NB_AGENTS
	assert player == 0 or player == 1
	if Input.is_action_pressed("ui_ctrl"):
		animating = $GameState.push(agent_id, dir, player)
	elif dash:
		$GameState.slide(agent_id, dir, player)
		animating = true
	else:
		animating = $GameState.move(agent_id, $GameState/TileMap.agents_pos[agent_selected] + DIR[dir], player)

func _select_agent(i):
	assert i >= 0 and i < 2 * NB_AGENTS
	$GameState/TileMap.agents[agent_selected].unfocus()
	$GameState/TileMap.agents[i].focus()
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
