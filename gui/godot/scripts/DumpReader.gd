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

class Turn:
	var roundNumber = 0
	var roundTotal = 0
	var players = []
	var map_size = 0
	var walls = []

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
			player.agents.append([-1, -1])
		for agent in node["agents"]:
			player.agents[agent["id_agent"]] = [agent["pos"]["r"], agent["pos"]["c"]]
		for history in node["history"]:
			pass # TODO
		result.players.append(player)
	var cells = json["map"]["cells"]
	var size = sqrt(cells.size())
	result.map_size = size
	for r in range(size):
		for c in range(size):
			if cells[r * size + c] == "MUR":
				result.walls.append([r, c])