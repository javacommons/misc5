#lang racket

(require "arch-api.rkt")

(printf "Given arguments: ~s\n"
        (current-command-line-arguments))

(define api-input (hash "a" 11.11 "b" 22.22))
api-input

(arch-api "api1" api-input)
(println "bofore sum")
(arch-api "sum" '[11 99 33])
(println "after sum")
(arch-api* "sum" 1 2 33)
(arch-api* "none" 1 "abc" 33)
					;(arch-api "sum" "dummy")

(find-system-path 'run-file)

(define book-class%
  (class object%
    (field (pages 5))
    (define/public (letters)
      (* pages 500))
    (super-new)))

(define book (new book-class%))
book

(send book letters)

(define account%
  (class object%
	 (super-new)
	 (init-field balance)
	 (define/public (add n)
	   (new this% [balance (+ n balance)]))))
(define savings%
  (class account%
	 (super-new)
	 (inherit-field balance)
	 (define interest 0.04)
	 (define/public (add-interest)
	   (send this add (* interest balance)))))

(let* ([acct (new savings% [balance 500])]
       [acct (send acct add 500)]
       [acct (send acct add-interest)])
  (printf "Current balance: ~a\n" (get-field balance acct)))

(define acct (new account% [balance 1200]))
(get-field balance acct)

(define c1 (class object%
		  (super-new)
		  (init turnip
			[(internal-potato potato)]
			[carrot 'good]
			[(internal-rutabaga rutabaga) 'okay])))

(new c1 [turnip 123][potato 456])
