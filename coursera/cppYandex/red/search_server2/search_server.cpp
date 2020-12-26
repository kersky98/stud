#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <deque>
#include <queue>
#include <functional>
#include <future>

vector<string_view> SplitIntoWords2(const string& doc){
  vector<string_view> vsv;
  vsv.reserve(1000);
  size_t offset = 0, pos1 = 0, pos2 = 0;

  while(pos1 < doc.size() && pos2 < doc.size()){
    pos1 = doc.find_first_not_of(' ', offset);
    pos2 = doc.find_first_of(' ', pos1);
    offset = pos2;
    if(pos2 <= doc.size()-1 && doc[pos2] == ' '){
      pos2--;
    }else if(pos2 > doc.size() && pos1 != pos2){
      pos2 = doc.size()-1;
    }
    if(pos1 < doc.size() && pos2 < doc.size()){
      vsv.emplace_back(&doc[pos1], pos2-pos1+1);
    }
  }
  return vsv;
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(ref(document_input));
}

// обновление базы, самая медленная функция
void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document); ) {
    // добавление предложения-документа в базу
    new_index.Add(move(current_document));
  }
  //lock_guard<mutex> lg(mtx);
  index = move(new_index);
  //swap(index, new_index);
}

string SearchServer::AddQueriesStreamSingleThread(vector<string> queries){
  ostringstream search_results_output;
  // вектор, где индекс-docid, а значение-кол-во вхождений какого-либо слова из запроса в документ
  vector<size_t> docid_count(index.docid);
  vector<pair<size_t, size_t>> search_results;
  search_results.reserve(5);
  // цикл по всем запросам
  for (string current_query : queries ) {
    fill(begin(docid_count), end(docid_count), 0);
    // цикл по словам одного предложения из запроса
    for (const auto& word : SplitIntoWords2(current_query)) {
      // цикл по списку docid для одного слова из предложения-запроса
      for (const pair<size_t, size_t> p : index.Lookup(move(word))) {
        // инкремент для docid кол-ва вхождений
        docid_count[p.first]+=p.second;
      }
    }

    //vector<pair<size_t, size_t>> search_results;
    //search_results.reserve(5);
    search_results.clear();
    auto it = max_element(begin(docid_count), end(docid_count));
    while(it != end(docid_count) && search_results.size() < 5 && *it != 0){
      search_results.emplace_back(it-begin(docid_count), *it);
      *it = 0;
      it = max_element(begin(docid_count), end(docid_count));
    }

    // вывод в поток первых пяти пар из результата одного предложения-запроса
    search_results_output << current_query << ':';
    for (auto [docid, hitcount] : Head(search_results, 5)) {
      search_results_output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;
  }// конец цикла по всем запросам
  return move(search_results_output.str());
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
    const size_t qsize = 2000;
    vector<string> queries;
    queries.reserve(qsize);
    deque<future<string>> futures;

    for (string current_query; getline(query_input, current_query); ) {
        queries.push_back(move(current_query));
        if (queries.size() == qsize) {
            futures.push_back(move(async(&SearchServer::AddQueriesStreamSingleThread, this, move(queries))));
            queries.clear();
        }
    }
    if (!queries.empty()) {
        futures.push_back(move(async(&SearchServer::AddQueriesStreamSingleThread, this, move(queries))));
    }

    for (size_t i = 0; i < futures.size(); ++i) {
        search_results_output << futures[i].get();
    }
}

// поиск всех вхождений по поисковому запросу
#if 0
void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
  // вектор, где индекс-docid, а значение-кол-во вхождений какого-либо слова из запроса в документ
  vector<size_t> docid_count(index.docid);
  // цикл по всем запросам
  for (string current_query; getline(query_input, current_query); ) {
    fill(begin(docid_count), end(docid_count), 0);
    // цикл по словам одного предложения из запроса
    for (const auto& word : SplitIntoWords2(current_query)) {
      // цикл по списку docid для одного слова из предложения-запроса
      for (const pair<size_t, size_t> p : index.Lookup(move(word))) {
        // инкремент для docid кол-ва вхождений
        docid_count[p.first]+=p.second;
      }
    }

    vector<pair<size_t, size_t>> search_results;
    search_results.reserve(5);
    auto it = max_element(begin(docid_count), end(docid_count));
    while(it != end(docid_count) && search_results.size() < 5 && *it != 0){
      search_results.emplace_back(it-begin(docid_count), *it);
      *it = 0;
      it = max_element(begin(docid_count), end(docid_count));
    }

    // вывод в поток первых пяти пар из результата одного предложения-запроса
    search_results_output << current_query << ':';
    for (auto [docid, hitcount] : Head(search_results, 5)) {
      search_results_output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;
  }// конец цикла по всем запросам
}
#endif

// добавление поредложения-документа в базу
void InvertedIndex::Add(string document) {
  docs.push_back(move(document));

  //const size_t docid = docs.size() - 1;
  for (const auto& word : SplitIntoWords2(ref(docs[docid]))) {
    // заполняется словарь слово: список пар номер документа, кол-во входжений
    // если данное слово встечается впервые, то создаем пару <docid, 1>, иначе
    // находим в векторе пар пару с нужным docid и инкрементируем hitcount
    if(auto it = index.find(word); it != index.end()){
      if(it->second.back().first == docid){
        it->second.back().second++;
      }else{
        it->second.emplace_back(docid, 1);
      }
    }else{
      index[word].reserve(20000);
      index[word].emplace_back(docid, 1);
    }
  }
  docid++;
}

// поиск в словаре по слову списка номеров документов
vector<pair<size_t, size_t>> InvertedIndex::Lookup(const string_view& word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return {};
  }
}

InvertedIndex::InvertedIndex(){
  index.reserve(15000);
  docs.reserve(50000);
}
