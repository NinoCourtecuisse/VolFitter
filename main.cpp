#include <iostream>
#include "DataContainer/Table.h"
#include "VolSlice/FlatSlice.h"
using namespace std;

int main() {
    string fileName("Data/August.csv");
    Table table(fileName);

    vector<string> header(table.getHeader());
    //cout << header[0] << " " << header[1] << endl;
    
    //table.printHead();

    FlatSlice slice(double(1.0));
    slice.calibrate(table);
    return 0;
}