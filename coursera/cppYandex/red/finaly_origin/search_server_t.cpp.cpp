#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <future>

vector<string> SplitIntoWords(string line) {
  istringstream words_input(move(line));
  return {
    make_move_iterator(istream_iterator<string>(words_input)), 
    make_move_iterator(istream_iterator<string>())
  };
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(move(current_document));
  }

  lock_guard<mutex> lg(mtx);
  index = move(new_index);
  //swap(index, new_index);
}

string SearchServer::AddQueriesStreamSingleThread(vector<string> queries) {
    const size_t index_size = 11000;
    vector<size_t> docid_count(index_size);
    vector<pair<size_t, size_t> > search_results;
    search_results.reserve(index_size);
    
    ostringstream search_results_output;
    for (auto &current_query : queries) {
        fill(docid_count.begin(), docid_count.end(), 0);
        for (const auto& word : SplitIntoWords(current_query)) {
          lock_guard<mutex> lg(mtx);
          for (auto [docid, count] : index.Lookup(word)) {
            docid_count[docid] += count;
          }
        }

        search_results.clear();
        for (size_t i = 0; i < docid_count.size(); ++i) {
            if (docid_count[i] > 0) {
                search_results.push_back({i, docid_count[i]});
            }
        }
        auto comp = [](const pair<size_t, size_t> &lhs, const pair<size_t, size_t> &rhs) {
          int64_t lhs_docid = lhs.first;
          auto lhs_hit_count = lhs.second;
          int64_t rhs_docid = rhs.first;
          auto rhs_hit_count = rhs.second;
          return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
        };
        auto part_end = search_results.begin() + min(static_cast<size_t>(5), search_results.size());
        /*nth_element(search_results.begin(), part_end, search_results.end(), comp);
        sort(search_results.begin(), part_end, comp);*/
        partial_sort(search_results.begin(), part_end, search_results.end(), comp);
        
        search_results_output << current_query << ':';
        for (auto [docid, hitcount] : Head(search_results, 5)) {
          search_results_output << " {"
            << "docid: " << docid << ", "
            << "hitcount: " << hitcount << '}';
        }
        search_results_output << '\n';
    }
    
    return move(search_results_output.str());
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
    const size_t BATCH_SIZE = 2250;
    vector<string> queries;
    queries.reserve(BATCH_SIZE);
    vector<future<string>> futures;
    
    for (string current_query; getline(query_input, current_query); ) {
        queries.push_back(move(current_query));
        if (queries.size() == BATCH_SIZE) {
            futures.push_back(async(&SearchServer::AddQueriesStreamSingleThread, this, move(queries)));
            queries.clear();
        }
    }
    if (!queries.empty()) {
        futures.push_back(async(&SearchServer::AddQueriesStreamSingleThread, this, move(queries)));
    }
    
    for (size_t i = 0; i < futures.size(); ++i) {
        search_results_output << futures[i].get();
    }
}

void InvertedIndex::Add(string &&document) {
  //docs.push_back(document);

  //const size_t docid = docs.size() - 1;
  const size_t docid = size++;
  map<string, size_t> word_count;
  for (auto& word : SplitIntoWords(move(document))) {
    ++word_count[move(word)];
  }
  for (auto &[word, count] : word_count) {
    index[move(word)].push_back({docid, count});
  }
}

const List &InvertedIndex::Lookup(const string& word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return index_empty;
  }
}