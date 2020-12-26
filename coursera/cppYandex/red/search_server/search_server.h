#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <string_view>
#include <utility>
using namespace std;

class InvertedIndex {
public:
  InvertedIndex();
  void Add(string document);
  vector<pair<size_t, size_t>> Lookup(const string_view& word) const;

  const string& GetDocument(size_t id) const {
    return docs[id];
  }

  size_t docid = 0;
private:
  vector<string> docs;
  map<string_view, vector<pair<size_t, size_t>>> index;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);
  size_t GetDocsCount();

private:
  InvertedIndex index;
};
