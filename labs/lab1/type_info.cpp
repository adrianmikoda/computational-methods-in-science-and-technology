#include <bits/stdc++.h>
using namespace std;

template<typename T>
std::string type_name();

template<>
std::string type_name<float>() { return "Float"; }

template<>
std::string type_name<double>() { return "Double"; }

template<>
std::string type_name<long double>() { return "Long Double"; }

bool open_output_file(ofstream& file, const string& file_name) {
    file.open(file_name);
    if(!file) {
        cerr << "Error opening " << file_name << "\n";
        return false;
    }
    return true;
}

void create_type_info_file() {
    remove("type_info.csv");

    ofstream type_info_file;
    if (!open_output_file(type_info_file, "type_info.csv")) return;

    type_info_file << "Name,Size,Precision,Min,Max,Mantissa Bits,Exponent Bits,Epsilon\n";
    auto write_properties_to_file = [&type_info_file](auto name, auto size, auto precision, auto min, auto max,
                                                       auto mantissa, auto exponent, auto epsilon) {
        type_info_file << name << ","
                       << size << ","
                       << precision << "," 
                       << min << ","
                       << max << ","
                       << mantissa << ","
                       << exponent << ","
                       << epsilon << "\n"; 
    };
    write_properties_to_file("float", sizeof(float), FLT_DIG, FLT_MIN, FLT_MAX,
                             FLT_MANT_DIG, ceil(log2(FLT_MAX_EXP - FLT_MIN_EXP + 1)), FLT_EPSILON);
    write_properties_to_file("double", sizeof(double), DBL_DIG, DBL_MIN, DBL_MAX,
                             DBL_MANT_DIG, ceil(log2(DBL_MAX_EXP - DBL_MIN_EXP + 1)), DBL_EPSILON);
    write_properties_to_file("long double", sizeof(long double), LDBL_DIG, LDBL_MIN, LDBL_MAX,
                             LDBL_MANT_DIG, ceil(log2(LDBL_MAX_EXP - LDBL_MIN_EXP + 1)), LDBL_EPSILON);

    type_info_file.close();
}

template<typename T>
string convert_to_binary(T x) {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&x);
    string s = "";
    size_t byte_count = is_same<T, long double>::value ? 9 : sizeof(T)-1;
    for (int i = byte_count; i >= 0; --i) {
        s += bitset<8>(bytes[i]).to_string();
    }

    size_t sgn = 1;
    size_t exp = 8;
    size_t mant = 23;
    if (is_same_v<T, double>) {
        exp = 11;
        mant = 52;
    }
    else if (is_same_v<T, long double>) {
        exp = 15;
        mant = 64;
    }

    return s.substr(0,sgn) + "," + s.substr(sgn,exp) + "," + s.substr(exp+sgn,mant);
}

template<typename T>
string csv_line(string label, T value) {
    return label + "," + type_name<T>() + "," + convert_to_binary(value) + "\n";
}

template<typename... Ts>
string zero_representation() {
    string s;
    ((s += csv_line("-0", static_cast<Ts>(-0.0))), ...);
    ((s += csv_line("0",  static_cast<Ts>(0.0))), ...);
    return s;
}

template<typename... Ts>
string inf_representation() {
    string s;
    ((s += csv_line("-inf", static_cast<Ts>(-numeric_limits<Ts>::infinity()))), ...);
    ((s += csv_line("inf",  static_cast<Ts>(numeric_limits<Ts>::infinity()))), ...);
    return s;
}

template<typename... Ts>
string NaN_representation() {
    string s;
    ((s += csv_line("-inf", static_cast<Ts>(numeric_limits<Ts>::quiet_NaN()))), ...);
    ((s += csv_line("inf",  static_cast<Ts>(numeric_limits<Ts>::signaling_NaN()))), ...);
    return s;
}

void create_special_values_file() {
    remove("special_values.csv");

    ofstream special_values_file;
    if (!open_output_file(special_values_file, "special_values.csv")) return;

    special_values_file << "Value,Type,Sign,Exponent,Mantissa\n";
    special_values_file << zero_representation<float, double, long double>();
    special_values_file << inf_representation<float, double, long double>();
    special_values_file << NaN_representation<float, double, long double>();

    special_values_file.close();
}

int main(void) {
    create_type_info_file();
    create_special_values_file();    
}
