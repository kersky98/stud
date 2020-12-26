#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <mutex>
using namespace std;

using List = vector<pair<size_t, size_t> >;

class InvertedIndex {
public:
  void Add(string &&document);
  const List &Lookup(const string& word) const;

  /*const string& GetDocument(size_t id) const {
    return docs[id];
  }*/

  size_t Size() const {
    //return docs.size();
    return size;
  }

private:
  map<string, List> index;
  List index_empty;
  //vector<string> docs;
  size_t size = 0;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  string AddQueriesStreamSingleThread(vector<string> queries);

  InvertedIndex index;
  mutex mtx;
};