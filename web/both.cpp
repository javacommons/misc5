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

  svr.listen("127.0.0.1", 1234);
}

int main(void)
{

#if 0x1
  std::thread *th = new std::thread(worker);
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
#endif

  httplib::Client cli("127.0.0.1", 1234);

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

  return 0;
}
