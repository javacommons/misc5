#lang racket

(require gregor)
(require ffi/unsafe
         ffi/unsafe/define)
(require msgpack)
(require net/base64)

(require "ipc.rkt")

(printf "Given arguments: ~s\n"
        (current-command-line-arguments))

(define $args (current-command-line-arguments))
(vector? $args)
(vector-ref $args 0)
(define $name (vector-ref $args 0))

(define $pipe-client (new ::pipe-client% [$name $name]))

(send $pipe-client receive)
(send $pipe-client return '("output3" 10 20 30))

(send $pipe-client receive)
(send $pipe-client return '("output4" 10 20 30))

(send $pipe-client dbg "end-of-client")
