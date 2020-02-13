/*
 MIT License
 
 Copyright (c) 2020 Jordan Sola
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

class Player {
public:
    Player(string name = "") : player_name(name) {};
    ~Player() {};
    void GainSpy() {
        has_spy = true;
    }
    void RemoveSpy() {
        has_spy = false;
    }
    void GainHandmaid() {
        has_handmaid = true;
    }
    void RemoveHandmaid() {
        has_handmaid = false;
    }
    void GainToken() {
        token_count++;
    }
    void SetCurrentPlayer() {
        is_current_player = true;
    }
    int GetTokenCount() const {
        return token_count;
    }
    bool HandmaidStatus() const {
        return has_handmaid;
    }
    bool SpyStatus() const {
        return has_spy;
    }
    bool GetCurrentStatus() const {
        return is_current_player;
    }
    string GetName() const {
        return player_name;
    }
private:
    bool has_spy = false;
    bool has_handmaid = false;
    bool is_current_player = false;
    int token_count = 0;
    string player_name;
};
