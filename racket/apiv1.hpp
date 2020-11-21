#ifndef APIV1_HPP
#define APIV1_HPP

#ifdef __cplusplus
extern "C"
{
#endif

  const void *make_client_pipe(const char *prefix,
                               const char *client,
                               int debug);
  const void *make_server_pipe(const char *name);
  const char *read_from_pipe(const void *hPipe);
  void write_to_pipe(const void *hPipe, const char *s);

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

#endif // APIV1_HPP
