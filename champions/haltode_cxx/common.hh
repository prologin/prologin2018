// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright 2018 Thibault Allançon

#ifndef COMMON_HH
#define COMMON_HH

#include "prologin.hh"
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const int INF = 1e9;

// prologin.cc

int compute_average_alien_points();

// coop_mode.cc

void play_coop_mode();
void choose_coop_target();
void choose_coop_agents();
void guard_mode_coop(int agent_id);
void push_ennemy_from_coop_target();
bool is_coop_agent(int agent_id);
bool is_coop_target(alien_info alien);

// solo_mode.cc

void play_solo_mode();
void init_solo_targets();

// pathfinding.cc

std::vector<action_hist> get_shortest_path(position start, position dest);

// move.cc

void do_actions(int agent_id, std::vector<action_hist> actions);
void move_agent(int agent_id, position dest);
void move_agent_radius(int agent_id, position dest, int radius);
position simulate_slide(position start, direction dir);
int cost_action_points(std::vector<action_hist> path);
int cost_move(position start, position dest);
int cost_turn(position start, position dest);
int cost_turn_with_push(position start, position dest);

// push.cc

std::pair<position, direction> get_push_cell(int agent_id, position target);
void push_around(int agent_id);

// closest.cc

int get_closest_agent(int player_id, position dest);
alien_info get_closest_alien(int player_id, alien_info last_target);
position get_empty_cell_radius(position start, position dest, int radius);

// utils.cc

int cost_single_action(action_hist action);
bool can_push_agent_from(position pos);
int cnt_open_dir(position pos);
void sort_aliens_by_time(std::vector<alien_info>& aliens);
bool alien_shoud_be_on_round(alien_info alien);
bool inside_map(position pos);
bool is_obstacle(position pos);
int manhattan_dist(position a, position b);
position operator+(position a, position b);
position get_position_offset(const position pos, const direction dir);
direction opposite_dir(direction dir);
std::pair<direction, direction> orth_dir(direction dir);

#endif
