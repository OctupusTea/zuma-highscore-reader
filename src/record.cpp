#include "common.hpp"
#include "record.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>

#ifdef DEBUG
    #define DEBUG_RECORD
#endif

#ifdef DEBUG_RECORD
    #define DEBUG_RECORD_SCORE
    #define DEBUG_RECORD_TIME
#endif

using namespace std;

namespace zuma_highscore_reader {

ZumaHighscore::ZumaHighscore (istream *record_file) {
    Read(record_file);
}

void ZumaHighscore::Read (istream *record_file) {
    record_storage.version = Read_Int32(record_file);

#ifdef DEBUG_RECORD
    cerr << "version = " << record_storage.version << endl;
#endif

    //  Read score records
    record_storage.score_records.resize(Read_Int16(record_file));
#ifdef DEBUG_RECORD_SCORE
    cerr << "score record count = " << record_storage.score_records.size() << endl;
#endif
    for (auto &i : record_storage.score_records) {
        i.header = Read_String(record_file);
        i.score_list.resize(Read_Int16(record_file));
#ifdef DEBUG_RECORD_SCORE
        cerr << "score record of " << i.header << ", count = " << i.score_list.size() << endl;
#endif
        for (auto &j : i.score_list) {
            j.player = Read_String(record_file);
            j.score = Read_Int32(record_file);
#ifdef DEBUG_RECORD_SCORE
            cerr << "\t" << j.score << " by " << j.player << endl;
#endif
        }
    }

    //  Read time records
    record_storage.time_records.resize(Read_Int32(record_file));
#ifdef DEBUG_RECORD_TIME
    cerr << "time record count = " << record_storage.time_records.size() << endl;
#endif
    for (auto &i : record_storage.time_records) {
        i.header = Read_String(record_file);
        i.player = Read_String(record_file);
        i.time = Read_Int32(record_file);
#ifdef DEBUG_RECORD_TIME
        cerr << "Stage " << i.header << ": " << i.time << " seconds by " << i.player << endl;
#endif
    }
}

Time_Entry ZumaHighscore::Get_Best_Time (const int stage, const int level) const {
    int numeric_level = adventure_adder[stage] + level;
    string level_string = "a" + to_string(numeric_level);

    auto query_range = equal_range(record_storage.time_records.begin(),
                                   record_storage.time_records.end(),
                                   level_string);
    if (query_range.first == query_range.second) {
        return {level_string, "NONE", -1};
    }
    else {
        return *(query_range.first);
    }
}

}