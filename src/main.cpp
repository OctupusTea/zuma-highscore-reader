#include "common.hpp"
#include "record.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#ifdef DEBUG
    #define DEBUG_MAIN
#endif

using namespace std;

namespace zuma_highscore_reader{

string process_name = "";

istream *zuma_hs_file = nullptr;
istream *input_file = nullptr;
ostream *output_file = nullptr;

void Usage (int exit_code) {
    cerr << "Usage: " << process_name << " [[-z zuma-highscore-file] [-i input] [-o output] | -h]" << endl
         << "\t-z zuma-highscore-file: Specitfy Zuma highscore file locattion; otherwise, \"%programfiles(x86)%\\Zuma Deluxe\\userdata\\highscores.dat\" is used" << endl
         << "\t-i input: Specify input file location; otherwise, STDIN is used." << endl
         << "\t-o output: Specify output file location; otherwise, STDOUT is used." << endl
         << "\t-h: Show this message." << endl;
    exit(exit_code);
}

void Parse_Arg (int argc, char **argv, string &zuma_hs_file_path, string &input_path, string &output_path) {
    process_name = argv[0];

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            string file_path = "";
            if (i + 1 < argc) {
                file_path = argv[i + 1];
            }
            else {
                Usage(1);
            }

            switch (argv[i][1]) {
                case 'z':
                    zuma_hs_file_path = file_path;
                    break;
                case 'i':
                    input_path = file_path;
                    break;
                case 'o':
                    output_path = file_path;
                    break;
                case 'h':
                    Usage(0);
                    break;
                default:
                    Usage(1);
            }
            i++;
        }
        else {
            Usage(1);
        }
    }
}

void File_Check(const ios *test_file, const string &file_name, const bool empty_check) {
    if (empty_check and test_file -> eof()) {
        cerr << "Empty file: " << file_name << endl;
        exit(1);
    }
    if (test_file -> fail()) {
        cerr << "Error handling file: " << file_name << endl;
        exit(1);
    }
    if (test_file -> bad()) {
        cerr << "Error opening file: " << file_name << endl;
        exit(1);
    }
}

void File_Establishment (string &zuma_hs_file_path, const string &input_path, const string &output_path) {
    if (zuma_hs_file_path == "") {
        char *prog_path = getenv("%programfiles(x86)%");
        if (prog_path == nullptr) {
            cerr << "Are you not using 64-bit Windows?" << endl;
            Usage(1);
        }
        else {
            zuma_hs_file_path = string(prog_path) + "\\Zuma Deluxe\\userdata\\highscores.dat";
        }
    }

    ifstream *zuma_hs_fs = new ifstream(zuma_hs_file_path);
    zuma_hs_file = zuma_hs_fs;
    File_Check(zuma_hs_file, zuma_hs_file_path, true);

    if (input_path == "") {
        input_file = &cin;
    }
    else {    
        ifstream *input_fs = new ifstream(input_path);
        input_file = input_fs;
        File_Check(input_file, input_path, true);
    }

    if (output_path == "") {
        output_file = &cout;
    }
    else {
        ofstream *output_fs = new ofstream(output_path);
        output_file = output_fs;
        File_Check(output_file, output_path, false);
    }
}

int Zuma_Highscore_Reader (int argc, char **argv) {
    string zuma_hs_file_path;
    string input_path;
    string output_path;

    Parse_Arg(argc, argv, zuma_hs_file_path, input_path, output_path);

#ifdef DEBUG_MAIN
    cerr << "Parsed args: " << endl
         << "zuma_hs_file_path = " << zuma_hs_file_path << endl
         << "input_path = " << input_path << endl
         << "output_path = " << output_path << endl;
#endif

    File_Establishment(zuma_hs_file_path, input_path, output_path);

    ZumaHighscore highscore = ZumaHighscore(zuma_hs_file);
    /*for (int stage = 1; stage <= 12; stage++) {
        int level_count = stage > 6 ? 7 : (stage > 3 ? 6 : 5);
        for (int level = 1; level <= level_count; level++) {
            auto best_time_record = highscore.Get_Best_Time(stage, level);
            if (best_time_record.time == -1) {
                (*output_file) << "Stage " << to_string(stage) << "-" << to_string(level) << ": "
                               << "No recorded time so far." << endl;
            }
            else {
                (*output_file) << "Stage " << to_string(stage) << "-" << to_string(level) << ": "
                               << best_time_record.time << " seconds by " << best_time_record.player << endl;
            }
        }
    }*/

    delete zuma_hs_file;

    if (input_path != "") {
        delete input_file;
    }

    if (output_path != "") {
        delete output_file;
    }

    return 0;
}

}


int main (int argc, char **argv) {
    return zuma_highscore_reader::Zuma_Highscore_Reader(argc, argv);
}
