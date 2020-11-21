#! racket32
#lang racket

(require racket/gui)

(find-system-path 'run-file)


(define frame (new frame%
                   [label "Example"]
                   [width 800]
                   [height 600]
                   ))

(define list-box (new list-box%
                      (label "List Box")
                      (parent frame)
                      (choices (list "Item 0"
                                     "Item 1"
                                     "Item 2"))
                      (style (list 'single
                                   'column-headers))
                      (columns (list "First Column"))
                      [callback (lambda (button event)
                                  (println (send event get-event-type))
                                  (send msg set-label "Listbox click"))]
                      ))

(define msg (new message% [parent frame]
                 [label "No events so far..."]))

(define btn (new button% [parent frame]
                 [label "Click Me"]
                 [callback (lambda (button event)
                             (println (send event get-event-type))
                             (send msg set-label "Button click"))]))

(send frame show #t)
