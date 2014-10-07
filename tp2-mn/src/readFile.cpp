#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int > > leerInstancia0(string fileName) {
    vector<vector<int > > result;

    string line;
    int a,b,lastNode;
    lastNode = -1;
    ifstream myReadFile(fileName.c_str());
    if (myReadFile.is_open()){
        int page = 1;
        while (page < 3) {
            getline(myReadFile,line);
            page ++;
        }

        string q,w;
        int amount;

        myReadFile >> q >> w >> amount;

        result = vector<vector<int > >(amount);

        getline(myReadFile,line);
        getline(myReadFile,line);

        while (!myReadFile.eof()) {
            myReadFile >> a >> b;
            if ((a-1) != lastNode || lastNode == -1){
                result[a-1] = vector<int >();
                lastNode = a-1;
            }
            result[a-1].push_back((b-1));
        }
    }
    myReadFile.close();

    for (int i = 0 ; i < result.size() ; i++){
        cout << i << ": " << flush;
        for (int j = 0 ; j < result[i].size() ; j++){
            cout << result[i][j] << " ";
        }
        cout << endl;
    }



    return result;
}

vector<vector<int > > leerInstancia1(string fileName) {
    vector<vector<int > > result;

    string line, ss, node;
    int buf;

    ifstream myReadFile(fileName.c_str());

    if (myReadFile.is_open()){
        while (getline(myReadFile,line)) {
            node = line.substr(0, line.find(":"));
            ss = line.substr(line.find(":")+1, line.length()-1);

            istringstream iss(ss);

            vector<int > tokens;

            while (iss >> buf){
                if (buf == -1)
                    break;
                tokens.push_back(buf);
            }

            result.push_back(tokens);
        }
    }
    myReadFile.close();

    for (int i = 0 ; i < result.size() ; i++){
        cout << i << ": " << flush;
        for (int j = 0 ; j < result[i].size() ; j++){
            cout << result[i][j] << " ";
        }
        cout << endl;
    }



    return result;
}


