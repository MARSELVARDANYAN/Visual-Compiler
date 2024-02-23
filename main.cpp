#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

 // Structure to store information about variables
 struct INFO
 {
    std::string type;
    std::string value;
    std::string name;
    size_t arr_line;
    size_t arr_position;
 };

// Function to process a line and extract information
void foo(INFO &ob, std::string Tmp_str){ 
    std::string tmp;
    size_t index = 0;
    std::istringstream tmp_str(Tmp_str);
    std::vector<std::string> words;
    
    // Tokenize the line
    while(tmp_str >> tmp){
        words.push_back(tmp);
    }
    size_t size = words.size();
   
    // Find the position of '=' in the tokens           
    for(size_t i = 0; i < size; ++i){
        if(words[i] == "="){
            index = i;
        }
    }
    
    // If '=' found, extract value and adjust size
    if(index){
        ob.value = words[size - 1];
        size -= 2;
    }else{
        ob.value = "GARBAGE";
    }
    
    // Determine the type based on the number of tokens  
    switch(size){ 
        case 1:
            ob.name = words[0];
            ob.type = "-";
            ob.value = "-";
            break;
        case 2:
            ob.type = (words[0])[0];
            ob.name = words[1];
            break;
        case 3:
            ob.type = {(words[0])[0], (words[1])[0]};
            ob.name = words[2];
            break;
        case 4:
            ob.type = {words[0].front(), words[1].front(), words[2].front()};
            ob.name = words[3];
            break;
        case 5:
            ob.type = {words[0].front(), words[1].front(), words[2].front(), words[3].front()};
            ob.name = words[4];
            break;
        }
}

int main() {
    
    // Output file for the result
    std::string res_path = "result.txt";
    std::ofstream fout;
    fout.open(res_path);
    
    // Input file path
    std::string path;
    std::cout << "Plase write your .txt name" << std::endl;
    std::cin >> path;
    std::ifstream finp(path);
    
    // Check if the input file is open
    if (!finp.is_open())
    {
        throw 1;
    }
    
    // Vector to store lines of the input file
    std::vector <std::string> V_ob;
    
    // Temporary string to store each line
    std::string Tmp_str;
    
    // Size of the INFO array
    size_t ob_arr_size = 50;    
    INFO ob_arr[ob_arr_size];

    // Output header
    fout  << std::left << std::setw(15)  << "Type" 
          << std::setw(15) << "Value" 
          << std::setw(15) << "Name" 
          << std::setw(15) << "Line" 
          << std::setw(15) << "Position" 
          << std::endl
          << std::endl;
    
    size_t index = 0;
    size_t line = 0;

    // Read lines from the input file
    while(std::getline(finp, Tmp_str, ';'))
    { 
        // Check for newline character to update line and position
        for(size_t i = 0; i < Tmp_str.size(); ++i){
            if(Tmp_str[i] == '\n'){
                ++line;
                index = 0;
            }
        }
        
        // Update position and line in INFO structure
        ob_arr[index].arr_position = index;
        ob_arr[index].arr_line = line;

        // Process the line using foo function
        foo(ob_arr[index], Tmp_str);

        // Write information to the output file   
        fout << std::left << std::setw(15)  
             << ob_arr[index].type << std::setw(15) 
             << ob_arr[index].value << std::setw(15)
             << ob_arr[index].name << std::setw(15) 
             << ob_arr[index].arr_line << std::setw(15)  
             << ob_arr[index].arr_position  << std::endl;
        
        ++index;
    }

    // Close input and output files
    finp.close();
    fout.close();
    return 0;
}

