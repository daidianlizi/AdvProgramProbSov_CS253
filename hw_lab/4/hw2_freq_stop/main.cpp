#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <set>
#include <map>
using namespace std;

int main(){
    ifstream in("rand_numbers.txt");
    ifstream stop("stopwords.txt");
    ofstream out("frequency.txt.");
    set<string> exclusion_raw;
    copy(istream_iterator<string>(stop),
        istream_iterator<string>(),
        back_inserter(exclusion_raw) );
    set<string> exclusion;
    transform(exclusion_raw.begin(), exclusion_raw.end(), std::inserter(exclusion, exclusion.begin()), [](string s) {
        transform(s.begin(), s.end(), s.begin(), ::tolower); 
        return s;
    });

    map<string,int> freq;
    for_each( istream_iterator<string>(in), // start of source       
        istream_iterator<string>(), // end of source, EOF       
        [&](string & s){ 
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        if (exclusion.find(s) == exclusion.end())
            ++ freq[s]; 
    } );

    sort( begin(freq), end(freq) ); // sort all the words
    //cout<<*begin(nums)<<endl;
    //copy( begin(nums), end(nums), ostream_iterator<int>(cout, "\n") );
    auto lambdaWrite = [&out](const map<string, int> &pair){
        out << pair.fisrt << ": " << pair.second << "\n";
    };
    for_each( begin(freq), end(freq),lambdaWrite);
    cout<<"successed in process and save!\n";
    in.close();
    stop.close();
    out.close();
    return 0;
}