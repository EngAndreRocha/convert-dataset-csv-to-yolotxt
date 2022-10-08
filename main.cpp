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
    unsigned int bb_class_id = 0;
    std::string bb_filename = "";
    std::string bb_label = "";
    double bb_x_centre = 0.00, bb_y_centre = 0.00;
    double bb_width = 0.00, bb_height = 0.00;
    std::string bb_description = "";

public:
    BoundingBox(){}
    BoundingBox(unsigned int image_id, unsigned int class_id, std::string filename, std::string label, double x_centre = 0.00, double y_centre = 0.00, double width = 0.00, double height = 0.00, std::string description = "")
    {
        bb_image_id = image_id;
        bb_class_id = class_id;
        bb_filename = filename;
        bb_label = label;
        bb_x_centre = x_centre;
        bb_y_centre = y_centre;
        bb_width = width;
        bb_height = height;
        bb_description = description;
    }
    unsigned int get_bb_image_id(){ return bb_image_id; };
    unsigned int get_bb_class_id(){ return bb_class_id; };
    std::string get_bb_filename(){ return bb_filename; };
    std::string get_bb_label(){ return bb_label; };
    double get_bb_x_centre(){ return bb_x_centre; };
    double get_bb_y_centre(){ return bb_y_centre; };
    double get_bb_width(){ return bb_width; };
    double get_bb_height(){ return bb_height; };
    std::string get_bb_description(){ return bb_description; };
    void set_bb_image_id(unsigned int image_id){  bb_image_id = image_id; };
    void set_bb_class_id(unsigned int class_id){  bb_class_id = class_id; };
    void set_bb_filename(std::string filename){  bb_filename = filename; };
    void set_bb_label(std::string label){  bb_label = label; };
    void set_bb_x_centre(double x_centre){  bb_x_centre = x_centre; };
    void set_bb_y_centre(double y_centre){  bb_y_centre = y_centre; };
    void set_bb_width(double width){  bb_width = width; };
    void set_bb_height(double height){  bb_height = height; };
    void set_bb_description(std::string ){  bb_description; };

    void set_values(unsigned int image_id, unsigned int class_id, std::string filename, std::string label, double x_centre = 0.00, double y_centre = 0.00, double width = 0.00, double height = 0.00, std::string description = "");
    void print_values();
    ~BoundingBox()
    {
        bb_image_id = 0;
        bb_class_id = 0;
        bb_filename = "";
        bb_label = "";
        bb_x_centre = 0.00;
        bb_y_centre = 0.00;
        bb_width = 0.00;
        bb_height = 0.00;
        bb_description = "";
    }
};

void BoundingBox::set_values(unsigned int image_id, unsigned int class_id, std::string filename, std::string label, double x_centre, double y_centre, double width, double height, std::string description)
{
    bb_image_id = image_id;
    bb_class_id = class_id;
    bb_filename = filename;
    bb_label = label;
    bb_x_centre = x_centre;
    bb_y_centre = y_centre;
    bb_width = width;
    bb_height = height;
    bb_description = description;
}

void BoundingBox::print_values()
{
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "BOX[]" << std::endl;
    std::cout << std::endl;
    std::cout << "bb_id: " << bb_image_id << std::endl;
    std::cout << "bb_class_id: " << bb_class_id << std::endl;
    std::cout << "bb_filename: " << bb_filename << std::endl;
    std::cout << "bb_label: " << bb_label << std::endl;
    std::cout << "bb_x_centre: " << bb_x_centre << std::endl;
    std::cout << "bb_y_centre: " << bb_y_centre << std::endl;
    std::cout << "bb_width: " << bb_width << std::endl;
    std::cout << "bb_height: " << bb_height << std::endl;
    std::cout << "bb_description: " << bb_description << std::endl;
    std::cout << std::endl;
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
    std::array<std::string, 8> classes = { "Atelectasis", "Cardiomegaly", "Effusion", "Infiltrate", "Mass", "Nodule", "Pneumonia", "Pneumathorax" };

    ifs.open(CSV_FILENAME, std::fstream::in);
    if ( (ifs.rdstate() & std::ifstream::failbit ) != 0 ){
        std::cerr << "Error opening " CSV_FILENAME << std::endl;
    }
    else{
        std::getline(ifs, index_line);
        /* std::cout << "INDEX OF CSV => " << index_line << std::endl; */
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

            for(int classes_i = 0; classes_i < classes.size(); classes_i++){
                if(field_line_array[1] == classes[classes_i]){
                    BoundingBox box(i, classes_i , field_line_array[0], field_line_array[1], std::stod(field_line_array[2]) , std::stod(field_line_array[3]) , std::stod(field_line_array[4]) , std::stod(field_line_array[5]));
                    my_bb_list.push_back(box);
                }
            }
        }
    }

    std::cout << "(class_id, x_centre,  y_centre,  width,  height)"  << std::endl;
    for (it=my_bb_list.begin(); it != my_bb_list.end(); ++it)
        (*it).print_values();

    std::cout << "End of Program." << std::endl;
    ifs.close();
    return 0;
} // end of main function code block

