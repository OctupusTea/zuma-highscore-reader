#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace zuma_highscore_reader {

int16_t Read_Int16 (istream *input_stream) {
    int16_t temp;
    input_stream->read(reinterpret_cast<char *>(&temp), 2);
    return temp;
}

uint16_t Read_UInt16 (istream *input_stream) {
    uint16_t temp;
    input_stream->read(reinterpret_cast<char *>(&temp), 2);
    return temp;
}

int32_t Read_Int32 (istream *input_stream) {
    int32_t temp;
    input_stream->read(reinterpret_cast<char *>(&temp), 4);
    return temp;
}

uint32_t Read_UInt32 (istream *input_stream) {
    uint32_t temp;
    input_stream->read(reinterpret_cast<char *>(&temp), 4);
    return temp;
}

string Read_String (istream *input_stream) {
    int16_t length = Read_UInt16(input_stream);
    string temp(length, '\0');
    input_stream->read(&(temp[0]), length);
    return temp;
}

const static int adventure_adder[14] = {-1, -1, 4, 9, 14, 20, 26, 32, 39, 46, 53, 60, 67, 74};
const static string adventure_level_id[4][8] = {
    {"space"},
    {"", "spiral", "claw", "riverbed", "targetglyph", "blackswirley", "turnaround", "longrange"},
    {"", "tiltspiral", "underover", "warshak", "loopy", "snakepit", "groovefest", "spaceinvaders"},
    {"", "triangle", "coaster", "squaresville", "tunnellevel", "serpents", "overunder", "inversespiral"}
};

} // namespace zuma_highscore_reader