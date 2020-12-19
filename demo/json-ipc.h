#ifndef JSON_IPC_H
#define JSON_IPC_H

#ifdef __cplusplus
extern "C"
{
#endif

struct json_ipc;

int add2(int x, int y);

json_ipc *ipc_open_client(const char *server, int debug);

#ifdef __cplusplus
} // extern "C" {
#endif

#ifdef __cplusplus

#include <string>

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
