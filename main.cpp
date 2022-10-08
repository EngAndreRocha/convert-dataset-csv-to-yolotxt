#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <list>
#include "hello.hpp"

#define I_FILENAME "../../input_files/BBox_List_2017.csv" // FILENAME WITH PATH FROM DEBUG TO INPUT FILE
#define O_FILEPATH "../../output_files/" // PATH FROM DEBUG TO OUTPUT FILE

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

    std::fstream fs;
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

    fs.open(I_FILENAME, std::fstream::in);
    if ( (fs.rdstate() & std::ifstream::failbit ) != 0 ){
        std::cerr << "Error opening " I_FILENAME << std::endl;
        return 1;
    }
    else{
        std::getline(fs, index_line);
        /* std::cout << "INDEX OF CSV => " << index_line << std::endl; */
        while (fs.good()){
            std::getline(fs, line);
            if(line.empty()) break;
            /* std::cout << "Extracted Line [" << */ ++i /* << "] -> \"" << line << "\"" << std::endl */;

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
    /* for (it=my_bb_list.begin(); it != my_bb_list.end(); ++it)
        (*it).print_values(); */

    fs.close();

    for (it=my_bb_list.begin(); it != my_bb_list.end(); ++it){
        std::string filename = (*it).get_bb_filename();
        size_t lastindex = filename.find_last_of("."); 
        filename = filename.substr(0, lastindex);
        filename.append(".txt");

        fs.open(O_FILEPATH+filename, std::fstream::out);
        if ( (fs.rdstate() & std::ifstream::failbit ) != 0 ){
            std::cerr << "Error opening " O_FILEPATH << std::endl;
            return 1;
        }
        else{
            fs << "(" << (*it).get_bb_class_id() << "," << (*it).get_bb_x_centre() << "," << (*it).get_bb_y_centre() << "," << (*it).get_bb_width() << "," << (*it).get_bb_height() << ")" << std::endl;
        }
        fs.close();
    }


    std::cout << "End of Program." << std::endl;
    return 0;
} // end of main function code block

