#lang racket

(define &my-name (make-parameter (void)))
(define &file-name1 (make-parameter (void)))
(define &file-name2 (make-parameter (void)))

;; command line parser
(define $parser
  (command-line
   #:usage-help
   "Have the computer greet you!"
   "Have the computer greet you!"

   #:once-each
   [("-n" "--name") NAME
                    "Set your name"
                    (&my-name NAME)]

   #:args (FILENAME1 FILENAME2)
   (&file-name1 FILENAME1)
   (&file-name2 FILENAME2)
   (void)
   ))

(define (get-greeting %mn)
  (cond
    [(void? %mn) "Hello, unknown person!"]
    [(string? %mn) (string-append "Hello, " %mn "!")]))

;; prints result to the command line
(printf "~a\n" (get-greeting (&my-name)))
(&my-name)
(&file-name1)
(&file-name2)
(printf "void is: ~s\n" (void))
(printf "void is: ~a\n" (void))
(if (void) 11 22)
(if '() 33 44)
