# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright 2018 Sacha Delanoue

extends Node

const DIR = [Vector2(-1, 0), Vector2(0, 1), Vector2(1, 0), Vector2(0, -1)]
const NB_AGENTS = 4

const COST_MOVE = 1
const COST_SLIDE = 3
const COST_PUSH = 4

func agent_id_to_internal(agent_id, player_id):
	return agent_id + NB_AGENTS * player_id

func internal_to_agent_id(internal):
	return internal % NB_AGENTS

func move(agent_id, direction, player_id):
	var internal = agent_id_to_internal(agent_id, player_id)
	var destination = $TileMap.agents_pos[internal] + DIR[direction]
	if not $TileMap.is_cell_free(destination):
		return false
	$TileMap.move_agent(internal, destination, false, false)
	$Info.players[player_id].action_points -= COST_MOVE
	$Info.redraw()
	return true

func slide(agent_id, dir, player_id, pushed = false):
	var internal = agent_id_to_internal(agent_id, player_id)
	var dest = $TileMap.agents_pos[internal]
	while $TileMap.is_cell_free(dest + DIR[dir]):
		dest += DIR[dir]
	$TileMap.move_agent(internal, dest, true, pushed)
	if not pushed:
		$Info.players[player_id].action_points -= COST_SLIDE
		$Info.redraw()
	return true

func push(agent_id, dir, player_id):
	var internal = agent_id_to_internal(agent_id, player_id)
	var destination = $TileMap.agents_pos[internal] + DIR[dir]
	var agent = $TileMap.agents_pos.find(destination)
	if agent == -1:
		return false
	slide(internal_to_agent_id(agent), dir, agent / NB_AGENTS, true)
	$Info.players[player_id].action_points -= COST_PUSH
	$Info.redraw()
	return true

func init(walls, agents):
	$TileMap.init(walls, agents)
	$Info.position.y = $TileMap.walls.size() * $TileMap.cell_size.y * $TileMap.scale.y
