#include <iostream>
#include <fstream>
#include <cfloat>
#include <cmath>
#include <iomanip>

using namespace std;

template <typename T>
T calculate_next_term(T x_previous_previous, T x_previous) {
    return 111 - ((1130 - 3000/x_previous_previous) / x_previous);
}

bool open_output_file(ofstream& file, const string& file_name) {
    file.open(file_name);
    if(!file) {
        cerr << "Error opening " << file_name << "\n";
        return false;
    }
    return true;
}

void create_data_file() {
    ofstream data_file;
    remove("data.csv");
    if (!open_output_file(data_file, "data.csv")) return;

    data_file << std::setprecision(20) << "n;Float;Double;Long Double\n";
    auto write_data_to_file = [&data_file](int n, float float_value, double double_value, long double long_double_value) {
        data_file << n << ";"
                  << float_value << ";" 
                  << double_value << ";"
                  << long_double_value << "\n"; 
    };

    float float_prev_prev = 11.0f/2, float_prev = 61.0f/11, float_next;
    double double_prev_prev = 11.0/2, double_prev = 61.0/11, double_next;
    long double long_double_prev_prev = 11.0L/2, long_double_prev = 61.0L/11, long_double_next;
    write_data_to_file(0, float_prev_prev, double_prev_prev, long_double_prev_prev);
    write_data_to_file(1, float_prev, double_prev, long_double_prev);
    
    for (int i = 2; i <= 34; i++) {
        float_next = calculate_next_term<float>(float_prev_prev, float_prev);
        double_next = calculate_next_term<double>(double_prev_prev, double_prev);
        long_double_next = calculate_next_term<long double>(long_double_prev_prev, long_double_prev);
        write_data_to_file(i, float_next, double_next, long_double_next);

        float_prev_prev = float_prev;
        double_prev_prev = double_prev;
        long_double_prev_prev = double_prev;

        float_prev = float_next;
        double_prev = double_next;
        long_double_prev = long_double_next;
    }

    data_file.close();
}

int main(void) {
    create_data_file();
}
