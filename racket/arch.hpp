#ifdef __cplusplus
extern "C"
{
#endif

  const char *apicall(const char *name, const char *base64_args);

#ifdef __cplusplus
} // extern "C" {
#endif

#ifdef __cplusplus

#include "msgpack11.hpp"
using namespace msgpack11;

#include "msgpack11_dump.hpp"

#include <iostream>

struct api1_input
{
  double a;
  double b;
  api1_input(const MsgPack &obj)
  {
    double a = obj["a"].float64_value();
    double b = obj["b"].float64_value();
    this->a = a;
    this->b = b;
  }
};
struct api1_output
{
  double sum;
  double diff;
  std::string ts;
  std::string pack()
  {
    MsgPack obj = MsgPack::object{
        {"sum", this->sum},
        {"diff", this->diff},
        {"ts", this->ts}};
    return obj.dump();
  }
};
api1_output api1(const api1_input &input);

double sum(const std::vector<double> &args);

#endif
