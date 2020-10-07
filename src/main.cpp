#include "common.hpp"
#include "record.hpp"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#ifdef DEBUG
    #define DEBUG_MAIN
#endif

using namespace std;

namespace zuma_highscore_reader{

string process_name = "";

void Usage (int exit_code) {
    cerr << "Usage: " << process_name << " [[zuma-highscore-file]... | -h]" << endl
         << "\t-zuma-highscore-file: Specitfy Zuma highscore file locattion;" << endl
         << "\t                      otherwise, \"%programfiles(x86)%\\Zuma Deluxe\\userdata\\highscores.dat\" is used" << endl
         << "\t-h:                   Show this message." << endl;
    exit(exit_code);
}

void Parse_Arg (int argc, char **argv, vector<string> &zuma_hs_file_paths) {
    process_name = argv[0];

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'h':
                    Usage(0);
                    break;
                default:
                    Usage(1);
            }
            i++;
        }
        else {
            zuma_hs_file_paths.push_back(argv[i]);
        }
    }
}

bool File_Check(const fstream *test_file, const string &file_name, const bool empty_check) {
    if (empty_check and test_file -> eof()) {
        cerr << "Empty file: " << file_name << endl;
        return false;
    }
    if (test_file -> fail()) {
        cerr << "Error handling file: " << file_name << endl;
        return false;
    }
    if (test_file -> bad()) {
        cerr << "Error opening file: " << file_name << endl;
        return false;
    }
    return true;
}

void File_Establishment (vector<string> &zuma_hs_file_paths, vector<fstream *> &zuma_hs_files) {
    if (zuma_hs_file_paths.size() == 0) {
        char *prog_path = getenv("%programfiles(x86)%");
        if (prog_path == nullptr) {
            cerr << "Are you not using 64-bit Windows?" << endl;
            Usage(1);
        }
        else {
            zuma_hs_file_paths.push_back(string(prog_path) + "\\Zuma Deluxe\\userdata\\highscores.dat");
        }
    }

    bool file_error = false;
    for (auto &path : zuma_hs_file_paths) {
        fstream *fs = new fstream(path, ios_base::in | ios_base::binary);
        if (File_Check(fs, path, true)) {
            zuma_hs_files.push_back(fs);
        }
        else {
            file_error = true;
            break;
        }
    }

    if (file_error) {
        for (auto &fs : zuma_hs_files) {
            fs -> close();
            delete fs;
        }

        Usage(1);
    }
}

int Zuma_Highscore_Reader (int argc, char **argv) {
    vector<string> zuma_hs_file_paths;
    vector<fstream *> zuma_hs_files;
    vector<ZumaHighscore> zuma_highscores;

    Parse_Arg(argc, argv, zuma_hs_file_paths);

#ifdef DEBUG_MAIN
    cerr << "Parsed args: " << endl
         << "zuma_hs_file_path = " << zuma_hs_file_path << endl
         << "input_path = " << input_path << endl
         << "output_path = " << output_path << endl;
#endif

    File_Establishment(zuma_hs_file_paths, zuma_hs_files);

    for (auto& zuma_hs_file : zuma_hs_files) {
        ZumaHighscore temp = ZumaHighscore(zuma_hs_file);
        zuma_highscores.push_back(temp);
    }

    for (int stage = 1; stage <= 13; stage++) {
        int level_count = stage > 12 ? 1 : (stage > 6 ? 7 : (stage > 3 ? 6 : 5));
        for (int level = 1; level <= level_count; level++) {
            Time_Entry overall_best = Time_Entry::Empty_Entry("");
            for (auto &highscore : zuma_highscores) {
                auto best_time_record = highscore.Get_Best_Time(stage, level);
                if (best_time_record < overall_best) {
                    overall_best = best_time_record;
                }
            }

            if (overall_best.time == UINT32_MAX) {
                cout << "Stage " << to_string(stage) << "-" << to_string(level) << ": "
                     << "No recorded time so far." << endl;
            }
            else {
                cout << "Stage " << to_string(stage) << "-" << to_string(level) << ": "
                     << overall_best.time << " seconds by " << overall_best.player << endl;
            }
        }
    }

    for (auto &zuma_hs_file : zuma_hs_files) {
        zuma_hs_file -> close();
        delete zuma_hs_file;
    }

    return 0;
}

}


int main (int argc, char **argv) {
    return zuma_highscore_reader::Zuma_Highscore_Reader(argc, argv);
}
