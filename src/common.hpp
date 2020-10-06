#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace zuma_highscore_reader {

int32_t Read_Int32(istream *input_stream);
int16_t Read_Int16(istream *input_stream);
string Read_String(istream *input_stream);

const static int adventure_adder[14] = {-1, -1, 4, 9, 14, 20, 26, 32, 39, 46, 53, 60, 67, 74};
const static string adventure_level_id[4][8] = {
    {"space"},
    {"", "spiral", "claw", "riverbed", "targetglyph", "blackswirley", "turnaround", "longrange"},
    {"", "tiltspiral", "underover", "warshak", "loopy", "snakepit", "groovefest", "spaceinvaders"},
    {"", "triangle", "coaster", "squaresville", "tunnellevel", "serpents", "overunder", "inversespiral"}
};

} // namespace zuma_highscore_reader