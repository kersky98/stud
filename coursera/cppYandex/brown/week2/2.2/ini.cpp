#include <istream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>

#include "ini.h"

namespace Ini{

Section& Document::AddSection(string name){
  pair<unordered_map<string, Section>::iterator, bool> result =
      sections.insert(make_pair(name, Section()));
  return (*result.first).second;
}

const Section& Document::GetSection(const string& name) const{
  return sections.at(name);
}

size_t Document::SectionCount() const{
  return sections.size();
}

pair<string_view, string_view> Split(string_view line, char by) {
  size_t pos = line.find(by);
  string_view left = line.substr(0, pos);

  if (pos < line.size() && pos + 1 < line.size()) {
    return {left, line.substr(pos + 1)};
  } else {
    return {left, string_view()};
  }
}

Document Load(istream& input){
  string line;
  Document doc;

  Section* sec;
  while(getline(input, line)){
    // if new section
    if(line.size() == 0){
      continue;
    }
    if( line.front() == '[' && line.back() == ']'){
      sec = &doc.AddSection(line.substr(1, line.size()-2));
    }else{
      pair<string_view, string_view> st = Split(line, '=');
      sec->insert({string(st.first), string(st.second)});
    }
  }
  return doc;
}

}
