#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <list>
#include "hello.hpp"

#define CSV_FILENAME "../../input_files/BBox_List_2017.csv" // PATH FROM DEBUG TO INPUT FILE

class BoundingBox
{

    unsigned int bb_image_id = 0;
    std::string bb_filename = "";
    std::string bb_label = "";
    double bb_x_start = 0.00, bb_y_start = 0.00;
    double bb_width = 0.00, bb_height = 0.00;
    std::string bb_description = "";

public:
    BoundingBox()
    { /* Constructor 1*/
        std::cout << "BoundingBox class Constructor 1 called." << std::endl;
    }
    BoundingBox(unsigned int image_id, std::string filename, std::string label, double x_start = 0.00, double y_start = 0.00, double width = 0.00, double height = 0.00, std::string description = "")
    { /* Constructor 2*/
        std::cout << "BoundingBox class Constructor 2 called." << std::endl;
        bb_image_id = image_id;
        bb_filename = filename;
        bb_label = label;
        bb_x_start = x_start;
        bb_y_start = y_start;
        bb_width = width;
        bb_height = height;
        bb_description = description;
    }
    void set_values(unsigned int image_id, std::string filename, std::string label, double x_start = 0.00, double y_start = 0.00, double width = 0.00, double height = 0.00, std::string description = "");
    void print_values();
    ~BoundingBox()
    { /* Destructor */
        std::cout << "BoundingBox class Destructor called." << std::endl;
        bb_image_id = 0;
        bb_filename = "";
        bb_label = "";
        bb_x_start = 0.00;
        bb_y_start = 0.00;
        bb_width = 0.00;
        bb_height = 0.00;
        bb_description = "";
    }
};

void BoundingBox::set_values(unsigned int image_id, std::string filename, std::string label, double x_start, double y_start, double width, double height, std::string description)
{
    std::cout << "BoundingBox class set_values member function called!" << std::endl;
    bb_image_id = image_id;
    bb_filename = filename;
    bb_label = label;
    bb_x_start = x_start;
    bb_y_start = y_start;
    bb_width = width;
    bb_height = height;
    bb_description = description;
}

void BoundingBox::print_values()
{
    std::cout << "BoundingBox class print_values member function called!" << std::endl;
    std::cout << "bb_image_id: " << bb_image_id << std::endl;
    std::cout << "bb_filename: " << bb_filename << std::endl;
    std::cout << "bb_label: " << bb_label << std::endl;
    std::cout << "bb_x_start: " << bb_x_start << std::endl;
    std::cout << "bb_y_start: " << bb_y_start << std::endl;
    std::cout << "bb_width: " << bb_width << std::endl;
    std::cout << "bb_height: " << bb_height << std::endl;
    std::cout << "bb_description: " << bb_description << std::endl;
}

int main(int argc, char **argv){

    hello::say_hello();

    std::fstream ifs;
    std::string index_line;
    std::string line;
    size_t field_start = 0;
    std::string field = "";
    std::array<std::string, 8> field_line_array;
    std::array<std::string, 8Ui64>::iterator field_line_array_index = field_line_array.begin();
    unsigned int i = 0;
    std::list<BoundingBox> my_bb_list;
    std::list<BoundingBox>::iterator it;

    ifs.open(CSV_FILENAME, std::fstream::in);
    if ((ifs.rdstate() & std::ifstream::failbit) != 0){
        std::cerr << "Error opening " CSV_FILENAME << std::endl;
    }
    else{
        std::getline(ifs, index_line);
        std::cout << "INDEX OF CSV => " << index_line << std::endl;
        while (ifs.good()){
            std::getline(ifs, line);
            if(line.empty()) break;
            std::cout << "Extracted Line [" << ++i << "] -> \"" << line << "\"" << std::endl;

            while(line.find(',', field_start) !=  std::string::npos)
            {
                field = line.substr (field_start, line.find(',', field_start)-field_start);
                *(field_line_array_index++) = field;
                field_start = line.find(',', field_start) + 1;
            }

            field = line.substr (field_start, line.length()-field_start);
            *(field_line_array_index) = field;
            field_line_array_index = field_line_array.begin();
            field_start = 0;

            BoundingBox box(i, field_line_array[0], field_line_array[1], std::stod(field_line_array[2]) , std::stod(field_line_array[3]) , std::stod(field_line_array[4]) , std::stod(field_line_array[5]));
            my_bb_list.push_back(box);
        }
    }

    std::cout << "my_bb_list contains:";
    for (it=my_bb_list.begin(); it!=my_bb_list.end(); ++it)
        (*it).print_values();
    std::cout << '\n';

    std::cout << "End of Program." << std::endl;
    ifs.close();
    return 0;
} // end of main function code block

