#include <iostream> #include <fstream> #include <iterator> int main() {   ifstream in(“input.data”);   ofstream out(“output.data”);   vector<string> V;  
    
 // places all words from cin into V   
 copy( istream_iterator<string>(in), // start of source       
 istream_iterator<string>(), // end of source, EOF       
 back_inserter(V) ); // destination   
 sort( begin(V), end(V) ); // sort all the words   // print all words (without duplicates) to cout one per line   
 unique_copy( begin(V), end(V), // source          
 ostream_iterator<string>(out, "\n") ); // dest }