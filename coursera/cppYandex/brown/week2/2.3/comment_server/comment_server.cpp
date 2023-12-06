#include "test_runner.h"
 
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <map>
#include <optional>
#include <unordered_set>
 
using namespace std;
 
struct HttpRequest {
  // {"POST", "/add_user"}
  // {"POST", "/add_comment", "0 Hello"}
  // {"GET", "/user_comments", "", {{"user_id", "0"}}}
  // {"GET", "/captcha"}
  // {"POST", "/checkcaptcha", "1 24"}
  string method, path, body;
  map<string, string> get_params;
};
 
pair<string, string> SplitBy(const string& what, const string& by) {
  size_t pos = what.find(by);
  if (by.size() < what.size() && pos < what.size() - by.size()) {
    return {what.substr(0, pos), what.substr(pos + by.size())};
  } else {
    return {what, {}};
  }
}
 
template<typename T>
T FromString(const string& s) {
  T x;
  istringstream is(s);
  is >> x;
  return x;
}
 
pair<size_t, string> ParseIdAndContent(const string& body) {
  auto [id_string, content] = SplitBy(body, " ");
  return {FromString<size_t>(id_string), content};
}
 
struct LastCommentInfo {
  size_t user_id, consecutive_count;
};
 
enum class HttpCode {
  Ok = 200,
  NotFound = 404,
  Found = 302,
};
 
struct HttpHeader {
  string name, value;
};
 
struct Response {
  HttpCode code;
  vector<HttpHeader> headers;
  string content;
};
 
class HttpResponse {
public:
  explicit HttpResponse(HttpCode code): response_({code}) {};
 
  HttpResponse& AddHeader(string name, string value){
    if(name == "Content-Length"s){
      auto it = find_if(response_.headers.begin(), response_.headers.end(), [](const HttpHeader& item){
        return item.name == "Content-Length"s; 
      });
      
      if(it != response_.headers.end()){
        it->value = value;
      }else{
        response_.headers.push_back({name, value});
      }
    }else{
      response_.headers.push_back({name, value});
    }
    return *this;
  };
  HttpResponse& SetContent(string a_content){
    response_.content = a_content;
    string name = "Content-Length"s;
    string value = to_string(a_content.size());
    AddHeader(name, value);
    return *this;
  }
  HttpResponse& SetCode(HttpCode a_code){
    response_.code = a_code;
    return *this;
  }
 
  friend ostream& operator << (ostream& output, const HttpResponse& resp);
 
  Response response_;
};
 
ostream& operator << (ostream& output, const HttpResponse& resp){
  output << "HTTP/1.1 "s;
  output << static_cast<int>(resp.response_.code) << " "s;
  switch (resp.response_.code){
  case HttpCode::Ok:
    output << "OK\n"s;
    break;
  case HttpCode::Found:
    output << "Found\n";
    break;
  case HttpCode::NotFound:
    output << "Not found\n";
    break;
 
  default:
    break;
  }
  for(const HttpHeader& item : resp.response_.headers){
    output << item.name << ": " << item.value << "\n";
  }
 
  output << "\n";
 
  output << resp.response_.content;
 
  return output;
}
 
