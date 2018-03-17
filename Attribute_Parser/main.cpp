#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <fstream>
using namespace std;

fstream fin("in.txt", ios_base::in);
fstream fout("out.txt", std::ios_base::in | std::ios_base::out);
fstream fexpected("expected.txt", ios_base::in);

class Tag
{
public:
    Tag(string name) : name(name) {}
    
    string name;
    map<string, string> values;
    vector<Tag> innerTags;
    
    string getValue(const string& attribute)
    {
        if (values.find(attribute) == values.end())
            return "Not Found!";
        else
            return values[attribute];
    }

    Tag& getTag(list<string>& tags)
    {
        if (name == tags.front())
        {
            tags.pop_front();
        
            if (tags.size() == 0)
                return *this;
        }

        for (unsigned i=0; i < innerTags.size(); ++i)
        {
            if (innerTags[i].name == tags.front())
            {
                tags.pop_front();

                if (tags.size() == 0)
                    return innerTags[i];
                
                return innerTags[i].getTag(tags);
            }
        }

        throw "Not Found!";
    }
};

ostream& operator<<(ostream& stream, const Tag& tag) {
    stream << "<" << tag.name << ">" << endl;
    for(const auto& e : tag.values)
        stream << e.first << " = " << e.second << endl;
    stream << "<---" << tag.name << "--->" << endl;
    for(const auto& t : tag.innerTags)
        stream << t;
    stream << "<===" << tag.name << "===>" << endl;
    return stream;
}


list<string> getTagPathList(const string& line)
{
    list<string> tags;

    size_t tagBegin = 0;
    while(tagBegin != line.size())
    {
        size_t tagEnd = line.find(".", tagBegin);
        if (tagEnd == string::npos)
            tagEnd = line.size();
        tags.push_back(line.substr(tagBegin, tagEnd));
        tagBegin = tagEnd;
        if (tagEnd != line.size())
            ++tagBegin; // extra "."
    }

    return tags;
}

string extractTagName(string& line)
{
    size_t separator = line.find(' ');
    string tagName = line.substr(0, separator);
    
    if (separator != string::npos)
        line.erase(0, separator + 1); // remove the extra space
        
    return tagName;    
}

map<string, string> getValues(string& line)
{
    // clear the line, value and attributes seperated by a space
    line = regex_replace(regex_replace(regex_replace(line, regex(" = \""), " "), regex("\" "), " "), regex("\""), "");

    istringstream iss(line);
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};

    map<string, string> values;

    for (int i = 0; i < (int)(tokens.size() - 1); i += 2)
        values[tokens[i]] = tokens[i+1];
    
    return values;
}

void parseLine(const string& cline, Tag& root, string& tagPath)
{   
    string line = cline.substr(0, cline.size() - 1); // remove last '>'
    
    if (line[1] == '/') // closing
    {
        line = line.erase(0,2); // remove '</'

        string tagName = extractTagName(line);
    
        tagPath = tagPath.substr(0, tagPath.size() - tagName.size() - 1);        
    }
    else // opening
    {        
        line = line.erase(0,1);  // remove '<'

        string tagName = extractTagName(line);
        
        Tag tag(tagName);
        tag.values = getValues(line);

        list<string> ltagPath = getTagPathList(tagPath);                
        root.getTag(ltagPath).innerTags.push_back(tag);        

        tagPath += "." + tagName;        
    }
}

void parseQuery(const string& cquery, Tag& root)
{
    size_t separator = cquery.find("~");
    list<string> tags = getTagPathList(cquery.substr(0, separator));
    string attribute = cquery.substr(separator + 1, cquery.size() - separator - 1);
    
    tags.push_front("root");

    try
    {
        fout << root.getTag(tags).getValue(attribute) << endl;
    }
    catch (char const* c)
    {
        fout << c << endl;
    }
}

int main() {

    ifstream infile("in.txt", ifstream::in);

    ofstream outfile;
    outfile.open ("out.txt");

    /***********************************************************/
    
    int N, Q;

    string firstLine;
    getline(fin, firstLine);
    stringstream ss(firstLine);
    
    ss >> N >> Q;

    vector<string> lines;
    vector<string> queries;

    while (N--)
    {
        string s;
        getline(fin, s);
        lines.push_back(s);
    }

    Tag root = Tag("root");
    string currentTagPath = "root";
    
    for (const auto& line : lines)
    {
        parseLine(line, root, currentTagPath);
    }   
    
    while (Q--)
    {
        string q;
        getline(fin, q);
        queries.push_back(q); 
    }
    
    for (const auto& query : queries)
    {
        parseQuery(query, root);
    }

    /***********************************************************/

    fout.clear();
    fout.seekg(0, ios::beg);

    bool valid = true;
    string output, expected;
    while(getline(fout, output) && getline(fexpected, expected))
        if(output.compare(expected) != 0)
            valid = false;

    if (!fout.eof() || !fexpected.eof())
        valid = false;

    cout << (valid ? "ok" : "fail") << endl;
        
    return 0;
}