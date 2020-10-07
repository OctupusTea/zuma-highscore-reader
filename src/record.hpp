#ifndef ZUMA_RECORD_HPP
#define ZUMA_RECORD_HPP

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace zuma_highscore_reader {

struct Score_Entry {
    string player;
    int32_t score;
};

struct Time_Entry
{
    string header;
    string player;
    uint32_t time;

    bool operator< (const string &comp_header) const { return header < comp_header; }
    friend bool operator< (const string &comp_header, const Time_Entry &comp_entry) { return comp_header < comp_entry.header; }
    bool operator> (const string &comp_header) const { return header > comp_header; }
    friend bool operator> (const string &comp_header, const Time_Entry &comp_entry) { return comp_header > comp_entry.header; }

    bool operator< (const uint32_t comp_time) const { return time < comp_time; }
    friend bool operator< (const uint32_t comp_time, const Time_Entry &comp_entry) { return comp_time < comp_entry.time; }
    bool operator> (const uint32_t comp_time) const { return time > comp_time; }
    friend bool operator> (const uint32_t comp_time, const Time_Entry &comp_entry) { return comp_time > comp_entry.time; }

    bool operator< (const Time_Entry &comp_entry) { return time < comp_entry.time; }
    bool operator> (const Time_Entry &comp_entry) { return time > comp_entry.time; }

    bool operator== (const Time_Entry &assign_entry) const {
            return (header == assign_entry.header and player == assign_entry.player and time == assign_entry.time);
    }

    static Time_Entry Empty_Entry (const string &header) { return {header, "NONE", UINT32_MAX}; }
};

struct RecordStorage
{
    int32_t version;
    
    struct Score_List {
        string header;
        vector<Score_Entry> score_list;
    };
    vector<Score_List> score_records;
    vector<Time_Entry> time_records;
};

class ZumaHighscore {
    protected:
        RecordStorage record_storage;

    public:
        ZumaHighscore (istream *record_file);
        void Read (istream *record_file);
        Time_Entry Get_Best_Time (const int stage, const int level) const;
};

} // namespace zuma_highscord_reader

#endif