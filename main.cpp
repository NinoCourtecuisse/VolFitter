#include <iostream>
#include <fstream>
#include "DataContainer/Table.h"
#include "VolSlice/FlatSlice.h"
#include "VolSlice/SabrSlice.h"
#include "Utils/Utils.h"
#include <Eigen/Dense>
#include <format>
#include <chrono>

using namespace std;
using namespace Eigen;
typedef chrono::year_month_day Ymd;
typedef vector<Ymd> Dates;

int main() {
    string file_path = "Data/Input/";

    Ymd today{chrono::year{2024}, chrono::month{7}, chrono::day{31}};
    double S0 = 5535;
    double r = 0.05;

    vector<string> months({"August", "November", "October", "September"});
    Dates maturity_dates = {
        Ymd(chrono::year{2024}, chrono::month{8}, chrono::day{16}),
        Ymd(chrono::year{2024}, chrono::month{9}, chrono::day{20}),
        Ymd(chrono::year{2024}, chrono::month{10}, chrono::day{18}),
        Ymd(chrono::year{2024}, chrono::month{11}, chrono::day{15})
    };
    for (size_t i(0); i < months.size(); ++i) {
        string file_name(file_path + months[i] + ".csv");
        Table table(file_name);
        Ymd maturity = maturity_dates[i];

        chrono::sys_days d1 = chrono::sys_days{today};
        chrono::sys_days d2 = chrono::sys_days{maturity};
        chrono::days delta = d2 - d1;
        double ttm = delta.count() / 365.25;

        double init_vol = 0.2;
        FlatSlice flat_slice(ttm, init_vol);
        flat_slice.calibrate(table, S0, r);

        string outputFile("Data/Output/" + months[i] + "_flat.csv");
        double min_strike = table.getMin(string("Strike"));
        double max_strike = table.getMax(string("Strike"));
        int N = 30;
        VectorXd K = linspace(min_strike, max_strike, N);
        flat_slice.save(K, ttm, S0, r, outputFile);

        Vector4d init_params(0.9, 0.3, -0.5, 1.0);
        SabrSlice sabr_slice(ttm, init_params);
        sabr_slice.calibrate(table, S0, r);

        outputFile = "Data/Output/" + months[i] + "_sabr.csv";
        sabr_slice.save(K, ttm, S0, r, outputFile);
    }
    return 0;
}