#lang racket

(require zeromq)

(define requester (zmq-socket 'req #:connect "tcp://127.0.0.1:50862"))
(for ([request-number (in-range 3)])
  (zmq-send requester "Hello漢字")
  (define response (zmq-recv-string requester))
  (printf "Client received ~s (#~s)\n" response request-number))
