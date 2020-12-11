#define CPPHTTPLIB_ZLIB_SUPPORT
#include "httplib.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "strutil.h"

using namespace httplib;
using namespace std;

void worker()
{
  //std::this_thread::sleep_for(std::chrono::milliseconds(10));
  Server svr;
  svr.set_tcp_nodelay(true);

  svr.Get("/hi", [](const Request &req, Response &res) {
    res.set_content("Hello World!2", "text/plain");
  });

  svr.Get(R"(/numbers/(\d+))", [&](const Request &req, Response &res) {
    auto numbers = req.matches[1];
    res.set_content(numbers, "text/plain");
  });

  svr.Post("/content_receiver",
           [&](const Request &req, Response &res, const ContentReader &content_reader) {
             cout << "handle: /content_receiver" << endl;
             if (req.is_multipart_form_data())
             {
               cout << "if (req.is_multipart_form_data())" << endl;
               MultipartFormDataItems files;
               content_reader(
                   [&](const MultipartFormData &file) {
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
           [&](const Request &req, Response &res, const ContentReader &content_reader) {
             cout << "handle: /post" << endl;
             if (req.has_param("name"))
             {
               std::string val = req.get_param_value("name");
               cout << "handle: /post name=" << val << endl;
             }
           });
  svr.listen("127.0.0.1", 1234);
}

int main(void)
{

#if 0x1
  std::thread *th = new std::thread(worker);
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
#endif

  httplib::Client cli("127.0.0.1", 1234);
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

  cout << "/content_receiver" << endl;
  res = cli.Post("/content_receiver", "abc", "text/plainXXX");
  if (res)
  {
    cout << res->status << endl;
    //cout << res->get_header_value("Content-Type") << endl;
    cout << res->body << endl;
  }

  Params params;
  params.emplace("name", "john");
  params.emplace("note", "coder");
  res = cli.Post("/content_receiver", params);
  if (res)
  {
    cout << res->status << endl;
    //cout << res->get_header_value("Content-Type") << endl;
    cout << res->body << endl;
  }

  return 0;
}