class CommentServer {
private:
  vector<vector<string>> comments_;
  std::optional<LastCommentInfo> last_comment;
  unordered_set<size_t> banned_users;
 
public:
  HttpResponse ServeRequest(const HttpRequest& req){
    HttpResponse response(HttpCode::Ok);
 
    if (req.method == "POST") {
      if (req.path == "/add_user") {
        comments_.emplace_back();
        string content = to_string(comments_.size() - 1);
        response.SetContent(content);
      }else if (req.path == "/add_comment") {
        auto [user_id, comment] = ParseIdAndContent(req.body);
 
        if (!last_comment || last_comment->user_id != user_id) {
          last_comment = LastCommentInfo {user_id, 1};
        } else if (++last_comment->consecutive_count > 3) {
          banned_users.insert(user_id);
        }
 
        if (banned_users.count(user_id) == 0) {
          comments_[user_id].push_back(string(comment));
        } else {
          response.SetCode(HttpCode::Found).AddHeader("Location"s, "/captcha"s);
        }
      }else if (req.path == "/checkcaptcha") {
        auto [id, resp] = ParseIdAndContent(req.body);
        if (resp == "42") {
          banned_users.erase(id);
          if (last_comment && last_comment->user_id == id) {
            last_comment.reset();
          }
        }else{
          response.SetCode(HttpCode::Found).AddHeader("Location", "/captcha");
        }
      } else {
        response.SetCode(HttpCode::NotFound);
      }
    }  // end /post
    else if (req.method == "GET") {
      if (req.path == "/user_comments") {
        auto user_id = FromString<size_t>(req.get_params.at("user_id"));
        string content;
        for (const string& c : comments_[user_id]) {
          content += c + '\n';
        }
        response.SetContent(content);
      } else if (req.path == "/captcha") {
        string content("What's the answer for The Ultimate Question of Life, the Universe, and Everything?"s);
        response.SetContent(content);
      } else {
        response.SetCode(HttpCode::NotFound);
      }
    } // end get
    else{
       response.SetCode(HttpCode::NotFound);
    }
    return response;
  }
};
 
ostream& operator<<(ostream& output, const HttpHeader& h) {
  return output << h.name << ": " << h.value;
}
 
bool operator==(const HttpHeader& lhs, const HttpHeader& rhs) {
  return lhs.name == rhs.name && lhs.value == rhs.value;
}
 
// {200, {}, "0"}
struct ParsedResponse {
  int code;
  vector<HttpHeader> headers;
  string content;
};
 
istream& operator >>(istream& input, ParsedResponse& r) {
  string line;
  getline(input, line);
 
  {
    istringstream code_input(line);
    string dummy;
    code_input >> dummy >> r.code;
  }
 
  size_t content_length = 0;
 
  r.headers.clear();
  while (getline(input, line) && !line.empty()) {
    if (auto [name, value] = SplitBy(line, ": "); name == "Content-Length") {
      istringstream length_input(value);
      length_input >> content_length;
    } else {
      r.headers.push_back( {std::move(name), std::move(value)});
    }
  }
 
  r.content.resize(content_length);
  input.read(r.content.data(), r.content.size());
  return input;
}
 
void Test(CommentServer& srv, const HttpRequest& request, const ParsedResponse& expected) {
  stringstream ss;
  ss << srv.ServeRequest(request);
  ParsedResponse resp;
  ss >> resp;
  ASSERT_EQUAL(resp.code, expected.code);
  ASSERT_EQUAL(resp.headers, expected.headers);
  ASSERT_EQUAL(resp.content, expected.content);
}
 
void Test2(CommentServer& srv, const HttpRequest& request, const ParsedResponse& expected) {
  stringstream ss;
  ss << srv.ServeRequest(request);
  ParsedResponse resp;
  ss >> resp;
  ASSERT_EQUAL(resp.code, expected.code);
  ASSERT_EQUAL(resp.headers, expected.headers);
  ASSERT_EQUAL(resp.content, expected.content);
}
 
