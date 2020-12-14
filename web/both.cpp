//#define CPPHTTPLIB_ZLIB_SUPPORT
//#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "strutil.h"

//using namespace httplib;
using namespace std;

int port = 0;

void worker()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  httplib::Server svr;
  svr.set_tcp_nodelay(true);

  svr.Get("/hi", [](const httplib::Request &req, httplib::Response &res) {
    res.set_content("Hello World!2", "text/plain");
  });

  svr.Get(R"(/numbers/(\d+))", [&](const httplib::Request &req, httplib::Response &res) {
    auto numbers = req.matches[1];
    res.set_content(numbers, "text/plain");
  });

  svr.Post("/singlebody", [&](const httplib::Request &req, httplib::Response &res) {
    cout << "/singlebody " << req.is_multipart_form_data() << " " << req.body << " " << req.get_header_value("Content-Type") << endl;
  });

  svr.Post("/multipart", [&](const httplib::Request &req, httplib::Response &res) {
    cout << "/multipart " << req.is_multipart_form_data() << " " << req.get_header_value("Content-Type") << endl;
    auto size = req.files.size();
    auto ret = req.has_file("name1");
    const auto &file = req.get_file_value("name1");
    cout << file.filename << endl;
    cout << file.content_type << endl;
    cout << file.content << endl;
  });

  svr.Post("/content_receiver",
           [&](const httplib::Request &req, httplib::Response &res, const httplib::ContentReader &content_reader) {
             cout << "handle: /content_receiver" << endl;
             if (req.is_multipart_form_data())
             {
               cout << "if (req.is_multipart_form_data())" << endl;
               httplib::MultipartFormDataItems files;
               content_reader(
                   [&](const httplib::MultipartFormData &file) {
                     files.push_back(file);
                     return true;
                   },
                   [&](const char *data, size_t data_length) {
                     files.back().content.append(data, data_length);
                     return true;
                   });
               res.set_content("(req.is_multipart_form_data())", "text/plain");
             }
             else
             {
               cout << "else " << req.get_header_value("Content-Type") << endl;
               std::string body;
               content_reader([&](const char *data, size_t data_length) {
                 body.append(data, data_length);
                 return true;
               });
               res.set_content(body, "text/plain");
             }
           });

  svr.Post("/post",
           [&](const httplib::Request &req, httplib::Response &res, const httplib::ContentReader &content_reader) {
             cout << "handle: /post" << endl;
             if (req.has_param("name"))
             {
               std::string val = req.get_param_value("name");
               cout << "handle: /post name=" << val << endl;
             }
           });
  //svr.listen("127.0.0.1", 1234);
  port = svr.bind_to_any_port("127.0.0.1");
  svr.listen_after_bind();
}

int main(void)
{

#if 0x1
  std::thread *th = new std::thread(worker);
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
#endif

  while (port == 0)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }

  cout << "port=" << port << endl;

  httplib::Client cli("127.0.0.1", port);
  cli.set_default_headers({{"Accept-Encoding", "gzip, deflate"}});
  cli.set_keep_alive(true);
  cli.set_follow_location(true);
  cli.set_compress(true);

  auto res = cli.Get("/hi");
  if (res)
  {
    cout << res->status << endl;
    //cout << res->get_header_value("Content-Type") << endl;
    cout << res->body << endl;
  }

  for (int i = 0; i < 5; i++)
  {
    res = cli.Get(format("/numbers/%03d", i).c_str());
    if (res)
    {
      cout << res->status << endl;
      //cout << res->get_header_value("Content-Type") << endl;
      cout << res->body << endl;
    }
  }

  res = cli.Post("/singlebody", "abc", "text/plain");

  httplib::MultipartFormDataItems items = {
      {"text1", "text default", "", ""},
      {"text2", "aωb", "", ""},
      {"name1", "h\ne\n\nl\nl\no\n", "hello.txt", "text/plain"},
      {"file2", "{\n  \"world\", true\n}\n", "world.json", "application/json"},
      {"file3", "", "", "application/octet-stream"},
  };
  res = cli.Post("/multipart", items);

  cout << "/content_receiver" << endl;
  res = cli.Post("/content_receiver", "abc", "text/plainXXX");
  if (res)
  {
    cout << res->status << endl;
    //cout << res->get_header_value("Content-Type") << endl;
    cout << res->body << endl;
  }

  httplib::Params params;
  params.emplace("name", "john&tom");
  params.emplace("note", "coder");
  res = cli.Post("/content_receiver", params);
  if (res)
  {
    cout << res->status << endl;
    cout << res->get_header_value("Content-Type") << endl;
    cout << res->body << endl;
  }

  cout << "cli2" << endl;
  //httplib::Client cli2("https://www.google.com");
  //httplib::SSLClient cli2("https://repo.msys2.org");
  httplib::SSLClient cli2("repo.msys2.org", 443);
  cli2.set_default_headers({{"Accept-Encoding", "gzip, deflate"}});
  cli2.set_keep_alive(true);
  cli2.set_follow_location(true);
  cli2.set_compress(true);
  res = cli2.Get("/");
  if (res)
  {
    cout << res->status << endl;
    cout << res->get_header_value("Content-Type") << endl;
    cout << res->body << endl;
  }

  return 0;
}
