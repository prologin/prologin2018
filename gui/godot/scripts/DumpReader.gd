# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright 2018 Sacha Delanoue

static func parse_dump(filename):
	var file = File.new()
	file.open(filename, file.READ)
	var rounds = []
	
	while not file.eof_reached():
		rounds.append(JSON.parse(file.get_line()).result)
	
	return rounds

class PlayerStats:
	var name = ""
	var score = 0
	var agents = []
	var history = []

class Alien:
	var pos = Vector2()
	var points = 0
	var first_turn = 0
	var duration = 0
	var capture = 0

class Turn:
	var roundNumber = 0
	var roundTotal = 0
	var players = []
	var map_size = 0
	var walls = []
	var aliens = []
	var storms = []
	var storms_dir = ""

static func parse_turn(json):
	var result = Turn.new()
	result.roundNumber = json["round"][0]
	result.roundTotal = json["round"][1]
	assert(json["players"].size() == 2)
	for player_id in ["1", "2"]:
		var node = json["players"][player_id]
		var player = PlayerStats.new()
		player.name = node["name"]
		for i in range(node["agents"].size()):
			player.agents.append(Vector2(-1, -1))
		for agent in node["agents"]:
			player.agents[agent["id_agent"]] = Vector2(agent["pos"]["c"], agent["pos"]["r"])
		player.history = node["history"]
		result.players.append(player)
	var cells = json["map"]["cells"]
	var size = sqrt(cells.size())
	result.map_size = size
	for c in range(size):
		result.walls.append([])
		for r in range(size):
			result.walls[c].append(cells[r * size + c] == "MUR")
	for alien_data in json["map"]["aliens"]:
		var alien = Alien.new()
		alien.pos = Vector2(alien_data["pos"]["c"], alien_data["pos"]["r"])
		alien.points = alien_data["points_capture"]
		alien.first_turn = alien_data["tour_invasion"]
		alien.duration = alien_data["duree_invasion"]
		alien.capture = alien_data["capture_en_cours"]
		result.aliens.append(alien)
	result.storms = json["map"]["storms"]
	result.storms_dir = json["map"]["storms_dir"]
	return result