template <typename CommentServer>
void TestServer() {
  CommentServer cs;
 
  const ParsedResponse ok{200};
  const ParsedResponse redirect_to_captcha{302, {{"Location", "/captcha"}}, {}};
  const ParsedResponse not_found{404};
 
  Test(cs, {"POST", "/add_user"}, {200, {}, "0"});
  Test(cs, {"POST", "/add_user"}, {200, {}, "1"});
  Test(cs, {"POST", "/add_comment", "0 Hello"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Hi"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Enlarge"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, redirect_to_captcha);
  Test(cs, {"POST", "/add_comment", "0 What are you selling?"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, redirect_to_captcha);
  Test(
    cs,
    {"GET", "/user_comments", "", {{"user_id", "0"}}},
    {200, {}, "Hello\nWhat are you selling?\n"}
  );
  Test(
    cs,
    {"GET", "/user_comments", "", {{"user_id", "1"}}},
    {200, {}, "Hi\nBuy my goods\nEnlarge\n"}
  );
  Test(
    cs,
    {"GET", "/captcha"},
    {200, {}, {"What's the answer for The Ultimate Question of Life, the Universe, and Everything?"}}
  );
  Test(cs, {"POST", "/checkcaptcha", "1 24"}, redirect_to_captcha);
  Test(cs, {"POST", "/checkcaptcha", "1 42"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Sorry! No spam any more"}, ok);
  Test(
    cs,
    {"GET", "/user_comments", "", {{"user_id", "1"}}},
    {200, {}, "Hi\nBuy my goods\nEnlarge\nSorry! No spam any more\n"}
  );
 
  Test(cs, {"GET", "/user_commntes"}, not_found);
  Test(cs, {"POST", "/add_uesr"}, not_found);
}
 
int main() {
  TestRunner tr;
  RUN_TEST(tr, TestServer<CommentServer>);
  return 0;
}
 
void TESTS()
{
    HttpResponse found_response(HttpCode::Found);
    found_response.SetContent("CONTENT");
    found_response.AddHeader("LABEL1", "value1");
    std::stringstream ss;
    ss << found_response;
    auto response = ss.str();
    std::cout << response;
}

int main2(){
  CommentServer cs;
  
  TESTS();
  cout << endl << "exit" << endl;
 
  // Test2(cs, {"POST", "/add_user"}, {200, {}, "0"});
  // Test2(cs, {"POST", "/add_user"}, {200, {}, "1"});
  // Test2(cs, {"POST", "/add_comment", "0 Hello"}, {200});
  // Test2(cs, {"POST", "/add_comment", "0 Hello1"}, {200});
  // Test2(cs, {"POST", "/add_comment", "0 Hello2"}, {200});
  // const ParsedResponse redirect_to_captcha{302, {{"Location", "/captcha"}}, {}};
  // Test2(cs, {"POST", "/add_comment", "0 Hello1"}, redirect_to_captcha);
  // Test2(cs, {"POST", "/checkcaptcha", "0 24"}, redirect_to_captcha);
  // Test2(cs, {"POST", "/checkcaptcha", "0 42"}, {200});
  // Test2(cs, {"GET", "/user_comments", "", {{"user_id", "0"}}}, {200, {}, "Hello\nHello1\nHello2"});
 
  // HttpResponse hr = cs.ServeRequest({"POST", "/add_user"});
  // cout << hr << endl;
  // HttpResponse hr2 = cs.ServeRequest({"POST", "/add_user"});
  // cout << hr2 << endl;
  // HttpResponse hr3 = cs.ServeRequest({"POST", "/add_comment", "0 Hello"});
  // cout << hr3 << endl;
  // HttpResponse hr4 = cs.ServeRequest({"POST", "/add_comment", "0 Hello1"});
  // cout << hr3 << endl;
  // HttpResponse hr5 = cs.ServeRequest({"POST", "/add_comment", "0 Hello2"});
  // cout << hr5 << endl;
  // HttpResponse hr6 = cs.ServeRequest({"POST", "/add_comment", "0 Hello1"});
  // cout << hr6 << endl;
  // HttpResponse hr7 = cs.ServeRequest({"POST", "/checkcaptcha", "0 24"});
  // cout << hr7 << endl;
  // HttpResponse hr8 = cs.ServeRequest({"POST", "/checkcaptcha", "0 42"});
  // cout << hr8 << endl;
  // HttpResponse hr9 = cs.ServeRequest({"GET", "/user_comments", "", {{"user_id", "0"}}});
  // cout << hr9 << endl;
  // HttpResponse hr10 = cs.ServeRequest({"GET", "/captcha"});
  // cout << hr10 << endl;


 
  // for(int i = 0; i < 10; i++){
  //   cout << cs.ServeRequest({"POST", "/add_user"}) << endl;
  // }
 
  return 0;
}