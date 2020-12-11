#include "httplib.h"
#include <iostream>

using namespace std;

int main(void)
{
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
  httplib::SSLClient cli("localhost", 1234);
#else
  httplib::Client cli("localhost", 1234);
#endif

  auto res = cli.Get("/hi");
  if (res) {
    cout << res->status << endl;
    cout << res->get_header_value("Content-Type") << endl;
    cout << res->body << endl;
  }

  return 0;
}