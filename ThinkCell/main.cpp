
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <iostream>

using namespace std;


struct WordGreaterComparator
{
    bool operator()(const std::string & left, const std::string & right) const
    {
        return (left > right);
    }
};

void RunMapSamples() {
    std::map<std::string, int> mapOfWords;
    // Inserting data in std::map
    mapOfWords.insert(std::make_pair("moon", 1));
    mapOfWords.insert(std::make_pair("earth", 2));
    mapOfWords["sun"] = 3;
    // Will replace the value of already added key i.e. earth
    mapOfWords["earth"] = 4;
    // Iterate through all elements in std::map
    std::map<std::string, int>::iterator it = mapOfWords.begin();
    while(it != mapOfWords.end())
    {
        std::cout<<it->first<<" :: "<<it->second<<std::endl;
        it++;
    }
    // Check if insertion is successful or not
    if(mapOfWords.insert(std::make_pair("earth", 1)).second == false)
    {
        std::cout<<"Element with key 'earth' not inserted because already existed"<<std::endl;
    }
    // Searching element in std::map by key.
    if(mapOfWords.find("sun") != mapOfWords.end())
        std::cout<<"word 'sun' found"<<std::endl;
    if(mapOfWords.find("mars") == mapOfWords.end())
        std::cout<<"word 'mars' not found"<<std::endl;
    
    std::cout<<"##################################################################"<<std::endl;
    
    // Create an empty unordered_map
    std::unordered_map<std::string, int> wordMap;

    // Insert Few elements in map
    wordMap.insert({"First", 1});
    wordMap.insert({"Second", 2});
    wordMap.insert({"Third", 3});
    wordMap.insert({"Forth", 4});
    wordMap.insert({"Fifth", 5});
    wordMap.insert({"Sixth", 6});

    // Overwrite value of an element
    wordMap["Third"] = 8;

    // Iterate Over the unordered_map and display elements
    for (std::pair<std::string, int> element : wordMap)
        std::cout << element.first << " :: " << element.second << std::endl;
    
}

int main(int argc, char** argv) {
    RunMapSamples();
    return 0;
}