#ifndef ZUMA_RECORD_HPP
#define ZUMA_RECORD_HPP

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using std::istream;
using std::pair;
using std::string;
using std::vector;

namespace zuma_highscore_reader {

struct Score_Entry {
    string player;
    int32_t score;
};

struct Time_Entry
{
    string header;
    string player;
    int32_t time;

    bool operator< (const Time_Entry &comp_entry) const {
        return header.compare(comp_entry.header);
    }

    bool operator< (const string &comp_header) const {
        return header.compare(comp_header);
    }

    friend bool operator< (const string &comp_string, const Time_Entry &comp_header) {
        return comp_string.compare(comp_header.header);
    }
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