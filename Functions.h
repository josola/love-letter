/*
Jordan Sola 2019
Function delcarations that are used in Functions.cpp
TODO:

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
void choose_target_player(int target);

//suitor modifiers

void
switch_player_turn(),
discard(),
remove_player_from_play(int suitor),
set_winning_token_count();

//deck modifiers

void
shuffle_deck(),
reset_deck();

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
Princess(),
PlayCard();

//game state functions

void
initial_game_setup(),
begin_game_round(),
player_turn(),
end_game_round();

//game

void play_game();