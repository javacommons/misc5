#lang racket

(require "ipc.rkt")

(define $pipe-server
  (new ::pipe-server%
       [$prefix "prefix"]
       ;[$client "racket.exe client.rkt"]
       [$client "json-cli.exe"]
       ;[$client "json-cliXXX.exe"]
       [$debug 1]))
;(send $pipe-server get-name)
(send $pipe-server get-hpipe)
(send $pipe-server call-api "name0" (hash 'a 18446744073709551615 'b 456.7))
(send $pipe-server dbg "debug メッセージ")
(send $pipe-server dbg '("abc" xyz "debug メッセージ"))

(send $pipe-server dbg "end-of-server")
