/*
Jordan Sola 2019
Function delcarations that are used in Functions.cpp
TODO:
Need to finish placing suitor modifiers and deck functions. 1/29/20 10:34PM CST
*/

#pragma once

//output functions

void
print_player_name(int suitor),
clear_output_window(),
print_line_seperator(),
print_up_pile_cards(),
print_deck_size(),
print_players_with_spy_bonus(),
print_active_players(),
print_cards_in_hand(int suitor);

//cardposition functions

bool find_card_in_hand(int suitor, int card);
int find_card_position_within_hand(int suitor, int pos);

//input checks

void clear_input();
bool
check_proper_card_input(),
check_proper_player_input(),
check_proper_player_count();

//suitor status checks

bool
check_countess_restriction(),
check_player_active(),
check_target_handmaid_protection();

//suitor modifiers

//deck modifiers

//card functions

void
Spy(),
Guard(),
Priest(),
Baron(),
Handmaid(),
Prince(),
Chancellor(),
King(int agressor, int victim),
Princess();

//game functions

void
print_up_pile_cards(),
print_deck_size(),
print_players_with_spy_bonus(),
switch_player_turn(),
discard(),
print_active_players(),
choose_target_player(int target),
PlayCard(),
initial_game_setup(),
player_turn(),
end_game_round(),
PlayCard(),
clear_output_window(),
play_game(),
print_line_seperator(),
remove_player_from_play(int suitor),
set_winning_token_count(),
shuffle_deck(),
reset_deck(),
begin_game_round();

