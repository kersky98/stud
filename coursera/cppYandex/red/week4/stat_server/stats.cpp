/*
 * stats.cpp
 *
 *  Created on: 6 окт. 2020 г.
 *      Author: user
 */

#include "stats.h"
#include <sstream>
#include <iostream>

HttpRequest ParseRequest(string_view line){
  HttpRequest h;
  size_t begin_index_metod = 0, end_index_metod = 0,
      begin_index_uri = 0, end_index_uri = 0,
      begin_index_protocol = 0, end_index_protocol = 0;

  while(!isalpha(line[begin_index_metod])){
    begin_index_metod++;
  }
  end_index_metod = line.find_first_of(' ', begin_index_metod);
  begin_index_uri = end_index_metod + 1;
  end_index_uri = line.find_first_of(' ', begin_index_uri);
  begin_index_protocol = end_index_uri + 1;
  end_index_protocol = line.find_first_of(' ', begin_index_protocol);

  h.method = line.substr(begin_index_metod, end_index_metod - begin_index_metod);
  h.uri = line.substr(begin_index_uri, end_index_uri - begin_index_uri);
  h.protocol = line.substr(begin_index_protocol, end_index_protocol - begin_index_protocol);

  return h;
}

void Stats::AddMethod(string_view method){
  if(stat_metods.find(method) != end(stat_metods)){
    stat_metods[method]++;
  }else{
    stat_metods["UNKNOWN"]++;
  }
}
void Stats::AddUri(string_view uri){
  if(stat_uris.find(uri) != end(stat_uris)){
    stat_uris[uri]++;
  }else{
    stat_uris["unknown"]++;
  }
}

const map<string_view, int>& Stats::GetMethodStats() const{
  return stat_metods;
}

const map<string_view, int>& Stats::GetUriStats() const{
  return stat_uris;
}

Stats::Stats():
    stat_metods({
          {"GET", 0},
          {"PUT", 0},
          {"POST", 0},
          {"DELETE", 0},
          {"UNKNOWN", 0},
        }),
        stat_uris({
            {"/", 0},
            {"/order", 0},
            {"/product", 0},
            {"/basket", 0},
            {"/help", 0},
            {"unknown", 0}
         })
{
}
