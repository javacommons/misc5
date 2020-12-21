#ifndef JSON_IPC_H
#define JSON_IPC_H

#ifdef __cplusplus
extern "C"
{
#endif

struct json_ipc;

const char *ipc_find_endpont_from_args(int *debug);
json_ipc *ipc_open_client(const char *server, int debug);
const char *ipc_call_api(json_ipc *ipc, const char *api, const char *input);
typedef const char *(*ipc_handler)(const char *api, const char *input);
json_ipc *ipc_open_server(const char *endpoint, ipc_handler handler);

#ifdef __cplusplus
} // extern "C" {
#endif

#ifdef __cplusplus

#include <string>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

static inline json ipc_call_json_api(json_ipc *ipc, const std::string &api, const json &input)
{
    return json::parse(ipc_call_api(ipc, api.c_str(), input.dump().c_str()));
}

static inline std::string unsigned_to_string(unsigned long long n)
{
  return std::to_string(n);
}

static inline unsigned long long string_to_unsigned(const std::string &s)
{
  return std::stoull(s);
}

static inline std::string address_to_string(void *p)
{
  unsigned long long n = (unsigned long long)p;
  return std::to_string(n);
}

static inline void *string_to_address(const std::string &s)
{
  return (void *)std::stoull(s);
}

#endif // __cplusplus

#endif /* JSON_IPC_H */
