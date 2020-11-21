#! racket32
#lang racket

(require "apiv1.rkt")

(define $pipe-client
  (new ::pipe-client%
       [$prefix "prefix"]
       ;[$client "racket.exe client.rkt"]
       [$client (format "json-svr-~abit.exe" (system-type 'word))]
       ;[$client "json-cliXXX.exe"]
       [$debug 1]))
;(send $pipe-server get-name)
(send $pipe-client get-hpipe)
(send $pipe-client call-api "name0" (hash 'a 18446744073709551615 'b 456.7))
(send $pipe-client dbg "debug メッセージ")
(send $pipe-client dbg '("abc" xyz "debug メッセージ"))

(send $pipe-client dbg "end-of-server")
