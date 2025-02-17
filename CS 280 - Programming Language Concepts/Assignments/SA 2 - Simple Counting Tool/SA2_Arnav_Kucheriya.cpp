#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct FileStats {
    int totalLines = 0;
    int commentedLines = 0;
    int commandLines = 0;
    int boldCommands = 0;
    int italicCommands = 0;
    int regularCommands = 0;
    int underlineCommands = 0;
};

string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

string getCommand(const string& line) {
    // Check for "<<<" and treat it as an empty command
    if (line.length() >= 3 && line[0] == '<' && line[1] == '<' && line[2] == '<') {
        size_t pos = 3;
        // Skip leading spaces and tabs
        while (pos < line.length() && (line[pos] == ' ' || line[pos] == '\t')) pos++;
        // If there's any non-space character after "<<<", it's not an empty command
        if (pos < line.length()) {
            return ""; // Treat as empty command if there's any non-space character
        }
        return ""; // If only spaces/tabs after "<<<", treat as empty command
    }

    // Check for ">>>" and treat it as an empty command
    if (line.length() >= 4 && line[0] == '>' && line[1] == '>' && line[2] == '>' && line[3] == ' ') {
        return ""; 
    }

    // Check for ">>" command prompt
    if (line.length() < 2 || line[0] != '>' || line[1] != '>') 
        return "";

    string cmd = "";
    size_t pos = 2;  // Start after ">>"

    // Skip leading spaces and tabs
    while (pos < line.length() && (line[pos] == ' ' || line[pos] == '\t')) pos++;

    // Get the command
    while (pos < line.length() && line[pos] != ' ' && line[pos] != '\t') {
        cmd += line[pos];
        pos++;
    }

    return cmd;
}

FileStats processFile(const string& filename) {
    FileStats stats;
    ifstream file(filename);
    string line;
    int lineNumber = 1;

    if (!file.is_open()) {
        cout << endl << "CANNOT OPEN THE FILE " << filename << endl; 
        exit(1);
    }

    if (file.peek() == ifstream::traits_type::eof()) {
        cout << "The File is Empty." << endl;
        exit(1);
    }

    while (getline(file, line)) {
        stats.totalLines++;

        // Check for comments
        if (line.length() >= 2 && line[0] == '/' && line[1] == '/') {
            stats.commentedLines++;
            lineNumber++;
            continue;
        }

        // Check for commands
        if ((line.length() >= 2 && line[0] == '>' && line[1] == '>') ||
            (line.length() >= 3 && line[0] == '<' && line[1] == '<' && line[2] == '<') ||
            (line.length() >= 3 && line[0] == '>' && line[1] == '>' && line[2] == '>')) {
            string cmd = getCommand(line);

            // Check for empty command
            if (cmd.empty()) {
                cout << "Error: No command name following a command prompt in line " << lineNumber << endl;
                lineNumber++;
                continue;
            }

            string lcmd = toLowerCase(cmd);

            // Process commands
            if (lcmd == "bold" || lcmd == "bo") {
                stats.boldCommands++;
                stats.commandLines++;
            }
            else if (lcmd == "italic" || lcmd == "it") {
                stats.italicCommands++;
                stats.commandLines++;
            }
            else if (lcmd == "regular" || lcmd == "re") {
                stats.regularCommands++;
                stats.commandLines++;
            }
            else if (lcmd == "underline" || lcmd == "un") {
                stats.underlineCommands++;
                stats.commandLines++;
            }
            else {
                cout << "Error: Unrecognizable command name \"" << cmd << "\" in line " << lineNumber << endl;
            }
        }

        lineNumber++; 
    } 

    // Add a blank line after errors and before statistics
    if (lineNumber > 1) {
        cout << endl;
    }

    file.close();
    return stats;
}

int main() {
    string filename;
    cout << "Enter the file name to read from:" << endl;
    cin >> filename;

    FileStats stats = processFile(filename);

    // Print statistics
    cout << "Total lines: " << stats.totalLines << endl;
    cout << "Commented lines: " << stats.commentedLines << endl;
    cout << "Command lines: " << stats.commandLines << endl;
    cout << "Bold commands: " << stats.boldCommands << endl;
    cout << "Italic commands: " << stats.italicCommands << endl;
    cout << "Regular commands: " << stats.regularCommands << endl;
    cout << "Underline commands: " << stats.underlineCommands << endl;

    return 0;
}